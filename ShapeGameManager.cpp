#include "stdafx.h"
#include "ShapeGameManager.h"

#include "FloatingBlock.h"

//ShapeGameManager* ShapeGameManager::s_ShapeGameManager = NULL;

//const int ShapeGameManager::WorldZoom = 4;

ShapeGameManager::ShapeGameManager() {
  _cameraLockMin = theTuning.GetFloat("CameraLockMin");
  _cameraLockMax = theTuning.GetFloat("CameraLockMblockyX");

  //_debugDraw = false;
  theWorld.SetupPhysics(Vector2(0, -100.0f));
  //theWorld.GetPhysicsWorld().SetDebugDraw(this);
  //this->SetFlags(b2Draw::e_shapeBit);

  _blocky = new Shape(Vector2(-9.0f, -3.0f));
  _blocky->SetUp();
  theWorld.Add(_blocky);

  PhysicsActor* ground = new PhysicsActor();
  ground->SetPosition(0.0f, -11.0f);
  ground->SetSize(100.0f, 5.0f);
  ground->SetColor(0.0f, 1.0f, 0.0f);
  ground->SetDensity(0.0f);
  ground->SetFriction(0.1f);
  ground->SetRestitution(0.0f);
  ground->InitPhysics();
  ground->Tag("ground");
  ground->SetName("Ground");
  theWorld.Add(ground);

  Vector2 botLeft = theCamera.GetWorldMinVertex();
  Vector2 topRight = theCamera.GetWorldMaxVertex();
  float halfWidth = (topRight.X - botLeft.X) * 0.5f;

  PhysicsActor* leftBlocker = new PhysicsActor();
  leftBlocker->SetAlpha(0.0f);
  leftBlocker->SetSize(2.0f, 100.0f);
  leftBlocker->SetPosition((_cameraLockMin - halfWidth) - (leftBlocker->GetSize().X * 0.5f), 0.0f);
  leftBlocker->SetDensity(0.0f);
  leftBlocker->SetFriction(0.1f);
  leftBlocker->SetRestitution(0.0f);
  leftBlocker->InitPhysics();
  leftBlocker->SetName("LeftBLocker");
  theWorld.Add(leftBlocker);

  PhysicsActor* rightBlocker = new PhysicsActor();
  rightBlocker->SetAlpha(0.0f);
  rightBlocker->SetSize(2.0f, 100.0f);
  rightBlocker->SetPosition((_cameraLockMax + halfWidth) + (rightBlocker->GetSize().X * 0.5f), 0.0f);
  rightBlocker->SetDensity(0.0f);
  rightBlocker->SetFriction(0.1f);
  rightBlocker->SetRestitution(0.0f);
  rightBlocker->InitPhysics();
  rightBlocker->SetName("RightBlocker");
  theWorld.Add(rightBlocker);

  FloatingBlock* tam = new FloatingBlock();
  tam->SetPosition(-9.0f, 10.0f);
  tam->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
  tam->SetSize(2.8f);
  // tam->SetSprite("Resources/Images/tam.png");
  tam->SetDensity(0.5f);
  tam->SetFixedRotation(true);
  tam->InitPhysics();
  theWorld.Add(tam);

  FloatingBlock* b = new FloatingBlock();
  b->SetPosition(-5.0f, -2.0f);
  b->InitPhysics();
  theWorld.Add(b);

  FloatingBlock* c = new FloatingBlock();
  c->SetPosition(5.0f, 1.0f);
  c->SetColor(1.0f, 0.0f, 1.0f, 1.0f);
  c->InitPhysics();
  theWorld.Add(c);

  FloatingBlock* d = new FloatingBlock();
  d->SetPosition(-11.0f, 6.0f);
  d->SetColor(0.0f, 0.0f, 0.0f, 1.0f);
  d->InitPhysics();
  theWorld.Add(d);

  ParticleActor* fire = new ParticleActor();
  fire->SetColor(0.8f, 0.5f, 0.0f, 1.0f);
  fire->SetSize(Vector2(0.2f, 0.2f));
  fire->SetPosition(10.0f, -8.0f);
  //fire->SetDrawShape(ADS_Circle);
  fire->SetMaxParticles(500);
  fire->SetParticlesPerSecond(100.0f);
  fire->SetParticleLifetime(1.5f);
  fire->SetSpread(MathUtil::Pi);
  fire->SetEndScale(2.0f);
  fire->SetEndColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
  fire->SetSpeedRange(3.0f, 4.0f);
  fire->SetGravity(Vector2::Zero);
  theWorld.Add(fire);
}

void ShapeGameManager::Update(float dt) {
  float blockyX = _blocky->GetPosition().X;
  if ( (blockyX > _cameraLockMin) && (blockyX < _cameraLockMax) ) {
    if (theCamera.GetLockedActor() != _blocky) {
      theCamera.LockTo(_blocky, true, false);
    }
  }
  else {
    if (theCamera.GetLockedActor() == _blocky) {
      theCamera.LockTo(NULL);

      float camWidth = _cameraLockMax - _cameraLockMin;
      float midX = _cameraLockMax + (camWidth * 0.5f);
      if (_blocky->GetPosition().X < midX) {
        theCamera.SetPosition(_cameraLockMin, 0.0f);
      }
      else {
        theCamera.SetPosition(_cameraLockMax, 0.0f);
      }
    }
  }
}
