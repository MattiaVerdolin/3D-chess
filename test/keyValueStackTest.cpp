#include "keyValueStackTest.h"
#include <iostream>

// Colori ANSI
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// Funzione di test per `push` e `empty`
void testPushAndEmpty() {
    KeyValueStack& stack = KeyValueStack::getInstance();

    stack.push(1, 5);
    if (!stack.empty()) {
        std::cout << GREEN << "TEST PASSED: Stack is not empty after push." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Stack should not be empty after push." << RESET << "\n";
    }
}

// Funzione di test per `firstId`
void testFirstId() {
    KeyValueStack& stack = KeyValueStack::getInstance();

    // Assicurati che la chiave 1 sia inserita prima della chiave 2
    stack.push(1, 3); // Inserisci la chiave 1
    stack.push(2, 3); // Inserisci la chiave 2

    int id = stack.firstId();
    if (id == 1) { // Ora il primo ID sarà 1 a causa dell'ordinamento della mappa
        std::cout << GREEN << "TEST PASSED: First ID is correct." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Expected ID 1, got " << id << "." << RESET << "\n";
    }
}

// Funzione di test per `decrementValue`
void testDecrementValue() {
    KeyValueStack& stack = KeyValueStack::getInstance();

    stack.push(3, 2);

    if (stack.decrementValue(3)) {
        std::cout << GREEN << "TEST PASSED: Value decremented successfully." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Decrement should succeed." << RESET << "\n";
    }

    if (stack.decrementValue(3)) {
        std::cout << GREEN << "TEST PASSED: Value decremented to 0." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Decrement should succeed." << RESET << "\n";
    }

    if (!stack.decrementValue(3)) {
        std::cout << GREEN << "TEST PASSED: Decrement failed as value is 0." << RESET << "\n";
    }
    else {
        std::cout << RED << "TEST FAILED: Decrement should fail when value is 0." << RESET << "\n";
    }
}


