/*
 * Esta biblioteca é mais apropriada para controlar pushbutton de pullup.
 * 
 * Controla efeito debounce
 * Orientado a evento
 * Diferencia clique curto do longo
 * Atua com o número de cliques customizado (1, 2, 3+)
*/
#ifndef __PUSH_BUTTON_H__
#define __PUSH_BUTTON_H__

#define PUSHBUTTON_RELEASE_MODE 0
#define PUSHBUTTON_PRESS_MODE 1

#define PUSHBUTTON_LONG_PRESS_MS 200

#include <Arduino.h>

class PushButton {
  private:
    unsigned int pin;
    bool longPress = false;
    unsigned int times = 0;
    unsigned long debounce = 0L;
    void (*callback)();
    unsigned long lastPress = 0;
    unsigned int lastMode = PUSHBUTTON_PRESS_MODE;
    unsigned int timesPressed = 0;

    bool pressed();
  public:
    PushButton(unsigned int pin, bool longPress = false, unsigned long debounce = 15);
    void loop();
    void onPress(unsigned int times, void (*f)());
    void onSinglePress(void (*f)());
    void onDoublePress(void (*f)());
    unsigned long lastPressed();
};

#endif
