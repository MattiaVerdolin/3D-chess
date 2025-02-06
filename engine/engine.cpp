
// Main include:
#include "engine.h"
#include "ovoReader.h"

// C/C++:
#include <iostream>   
#include <source_location>

//FreeGLUT
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <FreeImage.h>

////////////////////////
// BODY OF CLASS Base //
////////////////////////

// Constructor
MVsio::MVsio() : frameCount(0), fps(0.0f)
{  
#ifdef _DEBUG   
   std::cout << "[+] Engine's constructor invoked" << std::endl;
#endif
   lastTime = std::chrono::high_resolution_clock::now();
   engineInitialized = true;
}

// Destructor
MVsio::~MVsio()
{
 free();

#ifdef _DEBUG
   std::cout << "[-] Engine's destructor invoked" << std::endl;
#endif
}


// Singleton instance
MVsio &MVsio::getInstance()
{
   static MVsio instance;
   return instance;
}

////////////////////
// Main functions //
////////////////////

bool MVsio::init(int argc, char* argv[])
{
    //inizializzazione FreeGlut
    initFreeGlut(argc, argv);

    // configurazione OpenGL
    initOpenGL();

    // Callback di Rendering
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutSpecialFunc(specialCallback);      // Per i tasti speciali (freccia)
    glutIdleFunc(MVsio::idleCallback);

    FreeImage_Initialise();

    return true;
}

bool MVsio::load(std::string path)
{
    OvoReader ovoReader = OvoReader::getInstance();
    Node* root = ovoReader.reader(path);

    if (root) {

        Camera* camera = new Camera("DynamicCamera", root, glm::mat4(1.0f));    
        Camera* upCamera = new Camera("UpCamera", root, glm::mat4(1.0f));

        //traslo la posizione della camera
        camera->translate(glm::vec3(-85.0, 78.0,70.0));
        camera->rotate(glm::vec3(0.0, -40.0, 0.0));
        camera->rotate(glm::vec3(-40.0, 0.0, 0.0));

        upCamera->translate(glm::vec3(-53.0, 32.0, 15.0));
        upCamera->rotate(glm::vec3(-90.0, 0.0, 0.0));

        // Aggiungi le camere al vettore
        cameras.push_back(camera);
        cameras.push_back(upCamera);

        // Imposta la prima camera come attiva
        currentCamera = cameras[0];


        nodeList.pass(root);
        rootNode = root;
        nodeList.printHierarchy();

        return true;
    }

    return false;
}

void MVsio::renderScene() {
    // Calcola le matrici di vista e proiezione della camera corrente
    if (currentCamera && rootNode) {
        glm::mat4 viewMatrix = currentCamera->getCameraMatrix();
        nodeList.render(viewMatrix);
    }
}

bool MVsio::swapAndLoop() {
    // Scambia i buffer per visualizzare il risultato
    glutSwapBuffers();
    glutMainLoop();

    return true;
}


bool ENG_API MVsio::free()
{
    // Non inizializzato?
    if (!engineInitialized) {
        return false;
    }

    if (rootNode) {
        delete rootNode;
        rootNode = nullptr;
    }

    if (!cameras.empty()) {
        cameras.clear();
        currentCamera = nullptr;
    }

    FreeImage_DeInitialise();

    std::cout << "[engine deinitialized]" << std::endl;
    engineInitialized = false;

    return true;
}

////////////
// OpenGL //
////////////

bool MVsio::initOpenGL()
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    // Pulizia del buffer colore e profondità
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

    glViewport(0, 0, 800, 600);

    return true;
}


//////////////
// FreeGlut //
//////////////

bool MVsio::initFreeGlut(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    windowId = glutCreateWindow("FreeGLUT Example - Engine Window");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    return true;
}

///////////////
// Callbacks //
///////////////

void MVsio::displayCallback() {
    // Ottieni l'istanza del singleton
    MVsio& engine = getInstance();

    // Pulisci i buffer colore e profondità
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Usa i metodi di istanza per il rendering
    if (engine.rootNode) {
        engine.renderScene();
    }

    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - engine.lastTime;
    engine.frameCount++;

    if (elapsedTime.count() >= 1.0f) {
        engine.fps = engine.frameCount / elapsedTime.count();
        engine.frameCount = 0;
        engine.lastTime = currentTime;
    }

    char fpsText[32];
    snprintf(fpsText, sizeof(fpsText), "FPS: %.2f", engine.fps);
    renderText(fpsText, 10.0f, 580.0f);

    glutSwapBuffers();
}


