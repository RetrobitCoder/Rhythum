#ifndef rhythm_beat_h
#define rhythm_beat_h

#include <Arduboy2.h>

class RhythmBeat
{
  public:
    RhythmBeat(){};
    RhythmBeat(const byte x, const byte y, const byte width, const byte height);
    ~RhythmBeat() = default;

    Rect getHitBox() const;
    void updatePos();
  private:
    float x;
    float y;
    const float MOVE_SPEED = 1 / 8;
    Rect hitBox;
};

#endif // rhythm_beat_h
