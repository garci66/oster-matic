#include "TKLCDL.h"

void TKLCDL::begin() {
  LiquidCrystal::begin(DEFAULT_SIZE_COL, DEFAULT_SIZE_COL);
  setBrightness(DEFAULT_BRIGHTNESS);
  setContrast(DEFAULT_CONTRAST);
  
  // fixes flickering when using Arduino default PWM frequency of 490Hz,
  // the following line, switches the PWM frequency to 3906.25Hz
  TCCR1B = TCCR1B & 0b11111000 | 0x02;
}

void TKLCDL::setBrightness(uint8_t brightness) {
  analogWrite(BACKLIGHT, brightness);
}

void TKLCDL::setContrast(uint8_t contrast) {
  analogWrite(CONTRASTPIN, 255-contrast); // contrast is reversed
}
