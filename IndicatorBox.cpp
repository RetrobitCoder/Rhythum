#include "IndicatorBox.h"

/*** Public ***/
IndicatorBox::IndicatorBox(const byte x, const byte y, const byte width, const byte height, const Arduboy2& arduboy)
{
  ab = arduboy;
  HIT_BOX = Rect(x, y, width, height);
}

bool IndicatorBox::collides(const Rect& object) const
{
  return ab.collide(HIT_BOX, object);
}
