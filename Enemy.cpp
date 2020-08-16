#include "Enemy.h"

#include "Bitmaps.h"

/*** Public ***/
Enemy::Enemy(uint8_t avatar, uint32_t attackDamage) : m_enemyID(avatar), m_attackDamage(attackDamage) {};

void Enemy::damage(uint8_t amount)
{
  m_hp -= amount;
}

void Enemy::drawEnemy(const Arduboy2& ab, const Sprites& sprite)
{
  uint8_t w = (1.0 * m_hp) / MAX_HP * (WIDTH/2 - 4);
  ab.fillRect(1,1, w, 2);

  ab.drawRect(0,0,WIDTH/2 - 1, HEIGHT);

  sprite.drawSelfMasked(0, 0, enemies, m_enemyID);
}

uint32_t Enemy::getAttackDamage() const
{
  return m_attackDamage;
}

bool Enemy::isDead() const
{
  return m_hp <= 0;
}

void Enemy::nextEnemy(uint32_t attackDamage = 10)
{
  m_enemyID++;
  m_attackDamage = attackDamage;
  m_hp = MAX_HP;
}

/*** Private ***/
