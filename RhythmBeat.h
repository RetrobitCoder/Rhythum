#ifndef rhythm_beat_h
#define rhythm_beat_h

#include <Arduboy2.h>

class RhythmBeat
{
  public:
    RhythmBeat(){}
    RhythmBeat(const byte x, const byte y, const byte width, const byte height, const byte button);
    ~RhythmBeat() = default;

    /**
     * Get the button to press for this beat
     * @return button
     */
    uint8_t getButton() const;

    /**
     * Get the hit box of this beat
     * @return rect of the hitbox
     */
    Rect getHitBox() const;

    /**
     * Set the position of the beat
     * @param x position for beat
     */
     void setPos(size_t x);

    /**
     * Update position of this beat
     */
    void updatePos();
    
  private:
    float m_x;
    float m_y;
    float MOVE_SPEED = 0.125;
    byte m_button;
    Rect m_hitBox;
};

#endif // rhythm_beat_h
