/**
 * @file	readData.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

// Node
#include "node.h"
#include "material.h"
#include "mesh.h"
#include "light.h"
#include "vertex.h"
#include "shadow.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/packing.hpp>

// C++
#include <memory>
#include <cstring>
#include <vector>

/**
 * @class ReadData
 * @brief Singleton class for reading and parsing binary data into scene graph components.
 *
 * The ReadData class provides methods to deserialize binary data into nodes, materials, meshes,
 * lights, and vertices, allowing the reconstruction of a scene graph from serialized data.
 */
class ENG_API ReadData {
private:
    /**
     * @brief Private constructor for Singleton implementation.
     */
    ReadData() {}

    int lightId = -1; ///< Internal counter for assigning unique IDs to lights.

public:
    /**
     * @enum LightSubtype
     * @brief Enum representing subtypes of lights.
     */
    enum class LightSubtype : int {
        OMNI = 0,       ///< Omni-directional light.
        DIRECTIONAL,    ///< Directional light.
        SPOT,           ///< Spot light.
        LAST,           ///< Marker for the last light subtype.
    };

    /**
     * @brief Retrieves the singleton instance of ReadData.
     *
     * @return A reference to the singleton instance of ReadData.
     */
    static ReadData& getInstance() {
        static ReadData instance;
        return instance;
    }

    /**
     * @brief Reads a Node from binary data.
     *
     * @param data Pointer to the binary data.
     * @param position The current position in the binary data.
     * @return A pointer to the deserialized Node object.
     */
    Node* readNode(char* data, unsigned int position);

    /**
     * @brief Reads a Material from binary data.
     *
     * @param data Pointer to the binary data.
     * @param position The current position in the binary data.
     * @return A pointer to the deserialized Material object.
     */
    Material* readMaterial(char* data, unsigned int position);

    /**
     * @brief Reads a Mesh from binary data.
     *
     * @param data Pointer to the binary data.
     * @param position Reference to the current position in the binary data.
     * @param materials A vector of available materials for associating with the mesh.
     * @return A pointer to the deserialized Mesh object.
     */
    Mesh* readMesh(char* data, unsigned int& position, const std::vector<Material*>& materials);

    /**
     * @brief Reads a Light from binary data.
     *
     * @param data Pointer to the binary data.
     * @param position Reference to the current position in the binary data.
     * @return A pointer to the deserialized Light object.
     */
    Lighting::Light* readLight(char* data, unsigned int& position);

    std::vector<Vertex*> tempVertices; ///< Temporary storage for vertices during parsing.
};
