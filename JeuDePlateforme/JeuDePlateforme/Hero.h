#pragma once

#include <SFML\Graphics.hpp>
#include "Constants.h"
#include "GameEntity.h"
#include "JumpStates.h"

using namespace sf;

class Hero : public GameEntity
{
public:
	Hero(const Texture&);
	~Hero();

	void manageAnimations();
	void update(bool hasReset, int speedMultiplier);
	JumpStates getJumpStatus();
	void setJumpStatus(JumpStates value);
	void setYVelocity(float value);
	float getYVelocity();
	void setXVelocity(float value);
	float getXVelocity();

	bool getIsGoingLeft() const { return isGoingLeft; }
	void setIsGoingLeft(bool val) { isGoingLeft = val; }
	bool getIsWalking() const { return isWalking; }
	void setIsWalking(bool val) { isWalking = val; }
private:
  int jumpHeigth;
	JumpStates jumpStatus = Standing;
	float yVelocity = 0.0f;
	float xVelocity = 0.0f;
	int animTick = 0;
	int animTickMax = 0;
	int animIndex = 0;
	bool isGoingLeft = false;
	bool isWalking = false;


	IntRect p3_duck = IntRect(365, 98, 70, 97);
	IntRect p3_duckFlip = IntRect(365 + 70, 98, -70, 97);
	IntRect p3_front = IntRect(0, 196, 70, 97);
	IntRect p3_frontFlip = IntRect(0 + 70, 196, -70, 97);
	IntRect	p3_hurt = IntRect(438, 0, 70, 97);
	IntRect	p3_hurtFlip = IntRect(438 + 70, 0, -70, 97);
	IntRect	p3_jump = IntRect(438, 93, 70, 97);
	IntRect	p3_jumpFlip = IntRect(438 + 70, 93, -70, 97);
	IntRect	p3_stand = IntRect(67, 196, 70, 97);
	IntRect	p3_standFlip = IntRect(67 + 70, 196, -70, 97);
	IntRect p3_walk[11];
	IntRect p3_walkFlip[11];

};

