#pragma once

#include "JumpStates.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include "Constants.h"
#include "Hero.h"
#include "Level.h"
#include "Platform.h"
#include "Resources.h"
#include "GameObject.h"
#include "Input.h"
#include "Spike.h"
#include "Lava.h"
#include "Water.h"
#include "TextureTypes.h"
#include "PowerUp.h"
#include "PowerUps.h"
#include "ObjectTypes.h"
#include "Enemy.h"
#include "RandomSpawner.h"
#include "StaticSpawner.h"
#include "Coin.h"


using namespace sf;
using namespace std;

class Game
{
public:
	Game();
	~Game();

	int run();
	bool testMovement(float xMove, float yMove, float xPosition, float yPosition, float sizeX, float sizeY, int xOrigin, int yOrigin);

private:
	bool init();
  bool loadLevel();
	void updateInputs();
  void manageHero();
  void manageEnemies();
	void getEvents();
	void update();
	void draw();
	void unload();
	void resetHeroPosition();
	int jump(int yMove, int xPos, int yPos, int width, int height, int xOrigin, int yOrigin);
	int moveLeftRight(int xMovement, int tempXMovement, int xPos, int yPos, int width, int height, int xOrigin, int yOrigin);
	void drawHud();
	void updateScore();


	Sprite background;
  RectangleShape heroProjectionShape;
  RectangleShape projectionShape;
	RenderWindow mainWin;
  RandomSpawner randomSpawner;
  StaticSpawner * staticSpawner;
	View view;
	Event event;
  Input input;
	Hero * hero;
	Level levelInitializer;
  Resources * resources;
	string levels[LEVEL_AMOUNT];
	string levelsCollisions[LEVEL_AMOUNT];
	string levelsItems[LEVEL_AMOUNT];
	GameObject * level[LEVEL_HEIGTH];
  vector<GameObject> collectibles;
  vector<Enemy> enemies;



	int currentLevel = 0;
	bool keyA = false;
	bool keyS = false;
	bool keyD = false;
	bool keyW = false;
	bool keySpace = false;
	bool walkingAnimationHasReset = false;
	float tempXMovement = 0.0f;
	int heroSpeedMultiplier = 1;
	int powerUpTime = 0;
  int enemyRandomSpawnerTimer = 0;
  int enemyStaticSpawnerTimer = 0;
	bool isElectricity = false;
	int staticSpawnedEnemyQty = 0;
	int randomSpawnedEnemyQty = 0;
	Sprite winning_Flag;

	Sprite hudElement;
	IntRect hudNums[10];
	IntRect hudCoin = IntRect(55, 0, 47, 47);
	IntRect p3 = IntRect(49, 190, 47, 47);
	int p_score = 0;
	int p_score1s = 0;
	int p_score10s = 0;
	int p_score100s = 0;
	int p_score1000s = 0;
};