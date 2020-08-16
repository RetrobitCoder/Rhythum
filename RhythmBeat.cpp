#include "RhythmBeat.h"

/*** Public ***/
RhythmBeat::RhythmBeat(int16_t x, uint8_t button) : m_x(x), m_button(button)
{
  m_hitBox = Rect(m_x, 48, 16, 16);
}

uint8_t RhythmBeat::getButton() const
{
  return m_button;
}

Rect RhythmBeat::getHitBox() const
{
  return m_hitBox;
}

void RhythmBeat::setPos(int16_t x)
{
  m_x = x;
  m_hitBox.x = x;
  m_hitBox.y = 48;
}

void RhythmBeat::updatePos()
{
  m_x -= MOVE_SPEED;

  m_hitBox.x = m_x;
}
