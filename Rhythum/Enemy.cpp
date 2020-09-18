#include "Enemy.h"

#include "Bitmaps.h"

/*** Public ***/
void Enemy::damage(const uint8_t& amount)
{
  m_hp -= amount;
}

void Enemy::drawEnemy(Arduboy2& ab)
{
  uint8_t w = (1.0 * m_hp) / MAX_HP * (WIDTH/2 - 4);
  ab.fillRect(1,1, w, 2);

  Sprites::drawSelfMasked(0, 0, enemies, m_enemyID);
}

uint32_t Enemy::getAttackDamage() const
{
  return m_attackDamage;
}

bool Enemy::isDead() const
{
  return m_hp <= 0;
}

void Enemy::nextEnemy()
{
  m_enemyID++;
  m_hp = MAX_HP;
}

/*** Private ***/
