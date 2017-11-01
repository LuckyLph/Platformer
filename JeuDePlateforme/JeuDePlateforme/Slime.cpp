#include "Slime.h"


Slime::Slime()
{
  
}

//Passe les paramètres au constructeur de son parent et instacie les tableaux de intrect pour les animations
Slime::Slime(const Vector2f position, const Texture& texture) : Enemy(position, texture)
{
  enemyWalk[0] = IntRect(52, 125, 50, 26);
  enemyWalk[1] = IntRect(0, 125, 50, 26);
  enemyWalkReverse[0] = IntRect(52 - 50, 125, -50, 26);
  enemyWalkReverse[1] = IntRect(0 - 50, 125, -50, 26);
  this->setTextureRect(enemyWalk[0]);
}


Slime::~Slime()
{
}


void Slime::update()
{

}
