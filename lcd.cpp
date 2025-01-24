#include "lcd.h"

// Define LCD pinout
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void lcd_setup() {
  lcd.begin(8, 2);  // The LCD is internally 8x2 (even though it appears as 16x1)
}