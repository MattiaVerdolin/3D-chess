/**
 * @file	object.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "lib.h"

// GLM
#include <glm/glm.hpp>

// C++
#include <string>

/**
 * @class Object
 * @brief Base class for all objects in the engine.
 *
 * The Object class provides a foundation for all objects, including unique identification,
 * a name, and rendering capabilities.
 */
class ENG_API Object {
private:
    unsigned int id = 0; ///< Unique identifier for the object.
    std::string name = ""; ///< Name of the object.

public:
    /**
     * @brief Default constructor for Object.
     */
    Object() = default;

    /**
     * @brief Constructs an Object with the specified name.
     *
     * @param name The name of the object.
     */
    Object(std::string name);

    /**
     * @brief Virtual destructor for Object.
     */
    virtual ~Object() = default;

    /**
     * @brief Pure virtual method for rendering the object.
     *
     * This method must be implemented by derived classes to define their rendering behavior.
     *
     * @param finalMatrix The transformation matrix to apply during rendering.
     */
    virtual void render(const glm::mat4& finalMatrix) = 0;

    /**
     * @brief Generates unique IDs for objects.
     *
     * @return A unique unsigned integer ID.
     */
    static unsigned int idGenerator();

    // Getters and Setters

    /**
     * @brief Retrieves the unique ID of the object.
     *
     * @return The unique ID as an unsigned integer.
     */
    unsigned int getID() const;

    /**
     * @brief Sets the unique ID of the object.
     *
     * @param id The new unique ID.
     */
    void setID(unsigned int id);

    /**
     * @brief Retrieves the name of the object.
     *
     * @return The name of the object as a string.
     */
    std::string getName() const;

    /**
     * @brief Sets the name of the object.
     *
     * @param name The new name of the object.
     */
    void setName(std::string name);
};
