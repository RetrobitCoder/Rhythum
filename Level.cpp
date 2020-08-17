#include "Level.h"

#include "Bitmaps.h"

/*** Public ***/
Level::Level()
{
  init();
}

Level::~Level()
{
  for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    m_beats[i].~RhythmBeat();
  }
}

void Level::drawBeats(const Sprites& sprites)
{

  for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(m_usable[i])
    {
     int16_t x = m_beats[i].getX();
     int16_t y = m_beats[i].getY();

      byte buttonFrame = 0;

      switch(m_beats[i].getButton())
      {
        case LEFT_BUTTON:
          buttonFrame = 0;
          break;
        case RIGHT_BUTTON:
          buttonFrame = 1;
          break;
        case UP_BUTTON:
          buttonFrame = 2;
          break;
        case DOWN_BUTTON:
          buttonFrame = 3;
          break;
        case A_BUTTON:
          buttonFrame = 4;
          break;
      }

      sprites.drawSelfMasked(x, y, buttons, buttonFrame);      
    }
  }
}

byte Level::getButton() const
{
  for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(m_usable[i])
    {
      return m_beats[i].getButton();
    }
  }

  // Return first beat if somehow all the beats aren't usable
  return m_beats[0].getButton();
}

Rect Level::getHitBox() const
{
  for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(m_usable[i])
    {
      return Rect(m_beats[i].getX(), m_beats[i].getY(), RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE);
    }
  }

  // Return first beat if somehow all the beats aren't usable // TODO remove? don't need it but just in case loop calls for hitbox when no beats are usable
  return Rect(m_beats[0].getX(), m_beats[0].getY(), 16, 16);
}

void Level::nextLevel()
{
  m_levelID++;

  m_beat = beatSequences[m_levelID];

  for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    m_usable[i] = false;
  }
  
  initBeats();
}

void Level::removeBeat()
{
  for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(m_usable[i])
    {
      m_usable[i] = false;
      break;
    }
  }

  resetBeats();
}

void Level::update()
{
  updateBeats();
}

/*** Private ***/
void Level::init()
{
  m_beat = beatSequences[m_levelID];

  initBeats();
}

void Level::initBeats()
{
  uint16_t beatSequence = m_beat;

  uint8_t index = 0;
  
  while(beatSequence > 0)
  {
    if (beatSequence & mask)
    {
      m_beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE) + m_gap, A_BUTTON);
    }
    else
    {
      byte buttonDirection = random(4);

      switch(buttonDirection)
      {
        case 0:
          m_beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE) + m_gap, LEFT_BUTTON);
          break;
        case 1:
          m_beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE) + m_gap, RIGHT_BUTTON);
          break;
        case 2:
          m_beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE) + m_gap, UP_BUTTON);
          break;
        default:
          m_beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE) + m_gap, DOWN_BUTTON);
          break;
      }
    }
    
     m_usable[index] = true;
    
    beatSequence = beatSequence >> 1;
    index++;
  }
}

void Level::removeBeat(uint8_t index)
{
  m_usable[index] = false;

  resetBeats();
}

void Level::resetBeats()
{
  bool allRemoved = true;

  for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(m_usable[i])
    {
      allRemoved = false;
      break;
    }
  }

  if(allRemoved)
  {
    for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
    {
      m_beats[i].setPos(WIDTH + (i * RHYTHM_BOX_SIZE) + m_gap);
      m_usable[i] = true;
    }
  }
}

void Level::updateBeats()
{
  for(uint8_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(m_usable[i])
    {
      if(m_beats[i].getX() <= WIDTH / 2)
      {
        removeBeat(i);
      }
      else
      {
        m_beats[i].updatePos();
      }
    }
  }
}
