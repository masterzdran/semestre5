// CriacaoProcessos.cpp : Defines the entry point for the console application.
//

#include "Include/stdafx.h"

const int DimCommandLine = 80;


int X_tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale( LC_ALL, TEXT("portuguese_portugal") );


    // Pedir ao utilizador o programa a executar
    TCHAR commandLine[ DimCommandLine ];
    _tprintf( TEXT("Escreve o nome de um programa a executar: ") );
    _fgetts( commandLine, DimCommandLine, stdin);
    commandLine[ _tcslen(commandLine)-1 ] = 0;
    _tprintf( TEXT("Li o comando: \"%s\"\n"), commandLine );



    STARTUPINFO si;
    ZeroMemory( &si, sizeof(STARTUPINFO) );
    si.cb = sizeof(STARTUPINFO);
    si.lpTitle = TEXT( "xpto" );

    DWORD flags = 0;
    //flags = CREATE_SUSPENDED;
    //flags = CREATE_SUSPENDED | CREATE_NEW_CONSOLE
    //flags = CREATE_SUSPENDED | ABOVE_NORMAL_PRIORITY_CLASS;

    PROCESS_INFORMATION pi;

    if ( CreateProcess( NULL, commandLine, NULL, NULL, FALSE, flags, NULL, NULL, &si, &pi)==0 ) {
        FatalErrorSystem( TEXT("Erro ao criar o comando \"%s\""), commandLine);
    }

    _tprintf( TEXT("O processo foi criado com sucesso.") );
    _tprintf( TEXT("Alguns dados relativos ao processo criado:\n") );
    _tprintf( TEXT("ID do processo: %d\n"), pi.dwProcessId );
    _tprintf( TEXT("ID da tarefa principal do processo: %d\n"), pi.dwThreadId );
    _tprintf( TEXT("HANDLE do processo: %p\n"), pi.hProcess );
    _tprintf( TEXT("HANDLE da tarefa principal do processo: %p\n"), pi.hThread );

    HANDLE handleNewProcess = pi.hProcess;
    HANDLE handleNewThread  = pi.hThread;

    if ( (flags & CREATE_SUSPENDED)!=0 ) {
        _tprintf( TEXT("\nPrima uma tecla para activar a tarefa principal do processo criado.\n") );
        _gettch();
        ResumeThread( handleNewThread );
    }

    _tprintf( TEXT("\nEsperar pela sua terminação.\n") );

    DWORD timeOut;
    timeOut = INFINITE;
    //timeOut = 5000;

    if (WaitForSingleObject( handleNewProcess, timeOut )==WAIT_TIMEOUT) {
        ReportErrorUser( TEXT("O processo ainda não terminou") );
    }
    else {
        _tprintf( TEXT("O processo já terminou.\n") );
        FILETIME creationTime;
        FILETIME exitTime;
        FILETIME kernelTime;
        FILETIME userTime;

        if ( GetProcessTimes( handleNewProcess, &creationTime, &exitTime, &kernelTime, &userTime)==0 ) {
            ReportErrorSystem( TEXT("Erro ao obter os tempos de excução do processo") );
        }
        else {
          SYSTEMTIME syCreationTime;
          SYSTEMTIME syExitTime;
          SYSTEMTIME syKernelTime;
          SYSTEMTIME syUserTime;

          // Convert to local time - FileTimeToLocalFileTime uses the current settings 
          // for the time zone and daylight saving time
          FileTimeToLocalFileTime( &creationTime, &creationTime);
          FileTimeToLocalFileTime( &exitTime, &exitTime);

          FileTimeToSystemTime( &creationTime, &syCreationTime);
          FileTimeToSystemTime( &exitTime, &syExitTime);
          FileTimeToSystemTime( &kernelTime, &syKernelTime);
          FileTimeToSystemTime( &userTime, &syUserTime);

          _tprintf( TEXT("Tempos associados ao processo criado (HH:MM:SS,sss)\n") );

          _tprintf( TEXT("Tempo de criação ------- %02d:%02d:%02d,%03d\n"), 
            syCreationTime.wHour, syCreationTime.wMinute, syCreationTime.wSecond, syCreationTime.wMilliseconds );
          _tprintf( TEXT("Tempo de terminação ---- %02d:%02d:%02d,%03d\n"), 
            syExitTime.wHour, syExitTime.wMinute, syExitTime.wSecond, syExitTime.wMilliseconds );
          _tprintf( TEXT("Tempo em modo kernel --- %02d:%02d:%02d,%03d\n"), 
            syKernelTime.wHour, syKernelTime.wMinute, syKernelTime.wSecond, syKernelTime.wMilliseconds );
          _tprintf( TEXT("Tempo em modo user ----- %02d:%02d:%02d,%03d\n"), 
            syUserTime.wHour, syUserTime.wMinute, syUserTime.wSecond, syUserTime.wMilliseconds );
        }
    }

    CloseHandle( handleNewProcess );
    CloseHandle( handleNewThread );

    _tprintf( TEXT("Prima uma tecla para terminar.") );
    _gettch();

    return 0;
}
