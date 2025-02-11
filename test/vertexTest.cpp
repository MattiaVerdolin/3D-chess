#include "vertexTest.h"
#include <iostream>

// Colori ANSI
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// Funzione per testare il costruttore e i getter
void testVertexConstructorAndGetters() {
    std::cout << "Testing Constructor and Getters:\n";

    glm::vec3 position(1.0f, 2.0f, 3.0f);
    glm::vec3 normal(0.0f, 1.0f, 0.0f);

    // Crea un oggetto Vertex
    Vertex v(position, normal);

    // Verifica i getter
    if (v.getPosition() == position) {
        std::cout << GREEN << "TEST PASSED: Position getter works." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Position getter did not return correct value." << RESET << "\n";
    }

    if (v.getNormal() == normal) {
        std::cout << GREEN << "TEST PASSED: Normal getter works." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Normal getter did not return correct value." << RESET << "\n";
    }

    if (v.getTextureCoordinates() == glm::vec2(0.0f, 0.0f)) {
        std::cout << GREEN << "TEST PASSED: Default texture coordinates are correctly initialized." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Default texture coordinates are incorrect." << RESET << "\n";
    }
}

// Funzione per testare il setter di texture coordinates
void testSetTextureCoordinates() {
    std::cout << "Testing setTextureCoordinates:\n";

    // Crea un oggetto Vertex
    glm::vec3 position(1.0f, 2.0f, 3.0f);
    glm::vec3 normal(0.0f, 1.0f, 0.0f);
    Vertex v(position, normal);

    glm::vec2 newTexCoord(0.75f, 0.25f);
    v.setTextureCoordinates(newTexCoord);

    // Verifica che il setter abbia funzionato
    if (v.getTextureCoordinates() == newTexCoord) {
        std::cout << GREEN << "TEST PASSED: Texture coordinates set successfully." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Texture coordinates setter did not work." << RESET << "\n";
    }
}
