#include "stdafx.h"
#include "Shape.h"

//#include "ShapeGameManager.h"

Shape::Shape(Vector2 startingPosition) {
  SetName("Blocky");

  SetPosition(startingPosition);

  _jumpTimeout = -1.0f;
  _onGround = true;

  SetColor(1.0f, 1.0f, 0.0f, 1.0f);
  SetDrawShape(ADS_Square);
  SetSize(2.0f);
  // SetSprite("Resources/Images/sven.png");
  SetFixedRotation(true);
  InitPhysics();
}

void Shape::SetUp() {
  theSwitchboard.SubscribeTo(this, "Jump");
}

void Shape::ReceiveMessage(Message* message) {
  String messageName = message->GetMessageName();

  if (messageName == "Jump") {
    if (CanJump()) {
      Jump();
    }
  }

}


void Shape::Update(float dt) {
  if (_jumpTimeout > 0.0f) {
    _jumpTimeout -= dt;
  }


  b2Vec2 currentVelocity = GetBody()->GetLinearVelocity();
  float maxVel = theTuning.GetFloat("BlockyMaxSpeed");
  float xVector = 0.0f;
  if (theController.IsConnected()) {
    xVector = theController.GetLeftThumbVec2().X;
  }
  if (theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)) {
    xVector = 1.0f;
  }
  if (theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)) {
    xVector = -1.0f;
  }
  if (theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW) && theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)) {
    xVector = 0.0f;
  }

  float desiredVelocity = xVector * maxVel;
  float velocityChange = desiredVelocity - currentVelocity.x;
  float impulse = GetBody()->GetMass() * velocityChange;
  ApplyLinearImpulse(Vector2(impulse, 0), Vector2());

  PhysicsActor::Update(dt);
}

void Shape::Render() {
  PhysicsActor::Render();
}

bool Shape::CanJump() {
  if (_jumpTimeout > 0.0f) {
    return false;
  }
  if (!_onGround) {
    return false;
  }

  return true;
}

void Shape::Jump() {
  _jumpTimeout = theTuning.GetFloat("BlockyJumpTimeout");
  //_onGround = false;
  GetBody()->SetLinearVelocity(b2Vec2(0.0f, theTuning.GetFloat("BlockyJumpHeight")));

}

