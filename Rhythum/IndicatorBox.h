#ifndef indicator_box_h
#define indicator_box_h

#include <Arduboy2.h>

class IndicatorBox
{
  public:
    IndicatorBox(){}
    IndicatorBox(const int16_t x, const int16_t y, const uint8_t width, const uint8_t height, Arduboy2& arduboy);
    ~IndicatorBox(){}

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
