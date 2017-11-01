#pragma once

#include "GameObject.h"

class Spike : public GameObject
{
public:
	Spike();
	Spike(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject);
	~Spike();

private:
  bool isCollisionBox = false;
};

