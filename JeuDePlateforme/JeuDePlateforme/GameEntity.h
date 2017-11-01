#pragma once

#include <SFML\Graphics.hpp>
#include "JumpStates.h"

using namespace sf;

class GameEntity : public Sprite
{
public:
  GameEntity();
  GameEntity(const Vector2f position, const Texture& texture);
  ~GameEntity();

  virtual void update();
  void setJumpStatus(const JumpStates value);
  void setYVelocity(const float value);
  void setXVelocity(const float value);
  float getYVelocity() const;
  float getXVelocity() const;
  JumpStates getJumpStatus() const;

private:
  float xVelocity;
  float yVelocity;
  int jumpHeight;
  JumpStates jumpStatus;

  virtual void manageMovement();
  virtual void manageAnimations();
};

