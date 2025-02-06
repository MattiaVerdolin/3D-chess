#include "chessModel.h"


ChessModel::ChessModel() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            matrixBoard[i][j] = nullptr;
        }
    }
}

ChessModel::~ChessModel() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete matrixBoard[i][j];
            matrixBoard[i][j] = nullptr;
        }
    }
    delete board;
    delete selector;
    board = nullptr;
    selector = nullptr;
}

void ChessModel::calculateOffset() {
    glm::vec3 min(FLT_MAX);
    glm::vec3 max(-FLT_MAX);

    for (const auto& vertex : board->getVertices(0)) {
        min = glm::min(min, vertex->getPosition());
        max = glm::max(max, vertex->getPosition());
    }

    glm::vec3 localDimensions = max - min;
    glm::mat4 localMatrix = board->getLocalMatrix();
    glm::vec3 scale(
        glm::length(glm::vec3(localMatrix[0])),
        glm::length(glm::vec3(localMatrix[1])),
        glm::length(glm::vec3(localMatrix[2]))
    );

    glm::vec3 dimensions3D = localDimensions * scale;
    offset = dimensions3D.x / 8;
}

void ChessModel::init(const List& engList) {
    // Initialize selector
    Node* selectorFound = engList.getElementByName("Selector");
    if (selectorFound) {
        Mesh* selectorMesh = dynamic_cast<Mesh*>(selectorFound);
        if (selectorMesh) {
            selector = new SelectorModel(0, 0, selectorMesh);
        }
        else {
            std::cerr << "Error: 'Selector' is not a valid Mesh!" << std::endl;
        }
    }
    else {
        std::cerr << "Error: 'Selector' node not found!" << std::endl;
    }

    // Initialize chessboard
    Node* chessBoard = engList.getElementByName("Chessboard");
    if (chessBoard) {
        board = dynamic_cast<Mesh*>(chessBoard);
        if (board) {
            calculateOffset();
        }
        else {
            std::cerr << "Error: 'Chessboard' is not a valid Mesh!" << std::endl;
        }
    }
    else {
        std::cerr << "Error: 'Chessboard' node not found!" << std::endl;
    }

    // Initialize pawns
    Node* chessPiecesNode = engList.getElementByName("Chess_Pieces");
    if (chessPiecesNode) {
        std::vector<Node*> children = chessPiecesNode->getChildren();

        for (Node* child : children) {
            Mesh* pawnMesh = dynamic_cast<Mesh*>(child);
            if (pawnMesh) {
                std::string name = child->getName();
                size_t commaPos = name.find(',');
                if (commaPos != std::string::npos && name[0] == '[' && name.back() == ']') {
                    unsigned int posX = std::stoi(name.substr(1, commaPos - 1));
                    unsigned int posY = std::stoi(name.substr(commaPos + 1, name.size() - commaPos - 2));

                    if (posX < 8 && posY < 8) {
                        matrixBoard[posX][posY] = new PawnModel(posX, posY, pawnMesh);
                        resetMatrix[posX][posY] = matrixBoard[posX][posY];
                    }
                    else {
                        std::cerr << "Error: Invalid position (" << posX << ", " << posY << ")" << std::endl;
                    }
                }
                else {
                    std::cerr << "Error: Invalid piece name: " << name << std::endl;
                }
            }
            else {
                std::cerr << "Error: Child node is not a valid Mesh!" << std::endl;
            }
        }
    }
    else {
        std::cerr << "Error: 'Chess_Pieces' node not found!" << std::endl;
    }
}

void ChessModel::moveSelector(int direction) {
    selector->changePosition(direction, offset);
}

void ChessModel::movePawn(PawnModel* pawn) {
    if (!pawn) {
        std::cerr << "Error: Null PawnModel passed!" << std::endl;
        return;
    }

    int currentX = -1, currentY = -1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (matrixBoard[i][j] == pawn) {
                currentX = i;
                currentY = j;
                break;
            }
        }
        if (currentX != -1) break;
    }

    if (currentX == -1 || currentY == -1) {
        std::cerr << "Error: PawnModel not found in matrix!" << std::endl;
        return;
    }

    int newX = selector->getPosX();
    int newY = selector->getPosY();

    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
        std::cerr << "Error: Coordinates out of matrix bounds!" << std::endl;
        return;
    }

    pawn->update(newX, newY, offset);
    matrixBoard[currentX][currentY] = nullptr;
    matrixBoard[newX][newY] = pawn;

    std::cout << "Pawn moved from (" << currentX << ", " << currentY << ") to ("
        << newX << ", " << newY << ")" << std::endl;
}

PawnModel* ChessModel::selectCell() {
    return matrixBoard[selector->getPosX()][selector->getPosY()];
}

void ChessModel::resetBoard() {
    if (!resetMatrix) {
        std::cerr << "Error: resetMatrix is not initialized!" << std::endl;
        return;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Clear the current matrix
            if (matrixBoard[i][j] != nullptr) {
                matrixBoard[i][j] = nullptr;
            }

            // Restore the piece from the reset matrix
            if (resetMatrix[i][j] != nullptr) {
                matrixBoard[i][j] = resetMatrix[i][j];
                matrixBoard[i][j]->getMesh()->setRender(true);

                // Update the piece position in the 3D scene
                matrixBoard[i][j]->update(i, j, offset);
            }
        }
    }

    std::cout << "The chessboard has been reset to its original configuration." << std::endl;
}

void ChessModel::undo() {
    if (undoVector.empty()) {
        std::cerr << "No moves to undo!" << std::endl;
        return;
    }

    GameState* lastState = undoVector.back();
    undoVector.pop_back();

    int oldX = lastState->getOldX();
    int oldY = lastState->getOldY();
    PawnModel* movedPawn = lastState->getPawnMoved();

    if (!movedPawn) {
        std::cerr << "Error: PawnModel in undo state is null!" << std::endl;
        delete lastState;
        return;
    }

    int currentX = -1, currentY = -1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (matrixBoard[i][j] == movedPawn) {
                currentX = i;
                currentY = j;
                break;
            }
        }
        if (currentX != -1) break;
    }

    if (currentX == -1 || currentY == -1) {
        std::cerr << "Error: PawnModel not found in the current matrix!" << std::endl;
        delete lastState;
        return;
    }

    // Move the pawn back to its original position
    matrixBoard[currentX][currentY] = nullptr;
    matrixBoard[oldX][oldY] = movedPawn;

    // Update the pawn's position in the 3D scene
    movedPawn->update(oldX, oldY, offset);

    // Restore any removed pawns
    PawnModel* removedPawn = lastState->getPawnRemoved();
    if (removedPawn) {
        int removedX = removedPawn->getPosX();
        int removedY = removedPawn->getPosY();

        matrixBoard[removedX][removedY] = removedPawn;
        removedPawn->getMesh()->setRender(true);
        removedPawn->update(removedX, removedY, offset);
    }

    std::cout << "Undo performed: pawn moved back from ("
        << currentX << ", " << currentY << ") to ("
        << oldX << ", " << oldY << ")" << std::endl;

    delete lastState;
}

void ChessModel::pushBackUndo(GameState* gamestate) {
    undoVector.push_back(gamestate);
}

void ChessModel::setRemoved(PawnModel* pawnRemoved) {
    if (!undoVector.empty()) {
        undoVector.back()->setPawnRemoved(pawnRemoved);
    }
    else {
        std::cerr << "Error: No undo state available to set removed pawn!" << std::endl;
    }
}
