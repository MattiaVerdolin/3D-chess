#include "shadow.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/freeglut.h>

Shadow::Shadow(Mesh* mesh)
    : Node("ShadowOf" + mesh->getName()), meshToShadow(mesh) {}

Shadow::~Shadow() {
    // Libera la memoria dei vertici proiettati
    for (Vertex* v : vertices) {
        delete v;
    }
    vertices.clear(); // Pulisce il vettore

    delete meshToShadow;
    meshToShadow = nullptr;
}


void Shadow::render(const glm::mat4& finalMatrix) {
    // Enable blending for translucent shadows
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Use stencil buffer to avoid shadows overlapping objects
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_EQUAL, 0, 0xFF); // Draw only where stencil is 0

    // Configure material for shadow
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

    // Dynamically project vertices on the ground plane
    glBegin(GL_TRIANGLES);
    float deepestPoint = getDeepestPoint();
    for (Vertex* v : meshToShadow->getVertices(0)) {
        glm::vec3 position = v->getPosition();
        position.y = deepestPoint + 0.1f;

        glNormal3fv(glm::value_ptr(v->getNormal()));
        glVertex3fv(glm::value_ptr(position));
    }
    glEnd();

    // Disable stencil test
    glDisable(GL_STENCIL_TEST);

    // Disable blending
    glDisable(GL_BLEND);
}

float Shadow::getDeepestPoint() {
    const auto& vertices = meshToShadow->getVertices(0);
    float deepestPoint = vertices.at(0)->getPosition().y;
    for (const Vertex* v : vertices) {
        if (v->getPosition().y < deepestPoint)
            deepestPoint = v->getPosition().y;
    }
    return deepestPoint;
}
