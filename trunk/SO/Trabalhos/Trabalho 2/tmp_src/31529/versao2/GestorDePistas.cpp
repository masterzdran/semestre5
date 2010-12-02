#include "stdafx.h"

#ifndef GESTORDEPISTAS_CPP
#define GESTORDEPISTAS_CPP

class GestorDePistas : public IGestorDePistas
{
	char _nLanes;
	//semaforos que vao bloquear as threads
	HANDLE _sWaitingListLanding;
	HANDLE _sWaitingListLiftoff;
	//mutexs para aceder 'as listas
	HANDLE _mPlaneListToLand;
	HANDLE _mPlaneListToLift;
	//listas de avioes para aterrar/descolar
	Plane * _planeListToLand;
	volatile LONG _countPlaneToLand;
	Plane * _planeListToLift;
	volatile LONG _countPlaneToLift;
	Plane * _planesOnTheGround;
	//nº de avioes criados ate' ao momento.
	long _planeCount;
	bool _bFuracao;
	/***************************************/
	/********Criar um objecto pista?!*******/
	/***************************************/
		//mutex para aceder 'as variaveis associadas a uma pista.
		 CRITICAL_SECTION _csLanes;
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
			if((_pdLanes[i] == direction || _bFuracao) && _bLanes[i])
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
		HANDLE mPlaneList, HANDLE sWaitingList)
	{
		Plane * p;
		do{
			EnterCriticalSection(&_csLanes);
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
					LeaveCriticalSection(&_csLanes);
					WaitForSingleObject(sWaitingList,INFINITE);
				}
			}

			if(nLane!=-1)
			{
				_bLanes[nLane]=false;
				LeaveCriticalSection(&_csLanes);
				//obter o aviao consoante a direccao
				WaitForSingleObject(mPlaneList,INFINITE);
				p = planeList->next;
				Remove(p);
				ReleaseMutex(mPlaneList);
				p->_finishedWork = true;
				p->_idLane = nLane;
				break;
			}
		}while(true);
		
		return p;
	}

	void SignalRespectiveWaitingList(Plane::PlaneDirection pd)
	{
		if(_bFuracao || pd==Plane::LAND && _planeListToLand->next != _planeListToLand 
			|| pd==Plane::LIFTOFF && _planeListToLift->next == _planeListToLift)
		{
			ReleaseSemaphore(_sWaitingListLanding,1,NULL);
		}
		else if(!_bFuracao && (pd==Plane::LIFTOFF && _planeListToLift->next != _planeListToLift 
			|| pd==Plane::LAND && _planeListToLand->next == _planeListToLand))
		{
			ReleaseSemaphore(_sWaitingListLiftoff,1,NULL);
		}
	}

public:

	GestorDePistas(int nLanes)
	{
		_nLanes = nLanes;
		_sWaitingListLanding = CreateSemaphore(NULL,0,MAXLONG,NULL);
		_sWaitingListLiftoff = CreateSemaphore(NULL,0,MAXLONG,NULL);
		_mPlaneListToLand = CreateMutex(NULL,FALSE,NULL);
		_mPlaneListToLift = CreateMutex(NULL,FALSE,NULL);
		
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
		_bFuracao=false;

		_bLanes = new bool[nLanes];
		for(int i = 0;i<nLanes;++i)
			_bLanes[i]=true;
		InitializeCriticalSectionAndSpinCount(&_csLanes,1000);
		_pdLanes = new Plane::PlaneDirection[nLanes];		
	}

	virtual Plane * criarAviaoPara(Plane::PlaneDirection direction)
	{
		HANDLE mPlaneList;
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
		WaitForSingleObject(mPlaneList,INFINITE);
		Plane * p = AddNewPlaneInEndOf(planeList,direction);
		p->_finishedWork = false;
		ReleaseMutex(mPlaneList);
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
		EnterCriticalSection(&_csLanes);
		_bLanes[p->_idLane]=true;
		Plane::PlaneDirection pd = _pdLanes[p->_idLane];
		LeaveCriticalSection(&_csLanes);

		SignalRespectiveWaitingList(pd);
		//DELETE TÁ A ATRUFIAR ISTO.
		//delete p;
	}

	virtual Plane::PlaneDirection getLaneDirectionUsedBy(Plane* p)
	{
		Plane::PlaneDirection direction;
		EnterCriticalSection(&_csLanes);
		direction = _pdLanes[p->_idLane];
		LeaveCriticalSection(&_csLanes);

		return direction;
	}
	virtual BOOL SetLanePriorityTo (Plane::PlaneDirection direction, int idLane)
	{
		EnterCriticalSection(&_csLanes);
		//if (!_bLanes[idLane])
		//{
		//	_mLanes->Signal();
		//	return false;
		//}
		_pdLanes[idLane] = direction;
		LeaveCriticalSection(&_csLanes);
		return true;
	}

	virtual void fecharPista (int idPista)
	{
		EnterCriticalSection(&_csLanes);
		if(_pdLanes[idPista]==Plane::LAND)
			_pdLanes[idPista]=Plane::LAND_CLOSED;
		else if (_pdLanes[idPista]==Plane::LIFTOFF)
			_pdLanes[idPista]=Plane::LIFT_CLOSED;
		LeaveCriticalSection(&_csLanes);
	}

	virtual void abrirPista (int idPista)
	{
		EnterCriticalSection(&_csLanes);
		if(_pdLanes[idPista]==Plane::LAND_CLOSED)
			_pdLanes[idPista]=Plane::LAND;
		else if (_pdLanes[idPista]==Plane::LIFT_CLOSED)
			_pdLanes[idPista]=Plane::LIFTOFF;

		SignalRespectiveWaitingList(_pdLanes[idPista]);
		LeaveCriticalSection(&_csLanes);
	}
	virtual void alertaFuracao(bool bFuracao)
	{
		//se alguma das pistas se encontrar fechada os aviões irão aterrar nela de qualquer forma.
		_bFuracao=bFuracao;
		EnterCriticalSection(&_csLanes);
		for(int i = 0;i<_nLanes;++i)
		{
			if(_bLanes[i])
			{
				SignalRespectiveWaitingList(_pdLanes[i]);
			}
		}
		LeaveCriticalSection(&_csLanes);
	}
};
#endif GESTORDEPISTAS_CPP