#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"
#include "tauler.hpp"
#include "cuaMoviments.hpp"

using namespace std;


class Joc 
{

public:
    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void finalitza();

private:
    Tauler m_tauler;
    ModeJoc m_mode;
    ColorFitxa m_jugadorActual;
    Posicio m_fitxaSeleccionada;
    bool m_fitxaSeleccionadaValida;
    bool m_partidaFinalitzada;
    bool m_repeticio;
    string m_fitxerMoviments;
    CuaMoviments m_cua;
};

#endif 
