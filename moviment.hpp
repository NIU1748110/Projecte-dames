#ifndef MOVIMENT_H
#define MOVIMENT_H
#include "posicio.hpp"
#include <vector>

class Moviment
{
public:
    void afegeixPas(const Posicio& p);
    int getNumPassos() const { return m_passos.size(); }
    Posicio getPas(int i) const { return m_passos[i]; }

private:
    vector<Posicio> m_passos;
};

#endif
