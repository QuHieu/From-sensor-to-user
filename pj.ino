/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-light-sensor
 */

#define LIGHT_SENSOR_PIN 36 // ESP32 pin GIOP36 (ADC0)
#include <stdbool.h>

bool isLightOn = false;
int window[10];

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LIGHT_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 500) {
    Serial.println(" => Light");
    // Shift the window to the right
    for (int i = 10 - 1; i > 0; i--) {
        window[i] = window[i - 1];
    }
    window[0] = 1;
  }  else {
    Serial.println(" => Dark");
    // Shift the window to the right
    for (int i = 10 - 1; i > 0; i--) {
        window[i] = window[i - 1];
    }
    window[0] = 0;
  }

  if (containsMotion() && isLightOn == false) {
    digitalWrite(LED_BUILTIN, HIGH);
    isLightOn = true;
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    isLightOn = false;
  }

  for (int i = 0; i < 10; i++) {
    Serial.print(window[i]);
    if (i==9){
      Serial.println(window[i]);
    }
  }

  delay(1000);
}

bool containsMotion() {
  // Check if window contains any motion data
  for (int i = 0; i < 10; i++) {
    if (window[i] == 1) {
      return true; // If motion data is found, return true
    }
  }
  return false; // If no motion data is found, return false
}
