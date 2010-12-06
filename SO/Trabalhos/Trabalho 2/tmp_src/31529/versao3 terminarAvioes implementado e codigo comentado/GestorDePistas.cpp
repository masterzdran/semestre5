#include "stdafx.h"

#ifndef GESTORDEPISTAS_CPP
#define GESTORDEPISTAS_CPP

class GestorDePistas : public IGestorDePistas
{
	static const INT _SpinCount=1000;
	//numero de pistas recebido por parametro
	char _nLanes;
	//semaforos que vao bloquear as threads
	HANDLE _sWaitingListLanding;
	HANDLE _sWaitingListLiftoff;
	//seccoes critica para aceder 'as listas
	CRITICAL_SECTION _csPlaneListToLand;
	CRITICAL_SECTION _csPlaneListToLift;
	//listas de avioes para aterrar/descolar
	Plane * _planeListToLand;
	volatile LONG _countPlaneToLand;
	Plane * _planeListToLift;
	volatile LONG _countPlaneToLift;
	//nº de avioes criados ate' ao momento.
	long _planeCount;
	//variavel utilizada para indicar a existencia de um furacao
	bool _bFuracao;
	//critical_section para aceder 'as variaveis associadas a uma pista.
	 CRITICAL_SECTION _csLanes;
	//indica se a pista esta em uso
	bool * _bLanes;
	//direccao prioritaria da pista
	Plane::PlaneDirection * _pdLanes;
	//evento que permite libertar as threads que estejam presas
	HANDLE _eTerminate;
	//variavel para permitir a saida das threads do ciclo existente no metodo UseLaneTo
	volatile LONG freeFromCycle;
	
	//Cria um novo objecto aviao com determinada direccao e adicina-o 'a lista recebida,
	Plane* AddNewPlaneInEndOf(Plane * planeList, Plane::PlaneDirection pd)
	{
		Plane * p = new Plane(pd,InterlockedIncrement(&_planeCount));
		AddPlaneIn(planeList,p);
		return p;
	}
	//Adiciona o objecto aviao 'a lista.
	Plane* AddPlaneIn(Plane * planeList,Plane * p)
	{
		planeList->prev->next = p;
		p->prev = planeList->prev;
		p->next = planeList;
		planeList->prev = p;
		return p;
	}
	//Remove o objecto aviao da lista onde se encontre inserido
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
	//devolve uma pista que nao esteja a ser utilizada
	// e que esteja a ser utilizada para determinada direccao
	int findLaneTo(Plane::PlaneDirection direction)
	{
		for(int i = 0;i<_nLanes;++i)
		{
			//Para utilizar uma pista mesmo que esteja fechada
			// utilizar o if que esta em comentario
			//if((_pdLanes[i] == direction || _bFuracao) && _bLanes[i])
			if(_pdLanes[i] == direction && _bLanes[i])
			{
				return i;
			}
		}
		return -1;
	}

