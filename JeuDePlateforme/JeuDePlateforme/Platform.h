#pragma once

#include "GameObject.h"

using namespace sf;

class Platform : public GameObject
{
public:
  Platform();
	Platform(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject);
  ~Platform();

private:
	bool isCollisionBox = false;
};

