/**
 * @file	texture.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "object.h"
#include <string>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT        0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT    0x84FF

/**
 * @class Texture
 * @brief Represents a texture in the graphics engine.
 *
 * The Texture class provides functionality to create, manage, and render textures.
 */
class ENG_API Texture : public Object {

public:
    /**
     * @brief Constructs a Texture object with the specified name.
     *
     * @param name The name of the texture.
     */
    Texture(std::string name);

    /**
     * @brief Destructor for the Texture class.
     */
    ~Texture();

    /**
     * @brief Creates a texture from the specified file path.
     *
     * @param path The file path to the texture image.
     */
    void createTexture(std::string path);

    /**
     * @brief Renders the texture using the specified transformation matrix.
     *
     * @param finalMatrix The transformation matrix to apply during rendering.
     */
    void render(const glm::mat4& finalMatrix);

    /**
     * @brief Releases the resources associated with the texture.
     */
    void release();

    /**
     * @brief Retrieves the name of the texture.
     *
     * @return The name of the texture as a string.
     */
    std::string getName() const;

    /**
     * @brief Sets the name of the texture.
     *
     * @param n The new name for the texture.
     */
    void setName(std::string& n);

private:
    unsigned int texID = 0; ///< OpenGL texture ID.
    std::string name; ///< Name of the texture.
};
