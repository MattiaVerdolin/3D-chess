#pragma once

#include "mesh.h"
#include "material.h"
#include "vertex.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Funzione per creare un materiale di test
Material* createTestMaterial();

// Test per il costruttore e il getter del materiale
void testConstructorAndMaterialGetter();

// Test per il setter del materiale
void testMaterialSetter();

// Test per l'aggiunta di vertici
void testAddVertex();

// Test per ottenere i vertici
void testGetVertices();

// Test del rendering
void testRenderMesh();


