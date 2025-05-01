#include "moviment.hpp"

void Moviment::afegeixPas(const Posicio& p) 
{
    if (m_numPassos < MAX_PASSOS)
        m_passos[m_numPassos++] = p;
}
