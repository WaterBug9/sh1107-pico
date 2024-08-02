#ifndef PAINT_H_
#define PAINT_H_

void display_hex_array(const uint8_t hex_array[], int x, int y);
void display_single_digit(int number, const uint8_t numbers[], int x, int y);
void display_number(char *number, const uint8_t numbers[], int x, int y, int spacing);
void draw_rectangle(int x1, int y1, int x2, int y2);
void draw_filled_rectangle(int x1, int y1, int x2, int y2);

#endif