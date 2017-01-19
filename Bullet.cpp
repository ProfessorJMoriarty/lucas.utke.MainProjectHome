#include "Bullet.h"

Bullet::Bullet(){}

void Bullet::Destroy()
{
	GameObject::Destroy();
}

void Bullet::Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y, int image_size_x, int image_size_y, double copy_MouseAngle, double copy_dirX, double copy_dirY)
{
	//cout << "(" << copy_dirX << ", " << copy_dirY << ")" << endl;
	GameObject::Init(copy_x, copy_y, 20, 20, copy_dirX, copy_dirY, image_size_x, image_size_y);
	SetID(BULLET);
	SetAlive(true);
	SetSelected(false);

	health = 5;

	maxFrame = 14;
	curFrame = 1;//horizontal
	frameWidth = image_size_x;
	frameHeight = image_size_y;
	animationColumns = 1;
	animationDirection = 1;
	MouseAngle = copy_MouseAngle;
	animationRow = 1;//vertical
	TimeUp = 20;

	srand(time(NULL));

	if (image != NULL)
		Bullet::image = image;
}

void Bullet::Update(double cameraX, double cameraY)
{
	Units::Update(cameraX, cameraY);

	MouseAngle += .25;
	if (MouseAngle > 360)
		MouseAngle = 0;

	TimeUp--;
	if (TimeUp == 0)
		SetAlive(false);
}

void Bullet::Render()
{
	if (x > 0 &&//will not render if outside console window
		x < SCREENW &&
		y > 0 &&
		y < SCREENH){
		GameObject::Render();
		int fx = curFrame * frameWidth;
		int fy = animationRow * frameHeight;
		al_draw_rotated_bitmap(image, frameWidth / 2, frameHeight / 2, x + frameWidth / 2, y + frameHeight / 2, MouseAngle, 0);
	}
}