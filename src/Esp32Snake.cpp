#include <Esp32Snake.h>

#include <Arduino.h>
#include <Snake.h>

#define TARGET_FRAME_TIME     15  // Desired update rate, though if too many leds it will just run as fast as it can!
#define INITIAL_DROP_FRAMES   20  // Start of game block drop delay in frames

static Adafruit_GFX* display;
static MusicManager* musicManager;
static Settings * settings;


unsigned long loopDelayMS, lastLoop;

Snake* snake;


void snakeInit(Adafruit_GFX* displayParam, MusicManager * musicManagerParam, Settings * settingsParam)
{
  display = displayParam;
  musicManager = musicManagerParam;
  settings = settingsParam;
  loopDelayMS = TARGET_FRAME_TIME;
  lastLoop = millis() - loopDelayMS;
  snake = new Snake();
}


void snakeLoop(GamepadCommand* command)
{
  if ((millis() - lastLoop) >= loopDelayMS)
  {
    lastLoop = millis();
    bool grow = false;
    if(command)
    {
      if(command->buttons[GamepadCommand::S_DPAD_UP]) snake->setDirection(Snake::UP);
      if(command->buttons[GamepadCommand::S_DPAD_DOWN]) snake->setDirection(Snake::DOWN);
      if(command->buttons[GamepadCommand::S_DPAD_LEFT]) snake->setDirection(Snake::LEFT);
      if(command->buttons[GamepadCommand::S_DPAD_RIGHT]) snake->setDirection(Snake::RIGHT);
      if(command->buttons[GamepadCommand::S_CROSS]) grow = true;
    }
    display->fillScreen(0);
    snake->advance(grow);
    snake->render(display);
    //Serial.printf("Draw pixel %d,%d\n",posX,posY);
  }
}