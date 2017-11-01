#pragma once

#include "Enemy.h"
#include "Fly.h"
#include "Blocker.h"
#include "Slime.h"
#include "typeEnemy.h"

class EnemyFactory
{
public:
  static Enemy * CreateEnemy(const Vector2f position, const Texture& texture, TypeEnemy type);
private:
  EnemyFactory();
};
