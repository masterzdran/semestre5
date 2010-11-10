#include "stdafx.h"

#ifndef GESTORDEPISTAS_CPP
#define GESTORDEPISTAS_CPP
class GestorDePistas : IGestorDePistas
{
	Semaforo * _mLanding;
	Semaforo * _mLiftoff;
	Semaforo * _sWaitingListLanding;
	Semaforo * _sWaitingListLiftoff;
	int _nWaitingToLand;
	int _nWaitingToLiftoff;
	volatile bool[] _bLanes;

public:

	GestorDePistas(int nLanes)
	{
		_mLanding = new Semaforo(1,1);
		_mLiftoff = new Semaforo(1,1);
		_sWaitingListLanding = new Semaforo(1, MAXLONG);
		_sWaitingListLiftoff = new Semaforo(1, MAXLONG);
		_nWaitingToLand=0;
		_nWaitingToLiftoff=0;
		_bLanes = new bool[nLanes];
	}

	virtual int esperarPistaParaAterrar ()
	{
		InterlockedIncrement(&_nWaitingToLand);
		_mLanding->Wait();
		InterlockedDecrement(&_nWaitingToLand);

		
		
		return _nWaitingToLand;
	}

	virtual int esperarPistaParaDescolar ()
	{
		return 0;
	}

	virtual void libertarPista (int idPista)
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