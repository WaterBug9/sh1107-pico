#ifndef PAINT_H_
#define PAINT_H_

void display_hex_array(const uint8_t hex_array[]);
void display_single_digit(int number, const uint8_t numbers[], int x, int y);
void display_number(char *number, const uint8_t numbers[], int x, int y);

#endif