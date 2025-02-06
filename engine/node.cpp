#include "node.h"

// C++
#include <iostream>


Node::Node(std::string name, std::vector<Node*> children, Node* parent, glm::mat4 localMatrix)
    : Object(std::move(name)), // Calls the constructor of Object with the name
    children{ std::move(children) },
    parent{ parent },
    localMatrix{ localMatrix }
{
    if (parent != nullptr) {
        parent->addChild(this);
    }
}

void Node::render(const glm::mat4& finalMatrix) {
    // Empty implementation for generic nodes
}

void Node::addChild(Node* newChild) {
    newChild->setParent(this);
    children.push_back(newChild);
    numChildren++;
}

void Node::removeChild(Node* childToRemove) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (*it == childToRemove) {
            children.erase(it);
            break;
        }
    }
}


glm::mat4 Node::getLocalMatrix() const {
    return localMatrix;
}

void Node::setLocalMatrix(const glm::mat4& localMatrix) {
    this->localMatrix = localMatrix;
}

glm::mat4 Node::getWorldMatrix() const {
    return worldMatrix;
}

void Node::setWorldMatrix(const glm::mat4& worldMatrix) {
    this->worldMatrix = worldMatrix;
}

Node* Node::getChild(int posizione) const {
    if (posizione >= children.size()) {
        std::cout << "Error: position out of bounds" << std::endl;
        return nullptr;
    }

    return children.at(posizione);
}

Node* Node::getParent() const {
    return parent;
}

void Node::setParent(Node* node) {
    parent = node;
}

Node* Node::findByName(const std::string& name) {
    if (getName() == name) {
        return this;
    }

    for (Node* child : children) {
        Node* result = child->findByName(name);
        if (result != nullptr) {
            return result;
        }
    }

    return nullptr;
}

Node* Node::findByID(int id) {
    if (getID() == id) {
        return this;
    }

    for (Node* child : children) {
        Node* result = child->findByID(id);
        if (result != nullptr) {
            return result;
        }
    }

    return nullptr;
}

const std::vector<Node*>& Node::getChildren() const {
    return children;
}

void Node::setChildren(const std::vector<Node*>& newChildren) {
    children = newChildren;
}

void Node::setnumChildren(unsigned int n) {
    numChildren = n;
}

unsigned int Node::getnumChildren() const {
    return numChildren;
}

bool Node::getRender() const {
    return toRender;
}

void Node::setToRender(bool cond) {
    toRender = cond;
}
