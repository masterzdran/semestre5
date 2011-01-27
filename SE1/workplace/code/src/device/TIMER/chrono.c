#include "lpc2106.h"
#include "chrono.h"
#include "led.h"
int main() {
    lpc2106_init();
    chrono_init();
    led_init();
    while (1) {
        led_write(1);
        chrono_delay(500);
        led_write(0);
        chrono_delay(500);
    }
}
