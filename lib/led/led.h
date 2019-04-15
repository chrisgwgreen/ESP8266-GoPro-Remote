// Copyright [2019] <Chris GW Green>
#ifndef LIB_LED_LED_H_
#define LIB_LED_LED_H_

class ledClass {
 private:
  int blinkCount;
  unsigned int blinkDelay;
  unsigned long blinkTimer;
  bool blinkState;

 public:
  ledClass();
  void init();
  void loop();
  void blink(); // Blocking
  void on();
  void flash();
  void slowFlash();
};

extern ledClass led;

#endif  // LIB_LED_LED_H_
