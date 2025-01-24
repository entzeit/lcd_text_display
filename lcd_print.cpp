#include "lcd_print.h"

#define LCD_LINE_LENGTH 16
const int scroll_delay_time = 350;
const int jump_time = 2200;
const int jump_step_offset = 0;
const int next_time = 2800;
const int clear_time = 80;


// Function to map multibyte German characters to their respective LCD byte codes
char map_german_char(uint8_t byte1, uint8_t byte2) {
  //assert: multibyte char
  switch (byte2) {
    case 0xA4: return 0xE1;  // 'ä'
    case 0xB6: return 0xEF;  // 'ö'
    case 0xBC: return 0xF5;  // 'ü'
    case 0x9F: return 0xE2;  // 'ß'
    case 0x84: return 0xE1;  // 'Ä' (same as 'ä')
    case 0x96: return 0xEF;  // 'Ö' (same as 'ö')
    case 0x9C: return 0xF5;  // 'Ü' (same as 'ü')
    default:   return '?';   // Unknown character, return placeholder
  }
}

bool is_multibyte_char(uint8_t c) {
  if (c == 0xC3) return true;
  return false;
}

//16x1 to 8x2 conversion:
int get_row(int pos) {
  if (pos >= 8) return 1;
  return 0;
}
int get_col(int pos) {
  return pos % 8;
}

// Function to print strings and handle multibyte UTF-8 characters
// The LCD is internally 8x2 (even though it appears as 16x1)
void print(const char* msg, int lcd_i) {
  lcd.clear();
  int col, row;
  int msg_i = 0; //message index
  while ((msg[msg_i] != '\0') && lcd_i <= (LCD_LINE_LENGTH - 1)) {
    col = get_col(lcd_i);
    row = get_row(lcd_i);
    lcd.setCursor(col, row);
    uint8_t byte1 = msg[msg_i];
    //check if utf-8 multibyte
    if (is_multibyte_char(byte1)) { 
      uint8_t byte2 = msg[msg_i + 1];  // Get the next byte for UTF-8 multibyte character
      lcd.write(map_german_char(byte1, byte2));  // Map and write the multibyte character
      msg_i+=2;  // Skip the second byte since it's part of the multibyte character
    } else {
      lcd.write(byte1);
      ++msg_i;
    }
    ++lcd_i;
  }
}

void jump_print(const char* message) {
  int i = 0;
  int line_length = LCD_LINE_LENGTH - jump_step_offset;
  int lines = (strlen(message) + (line_length - 1)) / line_length; // Ceiling division
  for (int i = 0; i < lines; ++i) {
    print(&message[i * line_length], 0);
    delay(jump_time);
  }
  lcd.clear();
  delay(next_time);
}

void scroll_print(const char* message) {
  for (int pos = 15; pos >= 1; --pos) {
    print(message, pos);
    delay(scroll_delay_time);
    lcd.clear();
    delay(clear_time);
  }
  for (int i = 0; message[i] != '\0'; ++i) {
    print(&message[i], 0);
    delay(scroll_delay_time);
    lcd.clear();
    delay(clear_time);
    if (is_multibyte_char(message[i])) ++i;
  }
  lcd.clear();
  delay(next_time);
}