#include "RandomSpawner.h"


RandomSpawner::RandomSpawner()
{
  srand(time(NULL));

  //Initialise le tableau de spawn locations avec les bonnes coordonnées
  spawnLocations[0] = Vector2f(7 * TILE_SIZE, 4 * TILE_SIZE);
  spawnLocations[1] = Vector2f(3 * TILE_SIZE, 8 * TILE_SIZE);
  spawnLocations[2] = Vector2f(4 * TILE_SIZE, 12 * TILE_SIZE);
  spawnLocations[3] = Vector2f(9 * TILE_SIZE, 10 * TILE_SIZE);
  spawnLocations[4] = Vector2f(23 * TILE_SIZE, 8 * TILE_SIZE);
  spawnLocations[5] = Vector2f(24 * TILE_SIZE, 13 * TILE_SIZE);
  spawnLocations[6] = Vector2f(32 * TILE_SIZE, 6 * TILE_SIZE);
  spawnLocations[7] = Vector2f(33 * TILE_SIZE, 12 * TILE_SIZE);
  spawnLocations[8] = Vector2f(39 * TILE_SIZE, 5 * TILE_SIZE);
  spawnLocations[9] = Vector2f(40 * TILE_SIZE, 10 * TILE_SIZE);
  spawnLocations[10] = Vector2f(45 * TILE_SIZE, 8 * TILE_SIZE);
  spawnLocations[11] = Vector2f(51 * TILE_SIZE, 8 * TILE_SIZE);
  spawnLocations[12] = Vector2f(44 * TILE_SIZE, 3 * TILE_SIZE);
  spawnLocations[13] = Vector2f(62 * TILE_SIZE, 5 * TILE_SIZE);
  spawnLocations[14] = Vector2f(74 * TILE_SIZE, 13 * TILE_SIZE);
  spawnLocations[15] = Vector2f(78 * TILE_SIZE, 9 * TILE_SIZE);
  spawnLocations[16] = Vector2f(69 * TILE_SIZE, 7 * TILE_SIZE);
  spawnLocations[17] = Vector2f(80 * TILE_SIZE, 5 * TILE_SIZE);
  spawnLocations[18] = Vector2f(80 * TILE_SIZE, 12 * TILE_SIZE);
  spawnLocations[19] = Vector2f(92 * TILE_SIZE, 8 * TILE_SIZE);
  spawnLocations[20] = Vector2f(98 * TILE_SIZE, 6 * TILE_SIZE);
  spawnLocations[21] = Vector2f(107 * TILE_SIZE, 8 * TILE_SIZE);
  spawnLocations[22] = Vector2f(106 * TILE_SIZE, 15 * TILE_SIZE);
  spawnLocations[23] = Vector2f(118 * TILE_SIZE, 7 * TILE_SIZE);

  for (int i = 0; i < RANDOM_SPAWN_LOCATION_AMOUNT; i++)
  {
    spawnLocationsStatus[i] = true;
  }
}


RandomSpawner::~RandomSpawner()
{
}

//Génère un ennemi de type et position aléatoire depuis le tableau de positions et le retourne
Enemy * RandomSpawner::spawnEnemy(Resources * resourceManager)
{
  //Vérifie qu'il reste de la place
  bool isSpaceAvailable = false;
  for (int i = 0; i < RANDOM_SPAWN_LOCATION_AMOUNT; i++)
  {
    if (spawnLocationsStatus[i])
    {
      isSpaceAvailable = true;
      break;
    }
  }
  if (isSpaceAvailable)
  {
    int position;
    //Génère un type et une position, cette dernière devant absolument être valide
    int type = rand() % 2;
    do { position = rand() % RANDOM_SPAWN_LOCATION_AMOUNT; } while (!spawnLocationsStatus[position]);
    Enemy * enemyToReturn;
    if (type == 0)
    {
      enemyToReturn = EnemyFactory::CreateEnemy(spawnLocations[position], resourceManager->getEnemiesSpriteSheet(), TypeEnemy::BLOCKER);
    }
    else if (type == 1)
    {
      enemyToReturn = EnemyFactory::CreateEnemy(spawnLocations[position], resourceManager->getEnemiesSpriteSheet(), TypeEnemy::SLIME);
    }
    spawnLocationsStatus[position] = false;
    return enemyToReturn;
  }
  return NULL;
}

//Ajuste le status de la position de spawn prise en paramètre
void RandomSpawner::setSpawnLocationState(const Vector2f spawnLocation, const bool state)
{
  for (int i = 0; i < RANDOM_SPAWN_LOCATION_AMOUNT; i++)
  {
    if (spawnLocations[i] == spawnLocation)
    {
      spawnLocationsStatus[i] = state;
      break;
    }
  }
}