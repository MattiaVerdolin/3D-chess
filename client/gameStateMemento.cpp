#include "gameStateMemento.h"


GameState::GameState(int x, int y, PawnModel* pawnMoved) :
    oldX(x), oldY(y), pawnMoved(pawnMoved), pawnRemoved(nullptr)
{}


void GameState::setPawnRemoved(PawnModel* pawnRemoved) {
    this->pawnRemoved = pawnRemoved;
}

PawnModel* GameState::getPawnMoved() const {
    return pawnMoved;
}

int GameState::getOldX() const {
    return oldX;
}

int GameState::getOldY() const {
    return oldY;
}

PawnModel* GameState::getPawnRemoved() const {
    return pawnRemoved;
}
