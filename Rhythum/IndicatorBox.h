#ifndef indicator_box_h
#define indicator_box_h

#include <Arduboy2.h>

class IndicatorBox
{
  public:
    IndicatorBox(){}
    IndicatorBox(int16_t x, int16_t y, uint8_t width, uint8_t height, Arduboy2& arduboy);
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
