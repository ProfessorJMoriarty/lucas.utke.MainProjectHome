#pragma once
#include "GameObject.h"
#include <iostream>
using namespace std;

class Tree : public GameObject//inheritance
{
private:
	int tree_num;
public:
	Tree();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image, int number, double copy_x, double copy_y);
	void Update();
	void Render();

};