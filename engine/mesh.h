/**
 * @file	mesh.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "node.h"
#include "material.h"
#include "vertex.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Forward declaration della classe Shadow
class Shadow;

/**
 * @class Mesh
 * @brief Represents a 3D mesh in the scene graph.
 *
 * The Mesh class extends the Node class and contains a set of vertices, a material, and rendering properties.
 */
class ENG_API Mesh : public Node {
private:
    Material* material = nullptr; ///< Pointer to the material associated with the mesh.
    std::vector<std::vector<Vertex*>> vertices; ///< 2D vector of pointers to vertices organized by Level of Detail (LOD).
    int lod = 0; ///< Current Level of Detail (LOD) for the mesh.

public:
    /**
     * @brief Constructs a Mesh object with the specified properties.
     *
     * @param name Name of the mesh.
     * @param parent Parent node in the scene graph.
     * @param localMatrix Local transformation matrix for the mesh.
     * @param material Pointer to the material associated with the mesh.
     */
    Mesh(const std::string& name, Node* parent, glm::mat4 localMatrix, Material* material);

    /**
     * @brief Default constructor for Mesh.
     */
    Mesh() = default;

    /**
     * @brief Renders the mesh using the specified transformation matrix.
     *
     * @param finalMatrix The final transformation matrix to apply to the mesh.
     */
    void render(const glm::mat4& finalMatrix) override;

    /**
     * @brief Sets the material for the mesh.
     *
     * @param material Pointer to the new material to associate with the mesh.
     */
    void setMaterial(Material* material);

    /**
     * @brief Retrieves the material associated with the mesh.
     *
     * @return Pointer to the Material object.
     */
    Material* getMaterial() const;

    /**
     * @brief Adds a vertex to the mesh at the specified Level of Detail (LOD).
     *
     * @param v Pointer to the Vertex to add.
     * @param lod The Level of Detail index where the vertex should be added.
     */
    void addVertex(Vertex* v, int lod);

    /**
     * @brief Retrieves the vertices of the mesh at the specified Level of Detail (LOD).
     *
     * @param lod The Level of Detail index to retrieve vertices from.
     * @return A vector of pointers to Vertex objects.
     */
    std::vector<Vertex*> getVertices(int lod) const;

    void translation(glm::vec3 translation);

    /**
    * @brief Sets whether the mesh should be rendered.
    *
    * @param cond True to enable rendering, false to disable it.
    */
    void setRender(bool cond);

};
