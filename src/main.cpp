// Copyright [2019] <Chris GW Green>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <conf.h>
#include <wifi.h>
#include <led.h>

wifiClass wifi = wifiClass();
ledClass led = ledClass();

unsigned int lastInterrupt = millis();
const int interruptDelay = 500;
bool interruptTriggered = false;
bool isRecording = false;

void buttonPress() {
  unsigned int now = millis();

  if (now - lastInterrupt > interruptDelay && !interruptTriggered) {
    lastInterrupt = now;
    interruptTriggered = true;
  }
}

void connecting() {
    led.blink();
}

void setup() {
  Serial.begin(config::serialbaudrate);

  // Setup Pins
  pinMode(config::buttonPin, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(config::buttonPin),
    buttonPress,
    CHANGE);

  void (*ptr)() = &connecting;

  // Setup Wifi & LED
  led.init(); 
  wifi.init(ptr);

  // Blink led for setup complete
  led.flash();
  wifi.setVideoMode();
  Serial.println("\nSETUP COMPLETE\n");
}

void loop() {
  if (interruptTriggered) {
    bool isSuccess = false;

    if (!isRecording) {
      Serial.println("START RECORDING...");
      led.on();

      isSuccess = wifi.shutterRelease(true);
      if (isSuccess) {
        isRecording = true;
      } else {
        led.slowFlash();
      }
    } else {
      Serial.println("STOP RECORDING...");
      isSuccess = wifi.shutterRelease(false);

      if (isSuccess) {
        led.flash();
        isRecording = false;
      } else {
        led.slowFlash();
      }
    }

    interruptTriggered = false;
  }

  led.loop();
}
