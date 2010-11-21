#include "stdafx.h"

#ifndef GESTORDEPISTAS_CPP
#define GESTORDEPISTAS_CPP

class GestorDePistas : IGestorDePistas
{
	char _nLanes;
	//semaforos que vao bloquear as threads
	Semaforo * _sWaitingListLanding;
	Semaforo * _sWaitingListLiftoff;
	//mutexs para aceder 'as listas
	Semaforo * _mPlaneListToLand;
	Semaforo * _mPlaneListToLift;
	//listas de avioes para aterrar/descolar
	Plane * _planeListToLand;
	Plane * _planeListToLift;
	//nº de avioes criados ate' ao momento.
	long _planeCount;
	/***************************************/
	/********Criar um objecto pista?!*******/
	/***************************************/
		//mutex para aceder 'as variaveis associadas a uma pista.
		Semaforo * _mLanes;
		//indica se a pista esta em uso
		bool * _bLanes;
		//direccao prioritaria da pista
		PlaneDirection * _pdLanes;
	/***************************************/

	/********TESTAR********/
	Plane* AddLast(Plane * planeList)
	{
		//if(planeList==0)
		//{
		//	(*planeList) = *(new Plane());
		//	planeList->next = planeList;
		//	planeList->prev = planeList;
		//	planeList->_idPlane = InterlockedIncrement(&_planeCount);
		//	return;
		//}

		Plane * p = new Plane();

		planeList->prev->next = p;
		p->prev = planeList->prev;
		p->next = planeList;
		planeList->prev = p;

		p->_idPlane = InterlockedIncrement(&_planeCount);
		return p;
	}
	/********TESTAR********/
	/***PRINCIPALMENTE A REMOCAO DO ULTIMO ELEMENTO***/
	void Remove(Plane * elemToRemove)
	{
		int id = elemToRemove->_idPlane;

		if(elemToRemove->prev==elemToRemove)
		{
			//significa que é o sentinela, logo não é para remover
			return;
		}

		elemToRemove->next->prev = elemToRemove->prev;
		elemToRemove->prev->next = elemToRemove->next;
	}

	int findLaneTo(PlaneDirection direction)
	{
		for(int i = 0;i<_nLanes;++i)
		{
			if(_pdLanes[i] == direction && _bLanes[i])
			{
				return i;
			}
		}
		return -1;
	}

	//As threads são desbloqueadas através de um método que indicará 
	//qual a pista a libertar e consoante a sua prioridade irá libertar
	//uma thread da lista correspondente ou uma de outra, caso não haja.
	virtual Plane * UseLaneTo(PlaneDirection direction, Plane * planeList, Semaforo * mPlaneList, Semaforo * sWaitingList)
	{
		mPlaneList->Wait();
		Plane * p = AddLast(planeList);
		p->_finishedWork = false;
		mPlaneList->Signal();
		do{
			_mLanes->Wait();
			int nLane = findLaneTo(direction);
			if(nLane == -1)
			{
				_mLanes->Signal();
				sWaitingList->Wait();
			}
			else
			{
				_bLanes[nLane]=false;
				_mLanes->Signal();
				//obter o aviao consoante a direccao
				mPlaneList->Wait();
				p = planeList->next;
				Remove(p);
				mPlaneList->Signal();

				p->_finishedWork = true;
				p->_idLane = nLane;
				break;
			}
		}while(true);
		
		return p;
	}

public:

	GestorDePistas(int nLanes)
	{
		_nLanes = nLanes;
		_sWaitingListLanding = new Semaforo(0);
		_sWaitingListLiftoff = new Semaforo(0);
		_mPlaneListToLand = new Semaforo(1,1);
		_mPlaneListToLift = new Semaforo(1,1);
		
		_planeListToLift = new Plane();
		_planeListToLift->next = _planeListToLift;
		_planeListToLift->prev = _planeListToLift;

		_planeListToLand = new Plane();
		_planeListToLand->next = _planeListToLand;
		_planeListToLand->prev = _planeListToLand;

		_planeCount=0;

		_bLanes = new bool[nLanes];
		for(int i = 0;i<nLanes;++i)
			_bLanes[i]=true;
		_mLanes = new Semaforo(1,1);
		_pdLanes = new PlaneDirection[nLanes];		
	}

	virtual Plane * LandPlane()
	{
		return UseLaneTo(LAND,_planeListToLand,_mPlaneListToLand,_sWaitingListLanding);
	}

	virtual Plane * LiftoffPlane()
	{
		return UseLaneTo(LIFTOFF,_planeListToLift,_mPlaneListToLift,_sWaitingListLiftoff);
	}

	virtual void ReleaseLaneUsedBy(Plane * p)
	{
		if(!p->_finishedWork)
			return;
		_mLanes->Wait();
		_bLanes[p->_idLane]=true;
		PlaneDirection pd = _pdLanes[p->_idLane];
		_mLanes->Signal();

		if(pd==LAND)
		{
			_sWaitingListLanding->Signal();
		}
		else if(pd==LIFTOFF)
		{
			_sWaitingListLiftoff->Signal();
		}
		//erro ao apagar o aviao.
		delete p;
	}

	virtual bool SetLanePriorityTo (PlaneDirection direction, int idLane)
	{
		_mLanes->Wait();
		if (!_bLanes[idLane])
		{
			_mLanes->Signal();
			return false;
		}
		_pdLanes[idLane] = direction;
		_mLanes->Signal();
		return true;
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