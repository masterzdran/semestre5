#include "headers\stdafx.h"
#include "headers\IGestorDePistas.h"
#include "Plane.cpp"
#include "PlaneList.cpp"

#ifndef GESTORDEPISTAS
#define GESTORDEPISTAS

const int NUMBER_OF_SKIING = 2;
const int SKIING_1 = 0;
const int SKIING_2 = 1;

class GestorDePistas : IGestorDePistas {
	//demasiadas variaveis - MELHORAR!!!!
private:
	//_pistas[0] - aterrar, _pistas[1] - descolar
	Semaforo** _pistas;
	
	Semaforo* _Mutex_Espera_Pista;
	Semaforo* _Mutex_Liberta_Pista;
	//quando a true as pistas estao fechadas
	//_closePistas[0] - pista 1, _closePistas[1] - pista 2
	bool* _closePistas;
	//lista necessaria para dar prioridade a ordem dos avioes para aterrar
	PlaneList* _hAterrar;
	PlaneList* _tAterrar;
	//controla fluxo de inserção de avioes para aterrar
	Semaforo* _ater;
	//lista necessaria para dar prioridade a ordem dos avioes para descolar
	PlaneList* _hDescolar;
	PlaneList* _tDescolar;
	//controla fluxo de inserção de avioes para descolar
	Semaforo* _desc;
public:
	//quando a true existe alerta de furacao
	bool _furacao;
public:
	GestorDePistas(){
		_pistas = new Semaforo*[2];
		_pistas[0] = new Semaforo(1,1);
		_pistas[1] = new Semaforo(1,1);
		_Mutex_Espera_Pista = new Semaforo(1,1);
		_Mutex_Liberta_Pista = new Semaforo(1,1);
		_closePistas = new bool[NUMBER_OF_SKIING];
		_closePistas[SKIING_1] = false;
		_closePistas[SKIING_2] = false;
		_ater = new Semaforo(1,1);
		_desc = new Semaforo(1,1);
		_hAterrar = _tAterrar = _hDescolar = _tDescolar = NULL;
		_furacao = false;
	}

	//demasiado igual ao metodo addPlaneTakeOff - MELHORAR!!!
	//FUNCIONA!!
	void addPlaneLanding(int id, char* name){
		_ater->Wait();
		Plane* p = new Plane(name,id);
		PlaneList* pl = new PlaneList(p);
		if(_hAterrar == NULL && _tAterrar == NULL){
			_hAterrar = _tAterrar = pl;
		}
		else{
			_tAterrar->_next = pl;
			_tAterrar = pl;
		}
		_ater->Signal();
	}


	//demasiado igual ao metodo addPlaneLanding - MELHORAR!!!
	//FUNCIONA!!
	void addPlaneTakeOff(int id, char* name){
		_desc->Wait();
		Plane* p = new Plane(name,id);
		PlaneList* pl = new PlaneList(p);
		if(_hDescolar == NULL && _tDescolar == NULL){
			_hDescolar = _tDescolar = pl;
		}
		else{
			_tDescolar->_next = pl;
			_tDescolar = pl;
		}
		_desc->Signal();
	}

	//E NECESSARIO ASSOCIAR A THREAD O AVIAO!!
	//NAO SEI COMO ASSOCIA-LO!!!!

	virtual int esperarPistaParaAterrar(){
		_Mutex_Espera_Pista->Wait();

		_pistas[SKIING_1]->Wait();
		
		while(
			(isAirportClosed() == true)
			);
		printf("\nJA TENHO PISTA 1!\n");
		//E NECESSARIO FAZER SIGNAL A PISTA 2 QUANDO
		//O METODO libertarPista VAI DAR COMO PARAMETRO 1!!!!
		//if(_closePistas[SKIING_1]==true){
			//_pistas[SKIING_2]->Wait();
		//}

		//guardar aviao
		Plane* p = _hAterrar->_p;
		//avançar ponteiro
		_hAterrar = _hAterrar->_next;

		//ASSOCIAR AVIAO!!

		printf("Aviao %s esta a aterrar\n",p->getName());

		_Mutex_Espera_Pista->Signal();
		return 0;
	}

	virtual int esperarPistaParaDescolar(){
		_Mutex_Espera_Pista->Wait();

		_pistas[SKIING_2]->Wait();
		
		while(
			_furacao == true
			||
			isAirportClosed() == true
			);
		printf("\nJA TENHO PISTA 2!\n");
		//E NECESSARIO FAZER SIGNAL A PISTA 1 QUANDO
		//O METODO libertarPista VAI DAR COMO PARAMETRO 2!!!

		/*if(_closePistas[SKIING_2]==true){
			_pistas[SKIING_2]->Signal();
			esperarPistaParaAterrar();
			libertarPista(1);
		}*/

		Plane* p = _hDescolar->_p;
		_hDescolar = _hDescolar->_next;

		//ASSOCIAR AVIAO!!
		printf("Aviao %s esta a descolar\n",p->getName());

		_Mutex_Espera_Pista->Signal();
		return 0;
	}

	//parametro e o numero da pista nao o indice do array _pistas
	virtual void libertarPista(int idPista){
		_Mutex_Liberta_Pista->Wait();
		if(idPista<=NUMBER_OF_SKIING){
			printf("ID da pista valido!\n");
			printf("VOU LIBERTAR PISTA %d!\n",idPista);
			_pistas[idPista-1]->Signal();
		}
		else
			printf("Number of skiing is invalid!!");
		_Mutex_Liberta_Pista->Signal();
	}

	virtual void fecharPista(int idPista){
		_closePistas[idPista] = true;
	}

	//ID=1, indice = 0 e ID=2, indice = 1
	virtual void abrirPista(int idPista){
		_closePistas[idPista-1] = false;
	}

	void alertaFuracao(bool al){
		_furacao = al;
	}

private:
	bool isAirportClosed(){
		return _closePistas[0] == true && _closePistas[1] == true;
	}
};
#endif GESTORDEPISTAS
