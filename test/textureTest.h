#pragma once

#include "texture.h"
#include <iostream>
#include <glm/mat4x4.hpp>

// Colori ANSI per il feedback dei test
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

/**
 * @brief Esegue i test per il costruttore e i getter della classe Texture.
 */
void testTextureConstructorAndGetters();

/**
 * @brief Esegue i test per il metodo createTexture della classe Texture.
 */
void testCreateTexture();

/**
 * @brief Esegue i test per il metodo render della classe Texture.
 */
void testRenderTex();

/**
 * @brief Esegue i test per il metodo release della classe Texture.
 */
void testRelease();

/**
 * @brief Esegue i test per i setter della classe Texture.
 */
void testSetName();
