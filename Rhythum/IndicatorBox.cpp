#include "IndicatorBox.h"

/*** Public ***/
IndicatorBox::IndicatorBox(int16_t x, int16_t y, uint8_t width, uint8_t height)
{
  m_hitBox = Rect(x, y, width, height);
}

bool IndicatorBox::collides(const Rect& object) const
{
  return Arduboy2Base::collide(m_hitBox, object);
}
