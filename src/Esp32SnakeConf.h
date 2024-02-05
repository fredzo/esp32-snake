#ifndef ESP32_SNAKE_CONF_H
#define ESP32_SNAKE_CONF_H

// Pin for Buzzer
#define BUZZER_PIN          32

// Taille écran
#define SCREEN_HEIGHT       64
#define SCREEN_WIDTH        64

// Taille Snake
#define SNAKE_SIZE         2

// Taille grille
#define GRID_HEIGHT         SCREEN_HEIGHT/SNAKE_SIZE     
#define GRID_WIDTH          SCREEN_WIDTH/SNAKE_SIZE     

// Default birghtness for LedMatrix
#define DEFAULT_BRIGHTNESS  40
// Default volume for melody
#define DEFAULT_VOLUME      60


// Uncomment to enable logs on serial out
#define SERIAL_OUT

#endif