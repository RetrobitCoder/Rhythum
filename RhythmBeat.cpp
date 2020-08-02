#include "RhythmBeat.h"

/*** Public ***/
RhythmBeat::RhythmBeat(const byte x, const byte y, const byte width, const byte height)
{
  this->x = x;
  this->y = y;

  hitBox = Rect(x, y, width, height);
}

Rect RhythmBeat::getHitBox() const
{
  return hitBox;
}

void RhythmBeat::updatePos()
{
  x -= MOVE_SPEED;

  hitBox.x = x;
}
