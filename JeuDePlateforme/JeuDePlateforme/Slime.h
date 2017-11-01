#pragma once

#include "Enemy.h"

class Slime : public Enemy
{
public:
	Slime();
  Slime(const Vector2f position, const Texture& texture);
	~Slime();

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

