#ifndef indicator_box_h
#define indicator_box_h

#include <Arduboy2.h>

class IndicatorBox
{
  public:
    IndicatorBox(const byte x, const byte y, const byte width, const byte height, const Arduboy2& arduboy);
    ~IndicatorBox() = default;

    /**
     * Checks if object collided with this box
     * @return false, true
     */
    bool collides(const Rect& object) const;
  private:
    Arduboy2 m_ab;
    Rect m_hitBox;
};

#endif // indicator_box_h
