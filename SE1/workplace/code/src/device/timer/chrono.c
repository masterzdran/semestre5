#include "chrono.h"


void chrono_init(){
	timer_init();
}
U32 chrono_elapsed(U32 initial) {
    return timer_read() - initial;
}

void chrono_delay(U32 msec){
	while(chrono_elapsed(timer_read()) == msec){}		
}
