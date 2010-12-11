#include "LPC2106.h"

U32 chrono_elapsed(U32 initial) {
    return timer_read() - initial;
}
void chrono_delay(U32 msec){
    
}
