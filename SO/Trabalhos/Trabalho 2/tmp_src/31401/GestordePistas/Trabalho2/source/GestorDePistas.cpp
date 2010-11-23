#include "../headers/Semaforo.h"
#include "../headers/Plane.h"
#include "../headers/IGestorDePistas.h"
#include <list>

class GestorDePistas:IGestorDePistas { 
	bool pista[2];
	bool lockLane[2];
	bool furacao;
	int nbrPlanesToLand;
	int nbrPlanesTakeoff;
	
	std::list<Plane*> landList;
	std::list<Plane*> takeOffList;

	Semaforo* mutexLand;
	Semaforo* mutexTakeOff;

public: 
	GestorDePistas(){
		pista[0]=false;
		pista[1]=false;

		lockLane[0] = false;
		lockLane[1] = false;

		furacao = false;
		nbrPlanesTakeoff = 0;
		nbrPlanesToLand = 0;

		mutexLand =  new Semaforo(1);
		mutexTakeOff =  new Semaforo(1);
	}

	~GestorDePistas(){
		pista[0]=false;
		pista[1]=false;

		lockLane[0] = false;
		lockLane[1] = false;

		furacao = false;
		nbrPlanesTakeoff = 0;
		nbrPlanesToLand = 0;

		delete(mutexLand);
		delete(mutexTakeOff);
	}

	virtual int  esperarPistaParaAterrar (){
		mutexLand->Wait();

		while (!(pista[0]) && !((pista[1] && nbrPlanesTakeoff == 0))){
			nbrPlanesToLand++;
			mutexLand->Signal();
			mutexLand->Wait();
		}
		int lane = 0;
		if (pista[0]){
			lockLane[0]= true;
			lane = 0;
		}else if(pista[1] && nbrPlanesTakeoff == 0){
			lockLane[1]= true;
			lane = 1;
		}
		mutexLand->Signal();
		return lane;
	} 
	
	virtual int  esperarPistaParaDescolar (){
		if( furacao){
			nbrPlanesTakeoff++;
		}else{
			if (pista[0]){
				lockLane[0]= true;
				return 0;
			}else if(pista[1] && nbrPlanesToLand == 0){
				lockLane[1]= true;
				return 1;
			}else{
				nbrPlanesTakeoff++;
			}
		}	
	} 
	
	virtual void libertarPista (int idPista){
		lockLane[idPista]= false;	
	}
	
	virtual void fecharPista (int idPista){
		pista[idPista] = false;
	}
	
	virtual void abrirPista (int idPista){
		pista[idPista] = true;
	}
	virtual void alertaFuracao(bool alerta){
		furacao= alerta;
	}
};
int _tmain(){

return 0;
}