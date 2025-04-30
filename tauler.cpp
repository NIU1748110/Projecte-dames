#include "tauler.h"

void Tauler::inicialitza(const string& nomFitxer)
{
    for (int i = 0; i < N_FILES; i++) {
        for (int j = 0; j < N_COLUMNES; j++) 
            m_tauler[i][j] = Fitxa();
    }

    ifstream fitxer(nomFitxer);
    if (!fitxer) return;

    char tipus;
    string posicio;
    while (!fitxer.eof()) 
    {
        fitxer >> tipus >> posicio;
        Posicio pos(posicio);
        if (pos.getFila() >= 0 && pos.getFila() < N_FILES &&
            pos.getColumna() >= 0 && pos.getColumna() < N_COLUMNES) 
        {

            TipusFitxa t = TIPUS_EMPTY;
            ColorFitxa color = COLOR_BLANC;

            if (tipus == 'O' || tipus == 'o') 
            {
                t = TIPUS_NORMAL;
                color = COLOR_BLANC;
            }
            else if (tipus == 'X' || tipus == 'x')
            {
                t = TIPUS_NORMAL;
                color = COLOR_NEGRE;
            }
            else if (tipus == 'D' || tipus == 'd') 
            {
                t = TIPUS_DAMA;
                color = COLOR_BLANC;
            }
            else if (tipus == 'R' || tipus == 'r') 
            {
                t = TIPUS_DAMA;
                color = COLOR_NEGRE;
            }

            m_tauler[pos.getFila()][pos.getColumna()] = Fitxa(t, color);
        }
    }
    fitxer.close();
}

void Tauler::actualitzaMovimentsValids()
{

}

string Tauler::toString() const 
{
    string resultat = "";

    for (int i = N_FILES - 1; i >= 0; --i) {
        resultat += char('0' + (i + 1));
        resultat += ": ";

        for (int j = 0; j < N_COLUMNES; ++j) 
        {
            const Fitxa& fitxa = m_tauler[i][j];
            char c = '_';

            if (fitxa.getTipus() == TIPUS_NORMAL) {
                if (fitxa.getColor() == COLOR_BLANC) 
                    c = 'O';
                else
                    c = 'X';
            }
            else if (fitxa.getTipus() == TIPUS_DAMA) 
            {
                if (fitxa.getColor() == COLOR_BLANC) 
                    c = 'D';
                else
                    c = 'R';
            }

            resultat += c;
            resultat += ' ';
        }

        resultat += '\n';
    }

    resultat += "   ";
    for (int j = 0; j < N_COLUMNES; ++j) {
        resultat += char('a' + j);
        resultat += ' ';
    }

    return resultat;
}
