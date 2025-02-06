/**
 * @file	node.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "object.h"

// GLM
#include <glm/glm.hpp>

// C++
#include <vector>
#include <string>

/**
 * @class Node
 * @brief Represents a node in the scene graph.
 *
 * The Node class serves as a hierarchical container for managing transformations, parent-child relationships,
 * and rendering operations in the scene graph.
 */
class ENG_API Node : public Object {
private:

protected:
    glm::mat4 worldMatrix = {}; ///< World transformation matrix.
    glm::mat4 localMatrix = {}; ///< Local transformation matrix.
    std::vector<Node*> children = {}; ///< List of pointers to child nodes.
    Node* parent = nullptr; ///< Pointer to the parent node.
    unsigned int numChildren = 0; ///< Number of child nodes.
    bool toRender = true; ///< Flag indicating whether the mesh should be rendered.

public:
    /**
     * @brief Constructs a Node with the specified properties.
     *
     * @param name The name of the node.
     * @param children The list of child nodes.
     * @param parent The parent node.
     * @param modelMatrix The local transformation matrix for the node.
     */
    Node(std::string name, std::vector<Node*> children = {}, Node* parent = nullptr, glm::mat4 localMatrix = glm::mat4(1.0f));

    /**
     * @brief Default constructor for Node.
     */
    Node() = default;

    /**
     * @brief Virtual destructor for Node.
     */
    virtual ~Node() = default;

    /**
     * @brief Renders the node.
     *
     * @param finalMatrix The transformation matrix to apply during rendering.
     */
    virtual void render(const glm::mat4& finalMatrix);

    /**
     * @brief Retrieves the world transformation matrix of the node.
     *
     * @return The world transformation matrix as a glm::mat4.
     */
    glm::mat4 getWorldMatrix() const;

    /**
     * @brief Sets the world transformation matrix of the node.
     *
     * @param worldMatrix The new world transformation matrix.
     */
    void setWorldMatrix(const glm::mat4& worldMatrix);

    /**
     * @brief Finds a node by its ID within the hierarchy.
     *
     * @param id The ID of the node to find.
     * @return A pointer to the node if found, or nullptr otherwise.
     */
    Node* findByID(int id);

    /**
     * @brief Retrieves the local transformation matrix of the node.
     *
     * @return The local transformation matrix as a glm::mat4.
     */
    glm::mat4 getLocalMatrix() const;

    /**
     * @brief Sets the local transformation matrix of the node.
     *
     * @param localMatrix The new local transformation matrix.
     */
    void setLocalMatrix(const glm::mat4& localMatrix);

    /**
     * @brief Retrieves a child node at the specified position.
     *
     * @param posizione The index of the child node to retrieve.
     * @return A pointer to the child node.
     */
    Node* getChild(int posizione) const;

    /**
     * @brief Adds a child node to this node.
     *
     * @param child A pointer to the child node to add.
     */
    void addChild(Node* child);

    /**
     * @brief Removes a child node from this node.
     *
     * @param nodeToRemove A pointer to the child node to remove.
     */
    void removeChild(Node* nodeToRemove);

    /**
     * @brief Retrieves the list of child nodes.
     *
     * @return A constant reference to the vector of child nodes.
     */
    const std::vector<Node*>& getChildren() const;

    /**
     * @brief Sets the list of child nodes for this node.
     *
     * @param newChildren The new list of child nodes.
     */
    void setChildren(const std::vector<Node*>& newChildren);

    /**
     * @brief Retrieves the parent node of this node.
     *
     * @return A pointer to the parent node, or nullptr if there is no parent.
     */
    Node* getParent() const;

    /**
     * @brief Sets the parent node of this node.
     *
     * @param newParent A pointer to the new parent node.
     */
    void setParent(Node* newParent);

    /**
     * @brief Finds a node by its name within the hierarchy.
     *
     * @param name The name of the node to find.
     * @return A pointer to the node if found, or nullptr otherwise.
     */
    Node* findByName(const std::string& name);

    /**
     * @brief Sets the number of child nodes.
     *
     * @param num The new number of child nodes.
     */
    void setnumChildren(unsigned int num);

    /**
     * @brief Retrieves the number of child nodes.
     *
     * @return The number of child nodes as an unsigned integer.
     */
    unsigned int getnumChildren() const;

    /**
     * @brief Checks if the mesh is set to be rendered.
     *
     * @return True if the mesh is set to be rendered, false otherwise.
     */
    bool getRender() const;

    void setToRender(bool cond);
};
