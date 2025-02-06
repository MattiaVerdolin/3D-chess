/**
 * @file	list.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "object.h"
#include "node.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"
#include "shadow.h"

// Librerie C++
#include <string>
#include <list>

/**
 * Classe List: una collezione di puntatori a oggetti `Node`.
 * Eredita dalla classe base `Object`.
 */
class ENG_API List : public Object {
private:
    std::list<Node*> nodeList;

public:
    List() = default;
    void printHierarchy() const;
    void render(const glm::mat4& InverseCamera);
    void pass(Node* root);

   /**
    * Aggiunge un elemento alla lista.
    * @param elementToAdd Puntatore al nodo da aggiungere.
    */
   void addElement(Node* elementToAdd);

   /**
    * Rimuove un elemento dalla lista in base al nome.
    * @param name Nome del nodo da rimuovere.
    */
   void removeElementByName(const std::string& name);

   /**
    * Rimuove un elemento dalla lista in base all'ID.
    * @param id ID del nodo da rimuovere.
    */
   void removeElementByID(int id);

   /**
    * Ottiene un elemento dalla lista in base all'ID.
    * @param id ID del nodo da cercare.
    * @return Puntatore al nodo trovato o nullptr se non esiste.
    */
   Node* getElementByID(int id) const;

   /**
 * Ritorna un elemento dalla lista in base al nome.
 * @param name Nome del nodo da ritornare.
 */
   Node* getElementByName(const std::string& name) const;

   std::list<Node*> getNodeList();

};
