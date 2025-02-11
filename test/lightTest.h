#pragma once

#include "light.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Colori ANSI per il feedback
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

/**
 * @brief Testa la classe base Light.
 */
void testLightBaseClass();

/**
 * @brief Testa la classe DirectionalLight.
 */
void testDirectionalLight();

/**
 * @brief Testa la classe OmniLight.
 */
void testOmniLight();

/**
 * @brief Testa la classe SpotLight.
 */
void testSpotLight();
