#include "stdafx.h"

#define NUMBER_OF_DECIMAL 1001
#define RADIUS (1/(float)2)

float __inline GenerateNumber()
{
	return (rand()%NUMBER_OF_DECIMAL)/(float)(NUMBER_OF_DECIMAL-1);
}

bool __inline CheckIfItIsInsideTheUnitaryCircle(int x, int y)
{
	return (x * x) + (y * y) <= RADIUS*RADIUS;
}

//retorna o núemro de pontos que estao dentro da circunferencia.
DWORD WINAPI FunctionOfThreads(LPVOID numPointers)
{
	int * numPointAndId = (int*) numPointers;
	DWORD inCircle = 0;
	DWORD num = (DWORD) numPointAndId[0];
	srand(time(*numPointAndId[1]));
	for(DWORD i = 0; i < num; ++i)
	{
		if(CheckIfItIsInsideTheUnitaryCircle(GenerateNumber(),GenerateNumber()))
		{
			++inCircle;
		}
	}
	return inCircle;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 2)
	{
		_tprintf(TEXT("PI <number-of-threads> <time>\n\n"));		
		return -1;
	}
	_tsetlocale( LC_ALL, TEXT("portuguese_portugal") );
	
	//ler do standart output o numero de tarefas a criar
//	DWORD NumThreads = _wtoi(argv[1]);
	DWORD NumThreads = 5;
	
	//ler numero de pontos a criar
//	DWORD Pontos  = _wtoi(argv[2]);
	DWORD Pontos = 5000000;

	_tprintf( TEXT("Tarefas: %d , Pontos: %d\n"), NumThreads, Pontos );
	
	DWORD NumPointForThread = NumThreads/Pontos;

	HANDLE* hThreads = (HANDLE*)calloc(NumThreads,sizeof(HANDLE));
	DWORD* idThreads = (DWORD *)calloc(NumThreads,sizeof(DWORD));
	int numPointAndId[2];

	for(DWORD i = 0; i < NumThreads; ++i)
	{
		numPointAndId[0] = NumPointForThread;
		numPointAndId[1] = &idThreads[i];
		hThreads[i] = chBEGINTHREADEX(NULL,
										0,
										FunctionOfThreads,
										(LPVOID) numPointAndId,
										NULL, 
										&idThreads[i] );
	}

	_tprintf( TEXT("Aguarde pela terminação das threads.\n") );
	WaitForMultipleObjects( NumThreads, hThreads, TRUE, INFINITE );

	_tprintf( TEXT("Fechar os HANDLES das tarefas.\n") );

	DWORD numOfPointsInCircle = 0;

	for (DWORD i=0; i<NumThreads; ++i)
	{
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