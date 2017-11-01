#pragma once

#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Constants.h"

using namespace sf;
using namespace std;

class Level
{
public:
	Level();
	~Level();

	int * loadLevel(const string);
private:
	void parse(const string);

	int * levelToReturn;
};
