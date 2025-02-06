/**
 * @file	ovoReader.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

// GLM (OpenGL Mathematics)
#include <glm/glm.hpp>
#include <glm/gtc/packing.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C++ Standard Library
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>

// Main Imports
#include "readData.h"
#include "object.h"
#include "material.h"
#include "node.h"
#include "mesh.h"
#include "light.h"
#include "keyValueStack.h"
#include "readData.h"

/**
 * @class OvoReader
 * @brief Singleton class for reading and parsing OVO scene files.
 *
 * The OvoReader class is responsible for creating scene graphs from OVO files, managing nodes, materials,
 * and interacting with the KeyValueStack and ReadData singleton instances.
 */
class ENG_API OvoReader {
private:
    std::vector<Material*> materials; ///< List of materials in the scene.
    std::vector<Node*> nodes; ///< List of nodes in the scene graph.
    KeyValueStack& kvStack; ///< Reference to the KeyValueStack singleton instance.
    ReadData& dataReader; ///< Reference to the ReadData singleton instance.

    /**
     * @brief Private constructor for implementing the singleton pattern.
     *
     * Initializes references to KeyValueStack and ReadData singletons.
     */
    OvoReader()
        : dataReader(ReadData::getInstance()),
        kvStack(KeyValueStack::getInstance())
    {
    }

    /**
     * @brief Creates the scene graph from a given node.
     *
     * @param node The root node of the scene graph.
     */
    void graph_creator(Node* node);

    /**
     * @brief Extracts the file path from a full file path.
     *
     * @param fullPath The full file path.
     * @return The extracted file path as a string.
     */
    std::string extractPath(const std::string& fullPath);

public:
    /**
     * @brief Retrieves the singleton instance of OvoReader.
     *
     * @return A reference to the singleton OvoReader instance.
     */
    static OvoReader& getInstance() {
        static OvoReader instance;
        return instance;
    }

    /**
     * @brief Reads and parses an OVO file to create a scene graph.
     *
     * @param paramFile The path to the OVO file.
     * @return A pointer to the root node of the created scene graph.
     */
    Node* reader(const std::string& paramFile);

    /**
     * @enum Type
     * @brief Enum representing different types of objects in the OVO file.
     */
    enum class Type : int {
        OBJECT = 0, ///< Generic object.
        NODE, ///< Scene graph node.
        OBJECT2D, ///< 2D object.
        OBJECT3D, ///< 3D object.
        LIST, ///< List object.
        BUFFER, ///< Buffer object.
        SHADER, ///< Shader object.
        TEXTURE, ///< Texture object.
        FILTER, ///< Filter object.
        MATERIAL, ///< Material object.
        FBO, ///< Framebuffer object.
        QUAD, ///< Quad geometry.
        BOX, ///< Box geometry.
        SKYBOX, ///< Skybox object.
        FONT, ///< Font object.
        CAMERA, ///< Camera object.
        LIGHT, ///< Light object.
        BONE, ///< Bone object.
        MESH, ///< Mesh object.
        SKINNED, ///< Skinned mesh object.
        INSTANCED, ///< Instanced object.
        PIPELINE, ///< Pipeline object.
        EMITTER, ///< Particle emitter.
        ANIM, ///< Animation object.
        PHYSICS, ///< Physics object.
        LAST ///< Marker for the last type.
    };
};
