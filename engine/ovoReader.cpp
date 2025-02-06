#include "ovoReader.h"
#include "keyValueStack.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>


std::string OvoReader::extractPath(const std::string& fullPath) {
    size_t lastSlash = fullPath.find_last_of("/\\");
    if (lastSlash == std::string::npos) {
        return fullPath; // Return the original path if no separator is found
    }
    return fullPath.substr(0, lastSlash + 1);
}

void OvoReader::graph_creator(Node* node) {
    int parent_id = kvStack.firstId();

    if (parent_id > -1) {
        Node* parent = nodes[0]->findByID(parent_id);

        if (parent) {
            node->setParent(parent);
            parent->addChild(node);
        }

        kvStack.decrementValue(parent_id);
    }

    if (node->getnumChildren() > 0) {
        kvStack.push(node->getID(), node->getnumChildren());
    }

    nodes.push_back(node);
}


Node* OvoReader::reader(const std::string& paramFile) {
    // Open the file for reading
    std::ifstream dat(paramFile, std::ios::binary);
    if (!dat) {
        std::cerr << "ERROR: unable to open file '" << paramFile << "'" << std::endl;
        return nullptr;
    }

    // Extract the path for materials
    std::string pathMaterial = extractPath(paramFile);

    std::cout.precision(2);
    std::cout << std::fixed;

    unsigned int chunkId, chunkSize;
    while (dat.read(reinterpret_cast<char*>(&chunkId), sizeof(chunkId))) {
        dat.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));
        if (dat.eof() || chunkSize == 0) break;

        std::vector<char> data(chunkSize); // Use std::vector for safer buffer management
        if (!dat.read(data.data(), chunkSize)) {
            std::cerr << "ERROR: unable to read from file '" << paramFile << "'" << std::endl;
            return nullptr;
        }

        unsigned int versionId;
        unsigned int position = 0;

        switch (static_cast<OvoReader::Type>(chunkId)) {
        case OvoReader::Type::OBJECT:
            // Process an OBJECT chunk
            memcpy(&versionId, data.data() + position, sizeof(versionId));
            position += sizeof(versionId);
            break;

        case OvoReader::Type::NODE: {
            Node* node = dataReader.readNode(data.data(), position);
            graph_creator(node);
        } break;

        case OvoReader::Type::MATERIAL: {
            Material* material = dataReader.readMaterial(data.data(), position);
            materials.push_back(material);
        } break;

        case OvoReader::Type::MESH:
        case OvoReader::Type::SKINNED: {
            Mesh* mesh = dataReader.readMesh(data.data(), position, materials);
            graph_creator(mesh);

            Shadow* shadow = new Shadow(mesh);
            mesh->addChild(shadow);
        } break;

        case OvoReader::Type::LIGHT: {
            Lighting::Light* light = dataReader.readLight(data.data(), position);
            graph_creator(light);
        } break;

        default:
            // Handle unknown chunk types
            std::cerr << "[UNKNOWN]" << std::endl;
            std::cerr << "ERROR: corrupted or bad data in file '" << paramFile << "'" << std::endl;
            return nullptr;
        }
    }

    return nodes[0];
}
