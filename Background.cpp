#include "Background.h"

Background::Background(ALLEGRO_BITMAP *image)
{
	GameObject::Init(0, 0, 0, 0, 0, 0, 0, 0);

	SetID(MISC);
	SetCollidable(false);

	Background::image = image;
	frameWidth = al_get_bitmap_width(image);
}

void Background::Destroy()
{
	GameObject::Destroy();
}

void Background::Update(double cameraX, double cameraY)
{
	GameObject::Update(cameraX, cameraY);
}

void Background::Render()
{
	al_draw_bitmap(image, x, y, 0);
}