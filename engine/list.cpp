#include "list.h"

// C++
#include <iostream>

/**
 * @brief Prints the hierarchy of the scene graph.
 *
 * This method traverses the scene graph and prints the hierarchy of nodes, including their names,
 * number of children, and parent information.
 */
void List::printHierarchy() const {
    std::cout << std::endl << "Graph scene..." << std::endl << std::endl;

    auto printNodeHierarchy = [](const Node* node, int depth, const auto& printRef) -> void {
        if (!node ) return; // Salta i nodi di tipo Shadow || dynamic_cast<const Shadow*>(node)

        for (int i = 0; i < depth; ++i) std::cout << "    ";
        std::cout << "Nodo: " << node->getName()
            << ", Numero figli: " << node->getnumChildren();
        if (Node* parent = node->getParent()) {
            std::cout << ", Figlio di: " << parent->getName();
        }
        std::cout << std::endl;

        for (Node* child : node->getChildren()) {
            printRef(child, depth + 1, printRef);
        }
        };

    for (const Node* node : nodeList) {
        if (!node->getParent() ) { // Salta i nodi root di tipo Shadow && !dynamic_cast<const Shadow*>(node)
            printNodeHierarchy(node, 0, printNodeHierarchy);
        }
    }
}


/**
 * @brief Updates the world matrices of all nodes connected to the specified node.
 *
 * This method recursively propagates transformations through the scene graph, starting
 * from the specified node, and updates the world matrices of all connected nodes.
 *
 * @param node The root node from which to start the update.
 */
void List::pass(Node* node) {
    if (node == nullptr) return;

    glm::mat4 parentWorldMatrix = node->getParent()
        ? node->getParent()->getWorldMatrix()
        : glm::mat4(1.0f);

    node->setWorldMatrix(parentWorldMatrix * node->getLocalMatrix());

    if (dynamic_cast<Lighting::Light*>(node) == nullptr) {
        nodeList.push_back(node);
    }
    else {
        nodeList.push_front(node);
    }

    for (Node* child : node->getChildren()) {
        if (child && !dynamic_cast<Camera*>(child)) {
            pass(child);
        }
    }
}

/* Quando si moltiplica la worldMatrix di un nodo per l'inversa della projection
*/
void List::render(const glm::mat4& inverseCamera) {
    for (auto& node : nodeList) {
        if (node && node->getRender()) {

            glm::mat4 finalMatrix = inverseCamera * node->getWorldMatrix();
            node->render(finalMatrix);

        }
        
    }
}

void List::addElement(Node* elementToAdd) {
    nodeList.push_back(elementToAdd);
}

void List::removeElementByName(const std::string& name) {
    for (auto it = nodeList.begin(); it != nodeList.end(); ++it) {
        if ((*it)->getName() == name) {
            nodeList.erase(it);
            return;
        }
    }
}

void List::removeElementByID(int id) {
    for (auto it = nodeList.begin(); it != nodeList.end(); ++it) {
        if ((*it)->getID() == id) {
            nodeList.erase(it);
            return;
        }
    }
}

Node* List::getElementByID(int id) const {
    for (auto it = nodeList.begin(); it != nodeList.end(); ++it) {
        if ((*it)->getID() == id) {
            return *it;
        }
    }
    return nullptr;
}

Node* List::getElementByName(const std::string& name) const {
    for (auto it = nodeList.begin(); it != nodeList.end(); ++it) {
        if ((*it)->getName() == name) {
            return *it;
        }
    }
    return nullptr;
}

std::list<Node*> List::getNodeList() {
    return nodeList;
}
