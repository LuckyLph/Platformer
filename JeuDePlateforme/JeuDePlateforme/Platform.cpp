#include "Platform.h"


Platform::Platform()
{

}

//Passe les paramètres au constructeur de son parent
Platform::Platform(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject) : GameObject(texture, rect, x, y, _typeObject)
{

}


Platform::~Platform()
{
}