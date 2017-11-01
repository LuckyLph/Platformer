#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::GameObject(Texture& texture, IntRect rect, int x, int y, ObjectTypes _typeObjet)
{
  this->setTextureRect(rect);
  this->setPosition((float)x, (float)y);
  this->setTexture(texture);
	typeObjet = _typeObjet;
}


GameObject::~GameObject()
{
}

//Set la propriété collisionBox à la valeur du paramètre
void GameObject::setIsCollisionBox(bool value)
{
	isCollisionBox = value;
}

//Retourne si l'objet est une collisionBox sous forme de booléen
bool GameObject::getIsCollisionBox() const
{
	return isCollisionBox;
}

//Set la propriété typeObject à la valeur du paramètre
void GameObject::setTypeObject(const ObjectTypes _typeObject)
{
	typeObjet = _typeObject;
}

//Retourne la propriété TypeObject de l'objet
ObjectTypes GameObject::getTypeObjet() const
{
	return typeObjet;
}