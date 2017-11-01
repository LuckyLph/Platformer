#include "StaticSpawner.h"


StaticSpawner::StaticSpawner()
{
  srand(time(NULL));

  //Initialise le tableau de spawn locations avec les bonnes coordonn�es
  spawnLocations[0] = Vector2f(4 * TILE_SIZE, 2 * TILE_SIZE);
  spawnLocations[1] = Vector2f(12 * TILE_SIZE, 2 * TILE_SIZE);
  spawnLocations[2] = Vector2f(27 * TILE_SIZE, 2 * TILE_SIZE);
  spawnLocations[3] = Vector2f(32 * TILE_SIZE, 9 * TILE_SIZE);
  spawnLocations[4] = Vector2f(38 * TILE_SIZE, 2 * TILE_SIZE);
  spawnLocations[5] = Vector2f(45 * TILE_SIZE, 5 * TILE_SIZE);
  spawnLocations[6] = Vector2f(35 * TILE_SIZE, 8 * TILE_SIZE);

  for (int i = 0; i < STATIC_SPAWN_LOCATION_AMOUNT; i++)
  {
    spawnLocationsStatus[i] = true;
  }
}

//Passe les param�tre au constructeur de son parent
StaticSpawner::StaticSpawner(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObject) : GameObject(texture, rect, x, y, _typeObject)
{

}

StaticSpawner::~StaticSpawner()
{
}

//G�n�re un Fly � une position al�atoire dans le tableau et le retourne
Enemy * StaticSpawner::spawnFly(Resources * resourceManager)
{
    int position;
    //G�n�re une position, cette derni�re devant absolument �tre valide
    do { position = rand() % STATIC_SPAWN_LOCATION_AMOUNT; } while (!spawnLocationsStatus[position]);
    Enemy * enemyToReturn = EnemyFactory::CreateEnemy(spawnLocations[position], resourceManager->getEnemiesSpriteSheet(), TypeEnemy::FLY);
    spawnLocationsStatus[position] = false;
    return enemyToReturn;
}

void StaticSpawner::setSpawnLocationState(const Vector2f spawnLocation, const bool state)
{
  for (int i = 0; i < STATIC_SPAWN_LOCATION_AMOUNT; i++)
  {
    if (spawnLocations[i] == spawnLocation)
    {
      spawnLocationsStatus[i] = state;
      break;
    }
  }
}