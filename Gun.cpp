#include "Gun.h"

Gun::Gun(){}

void Gun::Destroy()
{
	GameObject::Destroy();
}

void Gun::Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y, int image_size_x, int image_size_y, double copy_MouseAngle)
{
	GameObject::Init(copy_x, copy_y, 6, 6, 0, 0, image_size_x, image_size_y);
	SetID(WEAPON);
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

	MouseAngle = copy_MouseAngle;

	if (image != NULL)
		Gun::image = image;
}

void Gun::Update(double cameraX, double cameraY)
{
	Units::Update(cameraX, cameraY);
	TimeUp++;
	if (TimeUp == 2)
		SetAlive(false);
}

void Gun::Render()
{
	if (x > 0 &&//will not render if outside console window
		x < SCREENW &&
		y > 0 &&
		y < SCREENH){

		GameObject::Render();

		if (MouseAngle <= 67.5 && MouseAngle >= 22.5)
			curFrame = 2, animationRow = 0;
		else if (MouseAngle <= 112.5 && MouseAngle >= 67.5)
			curFrame = 1, animationRow = 0;
		else if (MouseAngle <= 157.5 && MouseAngle >= 112.5)
			curFrame = 0, animationRow = 0;
		else if (MouseAngle <= 202.5 && MouseAngle >= 157.5)
			curFrame = 0, animationRow = 1;
		else if (MouseAngle <= 247.5 && MouseAngle >= 202.5)
			curFrame = 0, animationRow = 2;
		else if (MouseAngle <= 292.5 && MouseAngle >= 247.5)
			curFrame = 1, animationRow = 2;
		else if (MouseAngle <= 337.5 && MouseAngle >= 292.5)
			curFrame = 2, animationRow = 2;
		else if ((MouseAngle <= 360 && MouseAngle >= 337.5) || (MouseAngle <= 22.5 && MouseAngle >= 0))
			curFrame = 2, animationRow = 1;


		int fx = curFrame * frameWidth;
		int fy = animationRow * frameHeight;
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x + frameWidth/2 - ((2-curFrame)*frameWidth/2), y + frameHeight/2 - ((2-animationRow)*frameHeight/2), 0);

		//cout << MouseAngle << endl;
		//al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, al_map_rgba(1, 1, 1, 1), x - ((2 - curFrame)*frameWidth / 2), y - ((2 - animationRow)*frameHeight / 2), x - ((2 - curFrame)*frameWidth / 2), y - ((2 - animationRow)*frameHeight / 2), 1, 1, MouseAngle, 0);
	}
}