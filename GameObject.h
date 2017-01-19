#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"

class GameObject
{
private:
	int ID;
	int health;
	bool alive;
	bool collidable;
	bool selected;
	bool collision;
	bool ColDir[2];

protected:
	double x;
	double y;

	double velX;
	double velY;

	double dirX;
	double dirY;

	int boundX;
	int boundY;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;
	
	int animationRow;

	ALLEGRO_BITMAP *image;



public:
	GameObject();
	void virtual Destroy();

	void Init(double x, double y, double velX, double velY, double dirX, double dirY, int boundX, int boundY);
	void virtual Update(double cameraX, double cameraY);
	void virtual Render();

	double GetX() { return x; }
	double GetY() { return y; }

	void SetX(double x) { GameObject::x = x; }
	void SetY(double y) { GameObject::y = y; }

	double GetDirX() { return dirX; }
	double GetDirY() { return dirY; }

	void SetDirX(double dirX) { GameObject::dirX = dirX; }
	void SetDirY(double dirY) { GameObject::dirY = dirY; }

	int GetBoundX() { return boundX; }
	int GetBoundY() { return boundY; }

	int GetVelX() { return velX; }
	int GetVelY() { return velY; }

	int GetID() { return ID; }
	void SetID(int ID) { GameObject::ID = ID; }

	bool GetCollision() { return collision; };
	void SetCollision(bool collision) { GameObject::collision = collision; };

	bool GetSelected() { return selected; }
	void SetSelected(int selected) { GameObject::selected = selected; }

	bool GetAlive() { return alive; }
	void SetAlive(bool alive) { GameObject::alive = alive; }

	bool GetCollidable() { return collidable; }
	void SetCollidable(bool collidable) { GameObject::collidable = collidable; }

	bool CheckCollisions(GameObject *otherObject);
	void virtual Collided(GameObject *otherObject);
	bool Collidable();
};