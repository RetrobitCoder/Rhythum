#ifndef player_h
#define player_h

#include <Arduboy2.h>

class Player
{
  public:
    Player(){}
    Player(uint8_t avatar);
    ~Player(){}

    /**
     * Amount of damager the player is taking
     * @param amount of damage
     */
    void damage(uint8_t amount);

    /**
     * Draw player info on screen
     */
    void drawPlayerInfo(const Arduboy2& ab, const Sprites& sprite);

     /**
      * Get the amount of damage the player will do
      */
    uint32_t getAttackDamage() const;

    /**
     * Checks if player is out of lives
     * @return lives == 0
     */
    bool isDead() const;

    /**
     * Reset player info
     */
    void reset(uint16_t lives = 3);

    /**
     * Increase streak counter
     * @param bool if perfect hit was made
     */
    void streakIncrease(bool perfectHit = false);
  private:
    uint8_t m_avatarID = 0; 
    uint8_t m_x = WIDTH/2 + 2;

    uint16_t m_lives = 1;
    int m_hp = 255; // Too low? Make it higher?
    uint16_t MAX_HP = 255;
    
    uint32_t m_streak = 0;
    uint32_t m_perfectStreak = 0;
    uint32_t m_attackDamage = 10;

    /**
     * Increase attack damage based on perfect streak count
     */
    void increaseAttack();
};

#endif // player_h
