#ifndef LIGHT_SHOW_H
#define LIGHT_SHOW_H

#include <FastLED.h>

// LED Configuration
#define NUM_LEDS_PER_GROUP 8
#define NUM_GROUPS 4
#define TOTAL_LEDS (NUM_LEDS_PER_GROUP * NUM_GROUPS)
#define DATA_PIN 1
#define BUTTON_PIN 2

// Function Declarations
void setup();
void loop();
void colorWave();
void singleColorWave();
void steadyColor(CRGB color);
void frenzy();

// Global Variables
extern CRGB leds[TOTAL_LEDS];
extern int currentMode;
extern unsigned long lastDebounceTime;
extern unsigned long debounceDelay;
extern bool lastButtonState;
extern bool buttonState;

#endif // LIGHT_SHOW_H
