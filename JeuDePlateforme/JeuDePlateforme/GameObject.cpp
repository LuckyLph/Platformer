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

//Set la propri�t� collisionBox � la valeur du param�tre
void GameObject::setIsCollisionBox(bool value)
{
	isCollisionBox = value;
}

//Retourne si l'objet est une collisionBox sous forme de bool�en
bool GameObject::getIsCollisionBox() const
{
	return isCollisionBox;
}

//Set la propri�t� typeObject � la valeur du param�tre
void GameObject::setTypeObject(const ObjectTypes _typeObject)
{
	typeObjet = _typeObject;
}

//Retourne la propri�t� TypeObject de l'objet
ObjectTypes GameObject::getTypeObjet() const
{
	return typeObjet;
}