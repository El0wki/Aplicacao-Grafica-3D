#ifndef CONTROLS_H
#define CONTROLS_H


#include "state.h"

class Controls {
public:
	Controls(SceneState& state);
	void teclado(unsigned char key, int x, int y);
	void mouseMove(int x, int y);
private:
	SceneState& sceneState;
};

#endif