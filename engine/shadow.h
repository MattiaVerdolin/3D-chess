/**
 * @file	shadow.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "lib.h"
#include "mesh.h"
#include "node.h"
#include "vertex.h"

/**
 * @class Shadow
 * @brief Represents a shadow in the scene graph.
 *
 * The Shadow class extends the Node class and is responsible for managing shadow-specific data and rendering.
 */
class ENG_API Shadow : public Node {

public:
    /**
     * @brief Constructs a Shadow object for the given Mesh.
     *
     * @param mesh A pointer to the Mesh object to shadow.
     */
    Shadow(Mesh* mesh);

    /**
     * @brief Destructor for the Shadow class.
     */
    ~Shadow();

    /**
     * @brief Renders the shadow using the given transformation matrix.
     *
     * @param finalMatrix The transformation matrix to apply during rendering.
     */
    void render(const glm::mat4& finalMatrix) override;

    /**
     * @brief Retrieves the deepest point of the shadow.
     *
     * @return The deepest point as a float value.
     */
    float getDeepestPoint();

private:
    Mesh* meshToShadow; ///< Pointer to the Mesh object this shadow is associated with.
    std::vector<Vertex*> vertices; ///< List of vertices defining the shadow.
};
