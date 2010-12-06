#include "headers\Semaforo.h"

#ifndef PLANE
#define PLANE
class Plane{
	DWORD id;
	//Semaforo *sPlane;
	HANDLE hSemaforo;
	int numberPlane;
	_TCHAR* name;
public:
	Plane(int number){
		id = GetCurrentThreadId();
		//sPlane = new Semaforo(0,1);
		hSemaforo = CreateSemaphore(NULL, 0, 1, NULL);
		numberPlane = number;
		name = new _TCHAR();
		(*name)=0;
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
	_TCHAR* GetName()
	{	
		if((*name)==0){ _stprintf(name,_T("A%d"),numberPlane); }
		return name;
	}
	~Plane(){
		//delete(sPlane);
		if (CloseHandle(hSemaforo)==0)
	    	FatalErrorSystem( TEXT("Erro ao fechar o semaforo") );
	}
};
#endif PLANE