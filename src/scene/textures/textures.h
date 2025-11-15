#ifndef TEXTURES_H
#define TEXTURES_H


#include "../core/state.h"

class TexturesManager {
public:
	TexturesManager(SceneState& state);
	void gerarTexturaChao();
	void gerarTexturaTijolo();
private:
	SceneState& sceneState;
};

#endif // TEXTURES_H