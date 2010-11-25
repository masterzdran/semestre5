#ifndef PLANE_HEADER
#define PLANE_HEADER

class Plane
{
	static const _TCHAR SIZE = 20;
public:
	static enum PlaneDirection { LAND,LIFTOFF,LAND_CLOSED,LIFT_CLOSED };

	INT _idPlane;
	INT _idLane;
	PlaneDirection _pd;
	BOOL _finishedWork;
	Plane * next;
	Plane * prev;
	_TCHAR * name;
	
	Plane()
	{
		_finishedWork=true;
		name = new _TCHAR[SIZE];
		(*name)=0;
	}

	Plane(PlaneDirection pd)
	{
		_finishedWork=true;
		name = new _TCHAR[SIZE];
		(*name)=0;
		_pd = pd;
	}

	Plane(PlaneDirection pd,INT idPlane)
	{
		_finishedWork=true;
		name = new _TCHAR[SIZE];
		(*name)=0;
		_pd = pd;
		_idPlane=idPlane;
		
	}

	PlaneDirection GetDirection()
	{
		return _pd;
	}

	_TCHAR* GetName()
	{
		if((*name)==0) 
		{
			_stprintf_s(name,sizeof(_TCHAR)*SIZE,_T("A%d"),_idPlane);
		}
		return name; 
	}
	~Plane()
	{
		delete name;
	}
};

#endif PLANE_HEADER