	//Recebe a direccao do aviao, a lista a utilizar, a seccao critica para aceder 'a lista
	// e um array de HANDLE com o semaforo de espera, caso nao estejam reunidas as condicoes
	// apropriadas, e o evento que libertera' as threads.
	Plane * UseLaneTo(Plane::PlaneDirection direction, Plane * planeList,
		CRITICAL_SECTION csPlaneList, HANDLE listAndEvent[])
	{
		Plane * p;
		do{
			EnterCriticalSection(&_csLanes);
			int nLane = findLaneTo(direction);
			if(nLane == -1)
			{
				//caso a direccao seja para aterrar e a lista de avioes para levantar voo
				//esteja vazia, procura vai 'a procura de uma pista para levantar voo
				if(direction==Plane::LAND && (_planeListToLift->next==_planeListToLift || _bFuracao))
				{
					nLane = findLaneTo(Plane::LIFTOFF);
				}
				//caso a direccao seja para levantar voo e a lista de avioes de aterrar 
				//esteja vazia, procura vai 'a procura de uma pista para aterrar
				else if(direction==Plane::LIFTOFF && _planeListToLand->next==_planeListToLand)
				{
					nLane = findLaneTo(Plane::LAND);
				}
				//Se ainda assim nao encontrar uma pista, bloqueia-se
				if(nLane==-1)
				{
					LeaveCriticalSection(&_csLanes);
					WaitForMultipleObjects(2,listAndEvent,FALSE,INFINITE);
				}
			}
			//se tiver encontrado uma pista vazia em qualquer uma das situacoes anteriormente
			//referidas vai buscar o primeiro aviao da fila de espera
			if(nLane!=-1)
			{
				_bLanes[nLane]=false;
				LeaveCriticalSection(&_csLanes);

				EnterCriticalSection(&csPlaneList);
				p = planeList->next;
				Remove(p);
				LeaveCriticalSection(&csPlaneList);

				p->_finishedWork = true;
				p->_idLane = nLane;
				return p;
			}
		} while(freeFromCycle==0);//Condicao que permite que as threads saiam
		//deste ciclo quando for para terminarem a sua execucao

		//obter o primeiro aviao da lista
		EnterCriticalSection(&csPlaneList);
		p = planeList->next;
		Remove(p);
		LeaveCriticalSection(&csPlaneList);

		p->_terminateQuickly = TRUE;
		return p;
	}

	//Metodo que desbloqueia uma thread consoante a direccao da pista recebida.
	//Vai libertar uma thread da lista correspondente 'a direccao ou se uma lista
	//estiver vazia libertara' uma thread da outra lista.
	void SignalRespectiveWaitingList(Plane::PlaneDirection pd)
	{
		if((_bFuracao || pd==Plane::LAND) && _planeListToLand->next != _planeListToLand
			|| pd==Plane::LIFTOFF && _planeListToLift->next == _planeListToLift)
		{
			ReleaseSemaphore(_sWaitingListLanding,1,NULL);
		}
		else if(pd==Plane::LIFTOFF && _planeListToLift->next != _planeListToLift 
			|| pd==Plane::LAND && _planeListToLand->next == _planeListToLand)
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

		InitializeCriticalSectionAndSpinCount(&_csPlaneListToLand,_SpinCount);
		InitializeCriticalSectionAndSpinCount(&_csPlaneListToLift,_SpinCount);

		_planeListToLift = new Plane();
		_planeListToLift->next = _planeListToLift;
		_planeListToLift->prev = _planeListToLift;
		_countPlaneToLift = 0;

		_planeListToLand = new Plane();
		_planeListToLand->next = _planeListToLand;
		_planeListToLand->prev = _planeListToLand;
		_countPlaneToLand = 0;

		_planeCount=0;
		_bFuracao=false;

		_bLanes = new bool[nLanes];
		for(int i = 0;i<nLanes;++i)
		{
			_bLanes[i]=true;
		}
		InitializeCriticalSectionAndSpinCount(&_csLanes,_SpinCount);
		_pdLanes = new Plane::PlaneDirection[nLanes];

		_eTerminate = CreateEvent(NULL,TRUE,FALSE,NULL);
		freeFromCycle=0;
	}

