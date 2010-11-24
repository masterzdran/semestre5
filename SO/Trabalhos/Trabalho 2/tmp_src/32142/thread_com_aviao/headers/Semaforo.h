/**
 *
 * IPL - Instituto Politecnico de Lisboa
 *
 * ISEL- Instituto Superior de Engenharia de Lisboa
 *
 * DEEC - Departamento de Engenharia Electronica e Comunicacoes
 *
 * SES - Sec��o de Engenharia de Sistemas
 *
 * Classe Semaforo
 *
 * Implementa��o de um sem�foro numa classe.
 *
 * Implementa��o usando a API Win32. Implementa��o C++.
 *
 * @version 3.0
 *
 * @autor Carlos Gon�alves
 * @autor Nuno Oliveira
 * @autor Luis Assun��o
 */

#ifndef _SEMAFORO_H_
#define _SEMAFORO_H_

// necess�rio para utiliza��o do system call SignalObjectAndWait utilizado na classe Semaforo
#define _WIN32_WINNT 0x0400
#include <windows.h>
#include "ListThreads.h"
#include "headers\SESError.h"


class Semaforo {
private:
	HANDLE hSemaforo;
	ListThreads* _head;
	ListThreads* _tail;
public:
	Semaforo(int numUnidades=1, int maxUnidades=MAXLONG, TCHAR * nomeSem=NULL) {
		if ( (hSemaforo = CreateSemaphore(NULL, numUnidades, maxUnidades, nomeSem)) == NULL )
		    FatalErrorSystem( TEXT("Erro ao criar o semaforo(1)") );
		_head = _tail = NULL;
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
			FatalErrorSystem( TEXT("Erro na opera��o de Wait do sem�foro") );
	}

	void V() {
		if ( ReleaseSemaphore(hSemaforo, 1, NULL) == 0 )
			FatalErrorSystem( TEXT("Erro na opera��o de Signal do sem�foro") );
	}

	//obrigatorio antes da invoca�ao deste metodo fazer Wait a qualquer semaforo!!!
	void Wait() {
		P();
		ListThreads* ret = GetHeadSemaforo();
		if(ret!=NULL){
			Semaforo* s = ret->_s;
			s->Signal();
		}
	}
	void Wait(Semaforo* f) {
		AddTailSemaforo(f);
		//P(); 
	}

	void Signal() {
		V();
	}

	void SignalAndWait(Semaforo *sWait){
		SignalObjectAndWait(hSemaforo, sWait->hSemaforo, INFINITE, FALSE);
	}

private:
	void AddTailSemaforo(Semaforo* s){
		if(_head==NULL){
			_head = _tail = new ListThreads(s);
		}
		else{
			ListThreads* l = new ListThreads(s);
			_tail->_next = l;
			_tail = l;
		}
	}
	ListThreads* GetHeadSemaforo(){
		if(_head==NULL)return NULL;
		ListThreads* ret = _head;
		_head = _head->_next;
		return ret;
	}
};

#endif	// _SEMAFORO_H_