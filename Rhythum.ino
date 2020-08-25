#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
#include <Sprites.h>

#include "Bitmaps.h"
#include "Enemy.h"
#include "IndicatorBox.h"
#include "Level.h"
#include "Player.h"
#include "Sounds.h"

enum class GameState : unsigned char
{
  Title, Play, Pause, Win, GameOver
};

Arduboy2 ab;
ArduboyPlaytune tunes(ab.audio.enabled);
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

uint8_t enemyCount = 0;

void setup()
{
  ab.begin();
  ab.clear();

  ab.audio.on();
  tunes.initChannel(PIN_SPEAKER_1);
  tunes.initChannel(PIN_SPEAKER_1);
  
  ab.drawCompressed(0, 0, title_card);
  
  ab.display();
  ab.delayShort(3000);
  ab.clear();

  ab.initRandomSeed();
}

void titleScreen()
{
  ab.drawCompressed(0, 0, title_screen);
  
  ab.setCursor(WIDTH/2 - 48, HEIGHT - 8);
  ab.print("Press A to start");
  
  if (ab.justPressed(A_BUTTON))
  {
    gameState = GameState::Play;

    enemy = Enemy();
    level = Level();
    player = Player();

    level.drawLevelCard(ab);
    tunes.playScore(battle_music);
  }
}

void drawGameDisplay()
{
  // Draw Bounding boxes
  ab.drawRect(WIDTH / 2, 0, PLAYER_INFO_BOX_WIDTH, PLAYER_INFO_BOX_HEIGHT);
  ab.drawRect(WIDTH / 2, HEIGHT - RHYTHM_BOX_HEIGHT, RHYTHM_BOX_WIDTH, RHYTHM_BOX_HEIGHT);

  // Draw good indicator box, perfect shouldn't be visible meant to be collision when perfect hit succeeds
    sprites.drawSelfMasked(WIDTH / 2, HEIGHT - INDICATOR_BOX_HEIGHT, icons, 0);
}

void drawSpace()
{
  ab.drawCompressed(0, 0, space);
  ab.fillRect(16, 16, 31, 31, BLACK);
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
    
    tunes.stopScore();
  }
  else if(enemyCount > 4)
  {
    gameState = GameState::Win;

    tunes.stopScore();
  }
  else if(enemy.isDead())
  {
    enemy.nextEnemy();
    
    enemyCount++;
    
    level.nextLevel();

    tunes.stopScore();
    
    if(enemyCount < 5)
    {
      level.drawLevelCard(ab);
    }

    tunes.playScore(battle_music);
    
    player.reset();
  }
  else
  {
    checkUserInput();

    level.update();

    drawGameDisplay();
    drawSpace();
    level.drawBeats(sprites);
    enemy.drawEnemy(ab, sprites);
    player.drawPlayerInfo(ab, sprites);
  }
}

void gamePause()
{
  ab.setCursor(WIDTH/2 - 16, HEIGHT/2 - 8);
  ab.print("Paused");
  ab.setCursor(WIDTH/2 - 36, HEIGHT/2 + 4);
  ab.print("B to unpause");

  ab.drawRect(16, 16, WIDTH - 32, 32);

  tunes.stopScore();
  
  if(ab.justPressed(B_BUTTON))
  {
    gameState = GameState::Play;

    tunes.playScore(battle_music);
  }
}

void gameWon()
{
  ab.drawCompressed(0, 0, victory);

  static bool playedMusic = false;

  if(!tunes.playing() && !playedMusic)
  {
    tunes.playScore(game_win);
    playedMusic = true;
  }
  
  if(ab.justPressed(A_BUTTON))
  {
    enemyCount = 0;
    
    gameState = GameState::Title;

    tunes.stopScore();
    playedMusic = false;
  }
}

void gameOver()
{
  ab.drawCompressed(0, 0, defeat);

  static bool playedMusic = false;

  if(!tunes.playing() && !playedMusic)
  {
    tunes.playScore(game_over);
    playedMusic = true;
  }
  
  if(ab.justPressed(A_BUTTON))
  { 
    enemyCount = 0;
    
    enemy.~Enemy();
    level.~Level();
    player.~Player();
    
    gameState = GameState::Title;

    tunes.stopScore();
    playedMusic = false;
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
