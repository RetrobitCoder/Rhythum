#include <Arduboy2.h>
#include <Sprites.h>

#include "Bitmaps.h"
#include "IndicatorBox.h"
#include "RhythmBeat.h"

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
RhythmBeat beats[5] = 
{
  RhythmBeat(WIDTH, HEIGHT - 12, 16, 16, LEFT_BUTTON),
  RhythmBeat(WIDTH + 16, HEIGHT - 12, 16, 16, RIGHT_BUTTON),
  RhythmBeat(WIDTH + 32, HEIGHT - 12, 16, 16, UP_BUTTON),
  RhythmBeat(WIDTH + 48, HEIGHT - 12, 16, 16, DOWN_BUTTON),
  RhythmBeat(WIDTH + 64, HEIGHT - 12, 16, 16, A_BUTTON)
};

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
  ab.setCursor(WIDTH/2, HEIGHT/2);
  ab.print("Rhythum");

  if(ab.justPressed(A_BUTTON))
  {
    gameState = GameState::Controls;
  }
}

void showControls()
{
  ab.setCursor(WIDTH/2, HEIGHT/2);
  ab.print("Controls");

  if(ab.justPressed(A_BUTTON))
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
void updateBeats()
{
  // TODO make beats a queue
  for(size_t i = 0; i < 5; i++)
  {
    beats[i].updatePos();
    Rect hitBox = beats[i].getHitBox();
    // TODO when hitBox.x hits WIDTH / 2 or collision happens when button is pressed delete beat
    // TODO check collision with boxes when button is pressed and check if button matches beat button
    ab.setCursor(hitBox.x, hitBox.y);
    ab.print(beats[i].getButton());
  }
}

void gameLoop()
{
     drawGameDisplay();
     updateBeats();
}

void gamePause()
{
  
}

void gameWon()
{
  
}

void gameOver()
{

}

void loop() 
{
  if(!ab.nextFrame()) return;

  ab.pollButtons();

  ab.clear();
  
  switch(gameState)
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
