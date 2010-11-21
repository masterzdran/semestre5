#include "stdafx.h"

#include "assert.h"

const int N_PLANES = 10;
const char N_LANES = 2;

Plane ** _planesLanded = new Plane*[N_PLANES];
Plane * _planesLifted = new Plane[N_PLANES];

volatile long _pix = -1;

IGestorDePistas * igdp;

HANDLE * _th = new HANDLE[N_PLANES];

void InitializeLanes()
{
	igdp->SetLanePriorityTo(igdp->LAND,0);
	igdp->SetLanePriorityTo(igdp->LIFTOFF,1);
}

DWORD WINAPI LandPlanes(LPVOID param)
{
	_planesLanded[(DWORD)param] = igdp->LandPlane();
	
	return 0;
}

void TakeoffPlanes(LPVOID param)
{
	_planesLifted[(DWORD)param] = (*igdp->LiftoffPlane());
}

void FreeLane(LPVOID param)
{
	igdp->ReleaseLaneUsedBy((Plane*)param);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	igdp = (IGestorDePistas*)new GestorDePistas(2);

	InitializeLanes();

	for(int i = 0;i<N_PLANES;++i)
	{
		_th[i] = CreateThread(NULL,0,LandPlanes,(LPVOID)i,0,NULL);
	}

	WaitForMultipleObjects(N_PLANES,_th,FALSE,INFINITE);
	
	int countFinished=0;

	bool * flagged = new bool[N_PLANES];
	for(int i=0;i<N_PLANES;++i)
		flagged[i]=false;

	for(int i = 0;countFinished<N_PLANES;++i)
	{
		if(!flagged[i] && _planesLanded[i]!=0 &&_planesLanded[i]->_finishedWork)
		{
			igdp->ReleaseLaneUsedBy(_planesLanded[i]);
			_planesLanded[i]=0;
			flagged[i]=true;
			++countFinished;
		}
		
		if(i==N_PLANES)
			i=0;
	}

	WaitForMultipleObjects(N_PLANES,_th,true,INFINITE);

	return 0;
}



