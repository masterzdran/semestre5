#include "Include/stdafx.h"

#define MAX_RUN_OPT 1
#define MIN_RUN_OPT 1
#define MAX_VALID_PARAM 3
#define PROCESS_ID 1
#define THREAD_ID 0

void executeOnThreads(DWORD tarefasNbr, DWORD expNbr);
void executeOnProcess(DWORD tarefasNbr, DWORD expNbr){};

void usage(){
	_tprintf(TEXT("Usage:\n"));
	_tprintf(TEXT("CalculoPI <taskNbr> <expNbr> [<runType>]\n"));
	_tprintf(TEXT("taskNbr : Number of Thread/Process\n"));
	_tprintf(TEXT("expNbr : Number of experiences to be runned\n"));
	_tprintf(TEXT("runType : if it will run as [0] multi-thread or as [1] multi-process. By default: 0\n"));
}

DWORD _tmain(DWORD argc, _TCHAR* argv[])
{
	if (argc < MAX_VALID_PARAM || argc > MAX_VALID_PARAM+1){
		_tprintf(TEXT("Invalid parameters.\n"));
		usage();
		_tprintf(TEXT("Press any key to continue.\n"));
		_gettchar();
		return 1;
	}
	void (*functions[2])(DWORD,DWORD) = {executeOnThreads,executeOnProcess};
	
	DWORD tarefasNbr	=	_ttoi((_TCHAR*) argv[1]);
	DWORD expNbr		=	_ttoi((_TCHAR*) argv[2]);
	DWORD runType		=	0;
	if (argc == MAX_VALID_PARAM+1){
		DWORD tmp 	= 	_ttoi((_TCHAR*) argv[3]);
		if ( tmp <MIN_RUN_OPT || tmp > MAX_RUN_OPT){
			_tprintf(TEXT("Invalid parameters."));
			usage();
			return 1;			
		}
		runType = tmp;
	}
	functions[runType](tarefasNbr,expNbr);
}