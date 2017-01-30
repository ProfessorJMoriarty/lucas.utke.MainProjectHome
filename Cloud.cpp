#include "Cloud.h"
#include <iostream>
using namespace std;

Cloud::Cloud(ALLEGRO_BITMAP *image)
{
	GameObject::Init(0, 0, 1, 1, 1, 0, 0, 0);

	SetID(CLOUD);
	SetCollidable(false);

	Cloud::image = image;
	frameWidth = al_get_bitmap_width(image);
}

void Cloud::Destroy()
{
	GameObject::Destroy();
}

void Cloud::Update(double cameraX, double cameraY)
{
	if (x >= WORLDW)
		x = 0;

	GameObject::Update(cameraX, cameraY);
}

void Cloud::Render()
{
	al_draw_tinted_bitmap(image, al_map_rgba_f(-255, -255, -255, 0.25), x, y, 0);

	if (x > 0) {
		al_draw_tinted_bitmap(image, al_map_rgba_f(-255, -255, -255, 0.25), x - WORLDW, y, 0);
	}
}