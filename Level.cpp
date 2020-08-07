#include "Level.h"

#include "Bitmaps.h"

/*** Public ***/
Level::Level()
{
  init();
}

Level::Level(size_t levelNum) : m_levelID(levelNum)
{
  init();
}

void Level::drawBeats(const Arduboy2& ab)
{
  for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(usable[i])
    {
      Rect box = beats[i].getHitBox();
      ab.setCursor(box.x, box.y);
      ab.print(beats[i].getButton());
    }
  }
}

Rect Level::getHitBox() const
{
  for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(usable[i])
    {
      return beats[i].getHitBox();
    }
  }

  // Return first beat if somehow all the beats aren't usable
  return beats[0].getHitBox();
}

bool Level::isInprogress() const
{
  return m_levelContinue;
}

bool Level::lost() const
{
  return m_levelLost;
}

void Level::removeBeat(size_t index)
{
  usable[index] = false;
}


void Level::update()
{
  updateBeats();
}

bool Level::won() const
{
  return m_levelWon;
}

/*** Private ***/
void Level::init()
{
  beat = beatSequences[m_levelID];

  uint16_t beatSequence = beatSequences[m_levelID];

  byte index = 0;
  while(beatSequence > 0)
  {

    if (beatSequence & mask)
    {
      beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE), HEIGHT - RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, A_BUTTON);
    }
    else
    {
      // TODO pick random direction
      beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE), HEIGHT - RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, LEFT_BUTTON);
    }

    usable[index] = true;

    beatSequence = beatSequence >> 1;
    index++;
  }
}

void Level::updateBeats()
{
  for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(usable[i])
    {
      beats[i].updatePos();
    }
  }
}
