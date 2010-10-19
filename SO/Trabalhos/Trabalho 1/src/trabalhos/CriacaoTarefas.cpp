/*
#=======================================================================
# SO		Sistemas Operativos
#-----------------------------------------------------------------------
# Numero	Nome
# 31401		Nuno Cancelo
# 31529		João Sousa
# 32142		Cláudia Crisóstomo
# 33595		Nuno Sousa
# Turma:	LI41N
#-----------------------------------------------------------------------
# Semestre:	Inverno 2010/2011
# Data:		Outubro/2010
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
Neste módulo é calculado o valor do PI utilizando tarefas.
É basedo no exemplo 4 fornecido.
 */
 
#include "Include/stdafx.h"
#include <time.h>
#include <MMSystem.h>

typedef struct _ThreadArgs {
  DWORD id;
  DWORD nbrExp;
  DWORD totalExp;
} ThreadArgs, * PThreadArgs;


/*
	Função que devolve um valor aleatório dentro do limite de um quadrado.
*/
static DOUBLE randVal(DOUBLE min, DOUBLE max){
	return (DOUBLE)rand()/(RAND_MAX + 1)*(max - min) + min;
}
/*
	Verifica se o ponto está dentro do circulo circunscrito no quadrado.
*/
static BOOL isInsideCircle(DOUBLE xx, DOUBLE yy, DOUBLE radius ){
	return ((xx*xx) + (yy*yy))<= radius*radius;
}

/*
	Devolve o valor achado.
*/
static DOUBLE piValue(DOUBLE insidePoints, DOUBLE totalExperiences){
	return (insidePoints/totalExperiences)*4;
}
/*
	Função que vai gerando os pontos e incrementando numero de pontos dentro do cirulo
*/
static DWORD WINAPI ThreadsCode(LPVOID args)
{
	PThreadArgs experiencias = (PThreadArgs)(args);
	DWORD n_expr = 0;
	
	DOUBLE xx = 0;
	DOUBLE yy = 0;
	//cria uma nova seed, para se poder gerar aleatóriamente os valores
	srand(experiencias->id+GetCurrentThreadId());
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
	return n_expr;
}

/*
 Função copiada do exemplo 5 de Sistemas Operativos
 Para imprimir os tempos de execução de cada tarefas
*/
static void showTimes(HANDLE hThread)
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
		_tprintf(TEXT("tarefa %h:\n"),hThread);
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

/*
	Verifica o estado das tarefas guardando o valor das experiencias para calcular o valor de PI
	Mostra os tempos de execução da tarefa
*/
static void IshowThreadExitCode(HANDLE * hThreads, DWORD NumThreads,DWORD* total)
{
  DWORD exitCode;

  for(DWORD idThread=0; idThread<NumThreads; ++idThread) {

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

/*
 Entry point do modulo.
 lança o numero de tarefas passadas por argumento e executa o numero de experiencias passado por argumento em cada tarefa
*/
void executeOnThreads(DWORD tarefasNbr, DWORD expNbr,_TCHAR* prog)
{
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


	WaitForMultipleObjects( tarefasNbr, hThreads, TRUE, INFINITE );
	
    IshowThreadExitCode( hThreads, tarefasNbr,(DWORD*)&totalExpInside );

	for (DWORD idThread=0; idThread<tarefasNbr; ++idThread) {
        CloseHandle( hThreads[ idThread ] );
    }

	_tprintf(TEXT("[PI VALUE] %f [Nbr Exp] %i [Nbr Inside] %i\n"),piValue(totalExpInside,totalExp), totalExp,totalExpInside);
	_tprintf( TEXT("[main] Função principal a terminar.\nPrima uma tecla para continuar.\n") );
    _gettch();

	free(args);
	free(hThreads);
	free(idThreads);

}