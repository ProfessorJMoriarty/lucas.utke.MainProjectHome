#pragma once
#include "Units.h"
#include <iostream>
using namespace std;

class FootSoldier : public Units//inheritance
{
private:
	int TimeUp;
	int health;
	int animationRow;

	//protected:
	//bool ifPursue;//this is what protected does!

public:
	FootSoldier();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y);
	void Update(double cameraX, double cameraY);
	void Render();

	void ResetAnimation(int position);

	int GetHealth() { return health; }

	void TakeDamage() { health--; }

	void LogicFunc();
};