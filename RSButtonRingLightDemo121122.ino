// This is a demo that shows that using a button you can switch between multiple functions, and shows off some leds.

#include <Adafruit_NeoPixel.h>

const int NUM_LEDS = 19;
const int BUTTON_PIN = 4;
const int LED_PIN = 7;
const int DELAY = 5;
int mode = 0;

Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRBW + NEO_KHZ800);

void setup() {                    // Runs one time at the startup of the board.
  pinMode(BUTTON_PIN, INPUT);        // Sets BUT_PIN to an input pin and uses the internal 10k pullup resistor for 5v button signal.
  pixels.begin();                 // Prepares data pin for output.
  pixels.show();                  // Since no color is set this clears any previous colors.
  pixels.setBrightness(75);      // You can set brightness to any value between 0-255.
}

// loop allows you to press a button and cycle through the different functions you want to have on the device.
void loop() { 
  if(readButton(BUTTON_PIN) == 1) {
    mode+=1;
  }
  if(mode >= 4) {
    mode = 0;
  }
  switch(mode) {
    case 0:
      cycleLights();
      break;
    case 1:
      partyLights();
      break;
    case 2:
      cycleBrightness();
      break;
  }
}

// cycleBrightness will cycle through the brightness from 0 to 255, or the lowest to the brightest settings.
void cycleBrightness() {
  int brightness;
  bool increasing;
  for(int i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i,0,0,0,255);
    if(increasing == true) {
      brightness+=1;
    } else {
      brightness-=1;
    }
    if(brightness == 255) {
      increasing = false;
    } else if(brightness == 0) {
      increasing = true;
    }
    pixels.setBrightness(brightness);
    pixels.show();
    delay(10);
  }
}

// partyLights will cycle thought the HSV spectrum at a high number you pick making it look random.
void partyLights() {
  word color;
  for(int i = 0; i < NUM_LEDS; i++) {
    color+=9525;
    if(i>=13) {
      pixels.setPixelColor(i,pixels.ColorHSV(color));
    } else {
      pixels.setPixelColor(i,pixels.ColorHSV(color-32768));
    }
  }
  pixels.setBrightness(75);
  pixels.show();
  delay(75);
}

// cycleLights will cycle through the colors of the rainbow. It requires values for: number of leds, brightness, and time for delay.
void cycleLights() {
  word color;
  for(int i = 0; i < NUM_LEDS; i++) {
    color+=75;
    pixels.setPixelColor(i,pixels.ColorHSV(color));
    pixels.setBrightness(75);
    pixels.show();
    delay(10);
  }  
}

// readButton will read the designated pin and decide if its getting a signal or not. If it is then it will return 1, if not then it will return 0.
int readButton(int pin) {
  bool currentState = digitalRead(pin);
  int state = 0;
  if(currentState == true) {
    state = 1;
    while(digitalRead(pin) == true) {
      // do nothing
    }
  } else {
    state = 0;
  }
  return state;
}