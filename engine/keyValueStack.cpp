#include "keyValueStack.h"
#include <stdexcept>
#include <iostream>

KeyValueStack::KeyValueStack() {
    keyValueMap.clear();
}

KeyValueStack& KeyValueStack::getInstance() {
    static KeyValueStack instance;
    return instance;
}

void KeyValueStack::push(const int& key, int value) {
    if (value > 0) {
        keyValueMap[key] = value; // Insert or update the key-value pair
    }
}

bool KeyValueStack::empty() const {
    return keyValueMap.empty();
}

int KeyValueStack::firstId() const {
    if (!keyValueMap.empty()) {
        return keyValueMap.begin()->first; // Return the first key in the map
    }
    return -1; // Return -1 if the map is empty
}

bool KeyValueStack::decrementValue(int id) {
    auto it = keyValueMap.find(id);
    if (it != keyValueMap.end()) {
        it->second--; // Decrement the value
        if (it->second <= 0) {
            keyValueMap.erase(it); // Remove the key if the value reaches 0
        }
        return true;
    }
    return false; // Key not found
}
