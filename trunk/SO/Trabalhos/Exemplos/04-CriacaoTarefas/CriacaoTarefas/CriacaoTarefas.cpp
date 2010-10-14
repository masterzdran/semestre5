// CriacaoTarefas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <MMSystem.h>

//const int NumThreads = 5;

int x;
void showTimes(HANDLE hThread);

typedef struct _ThreadArgs {
  DWORD id;
  DWORD nbrExp;
  DWORD totalExp;
} ThreadArgs, * PThreadArgs;


DWORD WINAPI ImprimeThread(LPVOID args)
{
    int id = (int)args;
    _tprintf( TEXT("[[1]Thread nº %2d] Olá Mundo.\n"), id);

    //ExitThread( (DWORD)id );
    //chENDTHREADEX( (DWORD)id );

    return (DWORD)id;
}


DWORD WINAPI ImprimeThreadArgsByStruct(LPVOID _args)
{
    PThreadArgs args = (PThreadArgs)_args;
    _tprintf( TEXT("[[2]Thread nº %2d] Olá Mundo.\n"), args->id);

    //chENDTHREADEX( args->id );

    return args->id;
}


void showThreadExitCode(HANDLE * hThreads, int NumThreads)
{
  DWORD exitCode;

  for(int idThread=0; idThread<NumThreads; ++idThread) {

    if (GetExitCodeThread(hThreads[idThread], &exitCode)==0) {
        ReportErrorSystem( TEXT("Erro ao obter o código de terminação da tarefa %d"), idThread);
    }
    else {
        if ( exitCode==STILL_ACTIVE ) {
            _tprintf( TEXT("A tarefa %d ainda se encontra em execução.\n"), idThread );
        }
        else {
            _tprintf( TEXT("A tarefa %d terminou com o valor %d.\n"), idThread, exitCode );
        }
    }
  }
}

void IshowThreadExitCode(HANDLE * hThreads, int NumThreads,int* total)
{
  DWORD exitCode;

  for(int idThread=0; idThread<NumThreads; ++idThread) {

    if (GetExitCodeThread(hThreads[idThread], &exitCode)==0) {
        ReportErrorSystem( TEXT("Erro ao obter o código de terminação da tarefa %d"), idThread);
    }
    else {
        if ( exitCode==STILL_ACTIVE ) {
            _tprintf( TEXT("A tarefa %d ainda se encontra em execução.\n"), idThread );
        }
        else {
            _tprintf( TEXT("A tarefa %d terminou com o valor %d.\n"), idThread, exitCode );
			*total = exitCode + *total;
			showTimes(hThreads[ idThread ] );
        }
    }
  }
}

static DOUBLE randVal(DOUBLE min, DOUBLE max){
	return (DOUBLE)rand()/(RAND_MAX + 1)*(max - min) + min;
}

BOOL isInsideCircle(DOUBLE xx, DOUBLE yy, DOUBLE radius ){
	return ((xx*xx) + (yy*yy))<= radius*radius;
}

DOUBLE piValue(DOUBLE insidePoints, DOUBLE totalExperiences){
	return (insidePoints/totalExperiences)*4;
}

