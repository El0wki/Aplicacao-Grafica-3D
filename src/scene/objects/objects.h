#ifndef OBJECTS_H
#define OBJECTS_H


#include "../core/state.h"

class AnimationsManager; // Forward declaration
class TexturesManager;   // Forward declaration

class ObjectsManager {
public:
	ObjectsManager(SceneState& state, AnimationsManager* animMgr, TexturesManager* texMgr);
	void desenharChao();
	void desenharCubo();
	void desenharCone();
	void desenharBola();
private:
	SceneState& sceneState;
	AnimationsManager* animationsManager;
	TexturesManager* texturesManager;
};

#endif 