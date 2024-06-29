

#include <Adafruit_NeoPixel.h>


// LED Configuration
#define NUM_LEDS_PER_GROUP 8
#define NUM_GROUPS 4
#define TOTAL_LEDS (NUM_LEDS_PER_GROUP * NUM_GROUPS)
#define DATA_PIN 5
#define BUTTON_PIN 23

// Function Declarations
void setup();
void loop();
void colorWave();
void singleColorWave();
void steadyColor(uint32_t color);
void frenzy();

// Global Variables
extern Adafruit_NeoPixel strip;
extern int currentMode;
extern unsigned long lastDebounceTime;
extern unsigned long debounceDelay;
extern bool lastButtonState;
extern bool buttonState;