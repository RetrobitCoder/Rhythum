#include "Enemy.h"

#include "Bitmaps.h"

/*** Public ***/
Enemy::Enemy(size_t avatar, uint32_t attackDamage) : m_avatarID(avatar), m_attackDamage(attackDamage) {};

void Enemy::damage(size_t amount)
{
  m_hp -= amount;
}

void Enemy::drawEnemyInfo(const Arduboy2& ab)
{
  uint8_t w = (1.0 * m_hp) / MAX_HP * (WIDTH/2 - 4);
  ab.fillRect(2,2, w, 6);

  ab.drawRect(0,0,WIDTH/2 - 1, HEIGHT);
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
  m_avatarID++;
  m_attackDamage = attackDamage;
  m_hp = MAX_HP;
}

void Enemy::reset()
{
  m_hp = MAX_HP;
}

/*** Private ***/
