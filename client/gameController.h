/**
 * @file	gameController.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "engine.h"
#include "chessModel.h"
#include "light.h"

/**
 * @class GameController
 * @brief Manages the overall game logic, including input handling and game phases.
 */
class GameController {
private:
    MVsio& engine;                           /**< Reference to the game engine instance. */
    ChessModel* chessModel = new ChessModel(); /**< Pointer to the ChessModel instance. */
    bool selectionPhase = true;              /**< Indicates whether the game is in the piece selection phase. */
    PawnModel* pawnSelected = nullptr;       /**< Pointer to the currently selected pawn. */

    /**
     * @brief Private constructor to enforce the singleton pattern.
     */
    GameController();

    /**
     * @brief Handles keyboard input events.
     * @param key The key pressed.
     * @param mouseX The X coordinate of the mouse when the key was pressed.
     * @param mouseY The Y coordinate of the mouse when the key was pressed.
     */
    void handleKeyboardInput(unsigned char key, int mouseX, int mouseY);

public:
    /**
     * @brief Provides access to the single instance of GameController.
     * @return Reference to the GameController instance.
     */
    static GameController& getInstance() {
        static GameController instance;
        return instance;
    }

    /**
     * @brief Callback function for handling keyboard input.
     * @param key The key pressed.
     * @param mouseX The X coordinate of the mouse when the key was pressed.
     * @param mouseY The Y coordinate of the mouse when the key was pressed.
     */
    static void keyboardCallback(unsigned char key, int mouseX, int mouseY);

    /**
     * @brief Initializes the GameController and sets up the game.
     */
    void init();

    void maskShadow() const;
};
