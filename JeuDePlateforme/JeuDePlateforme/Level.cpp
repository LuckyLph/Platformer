#include "Level.h"

Level::Level()
{
}


Level::~Level()
{
  delete levelToReturn;
}

//Charge le fichier et le parse puis retourne un tableau d'entiers contenant les informations du niveau
int * Level::loadLevel(const string levelToLoad)
{
	ifstream streamInput;

	//Tentative d'ouverture du fichier
	streamInput.open(levelToLoad);

	//Vérification du résultat
	if (!streamInput)
	{
		string exceptionCaption = "Le fichier " + levelToLoad + " n'existe pas.";
		throw invalid_argument(exceptionCaption);
	}

	string levelContent;
	string rawContent;
	getline(streamInput, rawContent);

	//On enlève des caractères indésirables dans le fichier
	for (size_t i = 0; i < rawContent.size(); ++i)
	{
		if (rawContent[i] != '\0') levelContent += rawContent[i];
	}

	try { parse(levelContent); }
	catch (exception exe) { throw exe; }

	return levelToReturn;
}

//Parse le fichier texte et l'insère dans un tableau
void Level::parse(const string levelContent)
{
  
  levelToReturn = new int[LEVEL_HEIGTH * LEVEL_WIDTH];
	stringstream ssin(levelContent);
  for (int i = 0; i < LEVEL_HEIGTH * LEVEL_WIDTH; i++)
	{
		if (!ssin.good())
			break;
		string tempString;
		ssin >> tempString;
		levelToReturn[i] = stoi(tempString);
	}
}