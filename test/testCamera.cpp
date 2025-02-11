#include "testCamera.h"
#include <iostream>
#include <cmath>

// Colori ANSI
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// Test di Creazione della Camera
void testCameraInitialization() {
    Camera camera("Camera1", nullptr, glm::mat4(1.0f));

    if (camera.getName() == "Camera1") {
        std::cout << GREEN << "TEST PASSED: Camera initialized correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Camera name is incorrect." << RESET << "\n";
    }

    if (!camera.isActive()) {
        std::cout << GREEN << "TEST PASSED: Camera is inactive by default." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Camera should be inactive by default." << RESET << "\n";
    }
}

// Test della Proiezione Perspectiva
void testPerspectiveProjection() {
    Camera camera("Camera1", nullptr, glm::mat4(1.0f));

    camera.setPerspective(45.0f, 1.6f, 0.1f, 100.0f);
    glm::mat4 projectionMatrix = camera.getProjectionMatrix();

    float fov = 45.0f;
    float aspect = 1.6f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::mat4 expectedProjection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);

    bool testPassed = true;
    const float tolerance = 0.001f;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (std::abs(projectionMatrix[i][j] - expectedProjection[i][j]) > tolerance) {
                testPassed = false;
                std::cout << RED << "TEST FAILED at [" << i << "][" << j << "]: Expected "
                    << expectedProjection[i][j] << " but got " << projectionMatrix[i][j] << RESET << "\n";
            }
        }
    }

    if (testPassed) {
        std::cout << GREEN << "TEST PASSED: Perspective projection is correct." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Perspective projection is incorrect." << RESET << "\n";
    }
}

// Test della Matrice della Camera
void testCameraMatrix() {
    Camera camera("Camera1", nullptr, glm::mat4(1.0f));

    glm::mat4 cameraMatrix = camera.getCameraMatrix();

    if (cameraMatrix == glm::mat4(1.0f)) {
        std::cout << GREEN << "TEST PASSED: Camera matrix is the identity matrix when parent is null." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Camera matrix is not the identity matrix." << RESET << "\n";
    }
}

// Test delle Trasformazioni
void testCameraTranslate() {
    Camera camera("Camera1", nullptr, glm::mat4(1.0f));

    glm::vec3 translation(1.0f, 0.0f, 0.0f);
    camera.translate(translation);

    glm::mat4 localMatrixAfterTranslation = camera.getLocalMatrix();

    if (localMatrixAfterTranslation[3][0] == 1.0f) {
        std::cout << GREEN << "TEST PASSED: Camera translated correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Camera translation did not work." << RESET << "\n";
    }
}

// Test dello Stato Attivo
void testCameraActivation() {
    Camera camera("Camera1", nullptr, glm::mat4(1.0f));

    if (!camera.isActive()) {
        std::cout << GREEN << "TEST PASSED: Camera is inactive by default." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Camera should be inactive by default." << RESET << "\n";
    }

    camera.setIsActive(true);
    if (camera.isActive()) {
        std::cout << GREEN << "TEST PASSED: Camera is active now." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Camera should be active." << RESET << "\n";
    }

    camera.setIsActive(false);
    if (!camera.isActive()) {
        std::cout << GREEN << "TEST PASSED: Camera is inactive again." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Camera should be inactive." << RESET << "\n";
    }
}
