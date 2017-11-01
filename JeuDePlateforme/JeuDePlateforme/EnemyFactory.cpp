#include "EnemyFactory.h"

//Retourne un ennemi du type voulu � la position pass�e en param�tre
Enemy * EnemyFactory::CreateEnemy(const Vector2f position, const Texture& texture, TypeEnemy type)
{
  if (type == FLY)
  {
    return new Fly(position, texture);
  }
  else if (type == BLOCKER)
  {
    return new Blocker(position, texture);
  }
  else if (type == SLIME)
  {
    return new Slime(position, texture);
  }
  return nullptr;
}