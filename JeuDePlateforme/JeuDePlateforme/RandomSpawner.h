#pragma once

#include <SFML\Graphics.hpp>
#include "Constants.h"
#include "EnemyFactory.h"
#include "GameObject.h"
#include "Resources.h"
#include "typeEnemy.h"

using namespace std;
using namespace sf;

class RandomSpawner
{
public:
  RandomSpawner();
  ~RandomSpawner();

  Enemy * spawnEnemy(Resources * resourceManager);
  void setSpawnLocationState(const Vector2f spawnLocation, const bool state);

private:
  Vector2f spawnLocations[RANDOM_SPAWN_LOCATION_AMOUNT];
  bool spawnLocationsStatus[RANDOM_SPAWN_LOCATION_AMOUNT];
};