void MVsio::idleCallback() {
    glutPostRedisplay(); // Forza il ridisegno della scena
}


void MVsio::reshapeCallback(int width, int height) {
    // Ottieni l'istanza del singleton
    MVsio& engine = getInstance();

    if (height == 0) 
        height = 1; // Evita divisioni per zero

    // Aggiorna il viewport
    glViewport(0, 0, width, height);

    // Aggiorna la matrice di proiezione della camera
    if (engine.currentCamera) {
        // Calcola il nuovo rapporto d'aspetto
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        engine.currentCamera->setPerspective(60.0f, aspectRatio, 0.1f, 500.0f);
        //carico la nuova matrice di proiezione in openGL
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(engine.currentCamera->getProjectionMatrix()));
        glMatrixMode(GL_MODELVIEW);
    }

    // Forza un ridisegno dopo il ridimensionamento
    glutPostRedisplay();
}

void MVsio::postWindowRedisplay() {
    // Force rendering refresh
    glutPostWindowRedisplay(windowId);
}

void MVsio::setKeyboardCallback(void (*func)(unsigned char, int, int)) {
    glutKeyboardFunc(func);
}

void MVsio::specialCallback(int key, int x, int y) {
    MVsio& engine = getInstance();

    if (engine.currentCamera->getName() == "DynamicCamera") {
        // Ottieni la matrice di trasformazione globale della fotocamera
        glm::mat4 transform = engine.currentCamera->getLocalMatrix();
        glm::vec3 position = glm::vec3(transform[3]); // Estrai la posizione della fotocamera
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);   // Verso "alto" globale
        glm::vec3 forward = glm::normalize(-glm::vec3(transform[2])); // Direzione in avanti
        glm::vec3 right = glm::normalize(glm::cross(forward, up));    // Direzione destra globale

        float speed = 8.0f;

        // Applica rotazioni relative agli assi globali
        switch (key) {
        case GLUT_KEY_UP:
            transform = glm::rotate(glm::mat4(1.0f), glm::radians(speed), right) * transform;
            break;
        case GLUT_KEY_DOWN:
            transform = glm::rotate(glm::mat4(1.0f), glm::radians(-speed), right) * transform;
            break;
        case GLUT_KEY_LEFT:
            transform = glm::rotate(glm::mat4(1.0f), glm::radians(speed), up) * transform;
            break;
        case GLUT_KEY_RIGHT:
            transform = glm::rotate(glm::mat4(1.0f), glm::radians(-speed), up) * transform;
            break;
        default:
            return;
        }

        // Reimposta la posizione originale per evitare che venga alterata dalle rotazioni
        transform[3] = glm::vec4(position, 1.0f);

        // Aggiorna la matrice locale della fotocamera
        engine.currentCamera->setLocalMatrix(transform);

        // Forza il rendering di un nuovo frame
        glutPostWindowRedisplay(engine.windowId);
    }
}

void MVsio::switchCamera() {
        if (!currentCamera) {
            std::cerr << "Current camera is not set!" << std::endl;
            return;
        }

        // Trova l'indice della camera corrente nel vettore
        size_t currentIndex = -1;

        for (size_t i = 0; i < cameras.size(); ++i) {
            if (cameras[i] == currentCamera) {
                currentIndex = i;
                break;
            }
        }

        if (currentIndex == -1) {
            std::cerr << "Current camera not found in the cameras vector!" << std::endl;
            return;
        }

        size_t nextIndex = (currentIndex + 1) % cameras.size();

        // Disattiva la camera corrente
        currentCamera->setIsActive(false);

        // Attiva la nuova camera
        currentCamera = cameras[nextIndex];
        currentCamera->setIsActive(true);

        std::cout << "Switched to camera: " << currentCamera->getName() << std::endl;

        // Forza il rendering di un nuovo frame
        postWindowRedisplay();
}

List MVsio::getList() const {
    return nodeList;
}


void MVsio::renderText(const char* text, float x, float y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}