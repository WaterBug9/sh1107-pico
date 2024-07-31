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

void display_single_digit(int number, const uint8_t numbers[], int x, int y) {
    number = 9-number;

    int interval = 5;
    int numWidth = numbers[18], numHeight = numbers[22];
    int offset = numbers[10];

    int startingPoint = (interval*number)+(20*number)-interval;
    int endingPoint = startingPoint+20;

    int count = 0;

//    printf("STARTING POINT: %d\n", startingPoint);
//    printf("ENDING POINT: %d\n", endingPoint);

    x-=startingPoint;

    for (int t = y+1; t < numHeight+1+y; t++) {
        for (int z = x+1; z < numWidth+1+x; z++) {
            if (count/4%numWidth >= startingPoint && count/4%numWidth <= endingPoint) {
                uint8_t pixel = numbers[count+offset];
                if (pixel == 0x00) {
                    sh1107_set_pixel(z, t, true);
                } else {
                    sh1107_set_pixel(z, t, false);
                }
            }
            count+=4;
        }
        
    }
}

void display_number(char *number, const uint8_t numbers[], int x, int y) {
    int length = strlen(number);
 //   char split = strtok(number, "");

    int interval = 5;
    int numWidth = 20;

    for (int i = 0; i < strlen(number); i++) {
        int num = number[i]-'0';
        printf("%d\n", num);

        display_single_digit(num, numbers, x-i*(interval+numWidth), y);
    }
}