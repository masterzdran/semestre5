/**
* Implementa��o do m�dulo de tratamento de erros
*/

#include "SesError.h"
#include "stdafx.h"



const int MAX_CH_ERROR_TITLE   =  64;  // Dimens�o max. do titulo em caracters
//const int ERROR_TITLE		=   64;
const int MAX_CH_ERROR_MESSAGE = 256;    // Dimens�o max. da mensagem de erro em caracters


//----------------------------------------------------------------------------
// Fun��o privada auxiliar que bloqueia o programa at� o utilizador
// primir uma tecla.
// Em ambiente Unix deve premir ENTER
//
void terminar()
{
    fputs("\nPrima uma tecla para terminar ", stderr);
    _getch();
}	// terminar


//----------------------------------------------------------------------------
// Fun��o privada que sabe mostrar um erro
//
void DisplayError(int errorn, const TCHAR * fmtStr, va_list args) {
    LPVOID errorBuf;
    TCHAR msgBuffer[MAX_CH_ERROR_MESSAGE];
    TCHAR title[MAX_CH_ERROR_TITLE] = TEXT("");
    TCHAR * progName;


    if ( GetConsoleTitle(title, MAX_CH_ERROR_TITLE) ) {
        progName = _tcsrchr(title, '\\');

        if ( progName != NULL ) {

            if ( progName[ _tcslen(progName)-1 ] == '"')
                progName[ _tcslen(progName)-1 ] = '\0';

            //_stprintf(title, TEXT("Error on %s"), ++progName);
            StringCchPrintf(title, MAX_CH_ERROR_TITLE, TEXT("Error on %s"), ++progName);
        }
    }

    DWORD res = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorn,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Linguagem por omiss�o do sistema
        (LPTSTR) &errorBuf,
        0,
        NULL );

    //_vstprintf( msgBuffer, fmtStr, args );
    StringCchVPrintf(msgBuffer, MAX_CH_ERROR_MESSAGE, fmtStr, args );

    //_stprintf( msgBuffer + _tcsclen(msgBuffer), TEXT(": (%d) %s"), errorn, (res ? errorBuf : "") );
    size_t dimMsg = _tcsclen(msgBuffer);
    StringCchPrintf(msgBuffer + dimMsg, MAX_CH_ERROR_MESSAGE - dimMsg,
                    TEXT(": (%d) %s"), errorn, (res ? errorBuf : TEXT("")) );

    MessageBox( NULL, (LPCTSTR)msgBuffer, title, MB_OK | MB_ICONERROR  | MB_SETFOREGROUND);

    // Libertar mem�ria referenciada por lpMsgBuf alocada pela fun��o FormatMessage
    LocalFree( errorBuf );
} // DisplayError


//----------------------------------------------------------------------------
// Fun��o privada que sabe mostrar um erro da aplica��o
//
void DisplayErrorApp(const TCHAR * fmtStr, va_list args) {
    TCHAR msgBuffer[MAX_CH_ERROR_MESSAGE];
    TCHAR title[MAX_CH_ERROR_TITLE] = TEXT("");
    TCHAR * progName;

    if ( GetConsoleTitle(title, MAX_CH_ERROR_TITLE) ) {
        progName = _tcsrchr(title, '\\');

        if ( progName!=NULL ) {
            if ( progName[ _tcsclen(progName)-1 ]=='"' )
                progName[ _tcsclen(progName)-1 ] = '\0';

            //_stprintf(title, TEXT("Error on %s"), ++progName);
            StringCchPrintf(title, MAX_CH_ERROR_TITLE, TEXT("Error on %s"), ++progName);
        }
    }

    //_vstprintf( msgBuffer, fmtStr, args );
    StringCchVPrintf(msgBuffer, MAX_CH_ERROR_MESSAGE, fmtStr, args );

    MessageBox( NULL, (LPCTSTR)msgBuffer, title, MB_OK | MB_ICONERROR  | MB_SETFOREGROUND);

} // DisplayErrorApp


//----------------------------------------------------------------------------
// Erro de sistema
//
void ReportErrorSystem( const TCHAR *fmtStr, ... ) {
    va_list args;

    int error = GetLastError();

    va_start( args, fmtStr );

    DisplayError( error, fmtStr, args );

    va_end( args );
} // ReportErrorSystem


//----------------------------------------------------------------------------
// Erro de sistema com termina��o do programa
//
void FatalErrorSystem( const TCHAR *fmtStr, ... ) {
    va_list args;

    int error = GetLastError();

    va_start( args, fmtStr );

    DisplayError( error, fmtStr, args );

    va_end( args );

    terminar();

    exit( 1 );
} // ErrorSystem



//----------------------------------------------------------------------------
// Erro da aplica��o
//
void ReportErrorUser( const TCHAR *fmtStr, ... ) {
    va_list args;

    va_start( args, fmtStr );

    DisplayErrorApp(fmtStr, args );

    va_end( args );
} // ReportErrorSystem


//----------------------------------------------------------------------------
// Erro da aplica��o com termina��o do programa
//
void FatalErrorUser( const TCHAR *fmtStr, ... ) {
    va_list args;

    va_start( args, fmtStr );

    DisplayErrorApp(fmtStr, args );

    va_end( args );

    terminar();

    exit( 1 );
} // FatalErrorSystem
