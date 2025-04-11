#ifndef FITXA_H
#define FITXA_H
#include "posicio.h"
#include "moviment.h"

const int N_FILES = 8;
const int N_COLUMNES = 8;

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC,
} ColorFitxa;

class Fitxa
{
public:
	Fitxa(ColorFitxa color, TipusFitxa tipus) : m_color(color), m_tipus(tipus) {}

	
private:
	ColorFitxa m_color;
	TipusFitxa m_tipus;
	Moviment m_movimentsValids[];

};


#endif
