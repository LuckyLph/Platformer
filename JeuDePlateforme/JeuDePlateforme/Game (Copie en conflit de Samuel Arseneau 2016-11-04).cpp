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
    getEvents();

		updateInputs();
    update();
    draw();
  }

  unload();

  return EXIT_SUCCESS;
}

void Game::update()
{
  manageHero();

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
  //mainWin.draw(background);
  for (int i = 0; i < LEVEL_HEIGTH; i++)
  {
    for (int j = 0; j < LEVEL_WIDTH; j++)
    {
      if (level[i][j].getTexture())
      {
        mainWin.draw(level[i][j]);
      }
    }
  }
  mainWin.draw(*hero);
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
      mainWin.close();
    }
    if (event.type == Event::KeyPressed)
    {
			//Retour à la position de départ du niveau.
      if (event.key.code == Keyboard::F1)
      {
        hero->setPosition(Vector2f(140, 140));
        view.setCenter(view.getSize().x / 2 + TILE_SIZE, view.getSize().y / 2 + TILE_SIZE * ZOOM_RATIO + 3);
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
	//heroProjectionShape.setPosition(hero->getPosition());
	JumpStates jumpStatus = hero->getJumpStatus();
	float xMovement = 0.0f;
	float yMovement = hero->getYVelocity();

	if (keyA && !keyD)
	{
		xMovement = -HERO_SPEED;
	}
	else if (keyD && !keyA)
	{
		xMovement = HERO_SPEED;
	}

	if (keySpace /*&& jumpStatus == Standing*/)
	{
		hero->setYVelocity(-10.0f);
		yMovement = hero->getYVelocity();
		//hero->setJumpStatus(Jumping);
	}

	float tempYMovement = yMovement;
	float tempXMovement = xMovement;
	float heroXPos = hero->getPosition().x;
	float heroYPos = hero->getPosition().y;
	//if (hero->getPosition().x + hero->getGlobalBounds().height +1 % TILE_SIZE == 0)
	//{
	//	jumpStatus = Standing;
	//}
	while (!testMovement(tempXMovement, tempYMovement, heroXPos, heroYPos, hero->getGlobalBounds().width, hero->getGlobalBounds().height))
	{
		if (tempYMovement > 0)
		{
			tempYMovement--;
		}
		else if (tempYMovement < 0)
		{
			tempYMovement++;
		}
		else if (xMovement < 0 && tempXMovement < 0)
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
	hero->move(tempXMovement, tempYMovement);
	//if (tempYMovement != 0)
	//{
	//	jumpStatus = Jumping;
	//}
	//else
	//{
	//	hero->setJumpStatus(Standing);
	//}
	//if (tempYMovement != yMovement)
	//{
	//	//hero->setYVelocity(0);
	//	hero->setJumpStatus(Standing);
	//}
	//if (jumpStatus == Jumping && yMovement < 10)
	//{
	//	hero->setYVelocity(yMovement + 1);
	//}
	if (hero->getYVelocity() < 10)
	{
		hero->setYVelocity(hero->getYVelocity() + 1);
	}
	
	

  //bool canMoveLeft = true;
  //bool canMoveDown = true;
  //bool canMoveRight = true;
  //bool canMoveUp = true;
  //bool upLocked = false;
  //bool leftLocked = false;
  //bool rightLocked = false;
  //bool downLocked = false;
  //int leftSpeed = HERO_SPEED;
  //int rightSpeed = HERO_SPEED;
  //int downSpeed = HERO_SPEED;
  //int upSpeed = HERO_SPEED;
  //heroProjectionShape.setPosition(hero->getPosition());
  //for (int i = 0; i < LEVEL_HEIGTH; i++)
  //{
  //  for (int j = 0; j < LEVEL_WIDTH; j++)
		//{
  //      if (canMoveLeft && !leftLocked)
  //      {
  //        for (int y = HERO_SPEED; y > 0; y--)
  //        {
  //          if (testMovement(y, 0, i, j))
  //          {
  //            if (y != HERO_SPEED)
  //            {
  //              canMoveLeft = true;
  //              leftLocked = true;
  //              leftSpeed = y;
  //            }
  //            break;
  //          }
  //          else
  //          {
  //            canMoveLeft = false;
  //          }
  //        }
  //      }
  //      if (canMoveRight && !rightLocked)
  //      {
  //        for (int y = HERO_SPEED; y > 0; y--)
  //        {
  //          if (testMovement(y, 1, i, j))
  //          {
  //            if (y != HERO_SPEED)
  //            {
  //              canMoveRight = true;
  //              rightLocked = true;
  //              rightSpeed = y;
  //            }
  //            break;
  //          }
  //          else
  //          {
  //            canMoveRight = false;
  //          }
  //        }
  //      }
  //      if (canMoveDown && !downLocked)
  //      {
  //        for (int y = HERO_SPEED; y > 0; y--)
  //        {
  //          if (testMovement(y, 2, i, j))
  //          {
  //            if (y != HERO_SPEED)
  //            {
  //              canMoveDown = true;
  //              downLocked = true;
  //              downSpeed = y;
  //            }
  //            break;
  //          }
  //          else
  //          {
  //            canMoveDown = false;
  //          }
  //        }
  //        if (canMoveUp && !upLocked)
  //        {
  //          for (int y = HERO_SPEED; y > 0; y--)
  //          {
  //            if (testMovement(y, 3, i, j))
  //            {
  //              if (y != HERO_SPEED)
  //              {
  //                canMoveUp = true;
  //                upLocked = true;
  //                upSpeed = y;
  //              }
  //              break;
  //            }
  //            else
  //            {
  //              canMoveUp = false;
  //            }
  //          }
  //        }
  //      }
  //  }
  //}
  //hero->Hero::update(keyA, keyS, keyD, keyW, keySpace, canMoveLeft, canMoveDown, canMoveRight, canMoveUp, leftSpeed, rightSpeed, upSpeed, downSpeed);
}

bool Game::testMovement(float xMove , float yMove, float xPosition, float yPosition, float sizeX, float sizeY)
{
	int xPos = xPosition + xMove;
	int yPos = yPosition + yMove;
	projectionShape.setSize(Vector2f(sizeX, sizeY));
	projectionShape.setPosition((float)xPos, (float)yPos);
	int xCollide = (xPos / TILE_SIZE) /*+ (xPos % TILE_SIZE)*/;
	int yCollide = ((yPosition + yMove) / TILE_SIZE) /*+ (yPos % TILE_SIZE)*/;
	//if (xMove > 0)
	//{
	//	xCollide++;
	//}
	//if (yMove > 0)
	//{
	//	yCollide++;
	//}
	for (int i = -1; i < 2; i++)
	{
		xCollide++;
		yCollide++;
		if (xCollide >= 0 && xCollide < LEVEL_WIDTH && yCollide >= 0 && yCollide < LEVEL_HEIGTH)
		{
			if (level[yCollide][xCollide].getIsCollisionBox() == true)
			{
				if (projectionShape.getGlobalBounds().intersects(level[yCollide][xCollide].getGlobalBounds()))
				{
					return false;
				}
			}
		}
	}


	return true;

	//bool test1 = level[i][j].getIsCollisionBox();
	//if (heroProjectionShape.getGlobalBounds().intersects(level[i][j].getGlobalBounds()))
	//	valueToReturn = false;
	//heroProjectionShape.move(speedToTest, 0);
  //bool valueToReturn = true;
  //if (level[i][j].getIsCollisionBox())
  //{
  //  if (direction == 0)
  //  {
  //    heroProjectionShape.move(-speedToTest, 0);
  //    bool test1 = level[i][j].getIsCollisionBox();
  //    if (heroProjectionShape.getGlobalBounds().intersects(level[i][j].getGlobalBounds()))
  //      valueToReturn = false;
  //    heroProjectionShape.move(speedToTest, 0);
  //  }
  //  else if (direction == 1)
  //  {
  //    heroProjectionShape.move(speedToTest, 0);
  //    bool test1 = level[i][j].getIsCollisionBox();
  //    if (heroProjectionShape.getGlobalBounds().intersects(level[i][j].getGlobalBounds()))
  //      valueToReturn = false;
  //    heroProjectionShape.move(-speedToTest, 0);
  //  }
  //  else if (direction == 2)
  //  {
  //    heroProjectionShape.move(0, speedToTest);
  //    bool test1 = level[i][j].getIsCollisionBox();
  //    if (heroProjectionShape.getGlobalBounds().intersects(level[i][j].getGlobalBounds()))
  //      valueToReturn = false;
  //    heroProjectionShape.move(0, -speedToTest);
  //  }
  //  else
  //  {
  //    heroProjectionShape.move(0, -speedToTest);
  //    bool test1 = level[i][j].getIsCollisionBox();
  //    if (heroProjectionShape.getGlobalBounds().intersects(level[i][j].getGlobalBounds()))
  //      valueToReturn = false;
  //    heroProjectionShape.move(0, speedToTest);
  //  }
  //}
  //return valueToReturn;
}

bool Game::init()
{
  currentLevel = 0;
  levels[currentLevel] = "Content/Levels/Niveau0_Terrain.txt";
	levelsCollisions[currentLevel] = "Content/Levels/Niveau0_Collision.txt";
	levelsItems[currentLevel] = "Content/Levels/Niveau0_Items.txt";
  for (int i = 0; i < LEVEL_HEIGTH; i++)
  {
    level[i] = new GameObject[LEVEL_WIDTH];
  }

  if (!resources.loadTextures())
    return false;
  loadLevel();
  hero = new Hero(resources.getHeroTexture());
  hero->setPosition(Vector2f(500, 1050));
  heroProjectionShape.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
	/*heroProjectionShape.setScale(0.50f, 0.50f);
	hero->setScale(0.5f, 0.5f);*/
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
			if (itemsContent[index] != -1)
			{
				int valueTest = itemsContent[index];
				if (itemsContent[index]+1000 == Tiles::spikes)
				{
					Spike spikeToInsert(resources.getItemSpriteSheet(), resources.getIntRect(itemsContent[index] + 1000, Item), j * TILE_SIZE, i * TILE_SIZE);
					objectToInsert = spikeToInsert;
          stateToSet = true;
				}
			}
      if (levelContent[index] != -1)
      {
				if (levelContent[index] == Tiles::liquidWater || levelContent[index] == Tiles::liquidWaterTop_mid)
				{
					Water waterToInsert(resources.getTerrainSpriteSheet(), resources.getIntRect(levelContent[index], Terrain), j * TILE_SIZE, i * TILE_SIZE);
					waterToInsert.setIsHalfBlock(levelContent[index] == Tiles::liquidWaterTop_mid);
					objectToInsert = waterToInsert;
				}
				else if (levelContent[index] == Tiles::liquidLava || levelContent[index] == Tiles::liquidLavaTop_mid)
				{
					Lava lavaToInsert(resources.getTerrainSpriteSheet(), resources.getIntRect(levelContent[index], Terrain), j * TILE_SIZE, i * TILE_SIZE);
					lavaToInsert.setIsHalfBlock(levelContent[index] == Tiles::liquidLavaTop_mid);
					objectToInsert = lavaToInsert;
				}
				else
				{
					Platform platformToInsert(resources.getTerrainSpriteSheet(), resources.getIntRect(levelContent[index], Terrain), j * TILE_SIZE, i * TILE_SIZE);
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
  /*for (int i = 0; i < LEVEL_HEIGTH; i++)
  {
    delete level[i];
  }*/
}