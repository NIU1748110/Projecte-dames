#include "fitxa.h"

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
