#include "nodeTest.h"
#include <iostream>

// Colori ANSI
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// Funzione per testare il costruttore e getter/setter
void testConstructorAndGettersNode() {
    Node parentNode("Parent", {}, nullptr, glm::mat4(1.0f));
    Node childNode("Child", {}, &parentNode, glm::mat4(1.0f));

    if (childNode.getName() == "Child") {
        std::cout << GREEN << "TEST PASSED: Name correctly set to 'Child'." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Name not set correctly." << RESET << "\n";
    }

    if (childNode.getParent() == &parentNode) {
        std::cout << GREEN << "TEST PASSED: Parent correctly set." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Parent not set correctly." << RESET << "\n";
    }
}

// Test per aggiungere e rimuovere figli
void testAddAndRemoveChild() {
    Node parentNode("Parent", {}, nullptr, glm::mat4(1.0f));

    Node childNode1("Child1", {}, &parentNode, glm::mat4(1.0f));
    Node childNode2("Child2", {}, &parentNode, glm::mat4(1.0f));

    if (parentNode.getChildren().size() == 2) {
        std::cout << GREEN << "TEST PASSED: Two children successfully added." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Children not added correctly." << RESET << "\n";
    }

    parentNode.removeChild(&childNode1);

    if (parentNode.getChildren().size() == 1 && parentNode.getChildren()[0] == &childNode2) {
        std::cout << GREEN << "TEST PASSED: Child1 successfully removed." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Child1 not removed correctly." << RESET << "\n";
    }
}

// Test per la ricerca di nodi per nome
void testFindByName() {
    Node rootNode("Root", {}, nullptr, glm::mat4(1.0f));
    Node childNode("Child", {}, &rootNode, glm::mat4(1.0f));
    rootNode.addChild(&childNode);

    Node* foundNode = rootNode.findByName("Child");
    if (foundNode && foundNode->getName() == "Child") {
        std::cout << GREEN << "TEST PASSED: Node found by name." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Node not found by name." << RESET << "\n";
    }
}

// Test per la ricerca di nodi per ID
void testFindByID() {
    Node rootNode("Root", {}, nullptr, glm::mat4(1.0f));
    Node childNode("Child", {}, &rootNode, glm::mat4(1.0f));
    rootNode.addChild(&childNode);

    Node* foundNode = rootNode.findByID(childNode.getID());
    if (foundNode && foundNode->getID() == childNode.getID()) {
        std::cout << GREEN << "TEST PASSED: Node found by ID." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Node not found by ID." << RESET << "\n";
    }
}

// Test per il calcolo della matrice mondiale
void testWorldMatrix() {
    Node rootNode("Root", {}, nullptr, glm::mat4(1.0f));
    rootNode.setWorldMatrix(rootNode.getLocalMatrix());
    Node childNode("Child", {}, &rootNode, glm::mat4(1.0f));
    rootNode.addChild(&childNode);
    childNode.setWorldMatrix(rootNode.getWorldMatrix() * childNode.getLocalMatrix());
    glm::mat4 childWorldMatrix = childNode.getWorldMatrix();

    if (childWorldMatrix == glm::mat4(1.0f)) {
        std::cout << GREEN << "TEST PASSED: World Matrix correctly calculated." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: World Matrix calculation is incorrect." << RESET << "\n";
    }
}
