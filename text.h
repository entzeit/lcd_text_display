#ifndef TEXT_H
#define TEXT_H

#include <avr/pgmspace.h>
#define MAX_STRING_LENGTH 256

extern const char text[][MAX_STRING_LENGTH] PROGMEM;
extern const int text_count;

#endif