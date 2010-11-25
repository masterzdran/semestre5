#include "stdafx.h"

#ifndef GESTORDEPISTAS_CPP
#define GESTORDEPISTAS_CPP

class GestorDePistas : public IGestorDePistas
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
	volatile LONG _countPlaneToLand;
	Plane * _planeListToLift;
	volatile LONG _countPlaneToLift;
	Plane * _planesOnTheGround;
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
		Plane::PlaneDirection * _pdLanes;
	/***************************************/

	/********TESTAR********/
	Plane* AddNewPlaneInEndOf(Plane * planeList, Plane::PlaneDirection pd)
	{
		Plane * p = new Plane(pd,InterlockedIncrement(&_planeCount));
		AddPlaneIn(planeList,p);
		return p;
	}
	Plane* AddPlaneIn(Plane * planeList,Plane * p)
	{
		planeList->prev->next = p;
		p->prev = planeList->prev;
		p->next = planeList;
		planeList->prev = p;
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

	int findLaneTo(Plane::PlaneDirection direction)
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
	Plane * UseLaneTo(Plane::PlaneDirection direction, Plane * planeList,
		Semaforo * mPlaneList, Semaforo * sWaitingList)
	{
		Plane * p;
		do{
			_mLanes->Wait();
			int nLane = findLaneTo(direction);
			if(nLane == -1)
			{
				if(direction==Plane::LAND && _planeListToLift->next==_planeListToLift)
				{
					nLane = findLaneTo(Plane::LIFTOFF);
				}
				else if(direction==Plane::LIFTOFF && _planeListToLand->next==_planeListToLand)
				{
					nLane = findLaneTo(Plane::LAND);
				}
				
				if(nLane==-1)
				{
					_mLanes->Signal();
					sWaitingList->Wait();
				}
			}

			if(nLane!=-1)
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

	void SignalRespectiveWaitingList(Plane::PlaneDirection pd)
	{
		if(pd==Plane::LAND && _planeListToLand->next != _planeListToLand 
			|| pd==Plane::LIFTOFF && _planeListToLift->next == _planeListToLift)
		{
			_sWaitingListLanding->Signal();
		}
		else if(pd==Plane::LIFTOFF && _planeListToLift->next != _planeListToLift 
			|| pd==Plane::LAND && _planeListToLand->next == _planeListToLand)
		{
			_sWaitingListLiftoff->Signal();
		}
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
		_countPlaneToLift = 0;

		_planeListToLand = new Plane();
		_planeListToLand->next = _planeListToLand;
		_planeListToLand->prev = _planeListToLand;
		_countPlaneToLand = 0;

		_planesOnTheGround = new Plane();
		_planesOnTheGround->next = _planesOnTheGround;
		_planesOnTheGround->prev = _planesOnTheGround;

		_planeCount=0;

		_bLanes = new bool[nLanes];
		for(int i = 0;i<nLanes;++i)
			_bLanes[i]=true;
		_mLanes = new Semaforo(1,1);
		_pdLanes = new Plane::PlaneDirection[nLanes];		
	}

	virtual Plane * criarAviaoPara(Plane::PlaneDirection direction)
	{
		Semaforo * mPlaneList;
		Plane * planeList;
		if(direction==Plane::LAND)
		{
			mPlaneList = _mPlaneListToLand;
			planeList = _planeListToLand;
			InterlockedIncrement(&_countPlaneToLand);
		}
		else if(direction==Plane::LIFTOFF)
		{
			InterlockedIncrement(&_countPlaneToLift);
			mPlaneList = _mPlaneListToLift;
			planeList = _planeListToLift;
		}
		mPlaneList->Wait();
		Plane * p = AddNewPlaneInEndOf(planeList,direction);
		p->_finishedWork = false;
		mPlaneList->Signal();
		return p;
	}
	virtual Plane * esperarPistaParaAterrar()
	{
		Plane * p = UseLaneTo(Plane::LAND,_planeListToLand,_mPlaneListToLand,_sWaitingListLanding);
		InterlockedDecrement(&_countPlaneToLand);
		return p;
	}

	virtual Plane * esperarPistaParaDescolar()
	{
		Plane * p = UseLaneTo(Plane::LIFTOFF,_planeListToLift,_mPlaneListToLift,_sWaitingListLiftoff);
		InterlockedDecrement(&_countPlaneToLift);
		return p;
	}

	virtual INT getCountPlanesToLand()
	{
		return (INT)_countPlaneToLand;
	}
	virtual INT getCountPlanesToLift()
	{
		return (INT)_countPlaneToLift;
	}
	virtual void libertarPista(Plane * p)
	{
		if(!p->_finishedWork)
			return;
		_mLanes->Wait();
		_bLanes[p->_idLane]=true;
		Plane::PlaneDirection pd = _pdLanes[p->_idLane];
		_mLanes->Signal();

		SignalRespectiveWaitingList(pd);
		//DELETE TÁ A ATRUFIAR ISTO.
		//delete p;
	}

	virtual Plane::PlaneDirection getLaneDirectionUsedBy(Plane* p)
	{
		Plane::PlaneDirection direction;
		_mLanes->Wait();
		direction = _pdLanes[p->_idLane];
		_mLanes->Signal();

		return direction;
	}
	virtual BOOL SetLanePriorityTo (Plane::PlaneDirection direction, int idLane)
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
		_mLanes->Wait();
		if(_pdLanes[idPista]==Plane::LAND)
			_pdLanes[idPista]=Plane::LAND_CLOSED;
		else
			_pdLanes[idPista]=Plane::LIFT_CLOSED;
		_mLanes->Signal();
	}

	virtual void abrirPista (int idPista)
	{
		_mLanes->Wait();
		if(_pdLanes[idPista]==Plane::LAND_CLOSED)
			_pdLanes[idPista]=Plane::LAND;
		else
			_pdLanes[idPista]=Plane::LIFTOFF;

		SignalRespectiveWaitingList(_pdLanes[idPista]);
		_mLanes->Signal();
	}
};
#endif GESTORDEPISTAS_CPP