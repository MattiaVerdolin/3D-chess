#include "readData.h"
#include <string>
#include <cstring>
#include <stdexcept> 
#include <iostream>

using namespace Lighting;


Node* ReadData::readNode(char* data, unsigned int position) {
    std::string nodeName(data + position);
    position += static_cast<unsigned int>(nodeName.length()) + 1;

    glm::mat4 matrix;
    memcpy(&matrix, data + position, sizeof(glm::mat4));
    position += sizeof(glm::mat4);

    unsigned int children;
    memcpy(&children, data + position, sizeof(unsigned int));
    position += sizeof(unsigned int);

    Node* node = new Node(nodeName, {}, nullptr, matrix);
    node->setnumChildren(children);
    return node;
}


Material* ReadData::readMaterial(char* data, unsigned int position) {
    Material* material = new Material();

    std::string materialName(data + position);
    position += static_cast<unsigned int>(materialName.length()) + 1;
    material->setName(materialName);

    glm::vec4 emission, albedo;
    memcpy(&emission, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);
    material->setEmissiveColor(emission);

    memcpy(&albedo, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    float roughness;
    memcpy(&roughness, data + position, sizeof(float));
    position += sizeof(float);

    float metalness;
    memcpy(&metalness, data + position, sizeof(float));
    position += sizeof(float);

    float alpha;
    memcpy(&alpha, data + position, sizeof(float));
    position += sizeof(float);

    std::string textureName(data + position);
    position += static_cast<unsigned int>(textureName.length()) + 1;

    material->setAmbientColor(albedo * 0.2f);
    material->setDiffuseColor(albedo * 0.6f);
    material->setSpecularColor(albedo * 0.4f);
    material->setShininess((1 - sqrt(roughness)) * 128);

    Texture* texture = new Texture(textureName);

    if (textureName != "[none]") {
        std::string texturePath = "../textures/" + textureName;
        texture->createTexture(texturePath.c_str());
    }

    material->setTexture(texture);

    std::string normalMapName(data + position);
    position += static_cast<unsigned int>(normalMapName.length()) + 1;

    std::string heightMapName(data + position);
    position += static_cast<unsigned int>(heightMapName.length()) + 1;

    std::string roughnessMapName(data + position);
    position += static_cast<unsigned int>(roughnessMapName.length()) + 1;

    std::string metalnessMapName(data + position);
    position += static_cast<unsigned int>(metalnessMapName.length()) + 1;

    return material;
}

Mesh* ReadData::readMesh(char* data, unsigned int& position, const std::vector<Material*>& materials) {
    std::string meshName(data + position);
    position += static_cast<unsigned int>(meshName.length()) + 1;

    glm::mat4 localMatrix;
    memcpy(&localMatrix, data + position, sizeof(glm::mat4));
    position += sizeof(glm::mat4);

    Mesh* mesh = new Mesh(meshName, nullptr, localMatrix, nullptr);

    unsigned int childrenCount;
    memcpy(&childrenCount, data + position, sizeof(unsigned int));
    position += sizeof(unsigned int);
    mesh->setnumChildren(childrenCount);

    std::string targetName(data + position);
    position += static_cast<unsigned int>(targetName.length()) + 1;

    unsigned char subtype;
    memcpy(&subtype, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

    std::string materialName(data + position);
    position += static_cast<unsigned int>(materialName.length()) + 1;

    Material* associatedMaterial = nullptr;
    for (const auto& material : materials) {
        if (material->getName() == materialName) {
            associatedMaterial = material;
            break;
        }
    }
    mesh->setMaterial(associatedMaterial);

    float radius;
    memcpy(&radius, data + position, sizeof(float));
    position += sizeof(float);

    glm::vec3 bBoxMin;
    memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    position += sizeof(glm::vec3);

    unsigned char hasPhysics;
    memcpy(&hasPhysics, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

    if (hasPhysics) {
        struct PhysProps {
            unsigned char type;
            unsigned char contCollisionDetection;
            unsigned char collideWithRBodies;
            unsigned char hullType;
            glm::vec3 massCenter;
            float mass;
            float staticFriction;
            float dynamicFriction;
            float bounciness;
            float linearDamping;
            float angularDamping;
            unsigned int nrOfHulls;
            unsigned int _pad;
            void* physObj;
            void* hull;
        };

        PhysProps mp;
        memcpy(&mp, data + position, sizeof(PhysProps));
        position += sizeof(PhysProps);

        if (mp.nrOfHulls) {
            for (unsigned int c = 0; c < mp.nrOfHulls; c++) {
                unsigned int nrOfVertices;
                memcpy(&nrOfVertices, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);

                unsigned int nrOfFaces;
                memcpy(&nrOfFaces, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);

                position += sizeof(glm::vec3);

                for (unsigned int c = 0; c < nrOfVertices; c++) {
                    position += sizeof(glm::vec3);
                }

                for (unsigned int c = 0; c < nrOfFaces; c++) {
                    position += sizeof(unsigned int) * 3;
                }
            }
        }
    }

    unsigned int LODs;
    memcpy(&LODs, data + position, sizeof(unsigned int));
    position += sizeof(unsigned int);

    for (unsigned int l = 0; l < LODs; l++) {
        unsigned int vertices, faces;
        memcpy(&vertices, data + position, sizeof(unsigned int));
        position += sizeof(unsigned int);

        memcpy(&faces, data + position, sizeof(unsigned int));
        position += sizeof(unsigned int);

        for (unsigned int c = 0; c < vertices; c++) {
            glm::vec3 vertex;
            memcpy(&vertex, data + position, sizeof(glm::vec3));
            position += sizeof(glm::vec3);

            unsigned int normalData, textureData, tangentData;
            memcpy(&normalData, data + position, sizeof(unsigned int));
            position += sizeof(unsigned int);

            memcpy(&textureData, data + position, sizeof(unsigned int));
            position += sizeof(unsigned int);

            memcpy(&tangentData, data + position, sizeof(unsigned int));
            position += sizeof(unsigned int);

            glm::vec4 normal = glm::unpackSnorm3x10_1x2(normalData);
            Vertex* newVertex = new Vertex(vertex, glm::vec3(normal.x, normal.y, normal.z));
            glm::vec2 uv = glm::unpackHalf2x16(textureData);
            newVertex->setTextureCoordinates(uv);
            tempVertices.push_back(newVertex);
        }

        for (unsigned int c = 0; c < faces; c++) {
            unsigned int face[3];
            memcpy(face, data + position, sizeof(unsigned int) * 3);
            position += sizeof(unsigned int) * 3;

            for (int i = 0; i < 3; i++) {
                mesh->addVertex(tempVertices.at(face[i]), l);
            }
        }

        tempVertices.clear();
    }

    return mesh;
}

Light* ReadData::readLight(char* data, unsigned int& position) {
    std::string lightName(data + position);
    position += static_cast<unsigned int>(lightName.length()) + 1;

    glm::mat4 matrix;
    memcpy(&matrix, data + position, sizeof(glm::mat4));
    position += sizeof(glm::mat4);

    unsigned int childrenCount;
    memcpy(&childrenCount, data + position, sizeof(unsigned int));
    position += sizeof(unsigned int);

    std::string targetName(data + position);
    position += static_cast<unsigned int>(targetName.length()) + 1;

    unsigned char subtype;
    memcpy(&subtype, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

    glm::vec3 color;
    memcpy(&color, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    float radius;
    memcpy(&radius, data + position, sizeof(float));
    position += sizeof(float);

    glm::vec3 direction;
    memcpy(&direction, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    float cutoff;
    memcpy(&cutoff, data + position, sizeof(float));
    position += sizeof(float);

    float spotExponent;
    memcpy(&spotExponent, data + position, sizeof(float));
    position += sizeof(float);

    unsigned char castShadows;
    memcpy(&castShadows, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

    unsigned char isVolumetric;
    memcpy(&isVolumetric, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

    glm::vec4 ambient = glm::vec4(color * 0.2f, 1.0f);
    glm::vec4 diffuse = glm::vec4(color, 1.0f);
    glm::vec4 specular = glm::vec4(1.0f);

    LightType type;
    Light* light = nullptr;

    switch (static_cast<LightType>(subtype)) {
    case LightType::DIRECTIONAL:

        light = new DirectionalLight(++lightId, lightName, nullptr, matrix, ambient, diffuse, 
                                        specular, direction);
        break;

    case LightType::OMNI:
        light = new OmniLight(++lightId, lightName, nullptr, matrix, ambient, diffuse,
            specular);

        break;

    case Lighting::LightType::SPOT:
        light = new SpotLight(++lightId, lightName, nullptr, matrix, ambient, diffuse,
            specular, direction, cutoff, spotExponent);

        break;

    default:
        std::cerr << "Unrecognized light type: " << static_cast<int>(subtype) << std::endl;
        return nullptr;
    }

    // Ritorna la luce letta
    return light;
}
