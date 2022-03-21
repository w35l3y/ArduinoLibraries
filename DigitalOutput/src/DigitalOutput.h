#define DIGITAL_OUTPUT_STATIC_MODE 0
#define DIGITAL_OUTPUT_BLINK_MODE_FINITE 1
#define DIGITAL_OUTPUT_BLINK_MODE_INFINITE 2

class DigitalOutput {
  private:
    unsigned mode = DIGITAL_OUTPUT_STATIC_MODE;
    bool lastState = false;
    bool lastStateBeforeBlink = false;
    bool inverted = false;
    unsigned int pin;
    unsigned int times = 0;
    unsigned long statusOn = 0L;
    unsigned long statusOff = 0L;
    unsigned long lastStatus = 0L;

    void localTurn(bool state);
  public:
    DigitalOutput(unsigned int pin, bool inverted = false);

    void turn(bool state);
    void turnOn();
    void turnOff();
    void play();
    void stop();
    void blink(unsigned int times = 0, unsigned long statusOn = 100L, unsigned long statusOff = 100L);

    void loop();
};
