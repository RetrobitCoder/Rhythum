#ifndef enemy_h
#define enemy_h

#include <Arduboy2.h>

class Enemy
{
  public:
    Enemy(){};
    Enemy(size_t avatar, uint32_t attackDamage);
    ~Enemy() = default;

     /**
      * Amount of damager the enemy is taking
      * @param amount of damage
      */
    void damage(size_t amount);

    /**
     * Draw enmey info on screen
     */
    void drawEnemyInfo(const Arduboy2& ab);

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
     // TODO maybe want to read attackDamage from Bitmaps
    void nextEnemy(uint32_t attackDamage = 10);

    /**
     * Reset enemy
     */
    void reset();
  private:
    size_t m_avatarID = 0;
    
    int m_hp = 255; // Too low? Make it higher?
    const uint16_t MAX_HP = 255;

    uint32_t m_attackDamage = 10;
};

#endif // enemy_h
