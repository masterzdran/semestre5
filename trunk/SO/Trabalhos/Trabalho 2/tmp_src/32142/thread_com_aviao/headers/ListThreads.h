#include "headers\Semaforo.h"
#ifndef LIST
#define LIST

class ListThreads{
public:
	Semaforo* _s;
	ListThreads* _next;
public:
	ListThreads(Semaforo* s){
		_s = s;
		_next = NULL;
	}
};

#endif LIST