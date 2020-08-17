#ifndef level_h
#define level_h

#include <Arduboy2.h>

#include "RhythmBeat.h"

// Mask to use for generating beats from a beat sequence
const byte mask = 1;

// TODO add bit more space and make beats faster

// Beat sequence needs at least one 1 in it, at least a 1 on the left most, and 10 bits long
const uint16_t beatSequences[] =
{
  0b1000000001, 0b1000000011, 0b1000000111, 0b1000001111, 0b10000011111
};

class Level
{
  public:
    Level();
    ~Level();

    void drawBeats(const Sprites& sprite);

    /**
     * Get button of the front most beat
     * @return button of beat
     */
    byte getButton() const;
    
    /**
     * Get hit box of the front most beat
     * @return rect of the hit box 
     */
    Rect getHitBox() const;

    /**
     * Advance level number
     */
    void nextLevel();

    /**
     * Remove beat front most beat
     */
    void removeBeat();

    /**
     * Update level components
     */
    void update();

  private:
    uint16_t m_levelID = 0;

    byte RHYTHM_BOX_SIZE = 16;

    uint16_t m_beat;
    // Max size of a single beat sequence
    byte MAX_BEAT_SIZE = 10;
    
    RhythmBeat m_beats[10];
    bool m_usable[10] = { true };

    byte m_gap = 100;
    
    /**
     * Do setup stuff for level
     */
    void init();

    /**
     * Setup beats
     */
    void initBeats();

    /**
     * Remove beat at index
     * @param index of beat
     */
    void removeBeat(uint8_t index);

     /**
     * CReset beats if all beats have been removed
     */
    void resetBeats();

    /**
     * Update beat positions
     */
    void updateBeats();
};

#endif // level_h
