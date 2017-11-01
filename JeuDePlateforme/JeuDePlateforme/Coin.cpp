#include "Coin.h"


Coin::Coin()
{
}

Coin::Coin(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject) : GameObject(texture, rect, x, y, _typeObject)
{
}


Coin::~Coin()
{
}
