#include "RhythmBeat.h"

/*** Public ***/
RhythmBeat::RhythmBeat(const byte x, const byte y, const byte width, const byte height, const uint8_t button) : m_x(x), m_y(y), m_button(button)
{
  m_hitBox = Rect(x, y, width, height);
}

uint8_t RhythmBeat::getButton() const
{
  return m_button;
}

Rect RhythmBeat::getHitBox() const
{
  return m_hitBox;
}

void RhythmBeat::updatePos()
{
  m_x -= MOVE_SPEED;

  m_hitBox.x = m_x;
}
