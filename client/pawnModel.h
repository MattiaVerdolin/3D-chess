/**
 * @file	pawnModel.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "pieceModel.h"

/**
 * @class PawnModel
 * @brief Represents a chess pawn in the game, inheriting from PieceModel.
 */
class PawnModel : public PieceModel {
public:
    /**
     * @brief Constructs a new PawnModel object.
     * @param x The initial X-coordinate of the pawn.
     * @param y The initial Y-coordinate of the pawn.
     * @param meshPtr Pointer to the Mesh representing the pawn in the 3D scene.
     */
    PawnModel(unsigned int x, unsigned int y, Mesh* meshPtr);

    /**
     * @brief Retrieves the unique identifier of the pawn.
     * @return The ID of the pawn as an unsigned integer.
     */
    unsigned int getPawnId() const;

    /**
     * @brief Updates the pawn's position on the board and in the 3D scene.
     * @param newPosX The new X-coordinate of the pawn.
     * @param newPosY The new Y-coordinate of the pawn.
     * @param offset The size of each cell on the chessboard.
     */
    void update(unsigned int newPosX, unsigned int newPosY, float offset) override;
};
