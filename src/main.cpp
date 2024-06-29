#include "main.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(TOTAL_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
int currentMode = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState = HIGH;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
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
      steadyColor(strip.Color(255, 0, 0)); // Red
      break;
    case 3:
      steadyColor(strip.Color(0, 255, 0)); // Green
      break;
    case 4:
      steadyColor(strip.Color(0, 0, 255)); // Blue
      break;
    case 5:
      steadyColor(strip.Color(255, 255, 0)); // Yellow
      break;
    case 6:
      steadyColor(strip.Color(0, 255, 255)); // Cyan
      break;
    case 7:
      steadyColor(strip.Color(255, 0, 255)); // Magenta
      break;
    case 8:
      steadyColor(strip.Color(255, 255, 255)); // White
      break;
    case 9:
      frenzy();
      break;
  }

  strip.show();
  delay(100);
}

void colorWave() {
  static uint8_t hue = 0;
  for (int group = 0; group < NUM_GROUPS; group++) {
    uint32_t color = strip.ColorHSV(hue * 256 + group * 65536 / NUM_GROUPS);
    for (int i = 0; i < NUM_LEDS_PER_GROUP; i++) {
      strip.setPixelColor(group * NUM_LEDS_PER_GROUP + i, color);
    }
  }
  hue++;
}

void singleColorWave() {
  static uint8_t hue = 0;
  uint32_t color = strip.ColorHSV(hue * 256);
  for (int i = 0; i < TOTAL_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  hue++;
}

void steadyColor(uint32_t color) {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
}

void frenzy() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(random(255), random(255), random(255)));
  }
}