DWORD WINAPI ThreadsCode(LPVOID args)
{
	PThreadArgs experiencias = (PThreadArgs)(args);
	DWORD n_expr = 0;
	
	DOUBLE xx = 0;
	DOUBLE yy = 0;
	srand(experiencias->id);
	for(DWORD i = 0;i < (experiencias->nbrExp) ;++i)
	{
		xx = randVal(-0.5,0.5) ;
		yy = randVal(-0.5,0.5);
		if(isInsideCircle(xx,yy,0.5))
		{
			++n_expr;
		}
	}
	experiencias->totalExp = n_expr;
//	_tprintf(TEXT("[[NAC] %i -> %i]\n"),experiencias->id,experiencias->totalExp);
	return n_expr;
}
void showTimes(HANDLE hThread)
{
    union { // simplifies elapsed time calculation
        LONG64   li;
        FILETIME ft;
    } creationTime, exitTime, elapsedTime;


    FILETIME kernelTime;
    FILETIME userTime;

    if ( GetThreadTimes(hThread, &creationTime.ft, &exitTime.ft, &kernelTime, &userTime)==0 ) {

        ReportErrorSystem( TEXT("Erro ao obter os tempos de execução da tarefa %h"), hThread );
    }
    else
    {
        SYSTEMTIME syElapsedTime;
        SYSTEMTIME syKernelTime;
        SYSTEMTIME syUserTime;

        elapsedTime.li = exitTime.li - creationTime.li; 

        FileTimeToSystemTime( &elapsedTime.ft, &syElapsedTime);
        FileTimeToSystemTime( &kernelTime, &syKernelTime);
        FileTimeToSystemTime( &userTime, &syUserTime);

        _tprintf( 
          TEXT("Tempo de execução ------ %02d:%02d:%02d,%03d\n"), 
          syElapsedTime.wHour, 
          syElapsedTime.wMinute, 
          syElapsedTime.wSecond, 
          syElapsedTime.wMilliseconds );

        _tprintf( 
           TEXT("Tempo em modo kernel --- %02d:%02d:%02d,%03d\n"), 
           syKernelTime.wHour, 
           syKernelTime.wMinute, 
           syKernelTime.wSecond, 
           syKernelTime.wMilliseconds );

        _tprintf(
          TEXT("Tempo em modo user ----- %02d:%02d:%02d,%03d\n"),
          syUserTime.wHour, 
          syUserTime.wMinute, 
          syUserTime.wSecond, 
          syUserTime.wMilliseconds );
    }
}
int _tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale( LC_ALL, TEXT("portuguese_portugal") );

    if (argc != 3 ) 
	{
		_tprintf(TEXT("Numero Invalido de Argumentos. Devem ser 3, existem %i"),argc);
		_gettchar();
		return 1;
	}


	//	Leitura dos valores da linha de comandos
	DWORD tarefasNbr	=	_ttoi((_TCHAR*) argv[1]);
	DWORD expNbr		=	_ttoi((_TCHAR*) argv[2]);
	//_tprintf(TEXT("[NAC] :: [0] %i [1] %i\n"),tarefasNbr, expNbr);

	//DOUBLE xx = 0;
	//DOUBLE yy = 0;
	//DWORD in = 0;
	
	
	
	//for (DWORD i =0;i<expNbr;++i){
	//	xx = randVal(-0.50,0.50);
	//	yy = randVal(-0.50,0.50);
	//	if (isInsideCircle(xx,yy,0.5)){++in;}
	//}
	//_tprintf(TEXT("[NAC] :: [PI VALUE] %f [Nbr Exp] %i [Nbr Inside] %i\n"),piValue(in,expNbr), expNbr,in);
	//_gettchar();
	//return 1;

	//	Criação do espaço que vai albergar das estruturas
	_tprintf( TEXT("[main] Vou criar as tarefas.\n") );
	HANDLE* hThreads	= (HANDLE*)calloc(tarefasNbr,sizeof(HANDLE));
	DWORD*  idThreads	= (DWORD*)calloc(tarefasNbr,sizeof(DWORD));	
	ThreadArgs* args = (ThreadArgs*)calloc(tarefasNbr,sizeof(ThreadArgs));

	DWORD totalExp=tarefasNbr*expNbr;
	DWORD totalExpInside=0;

    for (DWORD idThread=0; idThread < tarefasNbr; ++idThread) {

        args[ idThread ].id = idThread;
		args[ idThread ].nbrExp = expNbr;

		hThreads[ idThread ] = chBEGINTHREADEX( NULL, 0, ThreadsCode, (LPVOID)(&args[ idThread ]), NULL, idThreads[ idThread ] );
    }


	/*(LPVOID)(expNbr)*/
   // _tprintf( TEXT("[main] Esperar pela terminação das tarefas.\n") );

	WaitForMultipleObjects( tarefasNbr, hThreads, TRUE, INFINITE );
	
	//_tprintf( TEXT("[main] [HANDLES abertos] Mostrar o código de terminação das tarefas.\n") );
    IshowThreadExitCode( hThreads, tarefasNbr,(int*)&totalExpInside );

    //_tprintf( TEXT("[main] Fechar os HANDLES das tarefas.\n") );
	for (DWORD idThread=0; idThread<tarefasNbr; ++idThread) {

        CloseHandle( hThreads[ idThread ] );
    }
	_tprintf(TEXT("[NAC] :: [PI VALUE] %f [Nbr Exp] %i [Nbr Inside] %i\n"),piValue(totalExpInside,totalExp), totalExp,totalExpInside);
	//_tprintf( TEXT("[main] Função principal a terminar.\nPrima uma tecla para continuar.\n") );
    _gettch();

	free(args);
	free(hThreads);
	free(idThreads);
	return 0;
}
