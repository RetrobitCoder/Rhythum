#ifndef rhythm_beat_h
#define rhythm_beat_h

#include <Arduboy2.h>

class RhythmBeat
{
  public:
    RhythmBeat(){}
    RhythmBeat(const byte x, const byte y, const byte width, const byte height, const uint8_t button);
    ~RhythmBeat() = default;

    uint8_t getButton() const;  
    Rect getHitBox() const;
    void updatePos();
    
  private:
    float m_x;
    float m_y;
    float MOVE_SPEED = 0.125;
    uint8_t m_button;
    Rect m_hitBox;
};

#endif // rhythm_beat_h
