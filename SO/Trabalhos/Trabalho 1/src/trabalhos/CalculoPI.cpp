/*
#=======================================================================
# SO		Sistemas Operativos
#-----------------------------------------------------------------------
# Numero	Nome
# 31401		Nuno Cancelo
# 31529		Jo�o Sousa
# 32142		Cl�udia Cris�stomo
# 33595		Nuno Sousa
# Turma:	LI41N
#-----------------------------------------------------------------------
# Semestre:	Inverno 2010/2011
# Data:		Outubro/2010
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Inform�tica e Computadores
# DEETC - Dep. de Eng. Electr�nica e Telecomunica��es e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
 Programa de C�lculo do valor PI executando tarefas ou processos.
 O valor inicial do segundo parametro indica quantas experiencias v�o ser
 realizadas por cada tarefa/processo. 
 */
 
#include "Include/stdafx.h"

/*
 Defini��o de algumas constantes, utilizadas neste ficheiro
*/

#define MAX_RUN_OPT 1			// defini��o do valor m�ximo do parametro facultativo
#define MIN_RUN_OPT 0			// defini��o do valor minimo do parametro facultativo
#define MAX_VALID_PARAM 3		// numero m�ximo de parametros

/*
	indica��o que existem fun��es definidas noutros modulos que v�o ser executadas aqui
*/
void executeOnThreads(DWORD tarefasNbr, DWORD expNbr,_TCHAR* prog);
void executeOnProcess(DWORD tarefasNbr, DWORD expNbr,_TCHAR* prog);

/*
	Descri��o do modo de execu��o deste entry point
*/
void usage(){
	_tprintf(TEXT("Usage:\n"));
	_tprintf(TEXT("CalculoPI <taskNbr> <expNbr> [<runType>]\n"));
	_tprintf(TEXT("taskNbr : Number of Thread/Process\n"));
	_tprintf(TEXT("expNbr : Number of experiences to be runned\n"));
	_tprintf(TEXT("runType : if it will run as [0] multi-thread or as [1] multi-process. By default: 0\n"));
}

/*
	Ponto de entrada no programa
*/
DWORD _tmain(DWORD argc, _TCHAR* argv[])
{
	//Valida��o de Parametros
	if (argc < MAX_VALID_PARAM || argc > MAX_VALID_PARAM+1){
		_tprintf(TEXT("Invalid parameters.\n"));
		usage();
		_tprintf(TEXT("Press any key to continue.\n"));
		_gettchar();
		return 1;
	}
	//array de ponteiros para fun��o, que simplifica o modo como � indexado a sua chamada
	void (*functions[2])(DWORD,DWORD,_TCHAR*) = {executeOnThreads,executeOnProcess};
	
	DWORD tarefasNbr	=	_ttoi((_TCHAR*) argv[1]);
	DWORD expNbr		=	_ttoi((_TCHAR*) argv[2]);
	DWORD runType		=	0;
	//Verifica se existe o terceiro parametro e valida o valor encontrado
	if (argc == MAX_VALID_PARAM+1){
		DWORD tmp 	= 	_ttoi((_TCHAR*) argv[3]);
		if ( tmp <MIN_RUN_OPT || tmp > MAX_RUN_OPT){
			_tprintf(TEXT("Invalid parameters."));
			usage();
			return 1;			
		}
		runType = tmp;
	}
	//chama a fun��o correcta
	functions[runType](tarefasNbr,expNbr,argv[0]);
}