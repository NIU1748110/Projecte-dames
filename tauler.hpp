#ifndef TAULER_H
#define TAULER_H
#include <string>
#include <iostream>
#include <fstream>
#include "fitxa.hpp"
#include "posicio.hpp"
#include "moviment.hpp"

class Tauler
{
public:
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen,
		int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;
	Posicio posicioDesDeIndexos(int filaInterna, int columna) const;
	void movimentsDames(Fitxa& fitxa, int fila, int columna);
	void movimentsFitxesNormals(Fitxa& fitxa, int fila, int columna);
	bool esMovimentValid(int fila, int columna) const;
	bool esCasellaBuida(int fila, int columna) const;
	bool esEnemic(const Fitxa& fitxa, int fila, int columna) const;
	void afegirMoviment(Fitxa& fitxa, int filaDesti, int columnaDesti);

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif
