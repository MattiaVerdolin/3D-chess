/**
 * @file	keyValueStack.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "lib.h"
#include <map>

/**
 * @class KeyValueStack
 * @brief A singleton class for managing a stack-like structure of key-value pairs.
 *
 * The KeyValueStack class is used to store and manage key-value pairs where the key is an integer
 * and the value represents the count of children to process. The class provides methods to push
 * new entries, check if the stack is empty, retrieve the first key, and decrement the value for a specific key.
 */
class ENG_API KeyValueStack {
private:
    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    KeyValueStack();

    /**
     * @brief Map to store key-value pairs.
     *
     * The key represents an identifier, and the value represents the associated count.
     */
    std::map<int, int> keyValueMap;

public:
    /**
     * @brief Retrieves the singleton instance of KeyValueStack.
     *
     * @return A reference to the singleton instance.
     */
    static KeyValueStack& getInstance();

    /**
     * @brief Adds a key-value pair to the stack.
     *
     * @param id The key to be added.
     * @param children_to_process The value associated with the key.
     */
    void push(const int& id, int children_to_process);

    /**
     * @brief Checks if the stack is empty.
     *
     * @return True if the stack is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Retrieves the first key in the stack.
     *
     * @return The first key as an integer.
     */
    int firstId() const;

    /**
     * @brief Decrements the value associated with a specific key.
     *
     * @param id The key whose value is to be decremented.
     * @return True if the value was decremented successfully, false if the key does not exist.
     */
    bool decrementValue(int id);
};
