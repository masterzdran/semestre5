#include "..\headers\Semaforo.h"
#include "..\headers\Plane.h"

class GestorDePistas{ 
	bool aeroportoFechado;
	bool pista1Fechada;
	bool pista2Fechada;
	bool alertaFuracao;
	
	Semaforo *sAterrar;
	Semaforo *sLevantar;
	Semaforo *p1mutex;
	Semaforo *p2mutex;
	Semaforo *furacaoMutex;
	Semaforo *aeroportoFechadoMutex;


public: 
	GestorDePistas(){
		aeroportoFechado = false;
		pista1Fechada = false;
		pista2Fechada = false;
		alertaFuracao = false;
		sAterrar = new Semaforo(0);
		sLevantar = new Semaforo(0);
		p1mutex = new Semaforo(1);
		p2mutex = new Semaforo(1);
		furacaoMutex=  new Semaforo(1);
		aeroportoFechadoMutex = new Semaforo(1);
	}

	~GestorDePistas(){
	}

	int  esperarPistaParaAterrar (){
		p1mutex->Wait();

		while ( aeroportoFechado || pista1Fechada){
			p1mutex->Signal();
			sAterrar->Wait();
			p1mutex->Wait();
		}
		pista1Fechada = true;
		p1mutex->Signal();
		return 1;
	}

	int  esperarPistaParaDescolar (){} 
	void libertarPista (int idPista){}
	void fecharPista (int idPista){}
	void abrirPista (int idPista){}
}; 