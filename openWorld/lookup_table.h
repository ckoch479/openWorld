#pragma once

#include <iostream>
#include <vector>
#include <map>

struct ID
{
	unsigned int index; //index into the table
	unsigned int inner_id; //used to verify the object is still in the table
};

//simple lookup table with object ids
template <typename T> class lookup_table
{
	struct allocation //this struct allows us to attach the id and the next object to the given data type
	{
		ID id; 
		unsigned int next;
		T t;
	};

	unsigned int next_inner_id; //next available inner id, should start at 0
	std::vector <allocation> objects;
	unsigned int freeList; //next free spot in the table

	allocation& internal_lookup(ID id) //internal lookup for the data table that returns an allocation object and not the actual data
	{
		return objects[id.index];
	}

public:
	lookup_table()
	{
		next_inner_id = 0;
		freeList = UINT_MAX;
	}

	bool has(ID check_id)
	{
		return objects[check_id.index].id.inner_id == check_id.inner_id;
	}

	//return the object with this ID
	T& lookup(ID id)
	{
		return objects[id.index].t;
	}

	ID add(T& t) 
	{
		ID id;
		id.inner_id = next_inner_id++;
		if(freeList == UINT_MAX) //this checks to see if the current table has any open holes, the table will not move data however will fill holes before continuing
		{
			allocation o;
			id.index = objects.size();
			o.id = id;
			o.t = t;
			objects.push_back(o);
		}

		else //if the freelist variable is not equal to unit_max then the newly created object is placed in the open hole
		{
			id.index = freeList;
			freeList = objects[freeList].next;
		}
		return id;
	}

	unsigned int size()
	{
		return objects.size();
	}

	void remove(ID id) //remove the object referenced by the id and mark its hole as open for use
	{
		allocation& o = internal_lookup(id);
		o.id.inner_id = UINT_MAX;
		o.next = freeList;
		freeList = id.index;
	}


};

