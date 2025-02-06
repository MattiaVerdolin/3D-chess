/**
 * @file	camera.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "node.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C++
#include <string.h>

/**
 * @class Camera
 * @brief Represents a camera in the scene graph.
 * 
 * The Camera class extends the Node class and provides functionalities for perspective and orthographic projection.
 */
class ENG_API Camera : public Node {
private:
    /**
     * @brief The projection matrix of the camera.
     */
    glm::mat4 projectionMatrix = {};

    /**
     * @brief Flag indicating whether the camera is active.
     */
    bool active = false;

public:
    /**
     * @brief Constructs a Camera object.
     *
     * @param name The name of the camera node.
     * @param parent The parent node in the scene graph.
     * @param localMatrix The local transformation matrix of the camera.
     */
    Camera(const std::string& name, Node* parent, glm::mat4 localMatrix);

    /**
     * @brief Retrieves the projection matrix of the camera.
     *
     * @return The projection matrix as a glm::mat4.
     */
    glm::mat4 getProjectionMatrix() const;

    /**
     * @brief Sets the camera to use a perspective projection.
     *
     * @param fov The field of view in degrees.
     * @param aspect The aspect ratio of the viewport.
     * @param nearPlane The distance to the near clipping plane.
     * @param farPlane The distance to the far clipping plane.
     */
    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);

    /**
     * @brief Renders the camera node in the scene graph.
     *
     * @param finalMatrix The final transformation matrix of the scene.
     */
    void render(const glm::mat4& finalMatrix) override;

    /**
     * @brief Retrieves the camera matrix.
     *
     * The camera matrix is the inverse of the world coordinates matrix of the parent node.
     *
     * @return The camera matrix as a glm::mat4.
     */
    glm::mat4 getCameraMatrix() const;

    /**
     * @brief Translates and rotates the camera.
     *
     * @param translation The translation vector.
     * @param rotation The rotation vector.
     */
    void translate(const glm::vec3& translation);

    void rotate(const glm::vec3& rotation);

    /**
     * @brief Checks if the camera is active.
     *
     * @return True if the camera is active, false otherwise.
     */
    bool isActive();

    /**
     * @brief Sets the active state of the camera.
     *
     * @param act True to activate the camera, false to deactivate it.
     */
    void setIsActive(bool act);

};
