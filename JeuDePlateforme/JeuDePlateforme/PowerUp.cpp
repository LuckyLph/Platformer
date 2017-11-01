#include "PowerUp.h"


PowerUp::PowerUp()
{
}


PowerUp::PowerUp(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject, PowerUps _typePowerUp) : GameObject(texture, rect, x, y, _typeObject)
{
}


PowerUp::~PowerUp()
{
}