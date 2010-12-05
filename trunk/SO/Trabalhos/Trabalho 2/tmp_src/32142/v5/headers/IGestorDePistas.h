#ifndef IGESTORDEPISTAS
#define IGESTORDEPISTAS
#include "Plane.cpp"
class IGestorDePistas{
public:
	virtual int  esperarPistaParaAterrar (Plane* p) = 0; 
	virtual int  esperarPistaParaDescolar (Plane* p) = 0; 
	virtual void libertarPista (int idPista) = 0; 
	virtual void fecharPista (int idPista) = 0; 
	virtual void abrirPista (int idPista) = 0;
};
#endif 