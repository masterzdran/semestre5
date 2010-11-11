#ifndef IGESTORPISTAS_HEADER
#define IGESTORPISTAS_HEADER

class IGestorDePistas {
public:

	enum PlaneDirection { LAND,LIFTOFF,LAND_AND_LIFTOFF };

	virtual int UseLaneTo(PlaneDirection direction) = 0;
	virtual void SetLanePriorityTo (PlaneDirection direction) = 0;
	virtual void fecharPista (int idPista) = 0;
	virtual void abrirPista (int idPista) = 0;
};
#endif IGESTORPISTAS_HEADER