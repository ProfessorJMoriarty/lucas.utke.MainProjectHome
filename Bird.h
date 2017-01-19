#pragma once
#include "Units.h"
#include <iostream>
using namespace std;

class Bird : public Units//inheritance
{
private:
	int TimeUp;
	int health;
	int WalkLoop;
	int frameCounter;
	//int animationRow;
	enum AISTATE { IDLE, FLYING, PECKING };
	int AIstate;
	//protected:
	//bool ifPursue;//this is what protected does!

public:
	Bird();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y, int image_size_x, int image_size_y, int copy_dir_x, int copy_dir_y, int copy_vel_x, int copy_vel_y);
	void Update(double cameraX, double cameraY);
	void Render();

	int GetHealth() { return health; }

	void TakeDamage() { health--; }

	void StateHandler();
};