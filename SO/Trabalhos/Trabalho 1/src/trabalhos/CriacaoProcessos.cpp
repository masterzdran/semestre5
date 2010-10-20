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
Neste módulo é calculado o valor do PI utilizando processos.
É basedo no exemplo 3 fornecido.
 */

#include "Include/stdafx.h"

const int DimCommandLine = 80;

/*
	Mostra a informação do processo. Foi separado para tornar o código mais legivel
*/
void showProcessInfo(PROCESS_INFORMATION pi){
	_tprintf( TEXT("\n=====================================================================================\n"));
	_tprintf( TEXT("O processo foi criado com sucesso.") );
    _tprintf( TEXT("Alguns dados relativos ao processo criado:\n") );
    _tprintf( TEXT("ID do processo: %d\n"), pi.dwProcessId );
    _tprintf( TEXT("ID da tarefa principal do processo: %d\n"), pi.dwThreadId );
    _tprintf( TEXT("HANDLE do processo: %p\n"), pi.hProcess );
    _tprintf( TEXT("HANDLE da tarefa principal do processo: %p\n"), pi.hThread );
	_tprintf( TEXT("\n=====================================================================================\n"));
}

/*
	Mostra a informação detalhada sobre os tempos do processo. Foi separado para tornar o código mais legivel
*/
void endReport(HANDLE* handleNewProcess,FILETIME* creationTime, FILETIME* exitTime,FILETIME* kernelTime,FILETIME* userTime){
		_tprintf( TEXT("\n=====================================================================================\n"));
          SYSTEMTIME syCreationTime;
          SYSTEMTIME syExitTime;
          SYSTEMTIME syKernelTime;
          SYSTEMTIME syUserTime;

          // Convert to local time - FileTimeToLocalFileTime uses the current settings 
          // for the time zone and daylight saving time
          FileTimeToLocalFileTime( creationTime, creationTime);
          FileTimeToLocalFileTime( exitTime, exitTime);

          FileTimeToSystemTime( creationTime, &syCreationTime);
          FileTimeToSystemTime( exitTime, &syExitTime);
          FileTimeToSystemTime( kernelTime, &syKernelTime);
          FileTimeToSystemTime( userTime, &syUserTime);

          _tprintf( TEXT("Tempos associados ao processo criado (HH:MM:SS,sss) %d\n"),handleNewProcess );

          _tprintf( TEXT("Tempo de criação ------- %02d:%02d:%02d,%03d\n"), 
            syCreationTime.wHour, syCreationTime.wMinute, syCreationTime.wSecond, syCreationTime.wMilliseconds );
          _tprintf( TEXT("Tempo de terminação ---- %02d:%02d:%02d,%03d\n"), 
            syExitTime.wHour, syExitTime.wMinute, syExitTime.wSecond, syExitTime.wMilliseconds );
          _tprintf( TEXT("Tempo em modo kernel --- %02d:%02d:%02d,%03d\n"), 
            syKernelTime.wHour, syKernelTime.wMinute, syKernelTime.wSecond, syKernelTime.wMilliseconds );
          _tprintf( TEXT("Tempo em modo user ----- %02d:%02d:%02d,%03d\n"), 
            syUserTime.wHour, syUserTime.wMinute, syUserTime.wSecond, syUserTime.wMilliseconds );
		  _tprintf( TEXT("\n=====================================================================================\n"));
}


/*
 Funções que vão processar em diversas tarefas.
*/
void executeOnProcess(DWORD tarefasNbr, DWORD expNbr, _TCHAR* prog){
	HANDLE* handleNewProcess = (HANDLE*)calloc(tarefasNbr,sizeof(HANDLE));
	HANDLE* handleNewThread =(HANDLE*)calloc(tarefasNbr,sizeof(HANDLE));
	/*
	 * Create each new process
	 */
	DWORD flags = 0;
	//flags = CREATE_SUSPENDED;
	//flags = CREATE_SUSPENDED | CREATE_NEW_CONSOLE
	//flags = CREATE_SUSPENDED | ABOVE_NORMAL_PRIORITY_CLASS;

	for (DWORD i = 0;i<tarefasNbr; ++i){
		flags = 0;
		STARTUPINFO si;
		ZeroMemory( &si, sizeof(STARTUPINFO) );
		si.cb = sizeof(STARTUPINFO);
		si.lpTitle = TEXT( "Process" );	
		//Reconstroi a chamada do comando para usar o mesmo comando utilizado e chamar o modulo das tarefas
		TCHAR* newlinecomand = (TCHAR*)calloc(DimCommandLine,sizeof(TCHAR));
		_stprintf(newlinecomand,TEXT("%s %i %i"),prog,1,expNbr);

	    PROCESS_INFORMATION pi;

		if ( CreateProcess( NULL, newlinecomand, NULL, NULL, FALSE, flags, NULL, NULL, &si, &pi)==0 ) {
			FatalErrorSystem( TEXT("Erro ao criar o comando \"%s\""), newlinecomand);
		}
		handleNewProcess[i]=pi.hProcess;
		handleNewThread[i]=pi.hThread;

		showProcessInfo(pi);
		free(newlinecomand);
	}
	/*
	 * Start each new process
	 */
	for (DWORD i = 0;i<tarefasNbr; ++i){
		if ( (flags & CREATE_SUSPENDED)!=0 ) {
			_tprintf( TEXT("\nPrima uma tecla para activar a tarefa principal do processo criado.\n") );
			_gettch();
			ResumeThread( handleNewThread[i] );
		}
	}

	_tprintf( TEXT("\nEsperar pela sua terminação.\n") );
    DWORD timeOut;
    timeOut = INFINITE;
    //timeOut = 5000;
	/*
	 * End each new process
	 */
	for (DWORD i = 0;i<tarefasNbr; ++i){
		if (WaitForSingleObject( handleNewProcess[i], timeOut )==WAIT_TIMEOUT) {
			ReportErrorUser( TEXT("O processo ainda não terminou") );
		}
		else {
			_tprintf( TEXT("O processo já terminou.\n") );
			FILETIME creationTime;
			FILETIME exitTime;
			FILETIME kernelTime;
			FILETIME userTime;

			if ( GetProcessTimes( handleNewProcess[i], &creationTime, &exitTime, &kernelTime, &userTime)==0 ) {
				ReportErrorSystem( TEXT("Erro ao obter os tempos de excução do processo %i"),handleNewProcess[i] );
				return;
			}
			else {
				endReport(&handleNewProcess[i],&creationTime, &exitTime,&kernelTime,&userTime);
			}
		}
	}



	for (DWORD i = 0;i<tarefasNbr; ++i){
		CloseHandle( handleNewProcess[i] );
		CloseHandle( handleNewThread[i] );
	}
    _tprintf( TEXT("Prima uma tecla para terminar.") );
    _gettch();

	free(handleNewThread);
	free(handleNewProcess);
}
