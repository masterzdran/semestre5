#include "headers\Semaforo.h"

#ifndef PLANE
#define PLANE
class Plane{
	DWORD id;
	//Semaforo *sPlane;
	HANDLE hSemaforo;

public:
	Plane(){
		id = GetCurrentThreadId();
		//sPlane = new Semaforo(0,1);
		hSemaforo = CreateSemaphore(NULL, 0, 1, NULL);
	}
	DWORD GetIDThread(){
		return id;
	}
	void EsperarPista(){
		//sPlane->Wait();
		if ( WaitForSingleObject(hSemaforo, INFINITE) == WAIT_FAILED )
			FatalErrorSystem( TEXT("Erro na operação de Wait do semáforo") );
	}
	void TerPista(){
		//sPlane->Signal();
		if ( ReleaseSemaphore(hSemaforo, 1, NULL) == 0 )
			FatalErrorSystem( TEXT("Erro na operação de Signal do semáforo") );
	}
	~Plane(){
		id= 0;
		//delete(sPlane);
		if (CloseHandle(hSemaforo)==0)
	    	FatalErrorSystem( TEXT("Erro ao fechar o semaforo") );
	}
};
#endif PLANE