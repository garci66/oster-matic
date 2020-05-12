#ifndef TKLCDL_h
#define TKLCDL_h

#include <inttypes.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

// Define LCD pin mappings
#define LCD_D4  A3
#define LCD_D5  4
#define LCD_D6  12
#define LCD_D7  8
#define LCD_RS  A4
#define LCD_RW  A5
#define LCD_EN  7


// Define default settings
#define DEFAULT_CONTRAST 230
#define DEFAULT_BRIGHTNESS 255


// for 16x2 TK display
#define DEFAULT_SIZE_COL 16
#define DEFAULT_SIZE_ROWS 2

#define BACKLIGHT 10
#define CONTRASTPIN 9         // B7

class TKLCDL : public LiquidCrystal {
  public:
    TKLCDL() : LiquidCrystal(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7){};
    void begin();
    void setBrightness(uint8_t brightness);
    void setContrast(uint8_t contrast);

};

#endif TKLCDL_h

