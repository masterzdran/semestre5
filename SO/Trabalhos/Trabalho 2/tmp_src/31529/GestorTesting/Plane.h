#ifndef PLANE_HEADER
#define PLANE_HEADER

class Plane
{
	static const char SIZE = 20;
public:
	static enum PlaneDirection { LAND,LIFTOFF,LAND_CLOSED,LIFT_CLOSED };

	int _idPlane;
	int _idLane;
	PlaneDirection _pd;
	bool _finishedWork;
	Plane * next;
	Plane * prev;
	char * name;
	
	Plane()
	{
		_finishedWork=true;
		name = new char[SIZE];
		(*name)=0;
	}

	Plane(PlaneDirection pd)
	{
		_finishedWork=true;
		name = new char[SIZE];
		(*name)=0;
		_pd = pd;
	}

	Plane(PlaneDirection pd,int idPlane)
	{
		_finishedWork=true;
		name = new char[SIZE];
		(*name)=0;
		_pd = pd;
		_idPlane=idPlane;
	}

	PlaneDirection GetDirection()
	{
		return _pd;
	}

	char * GetName()
	{
		if((*name)==0) 
		{
			sprintf_s(name,sizeof(char)*SIZE,"A%d",_idPlane); 
		}
		return name; 
	}
	~Plane()
	{
		delete name;
	}
};

#endif PLANE_HEADER
