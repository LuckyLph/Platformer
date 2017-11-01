#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}

//Retourne l'état de la touche A
bool Input::getKeyA() const
{
	return Keyboard::isKeyPressed(Keyboard::A);
}

//Retourne l'état de la touche S
bool Input::getKeyS() const
{
	return Keyboard::isKeyPressed(Keyboard::S);
}

//Retourne l'état de la touche D
bool Input::getKeyD() const
{
	return Keyboard::isKeyPressed(Keyboard::D);
}

//Retourne l'état de la touche W
bool Input::getKeyW() const 
{
	return Keyboard::isKeyPressed(Keyboard::W);
}

//Retourne l'état de la touche espace
bool Input::getSpace() const
{
	return Keyboard::isKeyPressed(Keyboard::Space);
}