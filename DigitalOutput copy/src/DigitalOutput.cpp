#include "Buzzer.h"

Buzzer::Buzzer(unsigned int pin, bool inverted) {
  this->pin = pin;
  pinMode(pin, OUTPUT);

  this->inverted = inverted;

  bool state = false;
  this->lastStateBeforeBeep = this->lastState = (inverted ? !state : state);
}

void Buzzer::localTurn(bool state) {
  this->lastStatus = millis();
  this->lastState = state;

  if (this->inverted ^ state) {
    tone(this->pin, 400);
  } else {
    noTone(this->pin);
  }
}

void Buzzer::turn(bool state) {
  this->mode = BUZZER_STATIC_MODE;
  this->times = 0;

  this->localTurn(state);
}

void Buzzer::turnOn() {
  this->turn(true);
}

void Buzzer::play() {
  this->turnOn();
}

void Buzzer::turnOff() {
  this->turn(false);
}

void Buzzer::stop() {
  this->turnOff();
}

void Buzzer::loop() {
  if (this->mode == BUZZER_BEEP_MODE_INFINITE) {
    unsigned long diff = millis() - this->lastStatus;

    if (this->lastState && diff >= this->statusOn || !this->lastState && diff >= this->statusOff) {
      this->localTurn(!this->lastState);
    }
  } else if (this->times > 0) {
    unsigned long diff = millis() - this->lastStatus;

    if (!this->lastState && diff >= this->statusOff) {
      this->localTurn(true);
    } else if (this->lastState && diff >= this->statusOn) {
      this->localTurn(false);
      --this->times;
    }
  } else if (this->mode == BUZZER_BEEP_MODE_FINITE) {
    this->turn(this->lastStateBeforeBeep);
  }
}

void Buzzer::beep(unsigned int times, unsigned long statusOn, unsigned long statusOff) {
  this->mode = ( times == 0 ? BUZZER_BEEP_MODE_INFINITE : BUZZER_BEEP_MODE_FINITE );
  this->lastStateBeforeBeep = this->lastState;

  this->times = times;
  this->statusOn = statusOn;
  this->statusOff = statusOff;

  this->loop();
}