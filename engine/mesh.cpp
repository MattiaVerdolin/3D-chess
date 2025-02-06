#include "mesh.h"
#include "shadow.h"

// FreeGLUT
#include <GL/freeglut.h>

// C++
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Mesh::Mesh(const std::string& name, Node* parent, glm::mat4 localMatrix, Material* mat)
    : Node(name, {}, parent, localMatrix) {
    setName(name);
    material = mat;
}

void Mesh::setMaterial(Material* material) {
    this->material = material;
}

Material* Mesh::getMaterial() const {
    return material;
}

void Mesh::addVertex(Vertex* v, int lod) {
    if (vertices.size() <= lod) {
        std::vector<Vertex*> tempVec;
        tempVec.push_back(v);
        vertices.push_back(tempVec);
    }
    else {
        vertices.at(lod).push_back(v);
    }
}

std::vector<Vertex*> Mesh::getVertices(int lod) const {
    return vertices.at(lod);
}

void Mesh::setRender(bool cond) {
    toRender = cond;

    for (Node* child : children) {
        if (dynamic_cast<Shadow*>(child) != nullptr) {
            child->setToRender(cond);
        }
    }
}

void Mesh::translation(glm::vec3 translation) {
    worldMatrix =glm::translate(worldMatrix, translation);
}

void Mesh::render(const glm::mat4& finalMatrix) {
    if (material) {
        material->render(finalMatrix);
    }
    else {
        std::cout << "Nessun materiale associato alla mesh: " << getName() << std::endl;
    }

    // Load the final matrix into OpenGL
    glMatrixMode(GL_MODELVIEW);

    glLoadMatrixf(glm::value_ptr(finalMatrix));

    glBegin(GL_TRIANGLES);
    for (Vertex* v : vertices.at(lod)) {
        glNormal3fv(glm::value_ptr(v->getNormal()));
        glTexCoord2fv(glm::value_ptr(v->getTextureCoordinates()));
        glVertex3fv(glm::value_ptr(v->getPosition()));
    }
    glEnd();
}
