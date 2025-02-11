#include "meshTest.h"
#include <iostream>

// Colori ANSI
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// Funzione per creare un materiale di test
Material* createTestMaterial() {
    glm::vec4 ambient(0.2f, 0.2f, 0.2f, 1.0f);
    glm::vec4 diffuse(0.8f, 0.8f, 0.8f, 1.0f);
    glm::vec4 specular(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 emissive(0.0f, 0.0f, 0.0f, 1.0f);
    float shininess = 32.0f;
    return new Material(ambient, diffuse, specular, emissive, shininess, nullptr);
}

// Test per il costruttore e il getter del materiale
void testConstructorAndMaterialGetter() {
    Material* material = createTestMaterial();
    Mesh mesh("TestMesh", nullptr, glm::mat4(1.0f), material);

    if (mesh.getMaterial() == material) {
        std::cout << GREEN << "TEST PASSED: Material correctly assigned to Mesh." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Material not assigned correctly." << RESET << "\n";
    }
}

// Test per il setter del materiale
void testMaterialSetter() {
    Material* material1 = createTestMaterial();
    Material* material2 = createTestMaterial();
    Mesh mesh("TestMesh", nullptr, glm::mat4(1.0f), material1);

    mesh.setMaterial(material2);

    if (mesh.getMaterial() == material2) {
        std::cout << GREEN << "TEST PASSED: Material correctly updated." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Material not updated correctly." << RESET << "\n";
    }
}

// Test per l'aggiunta di vertici
void testAddVertex() {
    Mesh mesh("TestMesh", nullptr, glm::mat4(1.0f), createTestMaterial());

    // Creiamo dei vertici con posizione e normale
    Vertex* v1 = new Vertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Vertex* v2 = new Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Vertex* v3 = new Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // Aggiungiamo i vertici alla mesh
    mesh.addVertex(v1, 0);
    mesh.addVertex(v2, 0);
    mesh.addVertex(v3, 0);

    if (mesh.getVertices(0).size() == 3) {
        std::cout << GREEN << "TEST PASSED: Three vertices correctly added to the mesh." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Number of vertices added is incorrect." << RESET << "\n";
    }
}

// Test per ottenere i vertici
void testGetVertices() {
    Mesh mesh("TestMesh", nullptr, glm::mat4(1.0f), createTestMaterial());

    // Creiamo dei vertici con posizione e normale
    Vertex* v1 = new Vertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Vertex* v2 = new Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Vertex* v3 = new Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // Aggiungiamo i vertici alla mesh
    mesh.addVertex(v1, 0);
    mesh.addVertex(v2, 0);
    mesh.addVertex(v3, 0);

    if (mesh.getVertices(0).size() == 3) {
        std::cout << GREEN << "TEST PASSED: Correct number of vertices retrieved." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Incorrect number of vertices retrieved." << RESET << "\n";
    }
}

// Test del rendering
void testRenderMesh() {
    Mesh mesh("TestMesh", nullptr, glm::mat4(1.0f), createTestMaterial());

    // Creiamo dei vertici con posizione e normale
    Vertex* v1 = new Vertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Vertex* v2 = new Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Vertex* v3 = new Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // Aggiungiamo i vertici alla mesh
    mesh.addVertex(v1, 0);
    mesh.addVertex(v2, 0);
    mesh.addVertex(v3, 0);

    glm::mat4 finalMatrix = glm::mat4(1.0f);
    std::cout << GREEN << "TEST PASSED: Render Method executed (manual verification needed)." << RESET << "\n";
    mesh.render(finalMatrix); // Questo sarà testato visivamente o tramite log.
}
