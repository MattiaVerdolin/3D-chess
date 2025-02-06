/**
 * @file	selectorModel.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include <glm/glm.hpp>
#include "pieceModel.h"

/**
 * @class SelectorModel
 * @brief Represents the selector used to highlight and navigate cells on the chessboard.
 * Inherits from PieceModel.
 */
class SelectorModel : public PieceModel {
public:
    /**
     * @brief Constructs a new SelectorModel with the specified position and mesh.
     * @param x The initial X-coordinate of the selector.
     * @param y The initial Y-coordinate of the selector.
     * @param meshPtr Pointer to the Mesh representing the selector in the 3D scene.
     */
    SelectorModel(unsigned int x, unsigned int y, Mesh* meshPtr);

    /**
     * @brief Changes the position of the selector based on the specified direction.
     * @param direction The direction to move the selector:
     * - 1: Up
     * - 2: Right
     * - 3: Left
     * - 4: Down
     * @param offset The size of each cell on the chessboard.
     */
    void changePosition(int direction, float offset);

    /**
     * @brief Updates the selector's position on the chessboard and applies transformations in the 3D scene.
     * @param newPosX The new X-coordinate of the selector.
     * @param newPosY The new Y-coordinate of the selector.
     * @param offset The size of each cell on the chessboard.
     */
    void update(unsigned int newPosX, unsigned int newPosY, float offset) override;
};
