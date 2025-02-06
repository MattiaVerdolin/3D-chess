/**
 * @file	chessModel.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "selectorModel.h"
#include "pawnModel.h"
#include "mesh.h"
#include "list.h"
#include "gameStateMemento.h"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

/**
 * @class ChessModel
 * @brief Represents the model of a chess game, including board, pawns, and game states.
 */
class ChessModel {
private:
    Mesh* board = nullptr;                     /**< Mesh representing the chessboard. */
    SelectorModel* selector = nullptr;         /**< Selector for highlighting cells, initialized by default. */
    PawnModel* matrixBoard[8][8] = {};         /**< 8x8 matrix representing the chessboard with pawns. */
    float offset = 0;                          /**< Offset for calculating board dimensions. */
    PawnModel* resetMatrix[8][8] = {};         /**< Backup matrix for resetting the board. */
    std::vector<GameState*> undoVector;        /**< Stack of game states for undo functionality. */

    /**
     * @brief Calculates the dimensions of the chessboard.
     */
    void calculateOffset();

public:
    /**
     * @brief Constructs a new ChessModel instance.
     */
    ChessModel();

    /**
     * @brief Destroys the ChessModel instance and cleans up resources.
     */
    ~ChessModel();

    /**
     * @brief Initializes the chess model.
     * @param engList The list of game entities to initialize.
     */
    void init(const List& engList);

    /**
     * @brief Moves the selector in a specified direction.
     * @param direction The direction to move the selector (e.g., up, down, left, right).
     */
    void moveSelector(int direction);

    /**
     * @brief Moves a pawn to its new position.
     * @param pawn Pointer to the PawnModel to be moved.
     */
    void movePawn(PawnModel* pawn);

    /**
     * @brief Selects the currently highlighted cell on the board.
     * @return Pointer to the selected PawnModel.
     */
    PawnModel* selectCell();

    /**
     * @brief Resets the chessboard to its initial state.
     */
    void resetBoard();

    /**
     * @brief Undoes the last move by restoring the previous game state.
     */
    void undo();

    /**
     * @brief Adds a game state to the undo stack.
     * @param gamestate Pointer to the GameState to be stored.
     */
    void pushBackUndo(GameState* gamestate);

    /**
     * @brief Marks a pawn as removed in the undo stack.
     * @param pawnRemoved Pointer to the PawnModel that was removed.
     */
    void setRemoved(PawnModel* pawnRemoved);
};
