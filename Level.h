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
     * Get hit box of the front most beat
     * @return rect of the hit box 
     */
    Rect getHitBox() const;

    /**
     * Check if game is still in progress for the current level
     * @return false, true
     */
    bool isInprogress() const;

    /**
     * Check if failed to complete level
     * @return false, true
     */
    bool lost() const;

    /**
     * Remove beat at index
     * @param index of beat
     */
    void removeBeat(size_t index);

    /**
     * Update level components
     */
    void update();

    /**
     * Check if completed level
     * @return false, true
     */
    bool won() const;

  private:
    size_t m_levelID = 0;
    
    bool m_levelLost = false;
    bool m_levelWon = false;
    bool m_levelContinue = true;

    const byte RHYTHM_BOX_SIZE = 16;

    uint16_t beat;
    // Max size of a single beat sequence
    const byte MAX_BEAT_SIZE = 25; // TODO might want to remove, might not be used for anything
    // TODO may want to reduce size to save memory
    RhythmBeat beats[25];
    bool usable[25] = { false };

    /**
     * Do setup stuff for level
     */
    void init();

    /**
     * Update beat positions
     */
    void updateBeats();
};

#endif // level_h
