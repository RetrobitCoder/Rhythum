#include "RhythmBeat.h"

/*** Public ***/
RhythmBeat::RhythmBeat(int16_t x, uint8_t button) : m_x(x), m_button(button) {}

uint8_t RhythmBeat::getButton() const
{
  return m_button;
}

int16_t RhythmBeat::getX() const
{
  return m_x;
}

int16_t RhythmBeat::getY() const
{
  return m_y;
}

void RhythmBeat::setPos(int16_t x)
{
  m_x = x;
}

void RhythmBeat::updatePos()
{
  m_x -= MOVE_SPEED;
}
