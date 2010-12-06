#include "stdafx.h"

#ifndef IGESTORPISTAS_HEADER
#define IGESTORPISTAS_HEADER

class IGestorDePistas {
public:
	virtual Plane * criarAviaoPara(Plane::PlaneDirection direction)= 0;
	virtual Plane * esperarPistaParaAterrar() = 0;
	virtual Plane * esperarPistaParaDescolar() = 0;
	virtual void libertarPista(Plane * p) = 0;
	virtual BOOL SetLanePriorityTo (Plane::PlaneDirection direction, int idLane) = 0;
	virtual void fecharPista (int idPista) = 0;
	virtual void abrirPista (int idPista) = 0;
	virtual void alertaFuracao(bool bFuracao) = 0;
};
#endif IGESTORPISTAS_HEADER