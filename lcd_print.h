#ifndef LCD_PRINT_H
#define LCD_PRINT_H

#include "lcd.h"
#include <stdint.h>
#include <String.h>
#include <time.h>

void jump_print(const char* message);
void scroll_print(const char* message);

#endif