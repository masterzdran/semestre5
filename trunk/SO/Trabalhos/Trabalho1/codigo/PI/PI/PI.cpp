#include "stdafx.h"

#define NUMBER_OF_DECIMAL 1001
#define RADIUS (1/(float)4)

typedef struct Point{
	float x;
	float y;
} Point_t[1], * Point_ptr;

float __inline GenerateNumber(){
	return (rand()%NUMBER_OF_DECIMAL)/(float)(NUMBER_OF_DECIMAL-1);
}

void __inline SetCoors(Point_ptr p)
{
	p->x = GenerateNumber();
	p->y = GenerateNumber();
}

bool __inline CheckIfItIsInsideTheUnitaryCircle(Point_ptr p){
	return (p->x * p->x) + (p->y * p->y) <= RADIUS;
}

//retorna o núemro de pontos que estao dentro da circunferencia.
DWORD WINAPI FunctionOfThreads(LPVOID numPointers)
{
	DWORD inCircle = 0;
	DWORD num = (DWORD) numPointers;
	for(DWORD i = 0; i < num; ++i){
		Point_t p;
		SetCoors(p);
		if(CheckIfItIsInsideTheUnitaryCircle(p)) ++inCircle;
	}
	return inCircle;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 2){
		_tprintf(TEXT("PI <number-of-threads> <time>\n\n"));		
		return -1;
	}
	_tsetlocale( LC_ALL, TEXT("portuguese_portugal") );
	
	//ler do standart output o numero de tarefas a criar
	DWORD NumThreads = _wtoi(argv[1]);
	
	//ler numero de pontos a criar
	DWORD Pontos  = _wtoi(argv[2]);
	
	_tprintf( TEXT("Tarefas: %d , Pontos: %d\n"), NumThreads, Pontos );
	
	DWORD NumPointForThread = NumThreads/Pontos;

	HANDLE* hThreads = (HANDLE*)calloc(NumThreads,sizeof(HANDLE));
	DWORD* idThreads = (DWORD *)calloc(NumThreads,sizeof(DWORD));
	
	for(DWORD i = 0; i < NumThreads; ++i){
		hThreads[i] = chBEGINTHREADEX(NULL,
										0,
										FunctionOfThreads,
										(LPVOID) NumPointForThread,
										NULL, 
										&idThreads[i] );
		
	}

	_tprintf( TEXT("Aguarde pela terminação das threads.\n") );
	WaitForMultipleObjects( NumThreads, hThreads, TRUE, INFINITE );

	_tprintf( TEXT("Fechar os HANDLES das tarefas.\n") );

	DWORD numOfPointsInCircle = 0;

	for (DWORD i=0; i<NumThreads; ++i) {
		DWORD in = 0;
		GetExitCodeThread(hThreads[i],&in);
		CloseHandle(hThreads[i]);
		numOfPointsInCircle =+ in;
	}
	
	_tprintf( TEXT("A percentagem de pontos dentro da circunferencia foram:\n%d"), (numOfPointsInCircle/(float)Pontos)*100 );


	_tprintf( TEXT("[main] Função principal a terminar.\nPrima uma tecla para continuar.\n") );
    _gettch();

	free(idThreads);
	free(hThreads);
	return 0;
}