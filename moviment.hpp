#ifndef MOVIMENT_H
#define MOVIMENT_H
#include "posicio.hpp"

const int MAX_PASSOS = 8;


class Moviment
{
public:
    Moviment() : m_numPassos(0) {}
    void afegeixPas(const Posicio& p);
    int getNumPassos() const { return m_numPassos; }
    Posicio getPas(int i) const { return m_passos[i]; }

private:
    Posicio m_passos[MAX_PASSOS];
    int m_numPassos;
};

#endif
