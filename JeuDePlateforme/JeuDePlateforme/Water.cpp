#include "Water.h"


Water::Water()
{

}

Water::Water(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject) : GameObject(texture, rect, x, y, _typeObject)
{
}


Water::~Water()
{
}

void Water::setIsHalfBlock(bool value)
{
	isHalfBlock = value;
}

bool Water::getIsHalfBlock()
{
	return isHalfBlock;
}