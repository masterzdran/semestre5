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
private:
	//_pistas[0] - aterrar, _pistas[1] - descolar
	Semaforo* _pistas;
	//_closePistas[0] - pista 1, _closePistas[1] - pista 2
	bool* _closePistas;
	PlaneList* _head;
	PlaneList* _tail;
	bool _furacao;

public:

	GestorDePistas(){
		_pistas = new Semaforo[NUMBER_OF_SKIING];
		_closePistas = new bool[NUMBER_OF_SKIING];
		_head = _tail = NULL;
		_furacao = false;
	}

	void addPlane(int id, char* name){
		Plane* p = new Plane(name,id);
		PlaneList* pl = new PlaneList(p);
		if(_head == NULL & _tail == NULL){
			_head = _tail = pl;
		}
		else{
			_tail->_next = pl;
			_tail = pl;
		}
	}

	//E NECESSARIO ASSOCIAR A THREAD O AVIAO!!
	//NAO SEI COMO ASSOCIA-LO!!!!

	virtual int esperarPistaParaAterrar(){
		_pistas[SKIING_1].Wait();
		
		while(
			(isAirportClosed() == true)
			);
		//E NECESSARIO FAZER SIGNAL A PISTA 2 QUANDO
		//O METODO libertarPista VAI DAR COMO PARAMETRO 1!!!!
		if(_closePistas[SKIING_1]==true){
			_pistas[SKIING_2].Wait();
		}

		//ASSOCIAR AVIAO!!

		return 0;
	}

	virtual int esperarPistaParaDescolar(){
		_pistas[SKIING_2].Wait();
		while(
			_furacao == true
			||
			isAirportClosed() == true
			);

		//E NECESSARIO FAZER SIGNAL A PISTA 1 QUANDO
		//O METODO libertarPista VAI DAR COMO PARAMETRO 2!!!
		if(_closePistas[SKIING_2]==true){
			_pistas[SKIING_1].Wait();
		}

		//ASSOCIAR AVIAO!!

		return 0;
	}

	//parametro e o numero da pista nao o indice do array _pistas
	virtual void libertarPista(int idPista){

		//VERIFICAR SE E NECESSARIO MAIS ALGUMA OPERAÇAO!!

		if(idPista<=NUMBER_OF_SKIING)
			_pistas[idPista-1].Signal();
		else
			printf("Number of skiing is invalid!!");
	}

	virtual void fecharPista(int idPista){
		_closePistas[idPista] = true;
	}

	virtual void abrirPista(int idPista){
		if(_furacao == false)_furacao = true;
		_closePistas[idPista] = false;
	}

	void alertaFuracao(bool al){
		_furacao = true;
	}

private:
	Plane* getPlane(){
		Plane* p = _head->_p;
		_head = _head->_next;
		return p;
	}
	bool isAirportClosed(){
		return _closePistas[0] == true && _closePistas[1] == true;
	}
};
#endif GESTORDEPISTAS
