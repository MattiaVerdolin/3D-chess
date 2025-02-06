/**
 * @file	pieceModel.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once
#include "mesh.h"
#include <iostream>

/**
 * @class PieceModel
 * @brief Abstract base class for representing a chess piece in the game.
 */
class PieceModel {
protected:
    unsigned int posX; /**< The X-coordinate of the piece on the chessboard. */
    unsigned int posY; /**< The Y-coordinate of the piece on the chessboard. */
    Mesh* mesh;        /**< Pointer to the Mesh representing the piece in the 3D scene. */

    /**
     * @brief Constructs a PieceModel with the specified position and mesh.
     * @param x The initial X-coordinate of the piece.
     * @param y The initial Y-coordinate of the piece.
     * @param meshPtr Pointer to the Mesh representing the piece in the 3D scene.
     */
    PieceModel(unsigned int x, unsigned int y, Mesh* meshPtr);

public:
    /**
     * @brief Copy constructor for PieceModel.
     * @param other The PieceModel instance to copy from.
     */
    PieceModel(const PieceModel& other);

    /**
     * @brief Virtual destructor for PieceModel.
     */
    virtual ~PieceModel();

    /**
     * @brief Default constructor for PieceModel.
     */
    PieceModel() = default;

    /**
     * @brief Gets the X-coordinate of the piece on the chessboard.
     * @return The X-coordinate.
     */
    unsigned int getPosX() const;

    /**
     * @brief Gets the Y-coordinate of the piece on the chessboard.
     * @return The Y-coordinate.
     */
    unsigned int getPosY() const;

    /**
     * @brief Gets the Mesh associated with the piece.
     * @return Pointer to the Mesh.
     */
    Mesh* getMesh() const;

    /**
     * @brief Sets the X-coordinate of the piece on the chessboard.
     * @param x The new X-coordinate.
     */
    void setPosX(unsigned int x);

    /**
     * @brief Sets the Y-coordinate of the piece on the chessboard.
     * @param y The new Y-coordinate.
     */
    void setPosY(unsigned int y);

    /**
     * @brief Sets the Mesh associated with the piece.
     * @param newMesh Pointer to the new Mesh.
     */
    void setMesh(Mesh* newMesh);

    /**
     * @brief Updates the piece's position and applies transformations in the 3D scene.
     * @param newPosX The new X-coordinate of the piece.
     * @param newPosY The new Y-coordinate of the piece.
     * @param offset The size of each cell on the chessboard.
     * @note This is a pure virtual method that must be implemented by derived classes.
     */
    virtual void update(unsigned int newPosX, unsigned int newPosY, float offset) = 0;
};
