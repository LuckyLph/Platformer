#pragma once

#include "GameObject.h"


class Coin : public GameObject
{
public:
	Coin();
	~Coin();
	Coin(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject);

private:
	bool isCollisionBox = false;

};

