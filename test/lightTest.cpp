#include "light.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lightTest.h"

using namespace Lighting;

// Colori ANSI per il feedback
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

void testLightBaseClass() {
    std::cout << "Testing Light Base Class:\n";

    glm::vec4 ambient(0.1f, 0.1f, 0.1f, 1.0f);
    glm::vec4 diffuse(0.5f, 0.5f, 0.5f, 1.0f);
    glm::vec4 specular(1.0f, 1.0f, 1.0f, 1.0f);
    glm::mat4 matrix = glm::mat4(1.0f);

    Light light(0, "BaseLight", nullptr, matrix, LightType::OMNI, ambient, diffuse, specular, 1.0f);

    if (light.getAmbient() == ambient) {
        std::cout << GREEN << "TEST PASSED: Ambient color correctly initialized." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Ambient color not initialized correctly." << RESET << "\n";
    }

    if (light.getDiffuse() == diffuse) {
        std::cout << GREEN << "TEST PASSED: Diffuse color correctly initialized." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Diffuse color not initialized correctly." << RESET << "\n";
    }

    if (light.getSpecular() == specular) {
        std::cout << GREEN << "TEST PASSED: Specular color correctly initialized." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Specular color not initialized correctly." << RESET << "\n";
    }
}

void testDirectionalLight() {
    std::cout << "Testing Directional Light:\n";

    glm::vec4 ambient(0.1f, 0.1f, 0.1f, 1.0f);
    glm::vec4 diffuse(0.6f, 0.6f, 0.6f, 1.0f);
    glm::vec4 specular(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 direction(1.0f, -1.0f, 0.0f);
    glm::mat4 matrix = glm::mat4(1.0f);

    DirectionalLight dirLight(1, "DirectionalLight", nullptr, matrix, ambient, diffuse, specular, direction);

    dirLight.setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
    if (dirLight.getType() == LightType::DIRECTIONAL) {
        std::cout << GREEN << "TEST PASSED: Directional light type correctly set." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Directional light type not set correctly." << RESET << "\n";
    }
}

void testOmniLight() {
    std::cout << "Testing Omni Light:\n";

    glm::vec4 ambient(0.2f, 0.2f, 0.2f, 1.0f);
    glm::vec4 diffuse(0.7f, 0.7f, 0.7f, 1.0f);
    glm::vec4 specular(1.0f, 1.0f, 1.0f, 1.0f);
    glm::mat4 matrix = glm::mat4(1.0f);

    OmniLight omniLight(2, "OmniLight", nullptr, matrix, ambient, diffuse, specular);

    if (omniLight.getType() == LightType::OMNI) {
        std::cout << GREEN << "TEST PASSED: Omni light type correctly set." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Omni light type not set correctly." << RESET << "\n";
    }
}

void testSpotLight() {
    std::cout << "Testing Spot Light:\n";

    glm::vec4 ambient(0.2f, 0.2f, 0.2f, 1.0f);
    glm::vec4 diffuse(0.8f, 0.8f, 0.8f, 1.0f);
    glm::vec4 specular(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 direction(0.0f, -1.0f, 0.0f);
    glm::mat4 matrix = glm::mat4(1.0f);

    SpotLight spotLight(3, "SpotLight", nullptr, matrix, ambient, diffuse, specular, direction, 45.0f, 2.0f);

    spotLight.setCutoff(30.0f);
    spotLight.setDirection(glm::vec3(0.0f, -1.0f, 1.0f));

    if (spotLight.getType() == LightType::SPOT) {
        std::cout << GREEN << "TEST PASSED: Spot light type correctly set." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Spot light type not set correctly." << RESET << "\n";
    }
}


