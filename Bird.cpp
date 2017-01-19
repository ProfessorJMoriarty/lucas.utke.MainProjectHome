#include "Bird.h"

Bird::Bird(){}

void Bird::Destroy()
{
	GameObject::Destroy();
}

void Bird::Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y, int image_size_x, int image_size_y, int copy_dir_x, int copy_dir_y, int copy_vel_x, int copy_vel_y)
{
	GameObject::Init(copy_x, copy_y, copy_vel_x, copy_vel_y, copy_dir_x, copy_dir_y, image_size_x, image_size_y);
	SetID(MISC);
	SetAlive(true);
	SetSelected(false);
	SetCollidable(true);
	health = 5;

	maxFrame = 8;
	curFrame = 0;//horizontal
	animationRow = 0;//vertical

	frameWidth = image_size_x;
	frameHeight = image_size_y;

	TimeUp = 0;

	WalkLoop = 4;
	frameCounter = 0;

	enum AISTATE{ IDLE, FLYING, PECKING };
	AIstate = 0;
	if (image != NULL)
		Bird::image = image;
}

void Bird::Update(double cameraX, double cameraY)
{
	Units::Update(cameraX, cameraY);
	
	frameCounter++;
	if (frameCounter >= 60){
		frameCounter = 0;
		curFrame++;
		if (curFrame >= maxFrame){	
			if (rand() % 3 == 1)
				AIstate = PECKING;
			else
				AIstate = IDLE;
			StateHandler();
		}
	}
}

void Bird::Render()
{
	if (x > 0 &&//will not render if outside console window
		x < SCREENW &&
		y > 0 &&
		y < SCREENH){
		GameObject::Render();
		int fx = curFrame*frameWidth;
		int fy = animationRow*frameHeight;
		//int fx = 0;
		//int fy = 0;

		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x, y, 0);
	}
}

void Bird::StateHandler()
{
	if (AIstate == IDLE){
		maxFrame = 8;
		curFrame = 0;
		animationRow = 0;
	}
	else if (AIstate == PECKING){
		maxFrame = 6;
		curFrame = 0;
		animationRow = 1;
	}

}