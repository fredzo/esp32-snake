#ifndef TETRIS_H
#define TETRIS_H

#include <Esp32SnakeConf.h>
#include <GamepadCommand.h>
#include <Adafruit_GFX.h>
#include <MusicManager.h>
#include <Settings.h>

void snakeInit(Adafruit_GFX* display, MusicManager * musicManager, Settings * settings);
void snakeLoop(GamepadCommand* command);

#endif 