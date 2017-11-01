#pragma once

#include <SFML\Graphics.hpp>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <map>
#include "Tiles.h"
#include "textureTypes.h"

using namespace sf;
using namespace std;

class Resources
{
public:
	Resources();
	~Resources();


  bool loadTextures();
  Texture& getTerrainSpriteSheet();
  Texture& getItemSpriteSheet();
	Texture& getHudSpriteSheet();
	Texture& getHeroTexture();
  Texture& getP3Texture();
  Texture& getEnemiesSpriteSheet();
  IntRect& getIntRect(const int key, const TextureTypes type);

private:
  Texture terrainSpriteSheet;
  Texture itemSpriteSheet;
  Texture heroTexture;
	Texture p3Texture;
	Texture hudSpriteSheet;
  Texture enemiesSpriteSheet;
  map<Tiles, IntRect> textures;

  void loadIntRect();
};

