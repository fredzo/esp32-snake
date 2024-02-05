#include <Arduino.h>
#include <Esp32SnakeConf.h>
#include <Esp32GamepadHost.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Esp32Snake.h>
#include <MusicManager.h>
#include <Settings.h>

/// Gamepad host
static Esp32GamepadHost* gamepadHost;

/// Music Manager instance
static MusicManager* musicManager;

/// Settings
static Settings * settings;

// Pilote écran
static MatrixPanel_I2S_DMA *display = nullptr;



//////////// Initialisation du programme //////////////

void setup() {
#ifdef SERIAL_OUT
  Serial.begin(115200);
  Serial.println("Démarrage Esp32 Snake !");
  Serial.print("Chip Model : ");
  Serial.println(ESP.getChipModel());
  Serial.print("Chip Revision : ");
  Serial.println(ESP.getChipRevision());
  Serial.print("Chip Cores : ");
  Serial.println(ESP.getChipCores());
  Serial.print("Chip freq : ");
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print("Flash : ");
  Serial.println(ESP.getFlashChipSize());
#endif
  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  // Turn buzzer off
  digitalWrite(BUZZER_PIN,0);

  // Ecran
  HUB75_I2S_CFG mxconfig(64, 64, 1);
  mxconfig.gpio.e = 18;
  mxconfig.clkphase = false;
  display = new MatrixPanel_I2S_DMA(mxconfig);
  display->begin();
  display->setBrightness8(32);
  display->clearScreen();

  // Init gamepad host
  gamepadHost = Esp32GamepadHost::getEsp32GamepadHost();
  gamepadHost->init();

  // Settings init
  settings = Settings::getSettings();
  settings->init();

  // MusicManager init
  musicManager = MusicManager::getMusicManager();
  musicManager->init();
  musicManager->setVolume(settings->getVolume());


  snakeInit(display, musicManager, settings);


  display->fillScreenRGB888(0xFF,0x00,0x00);
  sleep(2);
  display->fillScreenRGB888(0x00,0xFF,0x00);
  sleep(2);
  display->fillScreenRGB888(0x00,0x00,0xFF);
  sleep(2);
  display->fillScreenRGB888(0xFF,0xFF,0xFF);
  sleep(5);
  display->clearScreen();
}

//////////// Boucle principale //////////////

// Button detection
boolean oldButtonState = HIGH;

int x    = 0;
int y    = 0;
int pass = 0;



void loop() {


  gamepadHost->processTasks();
  GamepadCommand* command = gamepadHost->getCommand();

  snakeLoop(command);

  // Handle setting autosave
  settings->processAutoSave();

}

