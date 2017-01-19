#pragma once
#include "GameObject.h"
#include <iostream>
using namespace std;

class Buildings : public GameObject//inheritance
{
private:
	int health;
public:
	Buildings();

	int GetHealth() { return health; }

	void TakeDamage() { health--; }
};