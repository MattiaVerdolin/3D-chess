#include "gameController.h"


GameController::GameController()
    : engine(MVsio::getInstance())
{}

void GameController::init() {

    std::cout << std::endl << "Client messages..." << std::endl << std::endl;

    chessModel->init(engine.getList());

    maskShadow();

    engine.setKeyboardCallback(keyboardCallback);
}

void GameController::keyboardCallback(unsigned char key, int mouseX, int mouseY) {
    GameController& controller = GameController::getInstance();
    controller.handleKeyboardInput(key, mouseX, mouseY);
}


void GameController::handleKeyboardInput(unsigned char key, int mouseX, int mouseY) {
    switch (key) {
    case 'a': // Move selector to the left
        chessModel->moveSelector(3);
        break;
    case 'd': // Move selector to the right
        chessModel->moveSelector(2);
        break;
    case 'w': // Move selector up
        chessModel->moveSelector(1);
        break;
    case 's': // Move selector down
        chessModel->moveSelector(4);
        break;
    case 'c': // Switch camera
        engine.switchCamera();
        break;
    case 'r': // Reset the board
        chessModel->resetBoard();
        maskShadow();
        break;
    case 'u': // Undo the last move
        chessModel->undo();
        break;
    case 'l':
        dynamic_cast<Lighting::Light*>(engine.getList().getElementByName("Fspot001"))->toggle();
        break;
    case ' ': // Spacebar pressed
        if (selectionPhase) { // Selection phase
            pawnSelected = chessModel->selectCell();
            if (pawnSelected != nullptr) {
                std::cout << "Pawn selected: " << pawnSelected->getMesh()->getName() << std::endl;
                GameState* state = new GameState(pawnSelected->getPosX(), pawnSelected->getPosY(), pawnSelected);
                chessModel->pushBackUndo(state);
                selectionPhase = false;
            }
            else {
                std::cout << "WARNING! The selected cell does not contain any pawn. Try again." << std::endl;
            }
        }
        else { // Move phase
            if (chessModel->selectCell() != nullptr && pawnSelected != chessModel->selectCell()) {

                PawnModel* pawnToRemove = chessModel->selectCell();

                chessModel->setRemoved(pawnToRemove);
                pawnToRemove->getMesh()->setRender(false);
            }
            chessModel->movePawn(pawnSelected);
            selectionPhase = true;
        }
        break;
    default:
        break; // No action for other keys
    }

    // Force rendering of a new frame
    engine.postWindowRedisplay();
}


void GameController::maskShadow() const
{

    std::vector<std::string> tempNames;
    tempNames.push_back("Light_Ceiling1");

    for (Node* n : engine.getList().getElementByName("Chess_Pieces")->getChildren()) {
        tempNames.push_back(n->getName());
    }

    for (std::string s : tempNames) {
        engine.getList().getElementByName("ShadowOf" + s)->setToRender(false);
    }
}
