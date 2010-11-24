#include "headers\stdafx.h"
#include "headers\IGestorDePistas.h"

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
	//Mutex associado as threads que pretendem descolar
	Semaforo* _DMutex;
	//Mutex associado as threads que pretendem aterrar
	Semaforo* _AMutex;
	//Mutex associado as threads que pretendem libertar a pista
	Semaforo* _LMutex;
	//quando a true as pistas estao fechadas
	//_closePistas[0] - pista 1, _closePistas[1] - pista 2
	bool* _closePistas;
	//quando a true existe alerta de furacao
	bool _furacao;
public:
	GestorDePistas(){
		_pistas = new Semaforo[NUMBER_OF_SKIING];
		_DMutex = new Semaforo[NUMBER_OF_SKIING];
		_AMutex = new Semaforo[NUMBER_OF_SKIING];
		_LMutex = new Semaforo[NUMBER_OF_SKIING];
		_closePistas = new bool[NUMBER_OF_SKIING];
		_furacao = false;
	}
	
	//thread ja sabe qual o aviao que lhe esta destinado
	int ThreadQuerPista(int op/*1->quer aterrar, 2->quer descolar*/){
		Semaforo* thread_actual = new Semaforo(0,0);
		if(op==1)_pistas[0]->Wait(thread_actual);
		else _pistas[1]->Wait(thread_actual);

		
		int pista = -1;
		if( (op==1 && (pista = esperarPistaParaAterrar())==-1) ){
			thread_actual->Wait();
			//pista = caso volte a invocar esperarPistaParaAterrar irao existir ja threads
			//em wait no _AMutex o que ira impedir o conhecimento da pista!
			//RESOLVER!!!
		}
		else if((op==2 && (pista = esperarPistaParaDescolar()) ==-1)){
			thread_actual->Wait();
		}

		
		//retorna o numero da pista
		return pista;
	}


	virtual int esperarPistaParaAterrar(){
		_AMutex->Wait();

		//necessario efectuar condiçoes para verificar qual das pistas esta vaga!

		//se houverem threads a espera na lista a que estiver a cabeça
		//sera efectuado Signal para que esta prociga, e entra na zona de exclusao
		//apos _AMutex sair de Signal
		_AMutex->Signal();
		return 0;
	}

	virtual int esperarPistaParaDescolar(){
		//condicoes necessarias para escolher pista
		return 0;
	}

	virtual void libertarPista(int idPista){
		//signal a pista correcta
	}

	virtual void fecharPista(int idPista){
		_closePistas[idPista] = true;
	}

	virtual void abrirPista(int idPista){
		_closePistas[idPista] = false;
	}

	void alertaFuracao(bool al){
		_furacao = true;
	}

private:
	bool isAirportClosed(){
		return _closePistas[0] == true && _closePistas[1] == true;
	}
};
#endif GESTORDEPISTAS
