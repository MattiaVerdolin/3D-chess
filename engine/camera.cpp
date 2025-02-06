#include "camera.h"

// FreeGLUT
#include <GL/freeglut.h>

// C++
#include <iostream>

Camera::Camera(const std::string& name, Node* parent, glm::mat4 modelMatrix)
    : Node(name, {}, parent, modelMatrix) {
    setName(name);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

/*
* Configura una proiezione prospettica:
* fov: campo visivo verticale (in gradi).
* aspect: rapporto d'aspetto (larghezza/altezza).
* nearPlane: distanza minima visibile dalla fotocamera.
* farPlane: distanza massima visibile.
*/
void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void Camera::render(const glm::mat4& finalMatrix) {
    // vuoto
}

glm::mat4 Camera::getCameraMatrix() const {
    if (getParent()) {
        // Calculate the inverse view matrix by combining the parent world matrix and local matrix
        return glm::inverse(getParent()->getWorldMatrix() * localMatrix);
    }
    return glm::mat4(1.0f); // Identity matrix if no parent exists
}


void Camera::translate(const glm::vec3& translation) {
    // Apply translation to the local matrix
    localMatrix = glm::translate(localMatrix, translation);
}

void Camera::rotate(const glm::vec3& rotation) {
    // Apply rotations to the local matrix
    localMatrix = glm::rotate(localMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // Rotate around X-axis
    localMatrix = glm::rotate(localMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Rotate around Y-axis
    localMatrix = glm::rotate(localMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotate around Z-axis
}

bool Camera::isActive() {
    return active;
}

void Camera::setIsActive(bool act) {
    active = act;
}
