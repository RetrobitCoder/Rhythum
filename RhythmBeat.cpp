#include "RhythmBeat.h"

/*** Public ***/
RhythmBeat::RhythmBeat(const byte x, const byte y, const byte width, const byte height, const byte button) : m_x(x), m_y(y), m_button(button)
{
  m_hitBox = Rect(x, y, width, height);
}

byte RhythmBeat::getButton() const
{
  return m_button;
}

Rect RhythmBeat::getHitBox() const
{
  return m_hitBox;
}

void RhythmBeat::setPos(size_t x)
{
  m_x = x;
  m_hitBox.x = x;
}

void RhythmBeat::updatePos()
{
  m_x -= MOVE_SPEED;

  m_hitBox.x = m_x;
}
