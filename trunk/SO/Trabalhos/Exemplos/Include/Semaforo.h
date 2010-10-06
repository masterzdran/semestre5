/**
 *
 * IPL - Instituto Politecnico de Lisboa
 *
 * ISEL- Instituto Superior de Engenharia de Lisboa
 *
 * DEEC - Departamento de Engenharia Electronica e Comunicacoes
 *
 * SES - Secção de Engenharia de Sistemas
 *
 * Classe Semaforo
 *
 * Implementação de um semáforo numa classe.
 *
 * Implementação usando a API Win32. Implementação C++.
 *
 * @version 3.0
 *
 * @autor Carlos Gonçalves
 * @autor Nuno Oliveira
 * @autor Luis Assunção
 */

#ifndef _SEMAFORO_H_
#define _SEMAFORO_H_

// necessário para utilização do system call SignalObjectAndWait utilizado na classe Semaforo
#define _WIN32_WINNT 0x0400
#include <windows.h>

#include "SESError.h"


class Semaforo {
private:
	HANDLE hSemaforo;

public:
	Semaforo(int numUnidades=1, int maxUnidades=MAXLONG, TCHAR * nomeSem=NULL) {
		if ( (hSemaforo = CreateSemaphore(NULL, numUnidades, maxUnidades, nomeSem)) == NULL )
		    FatalErrorSystem( TEXT("Erro ao criar o semaforo(1)") );
	}

    Semaforo(TCHAR * nomeSem) {
		if ( (hSemaforo = OpenSemaphore(SEMAPHORE_ALL_ACCESS, NULL, nomeSem)) == NULL )
			FatalErrorSystem( TEXT("Erro ao criar o semaforo(3)") );
	}

    ~Semaforo() {
        if (CloseHandle(hSemaforo)==0)
	    	FatalErrorSystem( TEXT("Erro ao fechar o semaforo") );
    }

	void P() {
		if ( WaitForSingleObject(hSemaforo, INFINITE) == WAIT_FAILED )
			FatalErrorSystem( TEXT("Erro na operação de Wait do semáforo") );
	}

	void V() {
		if ( ReleaseSemaphore(hSemaforo, 1, NULL) == 0 )
			FatalErrorSystem( TEXT("Erro na operação de Signal do semáforo") );
	}

	void Wait() { P(); }

	void Signal() {	V(); }

	void SignalAndWait(Semaforo *sWait){
		SignalObjectAndWait(hSemaforo, sWait->hSemaforo, INFINITE, FALSE);
	}

};

#endif	// _SEMAFORO_H_