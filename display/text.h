#ifndef TEXT_H_   /* Include guard */
#define TEXT_H

void sh1107_draw_char(uint8_t x, uint8_t y, char c, bool clear);
void sh1107_draw_string(uint8_t x, uint8_t y, char *str);
void sh1107_clear_string(uint8_t x, uint8_t y, const char *str);
void display_hex_array();

#endif