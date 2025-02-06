/**
 * @file	material.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "object.h"
#include "texture.h"

// GLM
#include <glm/glm.hpp>

/**
 * @class Material
 * @brief Represents a material in a 3D graphics engine.
 *
 * The Material class defines the visual properties of a surface, including color, shininess, and texture.
 */
class ENG_API Material : public Object {

private:
    glm::vec4 ambientColor{ 0.2f, 0.2f, 0.2f, 1.0f };  ///< Ambient color (RGBA).
    glm::vec4 diffuseColor{ 0.8f, 0.8f, 0.8f, 1.0f };  ///< Diffuse color (RGBA).
    glm::vec4 specularColor{ 1.0f, 1.0f, 1.0f, 1.0f }; ///< Specular color (RGBA).
    glm::vec4 emissiveColor{ 0.0f, 0.0f, 0.0f, 1.0f }; ///< Emissive color (RGBA).
    float shininess{ 32.0f };                          ///< Shininess exponent.
    Texture* texture{ nullptr };                       ///< Pointer to the texture.

public:
    /**
     * @brief Constructs a Material with specified properties.
     *
     * @param ambient The ambient color of the material (RGBA).
     * @param diffuse The diffuse color of the material (RGBA).
     * @param specular The specular color of the material (RGBA).
     * @param emissive The emissive color of the material (RGBA).
     * @param shininessVal The shininess exponent.
     * @param tex A pointer to the texture.
     */
    Material(
        const glm::vec4& ambient,
        const glm::vec4& diffuse,
        const glm::vec4& specular,
        const glm::vec4& emissive,
        float shininessVal,
        Texture* tex
    );

    /**
     * @brief Default constructor for Material.
     */
    Material() = default;

    /**
     * @brief Applies the material properties.
     *
     * @param finalMatrix The final transformation matrix.
     */
    void render(const glm::mat4& finalMatrix) override;

    /**
     * @brief Retrieves the texture associated with the material.
     *
     * @return A pointer to the Texture object.
     */
    Texture* getTex() const;

    // Getter and Setter for ambientColor

    /**
     * @brief Retrieves the ambient color of the material.
     *
     * @return The ambient color as a glm::vec4.
     */
    const glm::vec4& getAmbientColor() const;

    /**
     * @brief Sets the ambient color of the material.
     *
     * @param color The new ambient color (RGBA).
     */
    void setAmbientColor(const glm::vec4& color);

    // Getter and Setter for diffuseColor

    /**
     * @brief Retrieves the diffuse color of the material.
     *
     * @return The diffuse color as a glm::vec4.
     */
    const glm::vec4& getDiffuseColor() const;

    /**
     * @brief Sets the diffuse color of the material.
     *
     * @param color The new diffuse color (RGBA).
     */
    void setDiffuseColor(const glm::vec4& color);

    // Getter and Setter for specularColor

    /**
     * @brief Retrieves the specular color of the material.
     *
     * @return The specular color as a glm::vec4.
     */
    const glm::vec4& getSpecularColor() const;

    /**
     * @brief Sets the specular color of the material.
     *
     * @param color The new specular color (RGBA).
     */
    void setSpecularColor(const glm::vec4& color);

    // Getter and Setter for emissiveColor

    /**
     * @brief Retrieves the emissive color of the material.
     *
     * @return The emissive color as a glm::vec4.
     */
    const glm::vec4& getEmissiveColor() const;

    /**
     * @brief Sets the emissive color of the material.
     *
     * @param color The new emissive color (RGBA).
     */
    void setEmissiveColor(const glm::vec4& color);

    // Getter and Setter for shininess

    /**
     * @brief Retrieves the shininess exponent of the material.
     *
     * @return The shininess exponent as a float.
     */
    float getShininess() const;

    /**
     * @brief Sets the shininess exponent of the material.
     *
     * @param shininessVal The new shininess exponent.
     */
    void setShininess(float shininessVal);

    // Getter and Setter for texture

    /**
     * @brief Retrieves the texture associated with the material.
     *
     * @return A pointer to the Texture object.
     */
    Texture* getTexture() const;

    /**
     * @brief Sets the texture associated with the material.
     *
     * @param tex A pointer to the new Texture object.
     */
    void setTexture(Texture* tex);

};
