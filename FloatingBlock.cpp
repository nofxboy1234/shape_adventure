#include "stdafx.h"
#include "FloatingBlock.h"

FloatingBlock::FloatingBlock() {
  SetDensity(0.0f);
  SetFriction(0.5f);
  SetRestitution(0.0f);
  SetShapeType(PhysicsActor::SHAPETYPE_BOX);
  SetSize(6.0f, 2.0f);
  SetColor(1.0f, 1.0f, 0.0f, 1.0f);

  _bonked = false;

  Tag("ground");
  Tag("floating_block");
}

void FloatingBlock::Bonk() {
  if (!_bonked) {
    sysLog.Log("BONK!");
    _bonked = true;
  }

}


