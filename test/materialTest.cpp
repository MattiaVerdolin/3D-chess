#include "materialTest.h"
#include <iostream>

// Colori ANSI
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// Test dei costruttori e dei getter
void testConstructorAndGetters() {
    glm::vec4 ambient(0.2f, 0.2f, 0.2f, 1.0f);
    glm::vec4 diffuse(0.8f, 0.8f, 0.8f, 1.0f);
    glm::vec4 specular(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 emissive(0.0f, 0.0f, 0.0f, 1.0f);
    float shininess = 32.0f;
    Texture* texture = nullptr;

    Material material(ambient, diffuse, specular, emissive, shininess, texture);

    if (material.getAmbientColor() == ambient) {
        std::cout << GREEN << "TEST PASSED: Ambient color is correct." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Ambient color is incorrect." << RESET << "\n";
    }

    if (material.getDiffuseColor() == diffuse) {
        std::cout << GREEN << "TEST PASSED: Diffuse color is correct." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Diffuse color is incorrect." << RESET << "\n";
    }

    if (material.getSpecularColor() == specular) {
        std::cout << GREEN << "TEST PASSED: Specular color is correct." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Specular color is incorrect." << RESET << "\n";
    }

    if (material.getEmissiveColor() == emissive) {
        std::cout << GREEN << "TEST PASSED: Emissive color is correct." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Emissive color is incorrect." << RESET << "\n";
    }

    if (material.getShininess() == shininess) {
        std::cout << GREEN << "TEST PASSED: Shininess is correct." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Shininess is incorrect." << RESET << "\n";
    }

    if (material.getTexture() == texture) {
        std::cout << GREEN << "TEST PASSED: Texture is correct." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Texture is incorrect." << RESET << "\n";
    }
}

// Test dei setter
void testSetters() {
    Material material(glm::vec4(0), glm::vec4(0), glm::vec4(0), glm::vec4(0), 0.0f, nullptr);

    glm::vec4 newAmbient(0.3f, 0.3f, 0.3f, 1.0f);
    glm::vec4 newDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
    glm::vec4 newSpecular(0.7f, 0.7f, 0.7f, 1.0f);
    glm::vec4 newEmissive(0.1f, 0.1f, 0.1f, 1.0f);
    float newShininess = 16.0f;

    material.setAmbientColor(newAmbient);
    material.setDiffuseColor(newDiffuse);
    material.setSpecularColor(newSpecular);
    material.setEmissiveColor(newEmissive);
    material.setShininess(newShininess);

    if (material.getAmbientColor() == newAmbient) {
        std::cout << GREEN << "TEST PASSED: Ambient color set correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Ambient color not set correctly." << RESET << "\n";
    }

    if (material.getDiffuseColor() == newDiffuse) {
        std::cout << GREEN << "TEST PASSED: Diffuse color set correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Diffuse color not set correctly." << RESET << "\n";
    }

    if (material.getSpecularColor() == newSpecular) {
        std::cout << GREEN << "TEST PASSED: Specular color set correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Specular color not set correctly." << RESET << "\n";
    }

    if (material.getEmissiveColor() == newEmissive) {
        std::cout << GREEN << "TEST PASSED: Emissive color set correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Emissive color not set correctly." << RESET << "\n";
    }

    if (material.getShininess() == newShininess) {
        std::cout << GREEN << "TEST PASSED: Shininess set correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Shininess not set correctly." << RESET << "\n";
    }
}

// Test del metodo render senza texture
void testRenderWithoutTexture() {
    Material material(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
        glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        32.0f, nullptr);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    material.render(modelMatrix); // Renderizza il materiale senza texture.

    // Verifica che la texture sia nulla
    if (material.getTexture() == nullptr) {
        std::cout << GREEN << "TEST PASSED: Render without texture." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Expected no texture, but found one." << RESET << "\n";
    }
}

// Test del metodo render con texture
void testRenderWithTexture() {
    Texture texture("example_texture.png");
    Material material(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
        glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        32.0f, &texture);  // Passiamo una texture valida

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    material.render(modelMatrix); // Renderizza il materiale con la texture.

    // Verifica che la texture sia correttamente associata
    if (material.getTexture() != nullptr) {
        std::cout << GREEN << "TEST PASSED: Render with texture." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Expected texture, but found none." << RESET << "\n";
    }
}
