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

void Level::drawBeats(const Sprites& sprites)
{
  for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(usable[i])
    {
      Rect box = beats[i].getHitBox();

      byte buttonFrame = 0;

      switch(beats[i].getButton())
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
      
      sprites.drawSelfMasked(box.x, box.y, buttons, buttonFrame);
      
    }
  }
}

byte Level::getButton() const
{
  for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(usable[i])
    {
      return beats[i].getButton();
    }
  }

  // Return first beat if somehow all the beats aren't usable
  return beats[0].getButton();
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

void Level::nextLevel()
{
  m_levelID++;
}

void Level::removeBeat()
{
  for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(usable[i])
    {
      usable[i] = false;
      break;
    }
  }

  resetBeats();
}

void Level::reset()
{
  usable[MAX_BEAT_SIZE] = { true };
}

void Level::update()
{
  updateBeats();
}

/*** Private ***/
void Level::init()
{
  beat = beatSequences[m_levelID];

  initBeats();
}

void Level::initBeats()
{
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
      byte buttonDirection = random(4);

      switch(buttonDirection)
      {
        case 0:
          beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE), HEIGHT - RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, LEFT_BUTTON);
          break;
        case 1:
          beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE), HEIGHT - RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, RIGHT_BUTTON);
          break;
        case 2:
          beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE), HEIGHT - RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, UP_BUTTON);
          break;
        default:
          beats[index] = RhythmBeat(WIDTH + (index * RHYTHM_BOX_SIZE), HEIGHT - RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, RHYTHM_BOX_SIZE, DOWN_BUTTON);
          break;
      }
    }

    usable[index] = true;
    
    beatSequence = beatSequence >> 1;
    index++;
  }
}

void Level::removeBeat(size_t index)
{
  usable[index] = false;

  resetBeats();
}

void Level::resetBeats()
{
  bool allRemoved = true;

  for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(usable[i])
    {
      allRemoved = false;
      break;
    }
  }

  if(allRemoved)
  {
    for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
    {
      beats[i].setPos(WIDTH + (i * RHYTHM_BOX_SIZE));
      usable[i] = true;
    }
  }
}

void Level::updateBeats()
{
  for(size_t i = 0; i < MAX_BEAT_SIZE; i++)
  {
    if(usable[i])
    {
      Rect box = beats[i].getHitBox();

      if(box.x <= WIDTH / 2)
      {
        removeBeat(i);
      }
      else
      {
        beats[i].updatePos();
      }
    }
  }
}
