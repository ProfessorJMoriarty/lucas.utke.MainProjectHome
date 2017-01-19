#pragma once
#include "Units.h"
#include <iostream>
using namespace std;

class Bullet : public Units//inheritance
{
private:
	int TimeUp;
	int health;
	double MouseAngle;
	//int animationRow;

	//protected:
	//bool ifPursue;//this is what protected does!

public:
	Bullet();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y, int image_size_x, int image_size_y, double MouseAngle, double copy_dirX, double copy_dirY);
	void Update(double cameraX, double cameraY);
	void Render();

	int GetHealth() { return health; }

	void TakeDamage() { health--; }

	void LogicFunc();
};