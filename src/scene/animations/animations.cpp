#include "animations.h"
#include <cmath>

AnimationsManager::AnimationsManager(SceneState& state) : sceneState(state) {}

void AnimationsManager::animarBola() {
    if (sceneState.ball.isAnimating) {
        sceneState.ball.z += 0.03f;
        sceneState.ball.rotation += 10.0f;
        if (sceneState.ball.z > 2.0f) {
            sceneState.ball.z = -2.0f;
            sceneState.ball.rotation = 0;
        }
    }
}

void AnimationsManager::animarPendulo() {
    if (sceneState.pendulo.isAnimating) {
        sceneState.pendulo.tempo += 0.05f; // Incrementa o tempo
        sceneState.pendulo.rotation = sceneState.pendulo.amplitude * sin(sceneState.pendulo.velocidadeAngular * sceneState.pendulo.tempo);
    }
}
