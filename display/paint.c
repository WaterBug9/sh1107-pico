#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "string.h"
#include "stdio.h"
#include <oled.h>
#include "paint.h"

void display_hex_array(const uint8_t hex_array[]) {
    uint8_t x = 0, y = 0; // Starting coordinates
    int height = hex_array[22], width = hex_array[18];
    int offset = hex_array[10];

    int bpp = hex_array[28];
    printf("BPP: %d\n", bpp);

    int count = 0;

    for (int t = y+1; t < height+1; t++) {
        for (int z = x+1; z < width+1; z++) {
            uint8_t pixel = hex_array[count+offset];
            if (pixel != 0x00) {
                sh1107_set_pixel(z, t, true);
            } else {
                sh1107_set_pixel(z, t, false);
            }
            count+=4;
        }
    }
}