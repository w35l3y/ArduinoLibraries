#include "DigitalOutput.h"

DigitalOutput buzzer(8);

void setup() {
  buzzer.blink(0, 1000, 1000);
}

void loop() {
  buzzer.loop();
}
