#pragma once
#include "GameObject.h"
#include <iostream>
using namespace std;

class Units : public GameObject//inheritance
{
private:
	int health;
	//int WalkLoop;
	//int animationRow;

	//int RallyX;
	//int RallyY;

	//protected:
	//bool ifPursue;//this is what protected does!

public:
	
	Units();
	void Update(double CameraX, double CameraY);

	int GetHealth() { return health; }

	void TakeDamage() { health--; }

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void ResetAnimation(int position);

	void MoveToRally();
	void Collided(GameObject *otherObject);
	//int GetRallyX() { return RallyX; }
	//int GetRallyY() { return RallyY; }

	//void SetRallyX(int RallyX) { Units::RallyX = RallyX; }
	//void SetRallyY(int RallyY) { Units::RallyY = RallyY; }
};