#include "main.h"


CRGB leds[TOTAL_LEDS];
int currentMode = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState = HIGH;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, TOTAL_LEDS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Setup complete.");
}

void loop() {
  // Check button press
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
    if (reading == LOW) {
      Serial.println("Button pressed");
    } else {
      Serial.println("Button released");
    }
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        currentMode = (currentMode + 1) % 10;
        Serial.print("Mode changed to: ");
        Serial.println(currentMode);
      }
    }
  }

  lastButtonState = reading;

  // Display the current mode
  switch (currentMode) {
    case 0:
      colorWave();
      break;
    case 1:
      singleColorWave();
      break;
    case 2:
      steadyColor(CRGB::Red);
      break;
    case 3:
      steadyColor(CRGB::Green);
      break;
    case 4:
      steadyColor(CRGB::Blue);
      break;
    case 5:
      steadyColor(CRGB::Yellow);
      break;
    case 6:
      steadyColor(CRGB::Cyan);
      break;
    case 7:
      steadyColor(CRGB::Magenta);
      break;
    case 8:
      steadyColor(CRGB::White);
      break;
    case 9:
      frenzy();
      break;
  }

  FastLED.show();
  delay(100);
}

void colorWave() {
  static uint8_t hue = 0;
  for (int group = 0; group < NUM_GROUPS; group++) {
    for (int i = 0; i < NUM_LEDS_PER_GROUP; i++) {
      leds[group * NUM_LEDS_PER_GROUP + i] = CHSV(hue + (group * 64), 255, 255);
    }
  }
  hue++;
}

void singleColorWave() {
  static uint8_t hue = 0;
  for (int group = 0; group < NUM_GROUPS; group++) {
    for (int i = 0; i < NUM_LEDS_PER_GROUP; i++) {
      leds[group * NUM_LEDS_PER_GROUP + i] = CHSV(hue, 255, 255);
    }
  }
  hue++;
}

void steadyColor(CRGB color) {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    leds[i] = color;
  }
}

void frenzy() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    leds[i] = CHSV(random8(), 255, 255);
  }
}