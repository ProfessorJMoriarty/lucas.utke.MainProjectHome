#pragma once
#include "Units.h"
#include <iostream>
using namespace std;

class Gun : public Units//inheritance
{
private:
	int TimeUp;
	int health;
	//int animationRow;
	double MouseAngle;
	//protected:
	//bool ifPursue;//this is what protected does!

public:
	Gun();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y, int image_size_x, int image_size_y, double MouseAngle);
	void Update(double cameraX, double cameraY);
	void Render();

	int GetHealth() { return health; }

	void TakeDamage() { health--; }

	void LogicFunc();
};