	~GestorDePistas()
	{
		CloseHandle(_sWaitingListLanding);
		CloseHandle(_sWaitingListLiftoff);
		DeleteCriticalSection(&_csPlaneListToLand);
		DeleteCriticalSection(&_csPlaneListToLift);
		DeleteCriticalSection(&_csLanes);
		CloseHandle(_eTerminate);
	}
	//metodo publico que ira' utilizar os metodos anteriormente apresentados
	//para criar um aviao consoante a sua direccao
	virtual Plane * criarAviaoPara(Plane::PlaneDirection direction)
	{
		CRITICAL_SECTION csPlaneList;
		Plane * planeList;
		if(direction==Plane::LAND)
		{
			InterlockedIncrement(&_countPlaneToLand);
			csPlaneList = _csPlaneListToLand;
			planeList = _planeListToLand;
		}
		else if(direction==Plane::LIFTOFF)
		{
			InterlockedIncrement(&_countPlaneToLift);
			csPlaneList = _csPlaneListToLift;
			planeList = _planeListToLift;
		}
		EnterCriticalSection(&csPlaneList);
		Plane * p = AddNewPlaneInEndOf(planeList,direction);
		p->_finishedWork = false;
		LeaveCriticalSection(&csPlaneList);
		return p;
	}
	//Tenta aterrar o primeiro aviao na lista de avioes para aterrar
	virtual Plane * esperarPistaParaAterrar()
	{
		static HANDLE listAndEvent[] = {_sWaitingListLanding, _eTerminate};
		Plane * p = UseLaneTo(Plane::LAND,_planeListToLand,_csPlaneListToLand,listAndEvent);
		InterlockedDecrement(&_countPlaneToLand);
		return p;
	}
	//Tenta com que o p8rimeiro aviao da lista de avioes para levantar voo parta.
	virtual Plane * esperarPistaParaDescolar()
	{
		static HANDLE listAndEvent[] = {_sWaitingListLiftoff, _eTerminate};
		Plane * p = UseLaneTo(Plane::LIFTOFF,_planeListToLift,_csPlaneListToLift,listAndEvent);
		InterlockedDecrement(&_countPlaneToLift);
		return p;
	}

	//utilizado para indicar quantos avioes para aterrar existem
	virtual INT getCountPlanesToLand()
	{
		return (INT)_countPlaneToLand;
	}
	//utilizado para indicar quantos avioes para levantar voo existem
	virtual INT getCountPlanesToLift()
	{
		return (INT)_countPlaneToLift;
	}
	//liberta a pista que foi utilizada pelo aviao recebido por parametro
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
	//obter a direccao da pista utilizada pelo aviao
	virtual Plane::PlaneDirection getLaneDirectionUsedBy(Plane* p)
	{
		Plane::PlaneDirection direction;
		EnterCriticalSection(&_csLanes);
		direction = _pdLanes[p->_idLane];
		LeaveCriticalSection(&_csLanes);

		return direction;
	}
	//define a direccao de uma pista
	virtual BOOL SetLanePriorityTo (Plane::PlaneDirection direction, int idLane)
	{
		if(idLane>=_nLanes)
			return false;

		EnterCriticalSection(&_csLanes);
		_pdLanes[idLane] = direction;
		LeaveCriticalSection(&_csLanes);
		return true;
	}
	//fecha uma pista
	virtual void fecharPista (int idPista)
	{
		if(idPista>=_nLanes)
			return;

		EnterCriticalSection(&_csLanes);
		if(_pdLanes[idPista]==Plane::LAND)
			_pdLanes[idPista]=Plane::LAND_CLOSED;
		else if (_pdLanes[idPista]==Plane::LIFTOFF)
			_pdLanes[idPista]=Plane::LIFT_CLOSED;
		LeaveCriticalSection(&_csLanes);
	}
	//abre uma pista
	virtual void abrirPista (int idPista)
	{
		if(idPista>=_nLanes)
			return;

		EnterCriticalSection(&_csLanes);
		if(_pdLanes[idPista]==Plane::LAND_CLOSED)
			_pdLanes[idPista]=Plane::LAND;
		else if (_pdLanes[idPista]==Plane::LIFT_CLOSED)
			_pdLanes[idPista]=Plane::LIFTOFF;

		SignalRespectiveWaitingList(_pdLanes[idPista]);
		LeaveCriticalSection(&_csLanes);
	}
	//activa o alerta furacao
	virtual void alertaFuracao(bool bFuracao)
	{
		//se alguma das pistas se encontrar fechada os aviões
		//irão aterrar nela de qualquer forma.
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
	//liberta as threads que estejam presas em qualquer mecanismo de sincronizacao
	virtual void terminar()
	{
		SetEvent(_eTerminate);
		InterlockedIncrement(&freeFromCycle);
	}
};
#endif GESTORDEPISTAS_CPP
