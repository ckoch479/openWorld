#pragma once

#include <iostream>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"
#include <glm/gtx/string_cast.hpp>

#include "item.h"
#include "Model.h"

class itemSlot
{
public:

	itemSlot() : storedItem(nullptr) {}

    bool isEmpty() const {
        return storedItem == nullptr;
    }

    void storeItem(item* item) {
        storedItem = item;
    }

    void removeItem() {
        storedItem = nullptr;
    }

    item* getItem() const {
        return storedItem;
    }
private:

	item* storedItem;
};

