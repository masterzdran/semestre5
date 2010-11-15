#include "headers\stdafx.h"

#ifndef PLANE
#define PLANE

class Plane{
private:
	int _id;
	char* _name;
public:
	 Plane(char* name, int id){
		 _name = name;
		 _id = id;
	 }
	 int getID(){ return _id; }
	 char* getName(){ return _name; }
};

#endif PLANE