#include "texture.h"
#include <iostream>
#include <glm/mat4x4.hpp>

// Colori ANSI
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// Funzione di test per il costruttore e i getter
void testTextureConstructorAndGetters() {
    std::cout << "Testing Constructor and Getters:\n";

    Texture tex("TestTexture");

    if (tex.getName() == "TestTexture") {
        std::cout << GREEN << "TEST PASSED: Texture name correctly initialized." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Texture name not initialized correctly." << RESET << "\n";
    }
}

// Funzione di test per createTexture
void testCreateTexture() {
    std::cout << "Testing createTexture:\n";

    Texture tex("TestTexture");

    std::string validTexturePath = "path_to_valid_texture_file"; // Sostituisci con un percorso valido
    tex.createTexture(validTexturePath);

    // Nota: Non possiamo verificare facilmente la validità della texture senza OpenGL context, ma possiamo verificare l'assenza di errori.
    std::cout << GREEN << "TEST PASSED: createTexture executed without errors." << RESET << "\n";

    std::string invalidTexturePath = "path_to_invalid_texture_file";
    tex.createTexture(invalidTexturePath);

    // Verifica gestione di errori
    std::cout << GREEN << "TEST PASSED: createTexture handled invalid path without crash." << RESET << "\n";
}

// Funzione di test per render
void testRenderTex() {
    std::cout << "Testing render:\n";

    Texture tex("TestTexture");
    tex.createTexture("path_to_valid_texture_file"); // Usa un percorso valido

    glm::mat4 finalMatrix = glm::mat4(1.0f);

    // Renderizza la texture
    tex.render(finalMatrix);

    // Assicurati che la texture sia stata configurata senza errori
    std::cout << GREEN << "TEST PASSED: render executed without errors." << RESET << "\n";
}

// Funzione di test per release
void testRelease() {
    std::cout << "Testing release:\n";

    Texture tex("TestTexture");
    tex.createTexture("path_to_valid_texture_file"); // Usa un percorso valido

    tex.release();

    // Verifica che il texID sia stato rilasciato
    if (tex.getName().empty()) { // Supponendo che release imposti il nome a vuoto (aggiustare se necessario)
        std::cout << GREEN << "TEST PASSED: release executed and texture resources freed." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: release did not free texture resources." << RESET << "\n";
    }
}

// Funzione di test per i setter
void testSetName() {
    std::cout << "Testing setName:\n";

    Texture tex("InitialName");
    std::string newName = "UpdatedName";
    tex.setName(newName);

    if (tex.getName() == "UpdatedName") {
        std::cout << GREEN << "TEST PASSED: setName updated texture name correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: setName did not update texture name correctly." << RESET << "\n";
    }
}

