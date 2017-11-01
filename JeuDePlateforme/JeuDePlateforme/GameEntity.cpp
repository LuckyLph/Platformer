#include "GameEntity.h"


GameEntity::GameEntity()
{
}


GameEntity::GameEntity(const Vector2f position, const Texture& texture)
{
  this->setPosition(position);
  setTexture(texture);
}


GameEntity::~GameEntity()
{
}


void GameEntity::update()
{
  manageMovement();
  manageAnimations();
}

void GameEntity::manageMovement()
{

}

void GameEntity::manageAnimations()
{

}

//Retourne la v�locit� en X
float GameEntity::getXVelocity() const
{
  return xVelocity;
}

 //Retourne la v�locit� en Y
float GameEntity::getYVelocity() const
{
  return yVelocity;
}

//Retourne l'�tat du jump de l'entit�
JumpStates GameEntity::getJumpStatus() const
{
  return jumpStatus;
}

//Ajuste la v�locit� en X selon le param�tre
void GameEntity::setXVelocity(const float value)
{
  xVelocity = value;;
}

//Ajuste la v�locit� en Y selon le param�tre
void GameEntity::setYVelocity(const float value)
{
  yVelocity = value;
}

//Ajuste le status du saut selon le param�tre
void GameEntity::setJumpStatus(const JumpStates value)
{
  jumpStatus = value;
}