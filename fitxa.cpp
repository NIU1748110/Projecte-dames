#include "fitxa.hpp"

void Fitxa::convertirEnDama()
{
    if (m_tipus == TIPUS_NORMAL)
        m_tipus = TIPUS_DAMA;
}


void Fitxa::afegeixMoviment(const Moviment& moviment) 
{
    if (m_numMoviments < MAX_MOVIMENTS)
        m_movimentsValids[m_numMoviments++] = moviment;
}

bool Fitxa::teCaptura() const 
{
    for (int i = 0; i < m_numMoviments; ++i)
    {
        Moviment m = m_movimentsValids[i];
        if (m.getNumPassos() > 0) 
        {
            Posicio origen = m.getPas(0);
            Posicio desti = m.getPas(m.getNumPassos() - 1);
            int df = abs(origen.getFila() - desti.getFila());
            int dc = abs(origen.getColumna() - desti.getColumna());
            if (df > 1 && dc > 1) return true;
        }
    }
    return false;
}
