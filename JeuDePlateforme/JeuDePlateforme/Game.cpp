#define _USE_MATH_DEFINES

#include "Game.h"

Game::Game()
{
  //On place dans le contructeur ce qui permet à la game elle-même de fonctionner
  mainWin.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH, 32), "Jeu de Plateforme");
  view.setSize(mainWin.getSize().x, mainWin.getSize().y);
  view.zoom(ZOOM_RATIO);
  view.setCenter(view.getSize().x / 2 + TILE_SIZE, view.getSize().y / 2 + TILE_SIZE * ZOOM_RATIO + 3);
  mainWin.setView(view);
  mainWin.setVerticalSyncEnabled(true); //Équivalent... normalement

}


Game::~Game()
{
  unload();
}

int Game::run()
{
  if (!init())
  {
    cout << "Le chargement du fichier a echoue !";
    return EXIT_FAILURE;
  }

  while (mainWin.isOpen())
  {
		if (p_score >= 100)
		{
			cout << "YOU WIN!";
			exit(0);
		}
		else
		{
			getEvents();

			updateInputs();
			update();
			draw();
		}
  }

  unload();

  return EXIT_SUCCESS;
}

void Game::update()
{
	manageHero();
	manageEnemies();
	//View
	Vector2f heroPos = hero->getPosition();
	if (heroPos.x > view.getSize().x / 2 + TILE_SIZE - 3 && heroPos.x < LEVEL_WIDTH * TILE_SIZE - view.getSize().x / 2 - TILE_SIZE)
	{
		view.move(heroPos.x - view.getCenter().x, 0);
	}
}

void Game::draw()
{
  mainWin.clear();
  mainWin.setView(view);
  mainWin.draw(background);
  for (int i = 0; i < LEVEL_HEIGTH; i++)
  {
    for (int j = 0; j < LEVEL_WIDTH; j++)
    {
      mainWin.draw(level[i][j]);
    }
  }
  for (int i = 0; i < enemies.size(); i++)
  {
    mainWin.draw(enemies[i]);
  }
	hero->manageAnimations();
  mainWin.draw(*hero);
	updateScore();
	drawHud();
	mainWin.draw(winning_Flag);
  mainWin.display();
}

void Game::getEvents()
{
  //On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
  while (mainWin.pollEvent(event))
  {
    //x sur la fenêtre
    if (event.type == Event::Closed)
    {
      unload();
      exit(0);
    }
    if (event.type == Event::KeyPressed)
    {
			//Retour à la position de départ du niveau.
      if (event.key.code == Keyboard::F1)
      {
				resetHeroPosition();
      }
      else if (event.key.code == Keyboard::Escape)
      {
        unload();
        exit(0);
      }
    }
  }
}

void Game::updateInputs()
{
	keyA = input.getKeyA();
	keyS = input.getKeyS();
	keyD = input.getKeyD();
	keyW = input.getKeyW();
	keySpace = input.getSpace();
}

