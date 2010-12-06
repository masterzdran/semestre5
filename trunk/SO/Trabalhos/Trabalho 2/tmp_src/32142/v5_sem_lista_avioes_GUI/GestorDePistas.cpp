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
	DWORD* thread_pista;
	//quando a true existe alerta de furacao
	bool _furacao;
		
	std::list<Plane*> landList;
	std::list<Plane*> takeoffList;

public:
	GestorDePistas(){
		//_Mutex = new Semaforo[NUMBER_OF_SKIING];
		_Mutex = CreateMutex(NULL, false, NULL);
		_furacao = false;
		thread_pista = new DWORD[NUMBER_OF_SKIING];
		thread_pista[0] = -1;
		thread_pista[1] = -1;
	}
	
	~GestorDePistas(){
		delete _Mutex;
		delete thread_pista;
	}

	int esperarPistaParaAterrar(Plane* a){
		DWORD id = a->GetIDThread();
		//entra no while caso nao haja pista livre
		while( isAllRunWaysClose() || ( landList.size()>=0 && !isAvalaible(0, id) && !isAvalaible(1, id)) ){
			WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
			landList.push_back(a);
			ReleaseMutex(_Mutex);//_Mutex->Signal();
			a->EsperarPista();
		}
		//ja tem pista reservada!
		int p = 0;
		WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
		//necessario pista estar aberta, livre ou id seja igual ao seu
		if( ( thread_pista[0]==id) || thread_pista[0]==-1) p=0;
		else if( (thread_pista[1]==id) || thread_pista[1]==-1) p = 1;
		//caso pista estivesse vaga, sem reserva
		if(thread_pista[p]==-1)thread_pista[p]=a->GetIDThread();
		ReleaseMutex(_Mutex);//_Mutex->Signal();
		return p;
	}

	int esperarPistaParaDescolar(Plane* d){
		DWORD id = d->GetIDThread();
		//entra no while caso nao haja pista livre
		while( _furacao || isAllRunWaysClose() || (takeoffList.size()>=0 && !isAvalaible(0, id) && !isAvalaible(1, id)) ){
			WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
			takeoffList.push_back(d);
			ReleaseMutex(_Mutex);//_Mutex->Signal();
			d->EsperarPista();
		}
		//ja tem pista reservada!
		int p = 0;
		WaitForSingleObject(_Mutex, INFINITE);//_Mutex->Wait();
		//necessario pista estar aberta, livre ou id seja igual ao seu
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
				//caso pista esteja fechada, nao sera indicado que esta livre
				if(thread_pista[idPista]!=0)thread_pista[idPista]=-1;
				//se esta vaga entao posso ver se existe algum aviao para descolar
				if(!_furacao && takeoffList.size()>0 && thread_pista[idPista]!=0){
					ActiveTakeoffPlane(idPista);
				}
			}
			else{
				//reserva pista para o proximo aviao
				ActiveLandingPlane(idPista);
			}
		}
		else{//idPista==1
			if(_furacao || takeoffList.size()==0){
				//caso pista esteja fechada, nao sera indicado que esta livre
				if(thread_pista[idPista]!=0)thread_pista[idPista]=-1;
				//se esta vaga entao posso ver se existe algum aviao para aterrar
				if(landList.size()>0 && thread_pista[idPista]!=0)
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
		thread_pista[idPista] = 0;
	}

	void abrirPista(int idPista){
		thread_pista[idPista] = -1;
		if(landList.size()>0) NotifyLandingPlanesThatHadRunWay(idPista, idPista);
		else if(takeoffList.size()>0)NotifyTakeOffPlanesThatHadRunWay(idPista, idPista);
	}

	void alertaFuracao(bool al){
		_furacao = al;
		if(_furacao == false && takeoffList.size()>0){
			NotifyTakeOffPlanesThatHadRunWay(0,1);
		}
	}

private:
	bool isAllRunWaysClose(){
		return thread_pista[0] == 0 && thread_pista[1] == 0;
	}

	bool isAvalaible(int p, int id){
		//esta fechada
		if(thread_pista[p] == 0) return false;
		//esta ocupada
		if(thread_pista[p] != -1 && thread_pista[p] != id) return false;
		//pista e minha quando id e o meu ou esta vazia e ainda nao tem meu id
		return thread_pista[p]==id || thread_pista[p] == -1;
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

	void NotifyLandingPlanesThatHadRunWay(int pista_inicio, int pista_fim){
		for(int i = pista_inicio; i < pista_fim+1; ++i){
			if(thread_pista[i]==-1){
				WaitForSingleObject(_Mutex, INFINITE);
				ActiveLandingPlane(i);
				ReleaseMutex(_Mutex);
			}
		}
	}

	void NotifyTakeOffPlanesThatHadRunWay(int pista_inicio, int pista_fim){
		for(int i = pista_inicio; i < pista_fim+1; ++i){
			if(thread_pista[i]==-1){
				WaitForSingleObject(_Mutex, INFINITE);
				ActiveTakeoffPlane(i);
				ReleaseMutex(_Mutex);
			}
		}
	}

};
#endif GESTORDEPISTAS
