#ifndef TAULER_H
#define TAULER_H
#include <string>
#include <iostream>
#include <fstream>
#include "fitxa.h"
#include "posicio.h"
#include "moviment.h"

const int N_FILES = 8;
const int N_COLUMNES = 8;

using namespace std;

class Tauler
{
public:
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(cont Posicio& origen,
		int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif
