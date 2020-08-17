#ifndef rhythm_beat_h
#define rhythm_beat_h

#include <Arduboy2.h>

class RhythmBeat
{
  public:
    RhythmBeat(){}
    RhythmBeat(int16_t x, uint8_t button);
    ~RhythmBeat(){}

    /**
     * Get the button to press for this beat
     * @return button
     */
    uint8_t getButton() const;

    /**
     * Get the x position of this beat
     * @return x position
     */
    int16_t getX() const;

    /**
     * Get the y position of this beat
     * @return y position
     */
    int16_t getY() const;

    /**
     * Set the position of the beat
     * @param x position for beat
     */
     void setPos(int16_t x);

    /**
     * Update position of this beat
     */
    void updatePos();
    
  private:
    int16_t m_x = WIDTH;
    int16_t m_y = 48;
    
    byte MOVE_SPEED = 1;
    
    uint8_t m_button;
};

#endif // rhythm_beat_h
