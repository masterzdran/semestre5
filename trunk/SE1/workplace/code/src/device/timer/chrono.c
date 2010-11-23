#include "chrono.h"


void chrono_init(){
	timer_init();
}
U32 chrono_elapsed(U32 initial) {
    return timer_read() - initial;
}

void chrono_delay(U32 msec){
	U32 start = timer_read();
	while(chrono_elapsed(start) <= msec){}		
}
