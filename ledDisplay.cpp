#include "ledDisplay.h"
#include "mbed.h"

SPI spi(p5, p6, p7); // mosi, miso, sclk
DigitalOut cs(p18);
SPI spi1(p11, p12, p13);
DigitalOut cs1(p14);

int ms = 50;
int wt = 0.8;
int freq = 2;

    /*volatile uint8_t arrow_green_right[] = {
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 1, 0, 1, 1, 1, 0, 1,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    };*/

    volatile uint8_t arrow_red_left[] = {
        0, 0, 0, 224, 224, 224, 0, 0,
        0, 0, 224, 224, 224, 224, 224, 0,
        0, 224, 0, 224, 224, 224, 0, 224,
        0, 0, 0, 224, 224, 224, 0, 0,
        0, 0, 0, 224, 224, 224, 0, 0,
        0, 0, 0, 224, 224, 224, 0, 0,
        0, 0, 0, 224, 224, 224, 0, 0,
        0, 0, 0, 224, 224, 224, 0, 0,
    };

    volatile uint8_t arrow_blue_left[] = {
        0, 0, 0, 3, 3, 3, 0, 0,
        0, 0, 3, 3, 3, 3, 3, 0,
        0, 3, 0, 3, 3, 3, 0, 3,
        0, 0, 0, 3, 3, 3, 0, 0,
        0, 0, 0, 3, 3, 3, 0, 0,
        0, 0, 0, 3, 3, 3, 0, 0,
        0, 0, 0, 3, 3, 3, 0, 0,
        0, 0, 0, 3, 3, 3, 0, 0,
    };

    volatile uint8_t arrow_white_left[] = {
        0, 0, 0, 95, 95, 95, 0, 0,
        0, 0, 95, 95, 95, 95, 95, 0,
        0, 95, 0, 95, 95, 95, 0, 95,
        0, 0, 0, 95, 95, 95, 0, 0,
        0, 0, 0, 95, 95, 95, 0, 0,
        0, 0, 0, 95, 95, 95, 0, 0,
        0, 0, 0, 95, 95, 95, 0, 0,
        0, 0, 0, 95, 95, 95, 0, 0,
    };

    volatile uint8_t arrow_white_up[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 95, 0, 0,
        0, 0, 0, 0, 0, 0, 95, 0,
        0, 95, 95, 95, 95, 95, 95, 95,
        0, 95, 95, 95, 95, 95, 95, 95,
        95, 95, 95, 95, 95, 95, 95, 95,
        0, 0, 0, 0, 0, 0, 95, 0,
        0, 0, 0, 0, 0, 95, 0, 0,
    };

    volatile uint8_t arrow_blue_up[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 0, 0,
        0, 0, 0, 0, 0, 0, 3, 0,
        0, 3, 3, 3, 3, 3, 3, 3,
        0, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        0, 0, 0, 0, 0, 0, 3, 0,
        0, 0, 0, 0, 0, 3, 0, 0,
    };

    volatile uint8_t arrow_white_down[] = {
        0, 0, 0, 0, 95, 0, 0, 0,
        0, 0, 0, 95, 0, 0, 0, 0,
        0, 0, 95, 95, 95, 95, 95, 95,
        95, 95, 95, 95, 95, 95, 95, 95,
        95, 0, 95, 95, 95, 95, 95, 95,
        95, 0, 0, 95, 0, 0, 0, 0,
        0, 0, 0, 0, 95, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };

    volatile uint8_t arrow_blue_down[] = {
        0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 0, 3, 0, 0, 0, 0,
        0, 0, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        3, 0, 3, 3, 3, 3, 3, 3,
        3, 0, 0, 3, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };

    volatile uint8_t smiley_face[] = {
        0, 0, 0, 95, 95, 95, 0, 0,
        0, 0, 95, 95, 0, 95, 95, 0,
        0, 0, 95, 95, 0, 95, 95, 0,
        0, 0, 95, 95, 0, 0, 0, 0,
        0, 0, 0, 95, 95, 0, 0, 0,
        0, 0, 0, 95, 95, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 95, 95, 0, 0, 0,
    };

    volatile uint8_t smiley_smiley[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 95, 0, 0, 95, 0, 0,
        0, 0, 95, 0, 0, 95, 0, 0,
        0, 0, 95, 0, 0, 95, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 95, 0, 0, 0, 0, 95, 0,
        0, 95, 0, 0, 0, 0, 95, 0,
        0, 95, 95, 95, 95, 95, 95, 0,
    };

    volatile uint8_t blank[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };

    volatile uint8_t letter_a[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 204, 204, 46, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
    };

    volatile uint8_t letter_b[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
    };

    volatile uint8_t letter_c[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 204, 204, 204, 46, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 46, 204, 204, 204, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };

    volatile uint8_t letter_d[] = {
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 204, 204, 204, 46,
        46, 46, 46, 204, 46, 46, 204, 46,
        46, 46, 46, 204, 46, 46, 204, 46,
        46, 46, 46, 204, 204, 204, 204, 46,
    };

    volatile uint8_t letter_e[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 204, 204, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 204, 204, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 204, 204, 204, 46,
    };

    volatile uint8_t letter_f[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 204, 204, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 204, 204, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
    };

    volatile uint8_t letter_g[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 204, 204, 204, 46, 46,
        46, 46, 46, 204, 46, 204, 46, 46,
        46, 46, 46, 204, 204, 204, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 204, 46, 46,
        46, 46, 46, 204, 204, 204, 46, 46,
    };
    volatile uint8_t letter_h[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 204, 46, 46, 204, 46, 46, 46,
        46, 204, 46, 46, 204, 46, 46, 46,
        46, 204, 46, 46, 204, 46, 46, 46,
        46, 204, 204, 204, 204, 46, 46, 46,
        46, 204, 46, 46, 204, 46, 46, 46,
        46, 204, 46, 46, 204, 46, 46, 46,
        46, 204, 46, 46, 204, 46, 46, 46,
    };
    volatile uint8_t letter_i[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 46, 46, 46,
    };
    volatile uint8_t letter_j[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 204, 204, 204, 204, 204, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 204, 46, 46,
        46, 46, 46, 204, 204, 204, 46, 46,
    };
    volatile uint8_t letter_k[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 46, 204, 46, 204, 46, 46,
        46, 46, 46, 46, 204, 204, 46, 46,
        46, 46, 46, 46, 204, 204, 46, 46,
        46, 46, 46, 204, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_l[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 204, 204, 204, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_m[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 204, 204, 204, 204, 204, 204, 204,
        46, 204, 46, 46, 204, 46, 46, 204,
        46, 204, 46, 46, 204, 46, 46, 204,
        46, 204, 46, 46, 204, 46, 46, 204,
        46, 204, 46, 46, 46, 46, 46, 204,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_n[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 204, 46, 46, 204, 204, 46,
        46, 46, 204, 46, 204, 46, 204, 46,
        46, 46, 204, 204, 46, 46, 204, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_o[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
        46, 204, 46, 46, 46, 46, 204, 46,
        46, 204, 46, 46, 46, 46, 204, 46,
        46, 204, 46, 46, 46, 46, 204, 46,
        46, 204, 46, 46, 46, 46, 204, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_p[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 46, 46, 46,
        46, 46, 204, 46, 204, 46, 46, 46,
        46, 46, 204, 204, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_q[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 46, 46, 46,
        46, 46, 204, 46, 204, 46, 46, 46,
        46, 46, 204, 204, 204, 46, 46, 46,
        46, 46, 204, 46, 46, 46, 46, 46,
        46, 46, 204, 46, 46, 46, 46, 46,
        46, 204, 204, 204, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_r[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_s[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 204, 46,
        46, 46, 204, 204, 204, 204, 204, 46,
        46, 46, 204, 46, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 204, 204, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    volatile uint8_t letter_t[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 204, 204, 204, 204, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };

    volatile uint8_t letter_u[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };

    volatile uint8_t letter_v[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 46, 204, 46, 204, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };

    volatile uint8_t letter_w[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 204, 46, 46, 46, 204, 46, 46,
        46, 204, 46, 46, 46, 204, 46, 46,
        46, 204, 46, 204, 46, 204, 46, 46,
        46, 204, 46, 204, 46, 204, 46, 46,
        46, 204, 204, 204, 204, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };

    volatile uint8_t letter_x[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 204, 46, 46, 46, 46, 204, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 46, 204, 204, 46, 46, 46,
        46, 46, 46, 204, 204, 46, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 204, 46, 46, 46, 46, 204, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };

    volatile uint8_t letter_y[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 204, 46, 46, 46, 204, 46,
        46, 46, 46, 204, 46, 204, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };

    volatile uint8_t letter_z[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 204, 204, 204, 204, 204, 46, 46,
        46, 46, 204, 46, 46, 46, 46, 46,
        46, 46, 46, 204, 46, 46, 46, 46,
        46, 46, 46, 46, 204, 46, 46, 46,
        46, 46, 46, 46, 46, 204, 46, 46,
        46, 204, 204, 204, 204, 204, 204, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };
    
    volatile uint8_t letter_blank[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 46, 46, 46, 46, 46,
    };

ledDisplay::ledDisplay(PinName pin) : _pin(pin)
{
    _pin = 0;
     spi.format(8,3);
    spi.frequency(100000);
    spi1.format(8,3);
    spi1.frequency(100000);
}

void ledDisplay::drawChar(char character)
{
    if (character == 'a' || character == 'A'){
        draw_pattern(5);
    }
    else if (character == 'b' || character == 'B'){draw_pattern(6);
    }
    else if (character == 'c' || character == 'C'){draw_pattern(7);
    }
    else if (character == 'd' || character == 'D'){draw_pattern(8);
    }
    else if (character == 'e' || character == 'E'){draw_pattern(9);
    }
    else if (character == 'f' || character == 'F'){draw_pattern(10);
    }
    else if (character == 'g' || character == 'G'){draw_pattern(11);
    }
    else if (character == 'h' || character == 'H'){draw_pattern(12);
    }
    else if (character == 'i' || character == 'I'){draw_pattern(13);
    }
    else if (character == 'j' || character == 'J'){draw_pattern(14);
    }
    else if (character == 'k' || character == 'K'){draw_pattern(15);
    }
    else if (character == 'l' || character == 'L'){draw_pattern(16);
    }
    else if (character == 'm' || character == 'M'){draw_pattern(17);
    }
    else if (character == 'n' || character == 'N'){draw_pattern(18);
    }
    else if (character == 'o' || character == 'O'){draw_pattern(19);
    }
    else if (character == 'p' || character == 'P'){draw_pattern(20);
    }
    else if (character == 'q' || character == 'Q'){draw_pattern(21);
    }
    else if (character == 'r' || character == 'R'){draw_pattern(22);
    }
    else if (character == 's' || character == 'S'){draw_pattern(23);
    }
    else if (character == 't' || character == 'T'){draw_pattern(24);
    }
    else if (character == 'u' || character == 'U'){draw_pattern(25);
    }
    else if (character == 'v' || character == 'V'){draw_pattern(26);
    }
    else if (character == 'w' || character == 'W'){draw_pattern(27);
    }
    else if (character == 'x' || character == 'X'){draw_pattern(28);
    }
    else if (character == 'y' || character == 'Y'){draw_pattern(29);
    }
    else if (character == 'z' || character == 'Z'){draw_pattern(30);
    }
    else{draw_pattern(31);}
    
}

void ledDisplay::draw_pattern(int pattern)
{
    switch(pattern) {
        case 5: {
            int i=0;
            do {
                cs = 0;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_a[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 6: {
            int i=0;
            do {
                cs = 0;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_b[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 7: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_c[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 8: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_d[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 9: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_e[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 10: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_f[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 11: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_g[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 12: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_h[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 13: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_i[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 14: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_j[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 15: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_k[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 16: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_l[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 17: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_m[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 18: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_n[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 19: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_o[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 20: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_p[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 21: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_q[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 22: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_r[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 23: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_s[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 24: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_t[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 25: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_u[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 26: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_v[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 27: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_w[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 28: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_x[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 29: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_y[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 30: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_z[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
        case 31: {
            int i=0;
            do {
                cs = 0;
                //cs1 = 0;
                ////////myled = 1;
                wait_ms(ms);
                for(int k=0; k<65; k++) {
                    spi.write(letter_blank[k+1]);
                    //spi1.write(image[k+1]);
                }
                wait_ms(ms);
                cs = 1;
                ////////myled=0;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
    }//ACTUAL END
}