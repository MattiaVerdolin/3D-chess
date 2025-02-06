/**
 * @file	gameStateMemento.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "pawnModel.h"

/**
 * @class GameState
 * @brief Represents the state of a chess game, including moved pawns and captured pawns.
 */
class GameState {
private:
    PawnModel* pawnMoved;          /**< Pointer to the pawn that was moved. */
    int oldX;                      /**< The original X-coordinate of the moved pawn. */
    int oldY;                      /**< The original Y-coordinate of the moved pawn. */
    PawnModel* pawnRemoved = nullptr; /**< Pointer to the pawn that was removed (if any). */

public:
    /**
     * @brief Constructs a new GameState object.
     * @param x The original X-coordinate of the moved pawn.
     * @param y The original Y-coordinate of the moved pawn.
     * @param pawnMoved Pointer to the pawn that was moved.
     */
    GameState(int x, int y, PawnModel* pawnMoved);

    /**
     * @brief Sets the pawn that was removed in this game state.
     * @param pawnRemoved Pointer to the removed pawn.
     */
    void setPawnRemoved(PawnModel* pawnRemoved);

    /**
     * @brief Gets the pointer to the moved pawn.
     * @return Pointer to the PawnModel that was moved.
     */
    PawnModel* getPawnMoved() const;

    /**
     * @brief Gets the original X-coordinate of the moved pawn.
     * @return The original X-coordinate.
     */
    int getOldX() const;

    /**
     * @brief Gets the original Y-coordinate of the moved pawn.
     * @return The original Y-coordinate.
     */
    int getOldY() const;

    /**
     * @brief Gets the pointer to the removed pawn (if any).
     * @return Pointer to the removed PawnModel, or nullptr if no pawn was removed.
     */
    PawnModel* getPawnRemoved() const;
};
