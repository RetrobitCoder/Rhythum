#include "Player.h"

#include "Bitmaps.h"

/*** Public ***/
void Player::damage(const uint8_t& amount)
{
  m_hp -= amount;

  if(m_hp <= 0)
  {
    m_lives--;
    m_hp = MAX_HP;
  }

  m_streak = 0;
  m_perfectStreak = 0;
  m_attackDamage = 10;
}

void Player::drawPlayerInfo(const Arduboy2& ab, const Sprites& sprite)
{
  ab.setCursor(m_x, 2);
  ab.print("Lives ");
  ab.setCursor(m_x + 48, 2);
  ab.print(m_lives);

  ab.setCursor(m_x, 10);
  ab.print("HP");
  uint8_t w = (1.0 * m_hp)/MAX_HP * 45;
  ab.fillRect(m_x + 16, 10, w, 4);

  ab.drawRect(m_x, 18, 32, 28);
  sprite.drawSelfMasked(m_x, 18, avatar, 0);
  ab.setCursor(m_x + 34, 18);

  // Streak
  ab.print("S");
  ab.setCursor(m_x + 42, 18);
  ab.print(m_streak);

  // Damage amount
  ab.setCursor(m_x + 34, 34);
  ab.print("D");
  ab.setCursor(m_x + 42, 34);
  ab.print(m_attackDamage);
}

uint32_t Player::getAttackDamage() const
{
  return m_attackDamage;
}

bool Player::isDead() const
{
  return m_lives == 0;
}

void Player::reset()
{
  m_attackDamage = 10;
  m_hp = 255;
  m_lives = 3;
  m_perfectStreak = 0;
  m_streak = 0;
}

void Player::streakIncrease(bool perfectHit = false)
{
  m_streak++;

  if(perfectHit)
  {
    m_perfectStreak++;

    increaseAttack();
  }
}

/*** Private ***/
void Player::increaseAttack()
{
  m_attackDamage = 10 * m_perfectStreak;
}
