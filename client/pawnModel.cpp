#include "pawnModel.h"

PawnModel::PawnModel(unsigned int x, unsigned int y, Mesh* meshPtr)
    : PieceModel(x, y, meshPtr) {}

unsigned int PawnModel::getPawnId() const {
    return mesh->getID();
}

void PawnModel::update(unsigned int newPosX, unsigned int newPosY, float offset) {

    // Calculate the difference between the new position and the current position
    int deltaX = newPosX - posX;
    int deltaY = newPosY - posY;

    // Update the current positions
    posX = newPosX;
    posY = newPosY;

    // Compute the translation vector
    glm::vec3 translation((deltaX * offset) * 2.7f, (-deltaY * offset) * 2.7f, 0.0f);

    // Apply the translation to the world matrix of the mesh
    mesh->translation(translation);

    // Debug: Print the update information
    std::cout << "PawnModel updated: new position ("
        << posX << ", " << posY << ")" << std::endl;
}
