#include "headers\stdafx.h"
#include "headers\IGestorDePistas.h"
#include <list>
#include "Plane.cpp"

#ifndef GESTORDEPISTAS
#define GESTORDEPISTAS

const int NUMBER_OF_SKIING = 2;
const int SKIING_1 = 0;
const int SKIING_2 = 1;

class GestorDePistas : IGestorDePistas {

private:

	//Mutex associado as threads que pretendem descolar
	Semaforo* _Mutex;
	//Mutex associado as threads que pretendem libertar a pista
	//_closePistas[0] - pista 1, _closePistas[1] - pista 2
	bool* _closePistas;
	DWORD* thread_pista;
	//quando a true existe alerta de furacao
	bool _furacao;
		
	std::list<Plane*> landList;
	std::list<Plane*> takeoffList;

	/*
		std::list<HANDLE*> landList;
		landList.push_back((HANDLE*)GetCurrentThreadId());
		HANDLE* h = landList.front();
		landList.pop_front();
	*/

public:
	GestorDePistas(){
		_Mutex = new Semaforo[NUMBER_OF_SKIING];
		_closePistas = new bool[NUMBER_OF_SKIING];
		_closePistas[0]=false;
		_closePistas[1]=false;
		_furacao = false;
		thread_pista = new DWORD[2];
		thread_pista[0] = -1;
		thread_pista[1] = -1;
	}
	
	~GestorDePistas(){
		delete _Mutex;
		delete _closePistas;
		delete thread_pista;
	}


	int esperarPistaParaAterrar(Plane* a){
		DWORD id = a->GetIDThread();
		//entra no while caso nao haja pista livre
		while( (!_closePistas[0] && !_closePistas[1]) || thread_pista[0]!=id && thread_pista[1]!=id && landList.size()>0){
			_Mutex->Wait();
			landList.push_back(a);
			_Mutex->Signal();
			a->EsperarPista();
		}
		//ja tem pista reservada!
		int p = 0;
		_Mutex->Wait();
		if(thread_pista[0]==id) p=0;
		else if(thread_pista[1]==id) p = 1;
		_Mutex->Signal();
		return p;
	}

	int esperarPistaParaDescolar(Plane* d){
		DWORD id = d->GetIDThread();
		//entra no while caso nao haja pista livre
		while( _furacao || (!_closePistas[0] && !_closePistas[1]) || thread_pista[0]!=id && thread_pista[1]!=id && takeoffList.size()>0){
			_Mutex->Wait();
			takeoffList.push_back(d);
			_Mutex->Signal();
			d->EsperarPista();
		}
		//ja tem pista reservada!
		int p = 0;
		_Mutex->Wait();
		if(thread_pista[0]==id) p=0;
		else if(thread_pista[1]==id) p = 1;
		_Mutex->Signal();
		return p;
	}

	void libertarPista(int idPista){
		_Mutex->Wait();
		if(idPista==0){
			if(landList.size()==0)thread_pista[idPista]=-1;
			else{
				//reserva pista para o proximo aviao
				Plane* next = landList.front();
				landList.pop_front();
				thread_pista[idPista]=next->GetIDThread();
				next->TerPista();
			}
		}
		else{//idPista==1
			if(takeoffList.size()==0)thread_pista[idPista]=-1;
			else{
				//reserva pista para o proximo aviao
				Plane* next = takeoffList.front();
				takeoffList.pop_front();
				thread_pista[idPista]=next->GetIDThread();
				next->TerPista();
			}
		}
		_Mutex->Signal();
	}

	void fecharPista(int idPista){
		_closePistas[idPista] = true;
	}

	void abrirPista(int idPista){
		_closePistas[idPista] = false;
	}

	void alertaFuracao(bool al){
		_furacao = true;
	}

private:
	bool isAirportClosed(){
		return _closePistas[0] == true && _closePistas[1] == true;
	}

	void RegisterLanding(Semaforo* s){

	}
	void RegisterTakeOff(Semaforo* s){

	}


};
#endif GESTORDEPISTAS
