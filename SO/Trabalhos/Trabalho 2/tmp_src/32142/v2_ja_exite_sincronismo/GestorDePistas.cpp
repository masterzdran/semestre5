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
	//Semaforo* _Mutex;
	HANDLE _Mutex;
	//Mutex associado as threads que pretendem libertar a pista
	//_closePistas[0] - pista 1, _closePistas[1] - pista 2
	bool* _closePistas;
	DWORD* thread_pista;
	//quando a true existe alerta de furacao
	bool _furacao;
		
	std::list<Plane*> landList;
	std::list<Plane*> takeoffList;

public:
	GestorDePistas(){
		//_Mutex = new Semaforo[NUMBER_OF_SKIING];
		_Mutex = CreateMutex(NULL, false, NULL);
		_closePistas = new bool[NUMBER_OF_SKIING];
		_closePistas[0]=false;
		_closePistas[1]=false;
		_furacao = false;
		thread_pista = new DWORD[NUMBER_OF_SKIING];
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
		while( (_closePistas[0] && _closePistas[1]) ||
				(thread_pista[0]!=id && thread_pista[0]!=-1  && thread_pista[1]!=id
				&& thread_pista[1]!=-1 && landList.size()>=0)){
			WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
			landList.push_back(a);
			ReleaseMutex(_Mutex);//_Mutex->Signal();
			a->EsperarPista();
		}
		//ja tem pista reservada!
		int p = 0;
		WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
		if(thread_pista[0]==id || thread_pista[0]==-1) p=0;
		else if(thread_pista[1]==id || thread_pista[1]==-1) p = 1;
		//caso pista estivesse vaga, sem reserva
		if(thread_pista[p]==-1)thread_pista[p]=a->GetIDThread();
		ReleaseMutex(_Mutex);//_Mutex->Signal();
		return p;
	}

	int esperarPistaParaDescolar(Plane* d){
		DWORD id = d->GetIDThread();
		//entra no while caso nao haja pista livre
		while( _furacao || (_closePistas[0] && _closePistas[1]) ||
				thread_pista[0]!=id && thread_pista[0]!=-1 && thread_pista[1]!=id
				&& thread_pista[1]!=-1  && takeoffList.size()>=0){
			WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
			takeoffList.push_back(d);
			ReleaseMutex(_Mutex);//_Mutex->Signal();
			d->EsperarPista();
		}
		//ja tem pista reservada!
		int p = 0;
		WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
		if(thread_pista[0]==id || thread_pista[0]==-1) p=0;
		else if(thread_pista[1]==id || thread_pista[1]==-1) p = 1;
		//caso pista estivesse vaga, sem reserva
		if(thread_pista[p]==-1)thread_pista[p]=d->GetIDThread();
		ReleaseMutex(_Mutex);//_Mutex->Signal();
		return p;
	}

	void libertarPista(int idPista){
		WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
		if(idPista==0){
			if(landList.size()==0){
				thread_pista[idPista]=-1;
				//se esta vaga entao posso ver se existe algum aviao para descolar
				if(takeoffList.size()>0){
					ActiveTakeoffPlane(idPista);
				}
			}
			else ActiveLandingPlane(idPista);
		}
		else{//idPista==1
			if(takeoffList.size()==0){
				thread_pista[idPista]=-1;
				//se esta vaga entao posso ver se existe algum aviao para aterrar
				if(landList.size()>0)
					ActiveLandingPlane(idPista);
			}
			else{
				//reserva pista para o proximo aviao
				ActiveTakeoffPlane(idPista);
			}
		}
		ReleaseMutex(_Mutex);//_Mutex->Signal();
	}

	void fecharPista(int idPista){
		_closePistas[idPista] = true;
	}

	void abrirPista(int idPista){
		_closePistas[idPista] = false;
	}

	void alertaFuracao(bool al){
		_furacao = al;
		if(_furacao == false && takeoffList.size()>0){
			for(int i = NUMBER_OF_SKIING-1; i < NUMBER_OF_SKIING; ++i){
				if(thread_pista[i]==-1)ActiveTakeoffPlane(i);
			}	
		}
	}

private:
	bool isAirportClosed(){
		return _closePistas[0] == true && _closePistas[1] == true;
	}

	void ActiveLandingPlane(int idPista){
		Plane* next = landList.front();
		landList.pop_front();
		thread_pista[idPista]=next->GetIDThread();
		next->TerPista();
	}

	void ActiveTakeoffPlane(int idPista){
		Plane* next = takeoffList.front();
		takeoffList.pop_front();
		thread_pista[idPista]=next->GetIDThread();
		next->TerPista();
	}


};
#endif GESTORDEPISTAS
