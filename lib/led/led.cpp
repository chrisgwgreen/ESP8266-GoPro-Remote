// Copyright [2019] <Chris GW Green>
#include <Arduino.h>
#include <led.h>
#include <conf.h>

ledClass::ledClass() {
  blinkCount = 0;
  blinkDelay = 150;
  blinkTimer = millis();
  blinkState = false;
}

void ledClass::init() {
  pinMode(config::ledPin, OUTPUT);
  digitalWrite(config::ledPin, HIGH);
}

void ledClass::blink() {
  digitalWrite(config::ledPin, LOW);
  delay(100);
  digitalWrite(config::ledPin, HIGH);
}

void ledClass::on() {
  digitalWrite(config::ledPin, LOW);
}

void ledClass::flash() {
  digitalWrite(config::ledPin, LOW);
  blinkDelay = 150;
  blinkTimer = millis();
  blinkState = false;
  blinkCount = 6;
}

void ledClass::slowFlash() {
  flash();
  blinkDelay = 500;
  blinkCount = 4;
}

void ledClass::loop() {
  if (blinkCount >= 1 && millis() - blinkTimer > blinkDelay) {
    digitalWrite(config::ledPin, !blinkState);
    blinkState = !blinkState;
    if (blinkState) {
      blinkCount -= 1;
    }
    blinkTimer = millis();
  }
}
