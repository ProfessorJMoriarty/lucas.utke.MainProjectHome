#include "Units.h"

Units::Units(){}//the Units class includes movecommands and basic unit AI (attacking melee, ranged, responding to commands, etc)

void Units::MoveUp(){ animationRow = 3, dirY = -1; }
void Units::MoveDown(){ animationRow = 5, dirY = 1; }
void Units::MoveLeft(){ curFrame = 3, dirX = -1; }
void Units::MoveRight(){ curFrame = 5, dirX = 1; }
void Units::ResetAnimation(int position)
{
	if (position == 1)
	{
		animationRow = 4;
		dirY = 0;
	}
	else
	{
		curFrame = 4;
		dirX = 0;
	}
}
void Units::Update(double CameraX, double CameraY)
{
	GameObject::Update(CameraX, CameraY);
}
void Units::Collided(GameObject *otherObject){
	GameObject::Collided(otherObject);

	//if (GetID() == PLAYER){
	//	ResetAnimation(0);
	//	ResetAnimation(1);
	//}

}