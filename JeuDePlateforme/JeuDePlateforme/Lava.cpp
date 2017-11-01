#include "Lava.h"


Lava::Lava()
{

}

Lava::Lava(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject) : GameObject(texture, rect, x, y, _typeObject)
{
}


Lava::~Lava()
{
}

void Lava::setIsHalfBlock(bool value)
{
	isHalfBlock = value;
}

bool Lava::getIsHalfBlock()
{
	return isHalfBlock;
}