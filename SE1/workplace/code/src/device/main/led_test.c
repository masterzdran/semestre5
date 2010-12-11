#include "../led/led.h"


int main() {
    led_init();
    while (1) {
        int i;
        led_write(0);
        for (i = 0; i < 10000; ++i);
        led_write(1);
        for (i = 0; i < 10000; ++i);
    }
}
