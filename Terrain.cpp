#include "Terrain.h"

Terrain::Terrain(){}

void Terrain::Destroy()
{
	GameObject::Destroy();
}

void Terrain::Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y, double copy_image_x, double copy_image_y, double image_size_x, double image_size_y, bool collision)
{
	GameObject::Init(copy_x, copy_y, 6, 6, 0, 0, image_size_x, image_size_y);
	
	if (collision == true)
		SetCollidable(true);
	else if (collision == false)
		SetCollidable(false);
	//SetCollidable(false);

	SetID(TERRAIN_FULL);
	
	SetAlive(true);

	frameWidth = image_size_x;
	frameHeight = image_size_y;
	image_x = copy_image_x;
	image_y = copy_image_y;
	if (image != NULL)
		Terrain::image = image;
}

void Terrain::Update()
{}

//does not use animation rows, sprites, etc. unnecessary for basic box sprite.
void Terrain::Render()
{
	if (x > -frameWidth * 2 &&//will not render if outside console window
		x < SCREENW + frameWidth * 2 &&
		y > -frameHeight * 2 &&
		y < SCREENH + frameHeight * 2){
		GameObject::Render();
		//al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
		al_draw_bitmap_region(image, image_x, image_y, frameWidth, frameHeight, x, y, 0);
	}
}