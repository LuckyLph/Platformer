#pragma once

#include "GameObject.h"

class Lava : public GameObject
{
	public:
		Lava();
		Lava(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObjet);
		~Lava();
		void setIsHalfBlock(bool value);
		bool getIsHalfBlock();

  private:
    bool isCollisionBox = false;
		bool isHalfBlock = false;
};