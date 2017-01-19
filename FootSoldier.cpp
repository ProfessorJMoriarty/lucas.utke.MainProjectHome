#include "FootSoldier.h"

FootSoldier::FootSoldier(){}

void FootSoldier::Destroy()
{
	GameObject::Destroy();
}

void FootSoldier::Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y)
{
	GameObject::Init(copy_x, copy_y, 6, 6, 0, 0, 10, 10);
	SetID(FOOTSOLDIER);
	SetAlive(true);
	SetSelected(false);

	health = 5;

	maxFrame = 14;
	curFrame = 0;//horizontal
	frameWidth = 10;
	frameHeight = 10;
	animationColumns = 1;
	animationDirection = 1;

	animationRow = 1;//vertical
	TimeUp = 0;

	if (image != NULL)
		FootSoldier::image = image;
}

void FootSoldier::Update(double cameraX, double cameraY)
{
	Units::Update(cameraX, cameraY);
}

//does not use animation rows, sprites, etc. unnecessary for basic box sprite.
void FootSoldier::Render()
{
	if (x > 0 &&//will not render if outside console window
		x < SCREENW &&
		y > 0 &&
		y < SCREENH){
		GameObject::Render();
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = animationRow * frameHeight;
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x, y, 0);
		//al_draw_bitmap(image, x - frameWidth / 2, y - frameHeight / 2, 0);
	}
}

void FootSoldier::ResetAnimation(int position)
{
	if (position == 1)
	{
		animationRow = 1;
		dirY = 0;
	}
	else
	{
		curFrame = 0;
		dirX = 0;
	}
}