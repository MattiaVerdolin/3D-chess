#include "object.h"


Object::Object(std::string name)
    : name{ name } {
    id = idGenerator();
}

unsigned int Object::getID() const {
    return id;
}

void Object::setID(unsigned int newID) {
    id = newID;
}

std::string Object::getName() const {
    return name;
}

void Object::setName(std::string setName) {
    name = setName;
}

unsigned int Object::idGenerator() {
    static unsigned int counter = 0;
    return ++counter; // Increment before returning
}
