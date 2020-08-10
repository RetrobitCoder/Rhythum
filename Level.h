#ifndef level_h
#define level_h

#include <Arduboy2.h>

#include "RhythmBeat.h"

class Level
{
  public:
    Level();
    Level(size_t levelNum);
    ~Level() = default;

    void drawBeats(const Arduboy2& ab);

    /**
     * Get button of the front most beat
     * @return button of beat
     */
    uint8_t getButton() const;
    
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
    size_t m_levelID = 0;

    const byte RHYTHM_BOX_SIZE = 16;

    uint16_t beat;
    // Max size of a single beat sequence
    const byte MAX_BEAT_SIZE = 10;
    
    // TODO may want to reduce size to save memory
    RhythmBeat beats[10];
    bool usable[10] = { true };
    
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
    void removeBeat(size_t index);

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
