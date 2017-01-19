#include "Tree.h"

Tree::Tree(){}

void Tree::Destroy()
{
	GameObject::Destroy();
}

void Tree::Init(ALLEGRO_BITMAP *image, int number, double copy_x, double copy_y)
{
	GameObject::Init(copy_x, copy_y, 0, 0, 0, 0, 50, 50);
	SetID(TERRAIN_EMPTY);
	SetAlive(true);
	tree_num = number;
	frameWidth = DIMW;
	frameHeight = DIMH;

	if (image != NULL)
		Tree::image = image;
}

void Tree::Update()
{}
//does not use animation rows, sprites, etc. unnecessary for basic box sprite.
void Tree::Render()
{
	if ((x + (TREE_1_RW)) > -DIMW * 2 &&//will not render if outside console window
		x < SCREENW + DIMW * 2 &&
		y > -DIMH * 2 &&
		(y - (TREE_1_H)) < SCREENH + DIMH * 2){

		GameObject::Render();

		if (tree_num == 1){
			al_draw_bitmap(image, (x - (TREE_1_LW)), (y - (TREE_1_H)), 0);
		}
		else if (tree_num == 2){
			al_draw_bitmap(image, (x - (TREE_2_LW)), (y - (TREE_2_H)), 0);
		}
		else if (tree_num == 3){
			al_draw_bitmap(image, (x - (TREE_3_LW)), (y - (TREE_3_H)), 0);
		}
		else if (tree_num == 4){
			al_draw_bitmap(image, (x - (TREE_4_LW)), (y - (TREE_4_H)), 0);
		}
		else if (tree_num == 5){
			al_draw_bitmap(image, (x - (TREE_5_LW)), (y - (TREE_5_H)), 0);
		}
	}
}