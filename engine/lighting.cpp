#include "Lighting.h"

// Costruttore
Lighting::Lighting() {}

// Distruttore
Lighting::~Lighting() {}

// Aggiunge una nuova luce
void Lighting::addLight(const Light& light) {
    lights.push_back(light);
}

// Rimuove una luce tramite indice
void Lighting::removeLight(int index) {
    if (index >= 0 && index < lights.size()) {
        lights.erase(lights.begin() + index);
    }
}

// Restituisce tutte le luci
const std::vector<Lighting::Light>& Lighting::getLights() const {
    return lights;
}
