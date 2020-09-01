#include "IndicatorBox.h"

/*** Public ***/
IndicatorBox::IndicatorBox(const int16_t x, const int16_t y, const uint8_t width, const uint8_t height, Arduboy2& arduboy) : m_ab(arduboy)
{
  m_hitBox = Rect(x, y, width, height);
}

bool IndicatorBox::collides(const Rect& object) const
{
  return m_ab.collide(m_hitBox, object);
}
