#pragma once

#include "Shape.h"

class ShapeGameManager : public GameManager {
public:
  ShapeGameManager();

  //static const int WorldZoom;

  virtual void Update(float dt);
  //virtual void Render();

private:
  Shape* _blocky;

  //bool _debugDraw;

  float _cameraLockMin;
  float _cameraLockMax;
};
