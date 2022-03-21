#include "DigitalOutput.h"

DigitalOutput::DigitalOutput(unsigned int pin, bool inverted) {
  pinMode(pin, OUTPUT);

  this->pin = pin;
  this->inverted = inverted;

  bool state = digitalRead(pin);
  this->lastStateBeforeBlink = this->lastState = (inverted ? !state : state);
}

void DigitalOutput::localTurn(bool state) {
  this->lastStatus = millis();
  this->lastState = state;

  digitalWrite(this->pin, (this->inverted ? !state : state));
}

void DigitalOutput::turn(bool state) {
  this->mode = DIGITAL_OUTPUT_STATIC_MODE;
  this->times = 0;

  this->localTurn(state);
}

void DigitalOutput::turnOn() {
  this->turn(true);
}

void DigitalOutput::play() {
  this->turnOn();
}

void DigitalOutput::turnOff() {
  this->turn(false);
}

void DigitalOutput::stop() {
  this->turnOff();
}

void DigitalOutput::loop() {
  if (this->mode == DIGITAL_OUTPUT_BLINK_MODE_INFINITE) {
    unsigned long diff = millis() - this->lastStatus;

    if (!this->lastState && diff >= this->statusOn || this->lastState && diff >= this->statusOff) {
      this->localTurn(!this->lastState);
    }
  } else if (this->times > 0) {
    unsigned long diff = millis() - this->lastStatus;

    if (!this->lastState && diff >= this->statusOn) {
      this->localTurn(true);
    } else if (this->lastState && diff >= this->statusOff) {
      this->localTurn(false);
      --this->times;
    }
  } else if (this->mode == DIGITAL_OUTPUT_BLINK_MODE_FINITE) {
    this->turn(this->lastStateBeforeBlink);
  }
}

void DigitalOutput::blink(unsigned int times, unsigned long statusOn, unsigned long statusOff) {
  this->mode = (times == 0 ? DIGITAL_OUTPUT_BLINK_MODE_INFINITE : DIGITAL_OUTPUT_BLINK_MODE_FINITE);
  this->lastStateBeforeBlink = this->lastState;

  this->times = times;
  this->statusOn = statusOn;
  this->statusOff = statusOff;

  this->loop(); // executa efeito imediatamente
}
