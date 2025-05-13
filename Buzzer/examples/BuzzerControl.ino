#include "Buzzer.h"

Buzzer buzzer(8);

void setup() {
  buzzer.beep(0, 1000, 1000);
}

void loop() {
  buzzer.loop();
}
