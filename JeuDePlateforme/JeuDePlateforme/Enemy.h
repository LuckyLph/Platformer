#pragma once

#include "GameEntity.h"

class Enemy : public GameEntity
{
public:
	Enemy();
  Enemy(const Vector2f position, const Texture& texture);
	~Enemy();

  int getPatrolOffSet() const;
  Vector2f getStartingPosition() const;

private:
  float xVelocity;
  float yVelocity;
  int jumpHeight;
  int patrolOffSet;
  JumpStates jumpStatus;
  Vector2f startingPosition;

  void manageAnimations();
};

