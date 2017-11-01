#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::Enemy(const Vector2f position, const Texture& texture) : GameEntity(position, texture)
{
  startingPosition = position;
}


Enemy::~Enemy()
{
}


int Enemy::getPatrolOffSet() const
{
  return patrolOffSet;
}

Vector2f Enemy::getStartingPosition() const
{
  return startingPosition;
}

void Enemy::manageAnimations()
{

}