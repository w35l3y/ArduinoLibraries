#include "DigitalOutput.h"

DigitalOutput ledR(8);
DigitalOutput ledG(9, true);  // inverted signal
DigitalOutput ledB(10);
DigitalOutput ledI(LED_BUILTIN);

void setup() {
  ledI.blink(0, 1000, 1000);

  ledR.blink(15);
  ledG.blink(10, 2000, 500);
  ledB.blink(5, 3000);
}

void loop() {
  ledI.loop();

  ledR.loop();
  ledG.loop();
  ledB.loop();
}
