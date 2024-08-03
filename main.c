#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "string.h"
#include "stdio.h"
#include "oled.h"
#include "text.h"
#include "images.h"
#include "paint.h"

int main() {
    stdio_init_all();
    sh1107_init();

    printf("Running ...\n");

    sh1107_empty_buffer();

    sh1107_update_display();

    char n[] = "Hello World!";

    sh1107_draw_string(34, 10, n);

    sh1107_update_display();
    
    while (1) {
        tight_loop_contents();
    }

    return 0;
}