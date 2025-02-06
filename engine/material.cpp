#include "material.h"

// FreeGLUT
#include <GL/freeglut.h>
#include "iostream"

Material::Material(
    const glm::vec4& ambient,
    const glm::vec4& diffuse,
    const glm::vec4& specular,
    const glm::vec4& emissive,
    float shininessVal,
    Texture* tex)
    :
    ambientColor(ambient),
    diffuseColor(diffuse),
    specularColor(specular),
    emissiveColor(emissive),
    shininess(shininessVal),
    texture(tex) {
}

Texture* Material::getTex() const {
    return texture;
}

void Material::render(const glm::mat4& finalMatrix) {

    glMatrixMode(GL_MODELVIEW);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &ambientColor[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &diffuseColor[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &specularColor[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &emissiveColor[0]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    if (texture) {
        texture->render(glm::mat4(0.1f));
    }
    else {
        glDisable(GL_TEXTURE_2D);
    }
}

const glm::vec4& Material::getAmbientColor() const {
    return ambientColor;
}

void Material::setAmbientColor(const glm::vec4& color) {
    ambientColor = color;
}

const glm::vec4& Material::getDiffuseColor() const {
    return diffuseColor;
}

void Material::setDiffuseColor(const glm::vec4& color) {
    diffuseColor = color;
}

const glm::vec4& Material::getSpecularColor() const {
    return specularColor;
}

void Material::setSpecularColor(const glm::vec4& color) {
    specularColor = color;
}

const glm::vec4& Material::getEmissiveColor() const {
    return emissiveColor;
}

void Material::setEmissiveColor(const glm::vec4& color) {
    emissiveColor = color;
}

float Material::getShininess() const {
    return shininess;
}

void Material::setShininess(float shininessVal) {
    shininess = shininessVal;
}

Texture* Material::getTexture() const {
    return texture;
}

void Material::setTexture(Texture* tex) {
    texture = tex;
}
