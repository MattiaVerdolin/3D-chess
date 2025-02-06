/**
 * @file	engine.h
 * @brief	Graphics engine
 *
 * @author	Alessandro Cantoni (C) SUPSI [alessandro.cantoni@student.supsi.ch]
 * @author	Francesco Fasola (C) SUPSI [francesco.fasola@student.supsi.ch]
 * @author	Mattia Verdolin (C) SUPSI [mattia.verdolin@student.supsi.ch]
 */

#pragma once

#include "node.h"
#include "mesh.h"
#include "camera.h"
#include "list.h"
#include "light.h"
#include "material.h"
#include "texture.h"
#include <chrono> 

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// C/C++:         
#include <memory>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

/**
 * @brief Base engine main class. This class is a singleton.
 */
class ENG_API MVsio final {

private:
    // Membri per la scena:
    int windowId = 0;
    bool engineInitialized = false;
    Node* rootNode = nullptr;       // Nodo radice della scena
    Camera* currentCamera = nullptr; // Camera attuale
    std::vector<Camera*> cameras = {}; // Vettore di camere
    List nodeList;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    int frameCount;
    float fps;

    // Const/dest:
    MVsio(); // Costruttore privato per Singleton
    ~MVsio(); // Assicurati di liberare risorse

    // openGL:
    bool initOpenGL();

    // freeGlut:
    bool initFreeGlut(int argc, char* argv[]);
    // callbacks functions:
    static void displayCallback();
    static void reshapeCallback(int width, int height);

public:
    // Operators:
    void operator=(MVsio const&) = delete;

    // Singleton:
    static MVsio& getInstance();

    // main functions:
    bool init(int argc, char* argv[]);
    bool load(std::string path);
    void renderScene();
    bool swapAndLoop();
    bool free();

    void postWindowRedisplay();
    void setKeyboardCallback(void (*callback)(unsigned char, int, int));
    static void specialCallback(int key, int x, int y);
    static void idleCallback();

    List getList() const;

    void switchCamera();

    static void renderText(const char* text, float x, float y);
};

