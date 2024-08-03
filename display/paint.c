#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "string.h"
#include "stdio.h"
#include <oled.h>
#include "paint.h"
#include "math.h"

void display_hex_array(const uint8_t hex_array[], int x, int y) {
    int height = hex_array[22], width = hex_array[18];
    int offset = hex_array[10];

    int bpp = hex_array[28];
    printf("BPP: %d\n", bpp);

    int count = 0;

    for (int t = y+1; t < height+1+y; t++) {
        for (int z = x+1; z < width+1+x; z++) {
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
    int customOffset = 2;

    int numWidth = numbers[0];
    int interval = numbers[1];
    int width = numbers[18+customOffset], height = numbers[22+customOffset];
    int offset = numbers[10+customOffset];

    int startingPoint = (interval*number)+(numWidth*number)-interval+customOffset;
    int endingPoint = startingPoint+numWidth;

    int count = 0;

//    printf("STARTING POINT: %d\n", startingPoint);
//    printf("ENDING POINT: %d\n", endingPoint);

    x-=startingPoint;

    for (int t = y+1; t < height+1+y; t++) {
        for (int z = x+1; z < width+1+x; z++) {
            if (count/4%width >= startingPoint && count/4%width <= endingPoint) {
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

void display_number(char *number, const uint8_t numbers[], int x, int y, int spacing) {
    int length = strlen(number);

    int interval = numbers[1];  
    int numWidth = numbers[0];

    printf("WIDTH: %d\n", numWidth);
    printf("INTERVAL: %d\n", interval);

    for (int i = 0; i < strlen(number); i++) {
        int num = number[i]-'0';

        display_single_digit(num, numbers, x-i*(interval+numWidth)-(spacing*i), y);
    }
}

void draw_rectangle(int x1, int y1, int x2, int y2) {

    int xdiff = x2-x1;
    int ydiff = y2-y1;

    if (xdiff < 0) {
        xdiff = 0-xdiff;
    }

    if (ydiff < 0) {
        ydiff = 0-ydiff;
    }

    sh1107_draw_line(x2-xdiff, y2, x2, y2);
    sh1107_draw_line(x2, y2-ydiff, x2, y2);
    sh1107_draw_line(x1, y1, x1+xdiff, y1);
    sh1107_draw_line(x1, y1, x1, y1+ydiff);   
}

void draw_filled_rectangle(int x1, int y1, int x2, int y2) {
    int i = 0;

    while (true)
    {
        draw_rectangle(x1+i, y1+i, x2-i, y2-i);

        if (x1+i==x2-i || x1+i==x2-i-1 || x1+i-1==x2-i) {
            break;
        }

        sh1107_update_display();

        i++;
    }
    
}