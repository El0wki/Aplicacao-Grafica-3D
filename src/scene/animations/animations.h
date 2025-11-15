#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "../core/state.h"

class AnimationsManager {
public:
    AnimationsManager(SceneState& state);
    void animarBola();
    void animarPendulo();
private:
    SceneState& sceneState;
};

#endif