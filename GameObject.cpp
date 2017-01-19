#include "GameObject.h"
#include <math.h>
#include <iostream>
using namespace std;

GameObject::GameObject()
{
	x = 0;
	y = 0;

	velX = 0;
	velY = 0;

	dirX = 0;
	dirY = 0;

	boundX = 0;
	boundY = 0;

	maxFrame = 0;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;
	animationDirection = 0;

	animationRow = 0;

	image = NULL;

	alive = true;
	collidable = true;

	for (int a = 0; a < 2; a++){
		ColDir[a] = false;
	}
}

void GameObject::Destroy(){}

void GameObject::Init(double x, double y, double velX, double velY, double dirX, double dirY, int boundX, int boundY)
{
	GameObject::x = x;
	GameObject::y = y;//position

	GameObject::velX = velX;
	GameObject::velY = velY;//speed

	GameObject::dirX = dirX;
	GameObject::dirY = dirY;//direction

	GameObject::boundX = boundX;
	GameObject::boundY = boundY;//size
}

void GameObject::Update(double cameraX, double cameraY)
{
	x += velX * dirX;
	y += velY * dirY;

	x += cameraX;
	y += cameraY;
}

void GameObject::Render()
{}

bool GameObject::CheckCollisions(GameObject *otherObject)
{
	collision = false;
	double oX = otherObject->GetX();
	double oY = otherObject->GetY();

	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	double onewX = (otherObject->GetVelX()*otherObject->GetDirX());
	double onewY = (otherObject->GetVelY()*otherObject->GetDirY());

	double newX = velX *dirX;
	double newY = velY *dirY;

	/*
	double Rad = boundX / 2, oRad = obX / 2;
	double rX = x + Rad + newX, rY = y + Rad + newY;
	double orX = oX + oRad + onewX, orY = oY + oRad + onewY;

	//distance formula
	if (sqrt((rX - orX)*(rX - orX) + (rY - orY)*(rY - orY)) <= Rad + oRad)
	return true;
	else
	return false;*/

	if (x + boundX + newX > oX + onewX && x + newX < oX + obX + onewX){
		//cout << "blah1" << endl;
		ColDir[0] = true;
	}
	if (y + boundY + newY > oY + onewY && y + newY < oY + obY + onewY){
		//cout << "blah2" << endl;
		ColDir[1] = true;
	}
	if (x + boundX + newX > oX + onewX &&
		x + newX < oX + obX + onewX &&
		y + boundY + newY > oY + onewY &&
		y + newY < oY + obY + onewY)
		return true;
	else
		return false;
	/*if (x + boundX + newX > oX - obX &&
		x - boundX + newX < oX + obX &&
		y + boundY + newY > oY - obY &&
		y - boundY + newY < oY + obY)-
		return true;
		else
		return false;*/
}

void GameObject::Collided(GameObject *otherObject)
{
	collision = true;
	if (ID == BULLET && (otherObject)->GetID() == TERRAIN_FULL){
		dirX = 0;
		dirY = 0;
	}
	if (ID == PLAYER && (otherObject)->GetID() == TERRAIN_FULL){
		double oX = otherObject->GetX();
		double oY = otherObject->GetY();

		int obX = otherObject->GetBoundX();
		int obY = otherObject->GetBoundY();

		double onewX = (otherObject->GetVelX()*otherObject->GetDirX());
		double onewY = (otherObject->GetVelY()*otherObject->GetDirY());

		double newX = velX *dirX;
		double newY = 0;//if collision still works without Y, 

		if (x + boundX + newX > oX + onewX &&
			x + newX < oX + obX + onewX &&
			y + boundY + newY > oY + onewY &&
			y + newY < oY + obY + onewY){
			//then Y doesnt impact collision
			dirX = 0;
		}

		newX = 0;//same for X
		newY = velY *dirY;

		if (x + boundX + newX > oX + onewX &&
			x + newX < oX + obX + onewX &&
			y + boundY + newY > oY + onewY &&
			y + newY < oY + obY + onewY){
			//then X doesnt impact collision
			dirY = 0;
		}

		
	}
	if (ID == BULLET && otherObject->GetID() == MISC){
		SetAlive(false);
		otherObject->SetAlive(false);
	}
}

bool GameObject::Collidable()
{
	return alive && collidable;
}