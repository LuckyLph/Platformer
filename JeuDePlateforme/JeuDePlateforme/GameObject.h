#pragma once

#include <SFML\Graphics.hpp>
#include "ObjectTypes.h"

using namespace sf;

class GameObject : public Sprite
{
public:
	GameObject();
  GameObject(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObjet);
	~GameObject();
	void setIsCollisionBox(bool value);
	bool getIsCollisionBox() const;
	ObjectTypes getTypeObjet() const;
	void setTypeObject(const ObjectTypes _typeObject);

private:
	bool isCollisionBox = false;
	ObjectTypes typeObjet;
};

