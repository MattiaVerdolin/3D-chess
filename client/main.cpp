/**
 * @file	main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

//////////////
// #INCLUDE //
//////////////

   // Library header:
	#include "engine.h"
	#include "gameController.h"
  

	// C/C++:
	#include <iostream>
	#include <glm/glm.hpp>


//////////
// MAIN //
//////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char* argv[])
{
	// Credits:
	std::cout << "Chessboard - SUPSI Graphics Course Project (a.a. 2024/25)" << '\n' <<
		"A. Cantoni (C) SUPSI - alessandro.cantoni@student.supsi.ch" << '\n' <<
		"F. Fasola (C) SUPSI - francesco.fasola@student.supsi.ch" << '\n' <<
		"M. Verdolin (C) SUPSI - mattia.verdolin@student.supsi.ch" << '\n' << '\n';

	std::string scenePath;

	// Check for valid command-line arguments:
	if (argc < 2) {
		scenePath = "../resources/Roomfinal.ovo";
	}
	else {
		scenePath = argv[1];
	}

	MVsio& eng = MVsio::getInstance();
	GameController& gameController = GameController::getInstance();

	// Init engine:
	eng.init(argc, argv);

	if (eng.load(scenePath)) { // se caricamento andato a buon fine -> render

		eng.renderScene();
		gameController.init();

		eng.swapAndLoop();

	}
	else {
		std::cerr << "Failed to load scene file: " << scenePath << '\n';
	}

	// Release engine:
	eng.free();

	// Done:
	std::cout << "\n[application terminated]" << '\n';
	return 0;
}