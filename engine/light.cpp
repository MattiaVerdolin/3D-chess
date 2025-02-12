#include "light.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>

using namespace Lighting;

// Light Base Class
Light::Light(int id, const std::string& name, Node* parent, glm::mat4 localMatrix, LightType type,
    const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, float intensity)

    : Node(name, {}, parent, localMatrix), type(type), ambient(ambient), diffuse(diffuse),
    specular(specular) {

    setAttenuation(1.0f, 0.0f, 0.0f);
    setIntensity(intensity);

    if (id < 7) { //id allowed from 0 to 6
        this->lightNumber = GL_LIGHT0 + id;
        glEnable(lightNumber);
    }
	else
    {
	    std::cout << "number of lights higher than 7 \n";
    }
}


void Light::toggle() {
    if (isEnabled) {
        glDisable(lightNumber);
    }
    else {
        glEnable(lightNumber);
    }
    isEnabled = !isEnabled;
}


Light::~Light() {
    glDisable(lightNumber);
}

void Light::render(const glm::mat4& matrix) {
    glLoadMatrixf(glm::value_ptr(matrix));

    glLightfv(lightNumber, GL_AMBIENT, glm::value_ptr(ambient));
    glLightfv(lightNumber, GL_DIFFUSE, glm::value_ptr(diffuse * intensity));
    glLightfv(lightNumber, GL_SPECULAR, glm::value_ptr(specular));

    glLightfv(lightNumber, GL_CONSTANT_ATTENUATION, &constantAttenuation);
    glLightfv(lightNumber, GL_LINEAR_ATTENUATION, &linearAttenuation);
    glLightfv(lightNumber, GL_QUADRATIC_ATTENUATION, &quadraticAttenuation);

    glLightfv(lightNumber, GL_POSITION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, worldMatrix[3].w)));
}

void Light::setAttenuation(float constant, float linear, float quadratic) {
    constantAttenuation = constant;
    linearAttenuation = linear;
    quadraticAttenuation = quadratic;
}

void Light::setIntensity(float intensity) {
    this->intensity = intensity;
}

LightType Light::getType() const {
    return type;
}

glm::vec4 Lighting::Light::getAmbient() const {
    return ambient;
}

glm::vec4 Lighting::Light::getDiffuse() const {
    return diffuse;
}

glm::vec4 Lighting::Light::getSpecular() const {
    return specular;
}

// DirectionalLight
DirectionalLight::DirectionalLight(int id, const std::string& name, Node* parent, glm::mat4 localMatrix,
    const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular,
    const glm::vec3& direction)

    : Light(id, name, parent, localMatrix, LightType::DIRECTIONAL, ambient, diffuse, specular, 1.0f),
    direction(direction) {}

void DirectionalLight::setDirection(const glm::vec3& direction) {
    this->direction = direction;
}

void DirectionalLight::render(const glm::mat4& matrix) {
    Light::render(matrix);
}


// OmniLight
OmniLight::OmniLight(int id, const std::string& name, Node* parent, glm::mat4 localMatrix,
    const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular)

    : Light(id, name, parent, localMatrix, LightType::OMNI, ambient, diffuse, specular, 10.0f)
{}

void OmniLight::render(const glm::mat4& matrix) {
    glLightf(lightNumber, GL_SPOT_CUTOFF, 180);

    Light::render(matrix);
}


// SpotLight
SpotLight::SpotLight(int id, const std::string& name, Node* parent, glm::mat4 localMatrix,
    const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular,
    const glm::vec3& direction, float cutoff, float exponent)

    : Light(id, name, parent, localMatrix, LightType::SPOT, ambient, diffuse, specular, 2.0f),
    direction(direction), cutoff(cutoff), exponent(exponent) {}

void SpotLight::setDirection(const glm::vec3& direction) {
    this->direction = direction;
}

void SpotLight::setCutoff(float cutoff) {
    this->cutoff = cutoff;
}

void SpotLight::render(const glm::mat4& matrix) {
    glLightfv(lightNumber, GL_SPOT_DIRECTION, glm::value_ptr(glm::vec4(direction, 1.0f)));
    glLightf(lightNumber, GL_SPOT_CUTOFF, cutoff);
    glLightf(lightNumber, GL_SPOT_EXPONENT, exponent);
    
    Light::render(matrix);
}
