#include "listTest.h"
#include <iostream>

// Colori ANSI
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

void testPrintHierarchy() {
    List list;

    Node root("Root", {}, nullptr, glm::mat4(1.0f));
    Node child1("Child1", {}, &root, glm::mat4(1.0f));
    Node child2("Child2", {}, &root, glm::mat4(1.0f));

    list.addElement(&root);

    std::cout << "Testing printHierarchy():\n";
    list.printHierarchy(); // Verificare manualmente l'output.
}

void testPass() {
    List list;

    Node root("Root", {}, nullptr, glm::mat4(1.0f));
    Node child1("Child1", {}, &root, glm::mat4(1.0f));
    Node light("Child2", {}, &root, glm::mat4(1.0f));

    list.pass(&root);

    std::cout << "Testing pass():\n";
    for (auto node : list.getNodeList()) {
        std::cout << node->getName() << " ";
    }
    std::cout << "\n"; // Controllare che Light sia il primo nodo.
}

void testRenderList() {
    List list;

    Node root("Root", {}, nullptr, glm::mat4(1.0f));
    list.addElement(&root);

    glm::mat4 camera = glm::mat4(1.0f);
    std::cout << GREEN << "Testing render():" << RESET << "\n";
    list.render(camera); // Assicurarsi che non ci siano errori.
}

void testAddElement() {
    List list;

    Node node("TestNode", {}, nullptr, glm::mat4(1.0f));
    list.addElement(&node);

    if (list.getElementByID(node.getID()) == &node) {
        std::cout << GREEN << "TEST PASSED: addElement works correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: addElement does not work correctly." << RESET << "\n";
    }
}

void testRemoveElementByName() {
    List list;

    Node node("TestNode", {}, nullptr, glm::mat4(1.0f));
    list.addElement(&node);

    list.removeElementByName("TestNode");
    if (list.getElementByName("TestNode") == nullptr) {
        std::cout << GREEN << "TEST PASSED: removeElementByName works correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: removeElementByName does not work correctly." << RESET << "\n";
    }
}

void testRemoveElementByID() {
    List list;

    Node node("TestNode", {}, nullptr, glm::mat4(1.0f));
    list.addElement(&node);

    list.removeElementByID(node.getID());
    if (list.getElementByID(node.getID()) == nullptr) {
        std::cout << GREEN << "TEST PASSED: removeElementByID works correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: removeElementByID does not work correctly." << RESET << "\n";
    }
}

void testGetElementByID() {
    List list;

    Node node("TestNode", {}, nullptr, glm::mat4(1.0f));
    list.addElement(&node);

    if (list.getElementByID(node.getID()) == &node) {
        std::cout << GREEN << "TEST PASSED: getElementByID works correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: getElementByID does not work correctly." << RESET << "\n";
    }
}

void testGetElementByName() {
    List list;

    Node node("TestNode", {}, nullptr, glm::mat4(1.0f));
    list.addElement(&node);

    if (list.getElementByName("TestNode") == &node) {
        std::cout << GREEN << "TEST PASSED: getElementByName works correctly." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: getElementByName does not work correctly." << RESET << "\n";
    }
}
