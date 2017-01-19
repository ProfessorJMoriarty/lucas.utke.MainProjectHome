#include "Player.h"

Player::Player(){}

void Player::Destroy()
{
	GameObject::Destroy();
}

void Player::Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y, int image_size_x, int image_size_y, int copy_dir_x, int copy_dir_y, int copy_vel_x, int copy_vel_y)
{
	GameObject::Init(copy_x, copy_y, copy_vel_x, copy_vel_y, copy_dir_x, copy_dir_y, image_size_x, image_size_y);
	SetID(PLAYER);
	SetAlive(true);
	SetSelected(false);

	health = 5;

	maxFrame = 14;
	curFrame = 1;//horizontal
	frameWidth = image_size_x;
	frameHeight = image_size_y;
	animationColumns = 1;
	animationDirection = 1;

	animationRow = 1;//vertical
	TimeUp = 0;

	WalkLoop = 4;
	frameCounter = 0;
	if (image != NULL)
		Player::image = image;
}

void Player::Update(double cameraX, double cameraY)
{
	Units::Update(cameraX, cameraY);
	frameCounter++;
	if (frameCounter >= 10){
		frameCounter = 0;
		WalkLoop++;
		if (WalkLoop >= 4)
			WalkLoop = 0;
	}
}

void Player::Render()
{
	if (x > 0 &&//will not render if outside console window
		x < SCREENW &&
		y > 0 &&
		y < SCREENH){
		GameObject::Render();
		int fx = 0;
		int fy = 0;

		if (curFrame == 3)
			fx = (curFrame - WalkLoop) * frameWidth;
		else if (curFrame == 4)
			fx = (curFrame)* frameWidth;
		else if (curFrame == 5)
			fx = (curFrame + WalkLoop) * frameWidth;

		if (animationRow == 3)
			fy = (animationRow - WalkLoop) * frameHeight;
		else if (animationRow == 4)
			fy = (animationRow)* frameHeight;
		else if (animationRow == 5)
			fy = (animationRow + WalkLoop) * frameHeight;

		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x, y, 0);
	}
}