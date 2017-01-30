#pragma once

#include "GameObject.h"

class Cloud : public GameObject
{
private:

public:
	Cloud(ALLEGRO_BITMAP *image);
	void Destroy();

	void Update(double cameraX, double cameraY);
	void Render();
};