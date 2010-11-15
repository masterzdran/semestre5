#include "headers\stdafx.h"
#include "Plane.cpp"

#ifndef PLANELIST
#define PLANELIST

class PlaneList{
public:
	Plane* _p;
	PlaneList* _next;
	PlaneList(Plane* p){
		_p = p;
		_next = NULL;
	}
};

#endif PLANELIST
