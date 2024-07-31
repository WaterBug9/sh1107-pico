#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "string.h"
#include "stdio.h"
#include "oled.h"

uint8_t buffer[SH1107_WIDTH * (SH1107_HEIGHT / 8)];

void sh1107_init_spi() {
    spi_init(SPI_PORT, 10000 * 1000);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    gpio_init(PIN_DC);
    gpio_set_dir(PIN_DC, GPIO_OUT);

    gpio_init(PIN_RST);
    gpio_set_dir(PIN_RST, GPIO_OUT);
    gpio_put(PIN_RST, 1);
}

void sh1107_send_command(uint8_t cmd) {
    gpio_put(PIN_DC, 0);
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &cmd, 1);
    gpio_put(PIN_CS, 1);
}

void sh1107_send_data(uint8_t data, int len) {
    gpio_put(PIN_DC, 1);
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &data, len);
    gpio_put(PIN_CS, 1);
}

void sh1107_empty_buffer() {
    for (int i = 0; i < 2048; i++) {
        buffer[i] = 0x00;
    }
}

void sh1107_fill_buffer() {
    for (int i = 0; i < 2048; i++) {
        buffer[i] = 0xff;
    }
}

void sh1107_init() {
    sh1107_init_spi();

    gpio_put(PIN_RST, 0);
    sleep_ms(100);
    gpio_put(PIN_RST, 1);
    sleep_ms(100);

    sh1107_empty_buffer();

    // Initialization sequence for SH1107
    sh1107_send_command(0xAE);  // Display OFF
    sh1107_send_command(0xA8);  // Set multiplex ratio
    sh1107_send_command(0x7F);  // 128MUX
    sh1107_send_command(0xD3);  // Set display offset
    sh1107_send_command(0x00);  // No offset
    sh1107_send_command(0x40);  // Set display start line
    sh1107_send_command(0xA1);  // Segment re-map
    sh1107_send_command(0xC8);  // COM output scan direction
    sh1107_send_command(0xDA);  // Set COM pins hardware configuration
    sh1107_send_command(0x12);
    sh1107_send_command(0x81);  // Contrast control
    sh1107_send_command(0x80);
    sh1107_send_command(0xA4);  // Entire display ON
    sh1107_send_command(0xA6);  // Normal display
    sh1107_send_command(0xD5);  // Set display clock divide ratio
    sh1107_send_command(0x80);
    sh1107_send_command(0x8D);  // Charge pump setting
    sh1107_send_command(0x14);
    sh1107_send_command(0xAF);  // Display ON
}

void sh1107_update_display() {
    for (int page = 0; page < 16; page++) {

        sh1107_send_command(0xB0 | page);

        sh1107_send_command(0x00);
        sh1107_send_command(0x10);

        for (int index = page*SH1107_WIDTH; index < page*SH1107_WIDTH+128; index++) {
            sh1107_send_data(buffer[index], 1);
        }

    }
}

void sh1107_set_pixel(int x, int y, bool on) {

    if (on) {
   //     int index = x*y/4;
        uint16_t index = x + (y / 8) * SH1107_WIDTH;
        buffer[index] |= (1 << y%8);
    } else {
        uint16_t index = x + (y / 8) * SH1107_WIDTH;
        buffer[index] &= ~(1 << y%8);
    }
}

void sh1107_draw_line(int x1, int y1, int x2, int y2) {
    if (x1 != x2) {
        int gradient = 2 * (y2 - y1); 
        int slope_error_new = gradient - (x2 - x1); 
        for (int x = x1, y = y1; x <= x2; x++) {   
            // Add slope to increment angle formed 
            slope_error_new += gradient; 
    
            // Slope error reached limit, time to 
            // increment y and update slope error. 
            if (slope_error_new >= 0) { 
                y++; 
                slope_error_new -= 2 * (x2 - x1); 
            } 

            sh1107_set_pixel(x, y, true);
        } 
    } else {
        for (int y = y1; y <= y2; y++) {
            sh1107_set_pixel(x1, y, true);
        }
    }

}

void sh1107_draw_scaled_line(int x1, int y1, int x2, int y2, int thickness) {
    for (int t = -(thickness/2); t < thickness/2+1; t++) {
        if (y1 == y2) 
        {
            sh1107_draw_line(x1, y1+t, x2, y2+t);
        } else if (x1 == x2)
        {
            sh1107_draw_line(x1+t, y1, x2+t, y2);
        } else 
        {
            sh1107_draw_line(x1+t, y1, x2, y2+t);
            printf("damn %d\n", t);
        }
        
    }
}

void sh1107_draw_square(int x, int y, int size) {
    sh1107_draw_line(x+size/2, y-size/2, x+size/2, y+size/2);
    sh1107_draw_line(x-size/2, y-size/2, x+size/2, y-size/2);
    sh1107_draw_line(x-size/2, y-size/2, x-size/2, y+size/2);
    sh1107_draw_line(x-size/2, y+size/2, x+size/2, y+size/2);
}

void sh1107_draw_filled_square(int x, int y, int size) {
    for (int i = 0; i < size+1; i++) {
        sh1107_draw_square(x, y, i);
    }
}

void sh1107_fill_screen(bool white) {
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 128; y++) {
            sh1107_set_pixel(x, y, white);
        }
    }
}

void face() {
    sh1107_draw_filled_square(50, 60, 5);
    sh1107_draw_filled_square(70, 60, 5);
    sh1107_draw_line(45, 70, 75, 70);
}


