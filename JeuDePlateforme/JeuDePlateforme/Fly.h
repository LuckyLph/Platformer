#pragma once

#include "Enemy.h"

class Fly : public Enemy
{
public:
	Fly();
  Fly(const Vector2f position, const Texture& texture);
	~Fly();

  void update();
private:
  float xVelocity;
  float yVelocity;
  int jumpHeight;
  int patrolOffSet;
  int animTick;
  JumpStates jumpStatus;
  Vector2f startingPosition;

  IntRect enemyWalk[2];
  IntRect enemyWalkReverse[2];
};