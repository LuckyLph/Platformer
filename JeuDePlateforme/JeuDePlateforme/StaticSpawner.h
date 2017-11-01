#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include "Resources.h"
#include "EnemyFactory.h"
#include "Constants.h"

class StaticSpawner : public GameObject
{
public:
  StaticSpawner();
  StaticSpawner(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject);
  ~StaticSpawner();

  Enemy * spawnFly(Resources * resourceManager);
  void setSpawnLocationState(const Vector2f spawnLocation, const bool state);

private:
  bool isCollisionBox = false;

  Vector2f spawnLocations[STATIC_SPAWN_LOCATION_AMOUNT];
  bool spawnLocationsStatus[STATIC_SPAWN_LOCATION_AMOUNT];
};