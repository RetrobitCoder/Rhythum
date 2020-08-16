#ifndef level_h
#define level_h

#include <Arduboy2.h>

#include "RhythmBeat.h"

class Level
{
  public:
    Level(){};
    Level(uint8_t levelNum);
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
    uint8_t m_levelID = 0;

    byte RHYTHM_BOX_SIZE = 16;

    uint16_t m_beat;
    // Max size of a single beat sequence
    byte MAX_BEAT_SIZE = 10;
    
    // TODO may want to reduce size to save memory
    RhythmBeat* m_beats = nullptr;
    bool m_usable[10] = { true };
    
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
