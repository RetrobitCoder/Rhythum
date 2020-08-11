// TODO Try to meet dynamic memory below 70%, may have a chance to become un-updateable withou flash light mode
// TODO art
// TODO pause, win, gameover screens
// TODO test next enemy and next level
// TODO music and beatSequences
#include <Arduboy2.h>
#include <Sprites.h>

#include "Bitmaps.h"
#include "Enemy.h"
#include "IndicatorBox.h"
#include "Level.h"
#include "Player.h"

enum class GameState : unsigned char
{
  Title, Controls, Play, Pause, Win, GameOver
};

Arduboy2 ab;
Sprites sprites;

GameState gameState = GameState::Title;

const byte INDICATOR_BOX_HEIGHT = 16;
const byte INDICATOR_BOX_WIDTH = 16;
const byte RHYTHM_BOX_HEIGHT = 16;
const byte RHYTHM_BOX_WIDTH = WIDTH / 2;

const byte PLAYER_INFO_BOX_HEIGHT = HEIGHT - RHYTHM_BOX_HEIGHT - 1;
const byte PLAYER_INFO_BOX_WIDTH = WIDTH / 2;

IndicatorBox goodBox(WIDTH / 2, HEIGHT - INDICATOR_BOX_HEIGHT, INDICATOR_BOX_WIDTH, INDICATOR_BOX_HEIGHT, ab);
IndicatorBox perfectBox(WIDTH / 2 + (INDICATOR_BOX_WIDTH / 4), HEIGHT - (3 * INDICATOR_BOX_HEIGHT / 4), INDICATOR_BOX_WIDTH / 2, INDICATOR_BOX_HEIGHT / 2, ab);

Enemy enemy;
Level level;
Player player;

void setup()
{
  ab.begin();
  ab.clear();

  sprites.drawSelfMasked(0, 0, ArduboyTitle_RetrobitCoder, 0);

  ab.display();
  ab.delayShort(3000);
  ab.clear();

  ab.initRandomSeed();
}

void titleScreen()
{
  sprites.drawSelfMasked(0, 0, title_screen, 0);

  if (ab.justPressed(A_BUTTON))
  {
    gameState = GameState::Controls;
  }
}

void showControls()
{
  ab.setCursor(WIDTH / 2, HEIGHT / 2);
  ab.print("Controls");

  if (ab.justPressed(A_BUTTON))
  {
    gameState = GameState::Play;
  }
}

void drawGameDisplay()
{
  // Draw Bounding boxes
  ab.drawRect(WIDTH / 2, 0, PLAYER_INFO_BOX_WIDTH, PLAYER_INFO_BOX_HEIGHT);
  ab.drawRect(WIDTH / 2, HEIGHT - RHYTHM_BOX_HEIGHT, RHYTHM_BOX_WIDTH, RHYTHM_BOX_HEIGHT);

  // Draw good indicator box, perfect shouldn't be visible meant to be collision when perfect hit succeeds
  ab.drawRoundRect(WIDTH / 2, HEIGHT - INDICATOR_BOX_HEIGHT, INDICATOR_BOX_WIDTH, INDICATOR_BOX_HEIGHT, INDICATOR_BOX_WIDTH / 4);
  // TODO remove below debug drawRoundRect since we don't want perfect box to be visible
  ab.drawRoundRect(WIDTH / 2 + INDICATOR_BOX_WIDTH / 4, HEIGHT - (3 * INDICATOR_BOX_HEIGHT / 4), INDICATOR_BOX_WIDTH / 2, INDICATOR_BOX_HEIGHT / 2, INDICATOR_BOX_WIDTH / 8);

}

bool compareButtons(byte button)
{

  if(ab.justPressed(LEFT_BUTTON))
  {
    return LEFT_BUTTON == button;
  }
  else if(ab.justPressed(RIGHT_BUTTON))
  {
    return RIGHT_BUTTON == button;
  }
  else if(ab.justPressed(UP_BUTTON))
  {
    return UP_BUTTON == button;
  }
  else if(ab.justPressed(DOWN_BUTTON))
  {
    return DOWN_BUTTON == button;
  }
  else
  {
    return A_BUTTON == button;
  }
}

void checkUserInput()
{
  if(ab.justPressed(LEFT_BUTTON) || ab.justPressed(RIGHT_BUTTON) || ab.justPressed(UP_BUTTON) || ab.justPressed(DOWN_BUTTON) || ab.justPressed(A_BUTTON))
  {
    byte button = level.getButton();
    Rect hitBox = level.getHitBox();
    bool perfectHit = false;
    
    if(goodBox.collides(hitBox))
    {
     if(perfectBox.collides(hitBox))
     {
        perfectHit = true;
     }
      if(compareButtons(button))
      {
        player.streakIncrease(perfectHit);

        if(ab.justPressed(A_BUTTON))
        {
          enemy.damage(player.getAttackDamage());
        }
      }
      else
      {
        player.damage(enemy.getAttackDamage());
      }
    }
    else
    {
      player.damage(enemy.getAttackDamage());
    }

    level.removeBeat();
  }
  else if(ab.justPressed(B_BUTTON))
  {
    gameState = GameState::Pause;
  }
  else
  {
    Rect hitBox = level.getHitBox();

    if(hitBox.x <= WIDTH/2)
    {
      player.damage(enemy.getAttackDamage());
    }
  }
}

void gameLoop()
{
  if(player.isDead())
  {
    gameState = GameState::GameOver;
  }
  else if(enemy.isDead())
  {
    enemy.nextEnemy();
    player.reset();
  }
  else
  {
    checkUserInput();

    level.update();
  
    level.drawBeats(ab);
    enemy.drawEnemyInfo(ab);
    player.drawPlayerInfo(ab);
    drawGameDisplay();
  }
}

void gamePause()
{
  // TODO draw pause box
  ab.setCursor(0,0);
  ab.print("Paused");

  if(ab.justPressed(B_BUTTON))
  {
    gameState = GameState::Play;
  }
}

void gameWon()
{

}

void gameOver()
{
  // TODO draw game over screen
  ab.setCursor(0,0);
  ab.print("Game Over");

  if(ab.justPressed(A_BUTTON))
  {
    enemy.reset();
    player.reset(3);
    level.reset();
    gameState = GameState::Play;
  }
}

void loop()
{
  if (!ab.nextFrame()) return;

  ab.pollButtons();

  ab.clear();

  switch (gameState)
  {
    case GameState::Title:
      titleScreen();
      break;
    case GameState::Controls:
      showControls();
      break;
    case GameState::Play:
      gameLoop();
      break;
    case GameState::Pause:
      gamePause();
      break;
    case GameState::Win:
      gameWon();
      break;
    case GameState::GameOver:
      gameOver();
      break;
  }

  ab.display();
}
