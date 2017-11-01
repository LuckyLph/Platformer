#pragma once

#include "GameObject.h"

class Water : public GameObject
{
public:
	Water();
	Water(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObjet);
	~Water();
	void setIsHalfBlock(bool value);
	bool getIsHalfBlock();

private:
  bool isCollisionBox = false;
	bool isHalfBlock = false;

};

