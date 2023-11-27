#include <iostream>
#include <vector>
#include <map>

#include <cstdint>
#include <cassert>
#include <utility>

#pragma once

template <typename T> class packed_freelist
{
	//used to extract the allocation index from an object id
	static const uint16_t allocation_index_mask = 0xffff;

	//used to mark an allocation as owning no object
	static const uint16_t tombstone = 0x0ffff;

	struct allocation_t
	{
		//Id of this allocation
		//16 LSBs store the index of this allocation in the list of allocations
		//16 MSBs store the number of time this allocation struct was used to allocate an object
		//this is a non perfect counter measure to reusing IDs for objects
		uint32_t allocation_id;

		//the index in the objects array which stores the allocated object for this allocation
		uint16_t object_index;

		//the index in the allocations array for the next allocation to be allocated after this one (linked list tail)
		uint16_t next_allocation;
	};

	//storage for the objects
	size_t num_objects;
	size_t max_objects;
	size_t cap_objects;
	T* objects;

	//the allocation ID of each object in the object array
	uint32_t* object_allocation_ids;

	//FIFO queue to allocate objects with least ID reuse possible
	allocation_t* allocations;

	// when an allocation is freed, the enqueue index struct's next will point to it
	// this ensures that allocations are reused as infrequently as possible,
	// which reduces the likelihood that two objects have the same ID.
	// note objects are still not guaranteed to have globally unique IDs, since IDs will be reused after N * 2^16 allocations
	uint16_t last_allocation;

	//the next index struct to use for an allocation
	uint16_t next_allocation;

public:
	struct iterator
	{
		iterator(uint32_t* in)
		{
			current_object_allocation_id = in;
		}

		iterator& operator++()
		{
			current_object_allocation_id++;
			return *this;
		}

		uint32_t operator*()
		{
			return *current_object_allocation_id;
		}

		bool operator!=(const iterator& other) const
		{
			return current_object_allocation_id != other.current_object_allocation_id;
		}

	private:
		uint32_t* current_object_allocation_id;
	};

	packed_freelist()
	{
		num_objects = 0;
		max_objects = 0;
		cap_objects = 0;
		objects = nullptr;
		object_allocation_ids = nullptr;
		allocations = nullptr;
		last_allocation = -1;
		next_allocation = -1;
	}

	packed_freelist(size_t max_objects)
	{
		//-1 because index 0xffff is reserved as a tombstone
		assert(max_objects < 0x10000 - 1);

		num_objects = 0;
		this->max_objects = max_objects;
		cap_objects = max_objects;

		objects = (T*)new char[max_objects * sizeof(T)];
		assert(objects);

		object_allocation_ids = (uint32_t*)new uint32_t[max_objects];
		assert(object_allocation_ids);

		allocations = new allocation_t[max_objects];
		assert(allocations);

		for (size_t i = 0; i < max_objects; i++)
		{
			allocations->allocation_id = (uint32_t)i;
			allocations->object_index = tombstone;
			allocations->next_allocation = (uint16_t)(i + 1);
		}

		if (max_objects > 0)
		{
			allocations[max_objects - 1].next_allocation = 0;
		}

		last_allocation = (uint16_t)(max_objects - 1);
		next_allocation = 0;
	}

	~packed_freelist()
	{
		for(size_t i = 0; i < num_objects; i++)
		{
			objects[i].~T();
		}

		delete[]((char*)objects);
		delete[]object_allocation_ids;
		delete[] allocations;
	}

	packed_freelist(const packed_freelist& other)
	{
		num_objects = other.num_objects;
		max_objects = other.max_objects;
		cap_objects = other.cap_objects;

		objects = (T*)new char[other.max_objects * sizeof(T)];
		assert(objects);

		object_allocation_ids = new uint32_t[other.max_objects];
		assert(object_allocation_ids);

		allocations = new allocation_t[other.max_objects];
		assert(allocations);

		for(size_t i = 0; i < other.num_objects; i++)
		{
			new(objects + i) T(*(other.objects + i));
			object_allocation_ids[i] = other.object_allocation_ids[i];
		}

		for(size_t i = 0; i < other.max_objects; i++)
		{
			allocations[i] = other.allocations[i];
		}

		last_allocation = other.last_allocation;
		next_allocation = other.next_allocation;
	}

	packed_freelist& operator=(const packed_freelist& other)
	{
		if (this != &other)
		{

			if(cap_objects < other.max_objects)
			{
				this->~packed_freelist();
				new(this) packed_freelist(other);
			}
			else
			{
				for (size_t i = 0; i < other.num_objects; i++)
				{
					if (i < num_objects)
					{
						*(objects + i) = *(other.objects + i);
					}
					else
					{
						new(objects + i) T(*(other.objects + i));
					}
					object_allocation_ids[i] = other.object_allocation_ids[i];
				}

				for (size_t i = 0; i < other.max_objects; i++)
				{
					allocations[i] = other.allocations[i];
				}

				num_objects = other.num_objects;
				max_objects = other.max_objects;
				last_allocation = other.last_allocation;
				next_allocation = other.last_allocation;
			}
		}
		return *this;
	}

	void swap(packed_freelist& other)
	{
		using std::swap;
		swap(num_objects, other.num_objects);
		swap(max_objects, other.max_objects);
		swap(cap_objects, other.cap_objects);
		swap(objects, other.objects);
		swap(object_allocation_ids, other.object_allocation_ids);
		swap(allocations, other.allocations);
		swap(last_allocation, other.last_allocation);
		swap(next_allocation, other.next_allocation);
	}

	packed_freelist(packed_freelist&& other)
		: packed_freelist()
	{
		swap(other);
	}

	packed_freelist& operator=(packed_freelist&& other)
	{
		if (this != &other)
		{
			swap(other);
		}
		return *this;
	}

	bool contains(uint32_t id) const
	{
		//grab the allocation by grabbing the allocation index from the id's LSBs
		allocation_t* alloc = &allocations[id & allocation_index_mask];

		// NON-conservative test that the IDs match (if the allocation has been reused 2^16 times, it'll loop over)
		// Also check that the object is hasn't already been deallocated.
		// This'll prevent an object that was just freed from appearing to be contained, but still doesn't disambiguate between two objects with the same ID (see first bullet point)
		return alloc->allocation_id == id && alloc->object_index != tombstone;
	}

	T& operator[](uint32_t id) const
	{
		//grab the allocation corresponding to this ID
		allocation_t* alloc = &allocations[id & allocation_index_mask];

		//grab the object associated with the allocation
		return *(objects + (alloc->object_index));
	}

	uint32_t insert(const T& val)
	{
		allocation_t* alloc = insert_alloc();
		T* o = objects + alloc->object_index;
		new(o) T(val);
		return alloc->allocation_id;
	}

	uint32_t insert(T&& val)
	{
		allocation_t* alloc = insert_alloc();
		T* o = objects + alloc->object_index;
		new(o) T(std::move(val));
		return alloc->allocation_id;
	}

	template<class... Args>
	uint32_t emplace(Args&&... args)
	{
		allocation_t* alloc = insert_alloc();
		T* o = objects + alloc->object_index;
		new(o) T(std::forward<Args>(args)...);
		return alloc->allocation_id;
	}

	void erase(uint32_t id)
	{
		assert(contains(id));

		//grab location to delete
		allocation_t* alloc = &allocations[id & allocation_index_mask];

		//grab the object for this allocation
		T* o = objects + alloc->object_index;

		//if necessary, move (aka swap) the last object into the location of the object to erase, then unconditionally delete the last object
		if(alloc->object_index != num_objects - 1)
		{
			T* last = objects + num_objects - 1;
			*o = std::move(*last);
			o = last;

			//since the last object was moved into the deleted location, the associated object ID array's value must also be moved similarly
			object_allocation_ids[alloc->object_index] = object_allocation_ids[num_objects - 1];

			//since the last object has changed location, its allocation needs to be updated to the new location
			allocations[object_allocation_ids[alloc->object_index] & allocation_index_mask].object_index = alloc->object_index;
		}

		//destroy the removed object and pop it from the array
		o->~T();
		num_objects = num_objects - 1;

		//push the deleted allocation onto the FIFO
		allocations[last_allocation].next_allocation = alloc->allocation_id & allocation_index_mask;
		last_allocation = alloc->allocation_id & allocation_index_mask;

		//put a tombstone where the allocation used to point to an object index
		alloc->object_index = tombstone;
	}

	iterator begin() const
	{
		return iterator{ object_allocation_ids };
	}

	iterator end() const
	{
		return iterator{ object_allocation_ids + num_objects };
	}

	bool empty() const
	{
		return num_objects == 0;
	}

	size_t size() const
	{
		return num_objects;
	}

	size_t capacity() const
	{
		return max_objects;
	}

	private:
		allocation_t* insert_alloc()
		{
			assert(num_objects < max_objects);

			//pop an allocation from the FIFO
			allocation_t* alloc = &allocations[next_allocation];
			next_allocation = alloc->next_allocation;

			//increment the allocation count in the 16 MSBs without modifying the allocation's index (in the 16 LSBs)
			alloc->allocation_id += 0x10000;

			//always allocate the object at the end of the storage
			alloc->object_index = (uint16_t)num_objects;
			num_objects = num_objects + 1;

			//update reverse-lookup so objects can know their ID
			object_allocation_ids[alloc->object_index] = alloc->allocation_id;

			return alloc;
		}
};

template<class T>
typename packed_freelist<T>::iterator begin(const packed_freelist<T>& fl)
{
	return fl.begin();
}

template<class T>
typename packed_freelist<T>::iterator end(const packed_freelist<T>& fl)
{
	return fl.end();
}

template<class T>
void swap(packed_freelist<T>& a, packed_freelist<T>& b)
{
	a.swap(b);
}

