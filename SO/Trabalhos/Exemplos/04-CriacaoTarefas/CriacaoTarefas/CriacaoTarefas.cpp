// CriacaoTarefas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>


//const int NumThreads = 5;

int x;


typedef struct _ThreadArgs {
  DWORD id;
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

DOUBLE randVal(DOUBLE min, DOUBLE max){
	
	return (DOUBLE)rand()/(RAND_MAX + 1)*(max - min) + min;
}

BOOL isInsideCircle(DOUBLE xx, DOUBLE yy, DOUBLE radius ){
	return ((xx*xx) + (yy*yy))<= radius*radius;
}

DOUBLE piValue(DOUBLE insidePoints, DOUBLE totalExperiences){
	return (insidePoints/totalExperiences)*4;
}

int _tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale( LC_ALL, TEXT("portuguese_portugal") );

    if (argc != 3 ) 
	{
		_tprintf(TEXT("Numero Invalido de Argumentos. Devem ser 3, existem %i"),argc);
		Sleep(2000);
		return 1;
	}

	//	Leitura dos valores da linha de comandos
	int tarefasNbr	=	_ttoi((_TCHAR*) argv[1]);
	int expNbr		=	_ttoi((_TCHAR*) argv[2]);
	_tprintf(TEXT("[NAC] :: [0] %i [1] %i\n"),tarefasNbr, expNbr);

	DOUBLE xx = 0;
	DOUBLE yy = 0;
	int in = 0;
	srand(time(NULL));
	for (DWORD i =0;i<expNbr;++i){
		xx = randVal(-0.50,0.50);
		yy = randVal(-0.50,0.50);
		if (isInsideCircle(xx,yy,0.5)){++in;}
	}
	_tprintf(TEXT("[NAC] :: [PI VALUE] %f [Nbr Exp] %i [Nbr Inside] %i\n"),piValue(in,expNbr), expNbr,in);
	Sleep(10000);
	return 1;

	//	Criação do espaço que vai albergar das estruturas
	_tprintf( TEXT("[main] Vou criar as tarefas.\n") );
	HANDLE* hThreads	= (HANDLE*)calloc(tarefasNbr,sizeof(HANDLE));
	DWORD*  idThreads	= (DWORD*)calloc(tarefasNbr,sizeof(DWORD));	
	ThreadArgs* args = (ThreadArgs*)calloc(tarefasNbr,sizeof(ThreadArgs));



    for (int idThread=0; idThread<tarefasNbr; ++idThread) {
        args[ idThread ].id = idThread;
        hThreads[ idThread ] = chBEGINTHREADEX( NULL, 0, ImprimeThreadArgsByStruct, (LPVOID)(&args[ idThread ]), NULL, idThreads[ idThread ] );
    }

	
    _tprintf( TEXT("[main] Esperar pela terminação das tarefas.\n") );

	WaitForMultipleObjects( tarefasNbr, hThreads, TRUE, INFINITE );

    _tprintf( TEXT("[main] [HANDLES abertos] Mostrar o código de terminação das tarefas.\n") );
    showThreadExitCode( hThreads, tarefasNbr );

    _tprintf( TEXT("[main] Fechar os HANDLES das tarefas.\n") );
	for (int idThread=0; idThread<tarefasNbr; ++idThread) {
        CloseHandle( hThreads[ idThread ] );
    }

	_tprintf( TEXT("[main] Função principal a terminar.\nPrima uma tecla para continuar.\n") );
    _gettch();

	free(args);
	free(hThreads);
	free(idThreads);
	return 0;
}
