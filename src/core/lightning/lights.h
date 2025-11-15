#ifndef LIGHTS_H
#define LIGHTS_H

#include "../core/state.h"
#include <vector>

class LightsManager {
public:
	LightsManager();
	const std::vector<LightSource>& getLights() const;
private:
	std::vector<LightSource> lights;
	void createDefaultLights();
};

#endif