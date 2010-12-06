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
	CRITICAL_SECTION _GetRunWay;
	CRITICAL_SECTION _SetStateRunWay;
	//_closePistas[0] - pista 1, _closePistas[1] - pista 2
	DWORD* thread_pista;
	//quando a true existe alerta de furacao
	bool _furacao;

	HANDLE _Event;

	CRITICAL_SECTION _GetNumberLanding;
	CRITICAL_SECTION _GetNumberTakeOff;
	DWORD number_Planes_List_Landing;
	DWORD number_Planes_List_takeoff;

	_TCHAR buffer[10];

	std::list<Plane*> landList;
	std::list<Plane*> takeoffList;

public:
	GestorDePistas(){
		InitializeCriticalSection(&_GetRunWay);
		InitializeCriticalSection(&_SetStateRunWay);
		InitializeCriticalSection(&_GetNumberLanding);
		InitializeCriticalSection(&_GetNumberTakeOff);
		_furacao = false;
		thread_pista = new DWORD[NUMBER_OF_SKIING];
		thread_pista[0] = -1;
		thread_pista[1] = -1;
		number_Planes_List_Landing = 0;
		number_Planes_List_takeoff = 0;

		_Event = CreateEvent(NULL, false, false, (LPCWSTR)"Remove Planes");
	}
	
	~GestorDePistas(){
		delete thread_pista;
		CloseHandle(_Event);
		DeleteCriticalSection(&_GetRunWay);
		DeleteCriticalSection(&_SetStateRunWay);
		DeleteCriticalSection(&_GetNumberLanding);
		DeleteCriticalSection(&_GetNumberTakeOff);
	}

	int esperarPistaParaAterrar(Plane* a){
		DWORD id = a->GetIDThread();
		//entra no while caso nao haja pista livre
		while( isAllRunWaysClose() || ( landList.size()>=0 && !isAvalaible(0, id) && !isAvalaible(1, id)) ){
			EnterCriticalSection(&_GetRunWay);
			landList.push_back(a);
			LeaveCriticalSection(&_GetRunWay);
			a->EsperarPista(_Event);
		}
		//ja tem pista reservada!
		int p = -1;
		EnterCriticalSection(&_GetRunWay);
		//necessario pista estar aberta, livre ou id seja igual ao seu
		if( ( thread_pista[0]==id) || thread_pista[0]==-1) p=0;
		else if( (thread_pista[1]==id) || thread_pista[1]==-1) p = 1;
		//caso pista estivesse vaga, sem reserva
		if(p>-1 && thread_pista[p]==-1)thread_pista[p]=a->GetIDThread();
		LeaveCriticalSection(&_GetRunWay);
		return p;
	}

	int esperarPistaParaDescolar(Plane* d){
		DWORD id = d->GetIDThread();
		//entra no while caso nao haja pista livre
		while( _furacao || isAllRunWaysClose() || (takeoffList.size()>=0 && !isAvalaible(0, id) && !isAvalaible(1, id)) ){
			EnterCriticalSection(&_GetRunWay);
			takeoffList.push_back(d);
			LeaveCriticalSection(&_GetRunWay);
			d->EsperarPista(_Event);
		}
		//ja tem pista reservada!
		int p = -1;
		EnterCriticalSection(&_GetRunWay);
		//necessario pista estar aberta, livre ou id seja igual ao seu
		if(thread_pista[0]==id || thread_pista[0]==-1) p=0;
		else if(thread_pista[1]==id || thread_pista[1]==-1) p = 1;
		//caso pista estivesse vaga, sem reserva
		if(p>-1 && thread_pista[p]==-1)thread_pista[p]=d->GetIDThread();
		LeaveCriticalSection(&_GetRunWay);
		return p;
	}

	void libertarPista(int idPista){
		EnterCriticalSection(&_GetRunWay);
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
				if(landList.size() > 0 && thread_pista[idPista]!=0) ActiveLandingPlane(idPista);
			}
		}
		else{//idPista==1
			if(_furacao || takeoffList.size()==0){
				//caso pista esteja fechada, nao sera indicado que esta livre
				if(thread_pista[idPista]!=0)thread_pista[idPista]=-1;
				//se esta vaga entao posso ver se existe algum aviao para aterrar
				if(landList.size()>0 && thread_pista[idPista]!=0)
					if(thread_pista[idPista]!=0)ActiveLandingPlane(idPista);
			}
			else{
				//reserva pista para o proximo aviao
				if(takeoffList.size() > 0 && thread_pista[idPista]!=0) ActiveTakeoffPlane(idPista);
			}
		}
		LeaveCriticalSection(&_GetRunWay);
	}

	void fecharPista(int idPista){
		EnterCriticalSection(&_SetStateRunWay);
		thread_pista[idPista] = 0;
		LeaveCriticalSection(&_SetStateRunWay);
	}

	void abrirPista(int idPista){
		EnterCriticalSection(&_SetStateRunWay);
		thread_pista[idPista] = -1;
		LeaveCriticalSection(&_SetStateRunWay);
		if(landList.size()>0) NotifyLandingPlanesThatHadRunWay(idPista, idPista);
		else if(takeoffList.size()>0)NotifyTakeOffPlanesThatHadRunWay(idPista, idPista);
	}

	_TCHAR* AddOneNumberPlanesLanding(){
		EnterCriticalSection(&_GetNumberLanding);	
		_itot(++number_Planes_List_Landing,buffer,10);
		LeaveCriticalSection(&_GetNumberLanding);
		return buffer;
	}

	_TCHAR* RemoveOneNumberPlanesLanding(){
		EnterCriticalSection(&_GetNumberLanding);
		_itot(--number_Planes_List_Landing,buffer,10);
		LeaveCriticalSection(&_GetNumberLanding);
		return buffer;
	}
	
	_TCHAR* AddOneNumberPlanesTakeOff(){
		EnterCriticalSection(&_GetNumberTakeOff);
		_itot(++number_Planes_List_takeoff,buffer,10);
		LeaveCriticalSection(&_GetNumberTakeOff);
		return buffer;
	}

	_TCHAR* RemoveOneNumberPlanesTakeOff(){
		EnterCriticalSection(&_GetNumberTakeOff);
		_itot(--number_Planes_List_takeoff,buffer,10);
		LeaveCriticalSection(&_GetNumberTakeOff);
		return buffer;
	}

	void alertaFuracao(bool al){
		_furacao = al;
		if(_furacao == false && thread_pista[0]!=0 && takeoffList.size()>0){
			NotifyTakeOffPlanesThatHadRunWay(0,0);
		}
		if(_furacao == false && thread_pista[1]!=0 && takeoffList.size()>0){
			NotifyTakeOffPlanesThatHadRunWay(1,1);
		}
	}

	/*void EndAllPlanes(){
		SetEvent(_Event);
		landList.clear(); 
		takeoffList.clear();
		thread_pista[0] = -1;
		thread_pista[1] = -1;
	}*/

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
				EnterCriticalSection(&_GetRunWay);//WaitForSingleObject(_Mutex, INFINITE);
				ActiveLandingPlane(i);
				LeaveCriticalSection(&_GetRunWay);//ReleaseMutex(_Mutex);
			}
		}
	}

	void NotifyTakeOffPlanesThatHadRunWay(int pista_inicio, int pista_fim){
		for(int i = pista_inicio; i < pista_fim+1; ++i){
			if(thread_pista[i]==-1){
				EnterCriticalSection(&_GetRunWay);//WaitForSingleObject(_Mutex, INFINITE);
				ActiveTakeoffPlane(i);
				LeaveCriticalSection(&_GetRunWay);//ReleaseMutex(_Mutex);
			}
		}
	}

};
#endif GESTORDEPISTAS
