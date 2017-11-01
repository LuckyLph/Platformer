#pragma once

#include "GameObject.h"
#include "PowerUps.h"


class PowerUp : public GameObject
{
public:
	PowerUp();
	~PowerUp();
	PowerUp(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject, PowerUps _typePowerUp);

private:
	bool isCollisionBox = false;

};

