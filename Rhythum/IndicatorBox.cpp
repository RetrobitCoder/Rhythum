#include "IndicatorBox.h"

/*** Public ***/
IndicatorBox::IndicatorBox(const byte x, const byte y, const byte width, const byte height, Arduboy2& arduboy) : m_ab(arduboy)
{
  m_hitBox = Rect(x, y, width, height);
}

bool IndicatorBox::collides(const Rect& object) const
{
  return m_ab.collide(m_hitBox, object);
}
