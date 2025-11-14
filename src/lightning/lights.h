#ifndef LIGHTS_H
#define LIGHTS_H

#include <vector>

// Definição da struct da luz
struct LightSource {
    float position[4];
    float color[4];
};

std::vector<LightSource> createSceneLights();

#endif 