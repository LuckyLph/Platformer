#pragma once

#include "Enemy.h"

class Blocker : public Enemy
{
public:
	Blocker();
  Blocker(const Vector2f position, const Texture& texture);
	~Blocker();

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