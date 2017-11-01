#include "Fly.h"


Fly::Fly()
{

}

//Passe les paramètres au constructeur de son parent et instacie les tableaux de intrect pour les animations
Fly::Fly(const Vector2f position, const Texture& texture) : Enemy(position, texture)
{
  enemyWalk[0] = IntRect(0, 32, 72, 36);
  enemyWalk[1] = IntRect(0, 0, 75, 31);
  enemyWalkReverse[0] = IntRect(0 - 72, 32, -72, 36);
  enemyWalkReverse[1] = IntRect(0 - 75, 0, -75, 31);
  this->setTextureRect(enemyWalk[0]);
}


Fly::~Fly()
{

}

void Fly::update()
{

}