#ifndef PLANE_HEADER
#define PLANE_HEADER

class Plane
{
	static const char SIZE = 20;
public:
	int _idPlane;
	int _idLane;
	bool _finishedWork;
	Plane * next;
	Plane * prev;
	char * name;
	
	Plane()
	{
		_finishedWork=true;
		name = new char[SIZE];
	}
	
	char * GetName()
	{
		if(name==0) 
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