void Game::manageHero()
{
	if (powerUpTime > 0)
	{
		powerUpTime--;
	}
	else
	{
		heroSpeedMultiplier = 1;
		isElectricity = false;
		hero->setColor(Color::White);
	}
	
  for (int i = 0; i < enemies.size(); i++)
  {
    if (enemies[i].getGlobalBounds().intersects(hero->getGlobalBounds()) && !isElectricity)
    {
      resetHeroPosition();
    }
    else if (enemies[i].getGlobalBounds().intersects(hero->getGlobalBounds()))
    {
      string classType = typeid(enemies[i]).name();
      if (classType != "Fly")
        randomSpawner.setSpawnLocationState(enemies[i].getStartingPosition(), true);
      else
        staticSpawner->setSpawnLocationState(enemies[i].getStartingPosition(), true);
      enemies.erase(enemies.begin() + i);
			staticSpawnedEnemyQty++;
    }
  }

	float xMovement = 0.0f;
	float yMovement = 0.0f;
	float tempYMovement = 0.0f;
	int heroXPos = hero->getPosition().x;
	int heroYPos = hero->getPosition().y;
	int heroWidth = hero->getGlobalBounds().width;
	int heroHeight = hero->getGlobalBounds().height;
	int xPos = hero->getPosition().x / TILE_SIZE;
	int yPos = hero->getPosition().y / TILE_SIZE;
	//////////////////////////////////////////////////////////////////////////

	//Collisions avec un autre GameObject que platform
	xPos = hero->getPosition().x / TILE_SIZE;
	yPos = hero->getPosition().y / TILE_SIZE;
	GameObject toVerify;
	if (yPos < LEVEL_HEIGTH)
	{
		xPos = hero->getPosition().x / TILE_SIZE;
		yPos = (hero->getPosition().y + 30) / TILE_SIZE;

		toVerify = level[yPos][xPos];
		if (toVerify.getTypeObjet() == ObjectTypes::OBJECT_LAVA)
		{
			resetHeroPosition();
		}

		toVerify = level[yPos - 1][xPos];
		if (toVerify.getTypeObjet() == ObjectTypes::OBJECT_WATER)
		{
			resetHeroPosition();
		}
	}
	else //Le hero tombe dans un trou.
	{
		resetHeroPosition();
	}

	//////////////////////////////////////////////////////////////////////////
	//UP-DOWN
	if (keySpace)
	{
		if (hero->getJumpStatus() == Standing)
		{
			hero->setYVelocity(-20.0f);
			yMovement = hero->getYVelocity();
			hero->setJumpStatus(Jumping);
		}
		else if (keyA && !testMovement(-HERO_SPEED, 0, heroXPos, heroYPos, 70, 90, hero->getOrigin().x, hero->getOrigin().y) &&
						 hero->getYVelocity() >= 0 && level[yPos][xPos - 1].getTypeObjet() != OBJECT_MAPSIDE)
		{
			hero->setYVelocity(-20.0f);
			yMovement = hero->getYVelocity();
			hero->setJumpStatus(Jumping);

			hero->setXVelocity(6.0f);
		}
		else if (keyD && !testMovement(HERO_SPEED, 0, heroXPos, heroYPos, 70, 90,  hero->getOrigin().x, hero->getOrigin().y) &&
						 hero->getYVelocity() >= 0 && level[yPos][xPos + 1].getTypeObjet() != OBJECT_MAPSIDE)
		{
			hero->setYVelocity(-20.0f);
			yMovement = hero->getYVelocity();
			hero->setJumpStatus(Jumping);

			hero->setXVelocity(-6.0f);
		}
	}
	yMovement = hero->getYVelocity();
	tempYMovement = yMovement;
	tempXMovement = xMovement;
	heroXPos = hero->getPosition().x;
	heroYPos = hero->getPosition().y;

	tempYMovement = jump(tempYMovement, heroXPos, heroYPos, 70, 90, hero->getOrigin().x, hero->getOrigin().y);
	hero->move(tempXMovement, tempYMovement);

	//On gère la gravité et le JumpStatus du hero.
	heroXPos = hero->getPosition().x;
	heroYPos = hero->getPosition().y;
  xPos = hero->getPosition().x / TILE_SIZE;
	yPos = hero->getPosition().y / TILE_SIZE;
	
	if (tempYMovement == 0)
	{
		if (!testMovement(0, 20, heroXPos, heroYPos, hero->getGlobalBounds().width, hero->getGlobalBounds().height, hero->getOrigin().x, hero->getOrigin().y) && hero->getJumpStatus() == Jumping)
		{
			hero->setJumpStatus(Standing);
		}
		if (!testMovement(0, -20, heroXPos, heroYPos, hero->getGlobalBounds().width, hero->getGlobalBounds().height, hero->getOrigin().x, hero->getOrigin().y) && hero->getJumpStatus() == Jumping)
		{
			hero->setYVelocity(0);
		}
	}
	else
	{
		hero->setJumpStatus(Jumping);
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//LEFT-RIGHT
	yMovement = 0.0f;
	if (hero->getXVelocity() == 0)
	{
		if (keyA && !keyD)
		{
			xMovement = -HERO_SPEED * heroSpeedMultiplier;
			hero->update(walkingAnimationHasReset, heroSpeedMultiplier);
			hero->setIsGoingLeft(true);
			hero->setIsWalking(true);
			walkingAnimationHasReset = false;
		}
		else if (keyD && !keyA)
		{
			xMovement = HERO_SPEED * heroSpeedMultiplier;
			hero->update(walkingAnimationHasReset, heroSpeedMultiplier);
			hero->setIsGoingLeft(false);
			hero->setIsWalking(true);
			walkingAnimationHasReset = false;
		}
		else
		{
			hero->setIsWalking(false);
			walkingAnimationHasReset = true;
		}
	}

	tempYMovement = yMovement;
	tempXMovement = xMovement + hero->getXVelocity();
	heroXPos = hero->getPosition().x;
	heroYPos = hero->getPosition().y;
	tempXMovement = moveLeftRight(xMovement, tempXMovement, heroXPos, heroYPos, 70, 90, hero->getOrigin().x, hero->getOrigin().y);
	hero->move(tempXMovement, 0);
	if (tempXMovement == 0)
	{
		hero->setXVelocity(0);
	}
	//////////////////////////////////////////////////////////////////////////

	if (hero->getYVelocity() < 10)
	{
		hero->setYVelocity(hero->getYVelocity() + 1);
	}
	if (hero->getXVelocity() < 0)
	{
		hero->setXVelocity(hero->getXVelocity() + 1);
	}
	else if (hero->getXVelocity() > 0)
	{
		hero->setXVelocity(hero->getXVelocity() - 1);
	}
 }

 bool Game::testMovement(float xMove, float yMove, float xPosition, float yPosition, float sizeX, float sizeY, int xOrigin, int yOrigin)
{
	bool toReturn = true;
	int xPos = xPosition + xMove;
	int yPos = yPosition + yMove;
	projectionShape.setSize(Vector2f(sizeX, sizeY));
	projectionShape.setPosition((float)xPos, (float)yPos);
	projectionShape.setOrigin((float)xOrigin, (float)yOrigin);
	int xCollide = (xPos / TILE_SIZE);
	int yCollide = (yPos / TILE_SIZE);

	for (int i = -1; i < 3; i++)
	{
		int tempXCollide = xCollide + i;
		for (int j = -1; j < 3; j++)
		{
			int tempYCollide = yCollide + j;
			if (tempXCollide >= 0 && tempXCollide < LEVEL_WIDTH && tempYCollide >= 0 && tempYCollide < LEVEL_HEIGTH)
			{
				GameObject toVerify = level[tempYCollide][tempXCollide];

				//SPECIAL. Test de collision du hero avec un spike.
				if (toVerify.getTypeObjet() == OBJECT_SPIKES)
				{
					yPos = (hero->getPosition().y - 50);
					xPos = (hero->getPosition().x);
					projectionShape.setPosition((float)xPos, (float)yPos);
					if (projectionShape.getGlobalBounds().intersects(toVerify.getGlobalBounds()))
					{
						resetHeroPosition();
					}
				}
				if (toVerify.getTypeObjet() == ObjectTypes::OBJECT_COIN)
				{
					yPos = (hero->getPosition().y - 50);
					xPos = (hero->getPosition().x);
					projectionShape.setPosition((float)xPos, (float)yPos);
					if (projectionShape.getGlobalBounds().intersects(toVerify.getGlobalBounds()))
					{
						level[tempYCollide][tempXCollide].setTypeObject(OBJECT_NULL);
						level[tempYCollide][tempXCollide].setPosition(-6669, -6669);


						p_score += 10;
						if (p_score > 9999)
						{
							p_score = 9999;
						}
					}
				}
				if (toVerify.getTypeObjet() == ObjectTypes::OBJECT_BLUEPOWERUP || toVerify.getTypeObjet() == ObjectTypes::OBJECT_GREENPOWERUP)
				{
					yPos = (hero->getPosition().y - 50);
					xPos = (hero->getPosition().x);
					projectionShape.setPosition((float)xPos, (float)yPos);
					if (projectionShape.getGlobalBounds().intersects(toVerify.getGlobalBounds()))
					{
						powerUpTime = 60 * 5;
						if (toVerify.getTypeObjet() == ObjectTypes::OBJECT_BLUEPOWERUP)
						{
							heroSpeedMultiplier = 1;
							isElectricity = true;
							hero->setColor(Color::Blue);

						}
						else //OBJECT_GREENPOWERUP
						{
							heroSpeedMultiplier = 2;
							isElectricity = false;
							hero->setColor(Color::White);
						}
						level[tempYCollide][tempXCollide].setTypeObject(OBJECT_NULL);
						level[tempYCollide][tempXCollide].setPosition(-6669, -6669);
					}
				}

				//Test de collision normal.
				if (toVerify.getIsCollisionBox() == true || (toVerify.getTypeObjet() == OBJECT_SPIKES && xMove != 0))
				{
					yPos = yPosition + yMove;
					xPos = xPosition + xMove;
					projectionShape.setPosition((float)xPos, (float)yPos);
					if (projectionShape.getGlobalBounds().intersects(level[tempYCollide][tempXCollide].getGlobalBounds()))
					{
						toReturn = false;
					}
				}
			}
		}
	}

	return toReturn;
}

void Game::manageEnemies()
{
	if (enemyRandomSpawnerTimer >= ENEMY_RANDOM_SPAWN_DELAY && randomSpawnedEnemyQty < RANDOM_SPAWN_LOCATION_AMOUNT)
  {
    enemies.push_back(*randomSpawner.spawnEnemy(resources));
		int index = enemies.size() - 1;
		enemies[index].setXVelocity(ENEMY_SPEED);
		enemies[index].setPosition(enemies[index].getStartingPosition().x, (enemies[index].getStartingPosition().y + (TILE_SIZE - enemies[index].getTextureRect().height)));
    enemyRandomSpawnerTimer = 0;
		randomSpawnedEnemyQty++;
  }
	if (enemyStaticSpawnerTimer >= ENEMY_STATIC_SPAWN_DELAY && staticSpawnedEnemyQty < STATIC_SPAWN_LOCATION_AMOUNT)
	{
    Enemy flyToSpawn = *staticSpawner->spawnFly(resources);
		flyToSpawn.setPosition(staticSpawner->getPosition());
		flyToSpawn.setXVelocity(ENEMY_SPEED);
		enemies.push_back(flyToSpawn);
		enemyStaticSpawnerTimer = 0;
		staticSpawnedEnemyQty++;
  }
  enemyRandomSpawnerTimer++;
  enemyStaticSpawnerTimer++;

  for (int i = 0; i < enemies.size(); i++)
  {
		int xPos = enemies[i].getPosition().x;
		int yPos = enemies[i].getPosition().y;
		int width = enemies[i].getGlobalBounds().width;
		int height = enemies[i].getGlobalBounds().height;
		int xMove = enemies[i].getXVelocity();
		int tempXMove = moveLeftRight(xMove, xMove, xPos, yPos, width, height, 0, 0);
		if (enemies[i].getXVelocity() < 0)
		{
			if (testMovement(0, 10, enemies[i].getPosition().x + enemies[i].getXVelocity() -width, enemies[i].getPosition().y, width, height, 0, 0) ||
				enemies[i].getPosition().x <= enemies[i].getStartingPosition().x - ENEMY_HORIZONTAL_OFFSET || tempXMove == 0)
			{
				enemies[i].setXVelocity(ENEMY_SPEED);
			}
		}
		else
		{
			if (testMovement(0, 10, enemies[i].getPosition().x + enemies[i].getXVelocity() + width, enemies[i].getPosition().y, width, height, 0, 0) ||
					enemies[i].getPosition().x >= enemies[i].getStartingPosition().x + ENEMY_HORIZONTAL_OFFSET || tempXMove == 0)
			{
				enemies[i].setXVelocity(-ENEMY_SPEED);
			}
		}
		enemies[i].move(tempXMove, 0);
  }


}

bool Game::init()
{
  currentLevel = 0;
  levels[currentLevel] = "Content/Levels/Niveau0_Terrain.txt";
	levelsCollisions[currentLevel] = "Content/Levels/Niveau0_Collision.txt";
	levelsItems[currentLevel] = "Content/Levels/Niveau0_Items.txt";
  resources = new Resources();
  for (int i = 0; i < LEVEL_HEIGTH; i++)
  {
    level[i] = new GameObject[LEVEL_WIDTH];
  }

  if (!resources->loadTextures())
    return false;

	hudNums[0] = IntRect(230, 0, 30, 38);
	hudNums[1] = IntRect(196, 41, 26, 37);
	hudNums[2] = IntRect(55, 98, 32, 38);
	hudNums[3] = IntRect(239, 80, 28, 38);
	hudNums[4] = IntRect(238, 122, 29, 38);
	hudNums[5] = IntRect(238, 162, 28, 38);
	hudNums[6] = IntRect(230, 40, 30, 38);
	hudNums[7] = IntRect(226, 206, 32, 39);
	hudNums[8] = IntRect(192, 206, 32, 40);
	hudNums[9] = IntRect(196, 0, 32, 39);


  loadLevel();
  hero = new Hero(resources->getP3Texture());
	hero->manageAnimations();
	//hero->setOrigin(0, (hero->getGlobalBounds().height) - 70);
	hero->setPosition(Vector2f(70, 950));
	heroProjectionShape.setSize(Vector2f(hero->getGlobalBounds().width, hero->getGlobalBounds().height));
	hudElement.setTexture(resources->getHudSpriteSheet());
	winning_Flag.setTexture(resources->getItemSpriteSheet());
	winning_Flag.setTextureRect(IntRect(210, 140, 70, 70));
	return true;
}

bool Game::loadLevel()
{
  int * levelContent;
	int * collisionContent;
	int * itemsContent;
  try
  {
    levelContent = levelInitializer.loadLevel(levels[currentLevel]);
    collisionContent = levelInitializer.loadLevel(levelsCollisions[currentLevel]);
    itemsContent = levelInitializer.loadLevel(levelsItems[currentLevel]);
  }
  catch (exception exe)
  {
    cout << "Le chargement du fichier a echoue";
    return false;
  }

  int index = 0;
  bool stateToSet = false;
	GameObject objectToInsert;
  for (int i = 0; i < LEVEL_HEIGTH; i++)
  {
    for (int j = 0; j < LEVEL_WIDTH; j++)
    {

		//Item Content
		if (itemsContent[index] != -1)
		{
			int valueTest = itemsContent[index];
			if (itemsContent[index]+1000 == Tiles::spikes)
			{
        Spike spikeToInsert(resources->getItemSpriteSheet(), resources->getIntRect(itemsContent[index] + 1000, ITEM), j * TILE_SIZE, (i * TILE_SIZE) + 7, ObjectTypes::OBJECT_SPIKES);
				objectToInsert = spikeToInsert;
				stateToSet = false;
			}
			else if (itemsContent[index] + 1000 == Tiles::coin_gold)
			{
				//Create coin;
				Coin coinToInsert(resources->getItemSpriteSheet(), resources->getIntRect(itemsContent[index] + 1000, ITEM), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_COIN);
				objectToInsert = coinToInsert;
				stateToSet = false;

			}
			else if (itemsContent[index] + 1000 == Tiles::gem_blue)
			{
				//Create blue gem and powerup;
        PowerUp powerUpToInsert(resources->getItemSpriteSheet(), resources->getIntRect(itemsContent[index] + 1000, ITEM), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_BLUEPOWERUP, ELECTRICITY);
				objectToInsert = powerUpToInsert;
				stateToSet = false;
			}
			else if (itemsContent[index] + 1000 == Tiles::gem_green)
			{
				//Create blue gem and powerup;
        PowerUp powerUpToInsert(resources->getItemSpriteSheet(), resources->getIntRect(itemsContent[index] + 1000, ITEM), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_GREENPOWERUP, SUPERSPEED);
				objectToInsert = powerUpToInsert;
				stateToSet = false;
			}
			level[i][j] = objectToInsert;
			level[i][j].setIsCollisionBox(stateToSet);
		}

			//Level Content
      if (levelContent[index] != -1)
      {
				if (levelContent[index] == Tiles::liquidWater || levelContent[index] == Tiles::liquidWaterTop_mid)
				{
					Water waterToInsert(resources->getTerrainSpriteSheet(), resources->getIntRect(levelContent[index], TERRAIN), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_WATER);
					waterToInsert.setIsHalfBlock(levelContent[index] == Tiles::liquidWaterTop_mid);
					objectToInsert = waterToInsert;
					stateToSet = false;
				}
				else if (levelContent[index] == Tiles::liquidLava || levelContent[index] == Tiles::liquidLavaTop_mid)
				{
					Lava lavaToInsert(resources->getTerrainSpriteSheet(), resources->getIntRect(levelContent[index], TERRAIN), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_LAVA);
					lavaToInsert.setIsHalfBlock(levelContent[index] == Tiles::liquidLavaTop_mid);
					objectToInsert = lavaToInsert;
					stateToSet = false;
				}
				else if (levelContent[index] == Tiles::boxExplosive)
				{
          Platform platformToInsert(resources->getTerrainSpriteSheet(), resources->getIntRect(levelContent[index], TERRAIN), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_HOLE);
					objectToInsert = platformToInsert;
					stateToSet = false;
				}
				else if (levelContent[index] == 55)
				{
          Platform platformToInsert(resources->getTerrainSpriteSheet(), resources->getIntRect(levelContent[index], TERRAIN), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_MAPSIDE);
					objectToInsert = platformToInsert;
					stateToSet = true;
				}
        else if (levelContent[index] == 81)
        {
          StaticSpawner * spawnerToInsert = new StaticSpawner(resources->getTerrainSpriteSheet(), resources->getIntRect(levelContent[index], TERRAIN), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_MAPSIDE);
          objectToInsert = *spawnerToInsert;
          staticSpawner = spawnerToInsert;
          stateToSet = true;
        }
				else
				{
          Platform platformToInsert(resources->getTerrainSpriteSheet(), resources->getIntRect(levelContent[index], TERRAIN), j * TILE_SIZE, i * TILE_SIZE, ObjectTypes::OBJECT_TILES);
					objectToInsert = platformToInsert;
					stateToSet = true;
				}
        level[i][j] = objectToInsert;
        level[i][j].setIsCollisionBox(stateToSet);
      }
      index++;
    }
  }

  return true;
}

void Game::unload()
{
  delete resources;
  delete hero;
  delete staticSpawner;
  for (int i = 0; i < LEVEL_HEIGTH; i++)
  {
    delete[] level[i];
  }
}

void Game::resetHeroPosition()
{
	p_score -= 50;
	if (p_score < 0)
	{
		p_score = 0;
	}
	hero->setPosition(Vector2f(70, 1020));
	view.setCenter(view.getSize().x / 2 + TILE_SIZE, view.getSize().y / 2 + TILE_SIZE * ZOOM_RATIO + 3);
}

int Game::jump(int yMove, int xPos, int yPos, int width, int height, int xOrigin, int yOrigin)
{
	while (!testMovement(0, yMove, xPos, yPos, width, height, xOrigin, yOrigin))
	{
		if (yMove > 0)
		{
			yMove--;
		}
		else if (yMove < 0)
		{
			yMove++;
		}
		else
		{
			break;
		}
	}
	return yMove;
}

int Game::moveLeftRight(int xMovement, int tempXMovement, int xPos, int yPos, int width, int height, int xOrigin, int yOrigin)
{
	while (!testMovement(tempXMovement, 0, xPos, yPos, width, height, xOrigin, yOrigin))
	{
		if (xMovement < 0 && tempXMovement < 0)
		{
			tempXMovement++;
		}
		else if (xMovement > 0 && tempXMovement > 0)
		{
			tempXMovement--;
		}
		else
		{
			break;
		}
	}
	return tempXMovement;
}

void Game::drawHud()
{
	int xOffset = (view.getCenter().x - view.getSize().x / 2);
	int yOffset = (view.getCenter().y - view.getSize().y / 2);

	hudElement.setTextureRect(hudCoin);
	hudElement.setPosition(xOffset + 40, yOffset + 45);
	mainWin.draw(hudElement);

	hudElement.setTextureRect(hudNums[p_score1000s]);
	hudElement.setPosition(xOffset + 100, yOffset + 50);
	mainWin.draw(hudElement);

	hudElement.setTextureRect(hudNums[p_score100s]);
	hudElement.setPosition(xOffset + 130, yOffset + 50);
	mainWin.draw(hudElement);

	hudElement.setTextureRect(hudNums[p_score10s]);
	hudElement.setPosition(xOffset + 160, yOffset + 50);
	mainWin.draw(hudElement);

	hudElement.setTextureRect(hudNums[p_score1s]);
	hudElement.setPosition(xOffset + 190, yOffset + 50);
	mainWin.draw(hudElement);
}

void Game::updateScore()
{
	int tempValue = p_score;
	p_score1s = tempValue % 10;

	tempValue = tempValue / 10;
	p_score10s = tempValue % 10;

	tempValue = tempValue / 10;
	p_score100s = tempValue % 10;

	tempValue = tempValue / 10;
	p_score1000s = tempValue % 10;
}

