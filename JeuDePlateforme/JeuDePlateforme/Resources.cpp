#include "Resources.h"

Resources::Resources()
{
  loadIntRect();
}


Resources::~Resources()
{
}

//Initialise les textures 
bool Resources::loadTextures()
{
  if (!terrainSpriteSheet.loadFromFile("Content/Sprites/terrainSpriteSheet.png") ||
      !itemSpriteSheet.loadFromFile("Content/Sprites/itemsSpriteSheet.png") ||
      !heroTexture.loadFromFile("Content/Sprites/heroTexture.png") ||
      !p3Texture.loadFromFile("Content/Sprites/Player/p3_spritesheet.png") ||
      !hudSpriteSheet.loadFromFile("Content/Sprites/hudSpriteSheet.png") ||
      !enemiesSpriteSheet.loadFromFile("Content/Sprites/enemiesSpriteSheet.png"))
    return false;
  loadIntRect();
  return true;
}

//Charge les intrects pour accèder au bonnes textures
void Resources::loadIntRect()
{
	//Terrain
  textures[Tiles(132)] = IntRect(0, 792, 70, 70);
  textures[Tiles(60)] = IntRect(0, 360, 70, 70);
  textures[Tiles(55)] = IntRect(504, 288, 70, 70);
  textures[Tiles(127)] = IntRect(504, 720, 70, 70);
  textures[Tiles(81)] = IntRect(648, 432, 70, 70);
  textures[Tiles(69)] = IntRect(648, 360, 70, 70);
  textures[Tiles(57)] = IntRect(648, 288, 70, 70);
  textures[Tiles(45)] = IntRect(648, 216, 70, 70);
  textures[Tiles(9)] = IntRect(648, 0, 70, 70);
  textures[Tiles(140)] = IntRect(576, 792, 70, 70);
  textures[Tiles(138)] = IntRect(432, 792, 70, 70);
  textures[Tiles(43)] = IntRect(504, 216, 70, 70);
  textures[Tiles(102)] = IntRect(432, 576, 70, 70);
  textures[Tiles(28)] = IntRect(288, 144, 70, 70);
  textures[Tiles(16)] = IntRect(288, 72, 70, 70);
  textures[Tiles(7)] = IntRect(504, 0, 70, 70);

	//Items
	textures[Tiles(1000)] = IntRect(0, 0, 70, 70);
	textures[Tiles(1001)] = IntRect(70, 0, 70, 70);
	textures[Tiles(1002)] = IntRect(140,0, 70, 70);
	textures[Tiles(1003)] = IntRect(210, 0, 70, 70);
	textures[Tiles(1004)] = IntRect(280, 0, 70, 70);
	textures[Tiles(1005)] = IntRect(350, 0, 70, 70);
	textures[Tiles(1006)] = IntRect(420, 0, 70, 70);
	textures[Tiles(1007)] = IntRect(490, 0, 70, 70);
	textures[Tiles(1008)] = IntRect(0, 70, 70, 70);
	textures[Tiles(1009)] = IntRect(70, 70, 70, 70);
	textures[Tiles(1010)] = IntRect(140, 70, 70, 70);
	textures[Tiles(1011)] = IntRect(210, 70, 70, 70);
	textures[Tiles(1012)] = IntRect(280, 70, 70, 70);
	textures[Tiles(1019)] = IntRect(210, 140, 70, 70);
	textures[Tiles(1020)] = IntRect(280, 140, 70, 70);
	textures[Tiles(1027)] = IntRect(210, 210, 70, 70);
	textures[Tiles(1028)] = IntRect(280, 210, 70, 70);
}

//Retourne la spritesheet du terrain
Texture& Resources::getTerrainSpriteSheet()
{
  return terrainSpriteSheet;
}

//Retourne la spritesheet des items
Texture& Resources::getItemSpriteSheet()
{
  return itemSpriteSheet;
}

//Retourne la spritesheet du hud
Texture& Resources::getHudSpriteSheet()
{
	return hudSpriteSheet;
}

//Retourne le intrect correspondant à la clé prise en paramètre
IntRect& Resources::getIntRect(const int key, const TextureTypes type)
{
		return textures[Tiles(key)];
}

//Retourne la spritesheet du héro
Texture& Resources::getP3Texture()
{
	return p3Texture;
}

//Retourne la spritesheet des ennemis
Texture& Resources::getEnemiesSpriteSheet()
{
  return enemiesSpriteSheet;
}