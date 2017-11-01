#include "Spike.h"


Spike::Spike()
{

}

Spike::Spike(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject) : GameObject(texture, rect, x, y, _typeObject)
{
}


Spike::~Spike()
{
}
