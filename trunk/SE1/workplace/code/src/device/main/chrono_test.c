#include "../LPC2106/LPC2106.h"
#include "../timer/chrono.h"
#include "../led/led.h"

int main() {
    lpc2106_init();
    chrono_init();
    led_init();
    while (1) {
        led_write(1);
        chrono_delay(2000);
        led_write(0);
        chrono_delay(2000);
    }
}
