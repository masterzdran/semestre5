#include "headers\Semaforo.h"

#ifndef PLANE
#define PLANE
class Plane{
	DWORD id;
	Semaforo *sPlane;

public:
	Plane(){
		id = GetCurrentThreadId();
		sPlane = new Semaforo(0,0);
	}
	DWORD GetIDThread(){
		return id;
	}
	void EsperarPista(){
		sPlane->Wait();
	}
	void TerPista(){
		sPlane->Signal();
	}
	~Plane(){
		id= 0;
		delete(sPlane);
	}
};
#endif PLANE