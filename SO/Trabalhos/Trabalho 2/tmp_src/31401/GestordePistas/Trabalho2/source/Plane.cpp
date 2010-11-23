#include "..\headers\Semaforo.h"

class Plane{
	int id;
	Semaforo *sPlane;

public:
	Plane(){
		id = GetCurrentThreadId();
		sPlane = new Semaforo(0);
	}
	~Plane(){
		id= 0;
		delete(sPlane);
	}
};