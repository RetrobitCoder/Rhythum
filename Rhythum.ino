#include <Arduboy2.h>
#include <Sprites.h>

#include "Bitmaps.h"

enum class GameState : unsigned char
{
  Title, Controls, Play, Pause, Win, GameOver 
};

Arduboy2 ab;
Sprites sprites;

GameState gameState = GameState::Title;

const byte RHYTHM_BOX_HEIGHT = 16;
const byte RHYTHM_BOX_WIDTH = WIDTH / 2;

const byte PLAYER_INFO_BOX_HEIGHT = HEIGHT - RHYTHM_BOX_HEIGHT - 1;
const byte PLAYER_INFO_BOX_WIDTH = WIDTH / 2;

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

void gameWon()
{
  
}

void drawGameDisplay()
{
  ab.drawRect(WIDTH / 2, 0, PLAYER_INFO_BOX_WIDTH, PLAYER_INFO_BOX_HEIGHT); 
  ab.drawRect(WIDTH / 2, HEIGHT - RHYTHM_BOX_HEIGHT, RHYTHM_BOX_WIDTH, RHYTHM_BOX_HEIGHT);
}

void gameOver()
{

}

void gameLoop()
{
     drawGameDisplay();
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
  }

  ab.display();
}
