
#include <iostream>

//TEST INCLUDE
#include "testCamera.h"
#include "keyValueStackTest.h"
#include "lightTest.h"
#include "listTest.h"
#include "materialTest.h"
#include "meshTest.h"
#include "vertexTest.h"
#include "nodeTest.h"
#include "textureTest.h"

//MANCANO DA TESTARE ENGINE, READDATA E OVOREADER

int main()
{
    std::cout << "Testing Camera...!" << std::endl;;
    testCameraInitialization();
    testPerspectiveProjection();
    testCameraMatrix();
    testCameraTranslate();
    testCameraActivation();

    std::cout << "__________________________________________________________________________________" << std::endl;

    std::cout << "Testing KeyValueStack..." << std::endl;
    testPushAndEmpty();
    testFirstId();
    testDecrementValue();

    std::cout << "__________________________________________________________________________________" << std::endl;

    std::cout << "Testing Light..." << std::endl;
    testLightBaseClass();
    testDirectionalLight();
    testOmniLight();
    testSpotLight();

    std::cout << "__________________________________________________________________________________" << std::endl;

    std::cout << "Testing List class..." << std::endl;
    testPrintHierarchy();
    testPass();
    testRenderList();
    testAddElement();
    testRemoveElementByName();
    testRemoveElementByID();
    testGetElementByID();
    testGetElementByName();

    std::cout << "__________________________________________________________________________________" << std::endl;

    std::cout << "Running Material tests..." << std::endl;
    testConstructorAndGetters();
    testSetters();
    testRenderWithoutTexture();
    testRenderWithTexture();

    std::cout << "__________________________________________________________________________________" << std::endl;

    std::cout << "Running Mesh tests..." << std::endl;
    testConstructorAndMaterialGetter();
    testMaterialSetter();
    testAddVertex();
    testGetVertices();
    testRenderMesh();

    std::cout << "__________________________________________________________________________________" << std::endl;

    std::cout << "Running Node tests..." << std::endl;
    testConstructorAndGettersNode();
    testAddAndRemoveChild();
    testFindByName();
    testFindByID();
    testWorldMatrix();

    std::cout << "__________________________________________________________________________________" << std::endl;


    std::cout << "Running Texture tests..." << std::endl;
    testCreateTexture();
    testRenderTex();
    testRelease();
    testSetName();


    std::cout << "__________________________________________________________________________________" << std::endl;

    std::cout << "Running Vertex tests..." << std::endl;
    testVertexConstructorAndGetters();
    testSetTextureCoordinates();

    std::cout << "__________________________________________________________________________________" << std::endl;

    return 0;
}