/**
 *
 * IPL - Instituto Politecnico de Lisboa
 *
 * ISEL- Instituto Superior de Engenharia de Lisboa
 *
 * DEEC - Departamento de Engenharia Electronica e Comunicacoes
 *
 * ASO - Secção de Arquitectura e Sistemas Operativos
 *
 *
 * Modulo de Tratamento de Erros.
 *
 * Este modulo visa fornecer um conjunto de primitivas para auxiliar o tratamento de
 * erros no desenvolvimento nas aplicações
 *
 * As funções estão concebidas para a apresentação de erros no sistema Windows e podem ser 
 * utilizadas em aplicações que utilizem caracteres codificados em ASCII ou UNICODE. 
 * Para as fuções utilizarem os caracteres codificados em UNICODE devem estar definidos os 
 * simbolos de compilação _UNICODE e UNICODE
 *
 * As funções estão construídas utilizando funções seguras para manipulação de Strings 
 * definidas no ficheiro de definições StrSafe.h
 *
 * Estão disponiveis 4 primitivas:
 *
 * Erro de sistema não fatal - ReportErrorSystem(const char *fmtStr, ...);
 *
 * Erro de sistema fatal - FatalErrorSystem(const char *fmtStr, ...);
 *
 * Erro aplicacional não fatal - <code>ReportErrorUser(const char *fmtStr, ...);</code>;
 *
 * Erro aplicacional fatal - <code>FatalErrorUser(const char *fmtStr, ...);
 *
 *
 * @version 4.0
 *
 * @autor Nuno Oliveira
 * @autor Carlos Gonçalves
 * @autor Luis Assunção
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
