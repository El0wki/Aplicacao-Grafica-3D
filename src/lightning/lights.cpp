#include "lights.h" 

std::vector<LightSource> createSceneLights() {
    std::vector<LightSource> lights;

    LightSource sun;
    sun.position[0] = 5.0f;  sun.position[1] = 10.0f; sun.position[2] = 5.0f;  sun.position[3] = 0.0f; // w=0 -> Direcional
    sun.color[0] = 0.3f;   sun.color[1] = 0.4f;   sun.color[2] = 0.1f;  sun.color[3] = 1.0f;
    lights.push_back(sun);
/*
    // Luz 2: Luz pontual vermelha perto da casa
    LightSource redLight;
    redLight.position[0] = 1.0f; redLight.position[1] = 1.0f; redLight.position[2] = 2.0f; redLight.position[3] = 1.0f; // w=1 -> Pontual
    redLight.color[0] = 1.0f;  redLight.color[1] = 0.2f;  redLight.color[2] = 0.2f; redLight.color[3] = 1.0f;
    lights.push_back(redLight);

    // Luz 3: Luz pontual azul do outro lado
    LightSource blueLight;
    blueLight.position[0] = -3.0f; blueLight.position[1] = 2.0f; blueLight.position[2] = 3.0f; blueLight.position[3] = 1.0f; // w=1 -> Pontual
    blueLight.color[0] = 0.2f;   blueLight.color[1] = 0.2f;   blueLight.color[2] = 1.0f;  blueLight.color[3] = 1.0f;
    lights.push_back(blueLight);
*/
    return lights;
}