#pragma once

#include "GameObject.h"

class Background : public GameObject
{
private:

public:
	Background(ALLEGRO_BITMAP *image);
	void Destroy();

	void Update(double cameraX, double cameraY);
	void Render();
};