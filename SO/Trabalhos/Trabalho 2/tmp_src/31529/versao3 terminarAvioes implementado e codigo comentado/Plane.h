#ifndef PLANE_HEADER
#define PLANE_HEADER

class Plane
{
	static const _TCHAR SIZE = 20;
	_TCHAR * name;
	void Initialize()
	{
		_terminateQuickly=FALSE;
		_finishedWork=TRUE;
		name = new _TCHAR[SIZE];
		(*name)=0;
	}
public:
	static enum PlaneDirection { LAND,LIFTOFF,LAND_CLOSED,LIFT_CLOSED };

	INT _idPlane;
	INT _idLane;
	PlaneDirection _pd;
	BOOL _finishedWork;
	Plane * next;
	Plane * prev;
	
	BOOL _terminateQuickly;
	
	Plane()
	{
		Initialize();
	}
	Plane(PlaneDirection pd)
	{
		_pd = pd;
		Initialize();
	}

	Plane(PlaneDirection pd,INT idPlane)
	{
		_idPlane=idPlane;
		_pd = pd;
		Initialize();
	}
	~Plane()
	{
		delete name;
	}

	PlaneDirection GetDirection()
	{
		return _pd;
	}

	_TCHAR* GetName()
	{
		if((*name)==0) 
		{
			_stprintf(name,_T("A%d"),_idPlane);
		}
		return name; 
	}
	BOOL terminateQuickly()
	{
		return _terminateQuickly;
	}
};

#endif PLANE_HEADER
