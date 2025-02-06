#pragma once
#include <glm/glm.hpp>
#include <vector>

class Lighting {
public:
    // Tipi di luce supportati
    enum class LightType {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    // Struttura per definire una singola luce
    struct Light {
        LightType type;
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 color;
        float intensity;
        float cutOff;
    };

    Lighting();
    ~Lighting();

    void addLight(const Light& light);
    void removeLight(int index);
    const std::vector<Light>& getLights() const;

private:
    std::vector<Light> lights; // Lista delle luci attualmente nella scena
};