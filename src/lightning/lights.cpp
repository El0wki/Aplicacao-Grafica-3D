#include "lights.h" 

std::vector<LightSource> createSceneLights() {
    std::vector<LightSource> lights;

    LightSource sun;
    sun.position[0] = 0.0f;  sun.position[1] = 3.0f; sun.position[2] = 0.0f; sun.position[3] = 1.0f; // Pontual
    sun.color[0] = 1.0f;   sun.color[1] = 1.0f;   sun.color[2] = 1.0f;  sun.color[3] = 1.0f;
    lights.push_back(sun);

    return lights;
}