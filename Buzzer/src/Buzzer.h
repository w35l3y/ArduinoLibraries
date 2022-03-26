/*
 * https://github.com/w35l3y/ArduinoLibraries/tree/main/Buzzer
 *
 * Esta biblioteca é mais apropriada quando você tem um buzzer que precise ligar e desligar repetidas vezes.
 * 
 * Controla chamando as funções tone (ligado) e noTone (desligado)
 * 
 * Próximas evoluções em vista:
 * - Possibilidade de ajustar frequência
 * - Verificar possibilidade para delegar statusOn e statusOff para o 3º parâmetro da função tone
*/

#ifndef __BUZZER_H__
#define __BUZZER_H__

#define BUZZER_STATIC_MODE 0
#define BUZZER_BEEP_MODE_FINITE 1
#define BUZZER_BEEP_MODE_INFINITE 2

#include <Arduino.h>

class Buzzer {
  private:
    unsigned mode = BUZZER_STATIC_MODE;
    bool lastState = false;
    bool lastStateBeforeBeep = false;
    bool inverted = false;
    unsigned int pin;
    unsigned int times = 0;
    unsigned long statusOn = 0L;
    unsigned long statusOff = 0L;
    unsigned long lastStatus = 0L;

    void localTurn(bool state);
  public:
    Buzzer(unsigned int pin, bool inverted = false);

    void turn(bool state);
    void turnOn();
    void turnOff();
    void play();
    void stop();
    void beep(unsigned int times = 0, unsigned long statusOn = 100L, unsigned long statusOff = 100L);

    void loop();
};

#endif