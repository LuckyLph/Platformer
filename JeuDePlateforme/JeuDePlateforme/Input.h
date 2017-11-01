#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Input
{
public:
	Input();
	~Input();

  bool getKeyW() const;
  bool getKeyA() const;
  bool getKeyS() const;
  bool getKeyD() const;
  bool getSpace() const;
};

