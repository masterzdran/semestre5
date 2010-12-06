#include "headers\Semaforo.h"

#ifndef PLANE
#define PLANE
class Plane{
	DWORD id;
	HANDLE hSemaforo;
	int numberPlane;
	_TCHAR* name;
public:
	Plane(int number){
		id = GetCurrentThreadId();
		hSemaforo = CreateSemaphore(NULL, 0, 1, NULL);
		numberPlane = number;
		name = new _TCHAR();
		(*name)=0;
	}
	DWORD GetIDThread(){
		return id;
	}
	void EsperarPista(HANDLE Event){
		static HANDLE SH[] = {hSemaforo, Event};
		if ( WaitForSingleObject(hSemaforo, INFINITE) == WAIT_FAILED )
			FatalErrorSystem( TEXT("Erro na operação de Wait do semáforo") );
	}
	void TerPista(){
		if ( ReleaseSemaphore(hSemaforo, 1, NULL) == 0 )
			FatalErrorSystem( TEXT("Erro na operação de Signal do semáforo") );
	}
	_TCHAR* GetName()
	{	
		if((*name)==0){ _stprintf(name,_T("A%d"),numberPlane); }
		return name;
	}
	~Plane(){
		if (CloseHandle(hSemaforo)==0)
	    	FatalErrorSystem( TEXT("Erro ao fechar o semaforo") );
		delete name;
	}
};
#endif PLANE