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

 //   sh1107_fill_buffer();
    sh1107_update_display();

 //   display_hex_array(numbers);
    display_number("27", numbers12x16, 44, 64, 2);
    display_hex_array(thermometer, 64, 58);

    sh1107_update_display();
  //  sh1107_empty_buffer();

    sleep_ms(2000);

 //   sh1107_update_display();
    
    while (1) {
        tight_loop_contents();
    }

    return 0;
}