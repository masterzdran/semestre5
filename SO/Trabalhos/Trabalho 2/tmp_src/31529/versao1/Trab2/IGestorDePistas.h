#ifndef IGESTORPISTAS_HEADER
#define IGESTORPISTAS_HEADER

class IGestorDePistas {
public:
	virtual int esperarPistaParaAterrar () = 0;
	virtual int esperarPistaParaDescolar ()= 0;
	virtual void libertarPista (int idPista)= 0;
	virtual void fecharPista (int idPista) = 0;
	virtual void abrirPista (int idPista) = 0;
};
#endif IGESTORPISTAS_HEADER