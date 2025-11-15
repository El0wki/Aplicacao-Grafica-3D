#include "lights.h"

LightsManager::LightsManager() {
    createDefaultLights();
}

void LightsManager::createDefaultLights() {
    lights.clear();
    LightSource sun;
    // Posição lateral (esquerda/acima/frente)
    sun.position[0] = -3.0f;  // X: esquerda
    sun.position[1] = 2.0f;   // Y: acima
    sun.position[2] = 2.0f;   // Z: frente
    sun.position[3] = 1.0f;   // luz pontual

    // Cor intensa
    sun.color[0] = 2.0f; sun.color[1] = 2.0f; sun.color[2] = 2.0f; sun.color[3] = 1.0f;

    // Direção para o centro da cena (direita/baixo/trás)
    sun.spotDirection[0] = 1.0f;  // X: para direita
    sun.spotDirection[1] = -1.0f; // Y: para baixo
    sun.spotDirection[2] = -1.0f; // Z: para trás

    // Cone dramático
    sun.spotCutoff = 20.0f;

    lights.push_back(sun);
}

const std::vector<LightSource>& LightsManager::getLights() const {
    return lights;
}