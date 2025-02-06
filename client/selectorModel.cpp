
#include "selectorModel.h"
#include <iostream>

SelectorModel::SelectorModel(unsigned int x, unsigned int y, Mesh* meshPtr)
    : PieceModel(x, y, meshPtr) {} 

void SelectorModel::changePosition(int direction, float offset) {

    if (mesh) {
        // Calcola la nuova posizione del selettore basandosi sulla direzione
        unsigned int newPosX = posX;
        unsigned int newPosY = posY;

        switch (direction) {
        case 1: // Avanti
            newPosY = (posY == 7) ? 0 : posY + 1;
            break;

        case 2: // Destra
            newPosX = (posX == 7) ? 0 : posX + 1;
            break;

        case 3: // Sinistra
            newPosX = (posX == 0) ? 7 : posX - 1;
            break;

        case 4: // Indietro
            newPosY = (posY == 0) ? 7 : posY - 1;
            break;

        default:
            std::cerr << "Direzione non valida: " << direction << std::endl;
            return;
        }

        // Passa la nuova posizione al metodo update
        update(newPosX, newPosY, offset);
    }
    else {
        std::cerr << "Errore: Nodo 'mesh' non valido." << std::endl;
    }
}

void SelectorModel::update(unsigned int newPosX, unsigned int newPosY, float offset) {

    // Calcola la differenza tra la nuova posizione e quella corrente
    int deltaX = newPosX - posX;
    int deltaY = newPosY - posY;

    // Aggiorna le posizioni correnti
    posX = newPosX;
    posY = newPosY;

    // Calcola il vettore di traslazione
    glm::vec3 translation((deltaX * offset)*1.45f, 0.0f, -(deltaY * offset)*1.5f);

    // Applica la traslazione alla matrice globale della mesh
    mesh->translation(translation);

    // Debug: Stampa le informazioni di aggiornamento
    std::cout << "SelectorModel aggiornato: nuova posizione ("
        << posX << ", " << posY << ")" << std::endl;
}
