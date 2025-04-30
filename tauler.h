#ifndef TAULER_H
#define TAULER_H
#include <string>
#include <iostream>
#include <fstream>
#include "fitxa.h"
#include "posicio.h"
#include "moviment.h"

class Tauler
{
public:
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen,
		int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti) { return true; }
	string toString() const;

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif
