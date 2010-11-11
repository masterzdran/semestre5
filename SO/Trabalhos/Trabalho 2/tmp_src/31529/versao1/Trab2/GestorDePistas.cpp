#include "stdafx.h"

#ifndef GESTORDEPISTAS_CPP
#define GESTORDEPISTAS_CPP

class GestorDePistas : IGestorDePistas
{
	char _nLanes;
	Semaforo * _sWaitingListLanding;
	Semaforo * _sWaitingListLiftoff;
	Plane * _planeListToLand;
	Plane * _planeListToLift;
	bool * _bLanes;
	Semaforo * _mLanes;
	PlaneDirection * _pdLanes;
	long _planeCount;

	void AddLast(Plane * planeList)
	{
		if(planeList==0)
		{
			planeList = new Plane();
			planeList->_idPlane = InterlockedIncrement(&_planeCount);
			return;
		}
		Plane * p = new Plane();
		planeList->next = p;
		p->_idPlane = InterlockedIncrement(&_planeCount);
	}

	int RemoveFirst(Plane * planeList)
	{
		;
	}

	int findLaneTo(PlaneDirection direction)
	{
		for(int i = 0;i<_nLanes;++i)
		{
			if(_pdLanes[i]==direction)
				return i;
		}
		return -1;
	}

public:

	GestorDePistas(int nLanes)
	{
		_nLanes = nLanes;
		_bLanes = new bool[nLanes];
		_mLanes = new Semaforo[nLanes];
		_pdLanes = new PlaneDirection[nLanes];
		_planeCount=0;

		Semaforo * f;
		for(int i = 0;i<nLanes;++i)
		{
			f = new Semaforo(1,1);
			_mLanes[i] = (*f);
		}
	}



	virtual int UseLaneTo(PlaneDirection direction)
	{
		int nLane = findLaneTo(direction);
		if(nLane == -1)
		{
			if(direction == LAND)
			{
				;
			}
			else if(direction ==LIFTOFF)
			{
				;
			}
		}

		return _planeCount;
	}

	virtual void SetLanePriorityTo (PlaneDirection direction)
	{
		;
	}

	virtual void fecharPista (int idPista)
	{
		;
	}

	virtual void abrirPista (int idPista)
	{
		;
	}
};
#endif GESTORDEPISTAS_CPP