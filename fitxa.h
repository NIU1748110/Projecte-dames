#ifndef FITXA_H
#define FITXA_H
#include "posicio.h"
#include "moviment.h"

using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

const int MAX_MOVIMENTS = 16;

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

    Fitxa(TipusFitxa tipus, ColorFitxa color) : m_tipus(tipus), m_color(color), m_numMoviments(0) {}
    Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_BLANC), m_numMoviments(0) {}


    TipusFitxa getTipus() const { return m_tipus; }
    ColorFitxa getColor() const { return m_color; }
    void convertirEnDama();

    void afegeixMoviment(const Moviment& m);
    void resetMoviments() { m_numMoviments = 0; }
    int getNumMoviments() const { return m_numMoviments; }
    Moviment getMoviment(int i) const { return m_movimentsValids[i]; }

private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Moviment m_movimentsValids[MAX_MOVIMENTS];
    int m_numMoviments;

};


#endif
