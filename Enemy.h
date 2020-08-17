#ifndef enemy_h
#define enemy_h

#include <Arduboy2.h>

class Enemy
{
  public:
    Enemy(){};
    ~Enemy(){};

     /**
      * Amount of damager the enemy is taking
      * @param amount of damage
      */
    void damage(const uint8_t& amount);

    /**
     * Draw enmey info on screen
     */
    void drawEnemy(const Arduboy2& ab, const Sprites& sprite);

    /**
     * Get the amount of damage the enemy will do
     */
    uint32_t getAttackDamage() const;

    /**
     * Checks if enemy is dead
     * @return hp <= 0
     */
    bool isDead() const;

    /**
     * Set up the next enemy to attack
     */
    void nextEnemy();

  private:
    uint8_t m_enemyID = 0;
    int m_hp = 2; // Too low? Make it higher?
    uint16_t MAX_HP = 2;

    uint32_t m_attackDamage = 10;
};

#endif // enemy_h
