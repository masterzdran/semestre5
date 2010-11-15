#include "stdafx.h"

#ifndef IGESTORPISTAS_HEADER
#define IGESTORPISTAS_HEADER

class IGestorDePistas {
public:

	enum PlaneDirection { LAND,LIFTOFF,LAND_AND_LIFTOFF };

	virtual Plane * LandPlane() = 0;
	virtual Plane * LiftoffPlane() = 0;
	virtual void ReleaseLaneUsedBy(Plane * p) = 0;
	virtual void SetLanePriorityTo (PlaneDirection direction) = 0;
	virtual void fecharPista (int idPista) = 0;
	virtual void abrirPista (int idPista) = 0;
};
#endif IGESTORPISTAS_HEADER