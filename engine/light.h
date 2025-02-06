/**
 * @file	light.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>
#include "node.h"

namespace Lighting {

    enum class ENG_API LightType {
        DIRECTIONAL,
        OMNI,
        SPOT
    };

    /**
     * @class Light
     * @brief Base class for all types of lights.
     */
    class ENG_API Light : public Node {
    public:

        Light(int id, const std::string& name, Node* parent, glm::mat4 localMatrix, LightType type,
            const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, float intensity);

        virtual ~Light();

        // Setters and Getters
        virtual void setPosition(const glm::vec4& position) {}
        virtual void setDirection(const glm::vec3& direction) {}
        virtual void setCutoff(float cutoff) {}
        virtual void setSpotExponent(float exponent) {}

        void setAttenuation(float constant, float linear, float quadratic);
        void setIntensity(float intensity);

        // Render method
        virtual void render(const glm::mat4& matrix) override;

        void toggle();

        // Getters
        LightType getType() const;
        glm::vec4 getAmbient() const;
        glm::vec4 getDiffuse() const;
        glm::vec4 getSpecular() const;

    protected:
        int lightNumber;
        LightType type;
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;

        bool isEnabled = true;
        float constantAttenuation;
        float linearAttenuation;
        float quadraticAttenuation;
        float intensity;
    };

    /**
     * @class DirectionalLight
     * @brief Represents a directional light.
     */
    class ENG_API DirectionalLight : public Light {
    public:
        DirectionalLight(int id, const std::string& name, Node* parent, glm::mat4 localMatrix,
            const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular,
            const glm::vec3& direction);

        void setDirection(const glm::vec3& direction) override;
        void render(const glm::mat4& transform) override;

    private:
        glm::vec3 direction;
    };

    /**
     * @class OmniLight
     * @brief Represents a point light (omni-directional).
     */
    class ENG_API OmniLight : public Light {
    public:
        OmniLight(int id, const std::string& name, Node* parent, glm::mat4 localMatrix,
            const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular);

        void render(const glm::mat4& transform) override;
    };

    /**
     * @class SpotLight
     * @brief Represents a spot light.
     */
    class ENG_API SpotLight : public Light {
    public:
        SpotLight(int id, const std::string& name, Node* parent, glm::mat4 localMatrix,
            const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular,
            const glm::vec3& direction, float cutoff, float exponent);

        void setDirection(const glm::vec3& direction) override;
        void setCutoff(float cutoff) override;
        void render(const glm::mat4& transform) override;

    private:
        glm::vec3 direction;
        float cutoff;
        float exponent;

    };
}
