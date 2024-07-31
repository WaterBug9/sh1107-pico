#ifndef OLED_H_   /* Include guard */
#define OLED_H_

#define SPI_PORT spi1
#define PIN_CS 13
#define PIN_DC 14
#define PIN_RST 12
#define PIN_SCK 10
#define PIN_MOSI 11

#define SH1107_WIDTH 128
#define SH1107_HEIGHT 128

void sh1107_init_spi();
void sh1107_send_command(uint8_t cmd);
void sh1107_send_data(uint8_t data, int len);
void sh1107_empty_buffer();
void sh1107_fill_buffer();
void sh1107_init();
void sh1107_update_display();
void sh1107_set_pixel(int x, int y, bool on);
void sh1107_draw_line(int x1, int y1, int x2, int y2);
void sh1107_draw_scaled_line(int x1, int y1, int x2, int y2, int thickness);
void sh1107_draw_square(int x, int y, int size);
void sh1107_draw_filled_square(int x, int y, int size);
void sh1107_fill_screen(bool white);
void face();

#endif // FOO_H_