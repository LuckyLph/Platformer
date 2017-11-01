#include "Hero.h"

Hero::Hero(const Texture& texture)
{
	jumpHeigth = 30;
  setTexture(texture);
  //Initialise les tableaux de intrects pour les animations
  p3_walk[0] = IntRect(0, 0, 70, 97);
  p3_walk[1] = IntRect(73, 0, 70, 97);
  p3_walk[2] = IntRect(146, 0, 70, 97);
  p3_walk[3] = IntRect(0, 98, 70, 97);
  p3_walk[4] = IntRect(73, 98, 70, 97);
  p3_walk[5] = IntRect(146, 98, 70, 97);
  p3_walk[6] = IntRect(219, 0, 70, 97);
  p3_walk[7] = IntRect(292, 0, 70, 97);
  p3_walk[8] = IntRect(219, 98, 70, 97);
  p3_walk[9] = IntRect(365, 0, 70, 97);
  p3_walk[10] = IntRect(292, 98, 70, 97);

	p3_walkFlip[0] = IntRect(0 + 70, 0, -70, 97);
	p3_walkFlip[1] = IntRect(73 + 70, 0, -70, 97);
	p3_walkFlip[2] = IntRect(146 + 70, 0, -70, 97);
	p3_walkFlip[3] = IntRect(0 + 70, 98, -70, 97);
	p3_walkFlip[4] = IntRect(73 + 70, 98, -70, 97);
	p3_walkFlip[5] = IntRect(146 + 70, 98, -70, 97);
	p3_walkFlip[6] = IntRect(219 + 70, 0, -70, 97);
	p3_walkFlip[7] = IntRect(292 + 70, 0, -70, 97);
	p3_walkFlip[8] = IntRect(219 + 70, 98, -70, 97);
	p3_walkFlip[9] = IntRect(365 + 70, 0, -70, 97);
	p3_walkFlip[10] = IntRect(292 + 70, 98, -70, 97);
}


Hero::~Hero()
{
}

//Met à jour le héro
void Hero::update(bool hasReset, int speedMultiplier)
{
	if (hasReset)
	{
		animTick = 0;
	}
	animTick++;
	if (animTick >= HERO_WALK_ANIM_MAX_TICK * speedMultiplier)
	{
		animTick = 0;
	}
	animIndex = animTick / ((HERO_WALK_ANIM_MAX_TICK / HERO_WALK_ANIM_FRAME_QTY) * speedMultiplier);
}

//Met à jour les animations
void Hero::manageAnimations()
{
	if (isGoingLeft)
	{
		if (jumpStatus == Jumping)
		{
			this->setTextureRect(p3_jumpFlip);
		}
		else if (isWalking)
		{
			this->setTextureRect(p3_walkFlip[animIndex]);
		}
		else if (!isWalking)
		{
			this->setTextureRect(p3_standFlip);
		}

	}
	else
	{
		if (jumpStatus == Jumping)
		{
			this->setTextureRect(p3_jump);
		}
		else if (isWalking)
		{
			this->setTextureRect(p3_walk[animIndex]);
		}
		else if (!isWalking)
		{
			this->setTextureRect(p3_stand);
		}
	}
}

//Retourne le JumpState du héro
JumpStates Hero::getJumpStatus()
{
	return jumpStatus;
}

//Set le JumpState du héro à la valeur prise en paramètre
void Hero::setJumpStatus(JumpStates value)
{
	jumpStatus = value;
}

//Set la vélocité en Y selon la valeur prise en paramètre
void Hero::setYVelocity(float value)
{
	yVelocity = value;
}

//Retourne la vélocité en Y du héro
float Hero::getYVelocity()
{
	return yVelocity;
}

//Set la vélocité en X selon la valeur prise en paramètre
void Hero::setXVelocity(float value)
{
	xVelocity = value;
}

//Retourne la vélocité en X du héro
float Hero::getXVelocity()
{
	return xVelocity;
}