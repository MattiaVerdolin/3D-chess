#include "pieceModel.h"


PieceModel::PieceModel(unsigned int x, unsigned int y, Mesh* meshPtr)
    : posX(x), posY(y), mesh(meshPtr) {}


PieceModel::~PieceModel() {
    delete mesh;
}

PieceModel::PieceModel(const PieceModel& other)
    : posX(other.posX), posY(other.posY), mesh(other.mesh) {}


//  Getters

unsigned int PieceModel::getPosX() const {
    return posX;
}

unsigned int PieceModel::getPosY() const {
    return posY;
}

Mesh* PieceModel::getMesh() const {
    return mesh;
}

// Setters

void PieceModel::setPosX(unsigned int x) {
    posX = x;
}


void PieceModel::setPosY(unsigned int y) {
    posY = y;
}

void PieceModel::setMesh(Mesh* newMesh) {
    if (mesh) {
        delete mesh;
    }
    mesh = newMesh;
}
