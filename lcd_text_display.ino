#include "text.h"
#include "lcd.h"
#include "lcd_print.h"

int prevRand = -1;
int round_robin_rand(int max) {
  int next;
  do {
    next = random(max);
  }
  while (next == prevRand);
  prevRand = next;
  return next;
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0)); //otherwise it's always the same seed
  lcd_setup();
}

void loop() {
  char buffer[MAX_STRING_LENGTH];
  strcpy_P(buffer, text[round_robin_rand(text_count)]);
  // Serial.println(buffer);
  scroll_print(buffer);
  // jump_print(buffer);
}


