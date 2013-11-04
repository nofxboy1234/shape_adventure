#pragma once
#include "stdafx.h"

class FloatingBlock : public PhysicsActor {
public:
  FloatingBlock();

  void Bonk();

private:
  bool _bonked;

};
