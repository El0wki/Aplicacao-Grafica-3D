#include "animations.h"

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
