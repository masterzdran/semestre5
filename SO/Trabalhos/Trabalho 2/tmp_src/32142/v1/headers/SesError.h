/**
 *
 * IPL - Instituto Politecnico de Lisboa
 *
 * ISEL- Instituto Superior de Engenharia de Lisboa
 *
 * DEEC - Departamento de Engenharia Electronica e Comunicacoes
 *
 * ASO - Sec��o de Arquitectura e Sistemas Operativos
 *
 *
 * Modulo de Tratamento de Erros.
 *
 * Este modulo visa fornecer um conjunto de primitivas para auxiliar o tratamento de
 * erros no desenvolvimento nas aplica��es
 *
 * As fun��es est�o concebidas para a apresenta��o de erros no sistema Windows e podem ser 
 * utilizadas em aplica��es que utilizem caracteres codificados em ASCII ou UNICODE. 
 * Para as fu��es utilizarem os caracteres codificados em UNICODE devem estar definidos os 
 * simbolos de compila��o _UNICODE e UNICODE
 *
 * As fun��es est�o constru�das utilizando fun��es seguras para manipula��o de Strings 
 * definidas no ficheiro de defini��es StrSafe.h
 *
 * Est�o disponiveis 4 primitivas:
 *
 * Erro de sistema n�o fatal - ReportErrorSystem(const char *fmtStr, ...);
 *
 * Erro de sistema fatal - FatalErrorSystem(const char *fmtStr, ...);
 *
 * Erro aplicacional n�o fatal - <code>ReportErrorUser(const char *fmtStr, ...);</code>;
 *
 * Erro aplicacional fatal - <code>FatalErrorUser(const char *fmtStr, ...);
 *
 *
 * @version 4.0
 *
 * @autor Nuno Oliveira
 * @autor Carlos Gon�alves
 * @autor Luis Assun��o
 */

#ifndef _SES_ERROR_H
#define _SES_ERROR_H

#include <windows.h>
#include <tchar.h>
#include <conio.h>
#include <StrSafe.h>


#ifdef __cplusplus
extern "C" {
#endif


void ReportErrorSystem( const TCHAR *fmtStr, ... );

void FatalErrorSystem( const TCHAR *fmtStr, ... );

void ReportErrorUser( const TCHAR *fmtStr, ... );

void FatalErrorUser( const TCHAR *fmtStr, ... );


#ifdef __cplusplus
} //extern "C" {
#endif


#endif	// _SES_ERROR_H
