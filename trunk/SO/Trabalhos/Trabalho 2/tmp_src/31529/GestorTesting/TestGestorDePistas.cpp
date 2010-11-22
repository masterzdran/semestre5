#include "stdafx.h"

const int N_PLANES = 10;
const char N_LANES = 1;

Plane ** _planesLanded = new Plane*[N_PLANES];
Plane * _planesLifted = new Plane[N_PLANES];

volatile long _pix = -1;

IGestorDePistas * igdp;

HANDLE * _th = new HANDLE[N_PLANES];

void InitializeTest()
{
	igdp->SetLanePriorityTo(Plane::LAND,0);
	//igdp->SetLanePriorityTo(igdp->LIFTOFF,1);
	for(int i = 0;i<N_PLANES;++i)
	{
		_planesLanded[i]=0;
	}
}


Plane * LandPlanes(DWORD tID)
{
	Plane * p = igdp->esperarPistaParaAterrar();
	printf("[%d] Plane %s Landed on Lane %d\n",tID,p->GetName(),p->_idLane);
	Sleep(0);
	igdp->libertarPista(p);
	return p;
}
Plane * LiftPlanes(DWORD tID)
{
	Plane * p = igdp->esperarPistaParaDescolar();
	printf("[%d] Plane %s Lifted on Lane %d\n",tID,p->GetName(),p->_idLane);
	Sleep(0);
	igdp->libertarPista(p);
	return p;
}

DWORD WINAPI DoSomethingWithPlanes(LPVOID param)
{
	delete LandPlanes((DWORD) param);
	
	delete LiftPlanes((DWORD) param);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{

	igdp = (IGestorDePistas*)new GestorDePistas(2);

	InitializeTest();

	for(int i = 0;i<N_PLANES;++i)
	{
		_th[i] = CreateThread(NULL,0,DoSomethingWithPlanes,(LPVOID)i,0,NULL);
	}

	WaitForMultipleObjects(N_PLANES,_th,TRUE,INFINITE);
	return 0;
}



