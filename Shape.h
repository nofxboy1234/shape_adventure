#pragma once
#include "stdafx.h"

class Shape : public PhysicsActor {
public:
  Shape(Vector2 startingPosition);

  void SetUp();

  virtual void Update(float dt);
  virtual void Render();
  virtual void ReceiveMessage(Message* message);

private:
  bool CanJump();
  void Jump();

  float _jumpTimeout;
  bool _onGround;

};
