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

//Retourne la vélocité en X
float GameEntity::getXVelocity() const
{
  return xVelocity;
}

 //Retourne la vélocité en Y
float GameEntity::getYVelocity() const
{
  return yVelocity;
}

//Retourne l'état du jump de l'entité
JumpStates GameEntity::getJumpStatus() const
{
  return jumpStatus;
}

//Ajuste la vélocité en X selon le paramètre
void GameEntity::setXVelocity(const float value)
{
  xVelocity = value;;
}

//Ajuste la vélocité en Y selon le paramètre
void GameEntity::setYVelocity(const float value)
{
  yVelocity = value;
}

//Ajuste le status du saut selon le paramètre
void GameEntity::setJumpStatus(const JumpStates value)
{
  jumpStatus = value;
}