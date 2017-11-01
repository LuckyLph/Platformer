#include "Blocker.h"


Blocker::Blocker()
{
}

//Passe les paramètres au constructeur de son parent et instacie les tableaux de intrect pour les animations
Blocker::Blocker(const Vector2f position, const Texture& texture) : Enemy(position, texture)
{
  enemyWalk[0] = IntRect(136, 66, 51, 51);
  enemyWalk[1] = IntRect(188, 66, 51, 51);
  enemyWalkReverse[0] = IntRect(136 + 51, 66, -51, 51);
  enemyWalkReverse[1] = IntRect(188 + 51, 66, -51, 51);
  this->setTextureRect(enemyWalk[0]);
}


Blocker::~Blocker()
{
}


void Blocker::update()
{
  
}