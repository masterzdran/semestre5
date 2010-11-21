// Testar_Trab2_SO.cpp : Defines the entry point for the console application.
//

#include "headers\stdafx.h"
#include "GestorDePistas.cpp"
#include "Plane.cpp"
#include "Process.h"

typedef unsigned (__stdcall *PTHREAD_START) (void *);
#define chBEGINTHREADEX(psa, cbStack, pfnStartAddr, \
   pvParam, fdwCreate, pdwThreadId)                 \
      ((HANDLE)_beginthreadex(                      \
         (void *)        (psa),                     \
         (unsigned)      (cbStack),                 \
         (PTHREAD_START) (pfnStartAddr),            \
         (void *)        (pvParam),                 \
         (unsigned)      (fdwCreate),               \
         (unsigned *)    (pdwThreadId)))

GestorDePistas * g = new GestorDePistas();

void test1(){
	GestorDePistas * g1 = new GestorDePistas();

	g1->addPlaneLanding(1,"A331");
	g1->addPlaneLanding(2,"A332");
	g1->addPlaneLanding(3,"A333");
	g1->addPlaneLanding(4,"A334");
	
	g1->addPlaneTakeOff(1,"A331");
	g1->addPlaneTakeOff(2,"A332");
	g1->addPlaneTakeOff(3,"A333");
	g1->addPlaneTakeOff(4,"A334");

	//em debug e verificado que listas estao a ser inseridas correctamente
	
}


static DWORD WINAPI Aterrar(LPVOID args){
	g->esperarPistaParaAterrar();
	g->libertarPista(1);
	return 0;
}

void TestarAterragem(int n){
	int NUMBER_OF_THREADS = n;
	HANDLE* hThreads = new HANDLE[NUMBER_OF_THREADS];
	DWORD*  idThreads = new DWORD[NUMBER_OF_THREADS];
	char* airplane[] = {{"L01"},{"L02"},{"L03"},{"L04"},{"L05"},
						{"L06"},{"L07"},{"L08"},{"L09"},{"L10"}};
	for(int i = 0; i < NUMBER_OF_THREADS; ++i){
		idThreads[i] = i;
		g->addPlaneLanding(i+1,airplane[i]);
		hThreads[i] = chBEGINTHREADEX(NULL, 0, Aterrar, (LPVOID) 5, NULL, 0);
	}

	WaitForMultipleObjects( NUMBER_OF_THREADS , hThreads, TRUE, INFINITE );
	for (int i=0; i<NUMBER_OF_THREADS; ++i)
        CloseHandle(hThreads[i]);
}

DWORD WINAPI Descolar(LPVOID args){
	g->esperarPistaParaDescolar();
	g->libertarPista(2);
	return 0;
}
void TestarDescolagem(int n){
	int NUMBER_OF_THREADS = n;
	HANDLE* hThreads = new HANDLE[NUMBER_OF_THREADS];
	DWORD*  idThreads = new DWORD[NUMBER_OF_THREADS];
	char* airplane[] = {{"T01"},{"T02"},{"T03"},{"T04"},{"T05"},
						{"T06"},{"T07"},{"T08"},{"T09"},{"T10"}};
	for(int i = 0; i < NUMBER_OF_THREADS; ++i){
		idThreads[i] = i;
		g->addPlaneTakeOff(i+1,airplane[i]);
		hThreads[i] = chBEGINTHREADEX(NULL, 0, Descolar, (LPVOID) 5, NULL, 0);
	}

	WaitForMultipleObjects( NUMBER_OF_THREADS , hThreads, TRUE, INFINITE );
	for (int i=0; i<NUMBER_OF_THREADS; ++i)
        CloseHandle(hThreads[i]);
}

void TestarAlertaFuracao(){
	g->_furacao = true;
	TestarAterragem(3);
	//fica parado ja que com a alerta de furacao nenhum aviao sai do aeroporto
	printf("\n\nOs avioes que estavam com saidas previstas so partem apos o furacao passar!");
	printf("\nE favor FECHAR CONSOLA pois boolean furacao = true!");
	TestarDescolagem(2);
}

	//fechar uma das pistas para apenas uma funcionar e verificar reacçao do algoritmo!
	//fechar todas as pistas e verificar reacçao do algoritmo!!
	//activar alerta furacao e verificar reacçao do algoritmo!!

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Start _tmain\n\n");
	//TestarAterragem(10);
	//TestarDescolagem(10);
	TestarAlertaFuracao();
	printf("\nFinish _tmain\n\n");
	return 0;
}

