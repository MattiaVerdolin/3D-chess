/**
 * @file	vertex.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "lib.h"

#include <glm/glm.hpp>

/**
 * @class Vertex
 * @brief Represents a vertex in a 3D space with position, normal, and texture coordinates.
 *
 * The Vertex class provides functionality to manage vertex properties such as position, normal,
 * and texture coordinates, commonly used in 3D rendering.
 */
class ENG_API Vertex {

private:
    glm::vec3 position = {}; ///< The position of the vertex in 3D space.
    glm::vec3 normal = {}; ///< The normal vector at the vertex.
    glm::vec2 textureCoordinates = {}; ///< The texture coordinates of the vertex.

public:
    /**
     * @brief Constructs a Vertex object with the specified position and normal.
     *
     * @param position The position of the vertex in 3D space.
     * @param normal The normal vector at the vertex.
     */
    Vertex(glm::vec3 position, glm::vec3 normal);

    /**
     * @brief Destructor for the Vertex class.
     */
    ~Vertex();

    /**
     * @brief Retrieves the position of the vertex.
     *
     * @return The position of the vertex as a glm::vec3.
     */
    glm::vec3 getPosition() const;

    /**
     * @brief Retrieves the normal vector of the vertex.
     *
     * @return The normal vector of the vertex as a glm::vec3.
     */
    glm::vec3 getNormal();

    /**
     * @brief Retrieves the texture coordinates of the vertex.
     *
     * @return The texture coordinates of the vertex as a glm::vec2.
     */
    glm::vec2 getTextureCoordinates();

    /**
     * @brief Sets the texture coordinates for the vertex.
     *
     * @param textCoord The new texture coordinates as a glm::vec2.
     */
    void setTextureCoordinates(glm::vec2 textCoord);
};
