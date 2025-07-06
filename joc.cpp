//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"

using namespace std;

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    for (int fila = 0; fila < N_FILES; ++fila)
    {
        for (int col = 0; col < N_COLUMNES; ++col)
        {
            Fitxa f = m_tauler.getFitxa(fila, col);
            if (f.getTipus() != TIPUS_EMPTY)
            {
                int posX = POS_X_TAULER + CASELLA_INICIAL_X + col * AMPLADA_CASELLA;
                int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + ((N_FILES - 1 - fila) * ALCADA_CASELLA);

                IMAGE_NAME graf;
                if (f.getTipus() == TIPUS_NORMAL)
                {
                    if (f.getColor() == COLOR_BLANC) 
                    {
                        graf = GRAFIC_FITXA_BLANCA;
                    }
                    else 
                    {
                        graf = GRAFIC_FITXA_NEGRA;
                    }
                }
                else 
                {
                    if (f.getColor() == COLOR_BLANC)
                    {
                        graf = GRAFIC_DAMA_BLANCA;
                    }
                    else
                    {
                        graf = GRAFIC_DAMA_NEGRA;
                    }
                }

                GraphicManager::getInstance()->drawSprite(graf, posX, posY);
            }
        }
    }

   if(m_mode == MODE_JOC_NORMAL)
   {
       if ((!m_fitxaSeleccionadaValida) && (mouseStatus) && (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
           (mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
           (mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
           (mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
       {

           int filaPantalla = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;
           int columna = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
           int filaTauler = N_FILES - 1 - filaPantalla;

           Posicio clicada(filaTauler, columna);
           Fitxa fitxaClicada = m_tauler.getFitxa(clicada.getFila(), clicada.getColumna());

           if (fitxaClicada.getTipus() != TIPUS_EMPTY && fitxaClicada.getColor() == m_jugadorActual)
           {
               m_fitxaSeleccionada = clicada;
               m_fitxaSeleccionadaValida = true;
           }
           else
           {
               m_fitxaSeleccionadaValida = false;
           }
       }


       if (m_fitxaSeleccionadaValida)
       {
           Posicio posicions[16];
           int nPos = 0;
           m_tauler.getPosicionsPossibles(m_fitxaSeleccionada, nPos, posicions);

           for (int i = 0; i < nPos; ++i)
           {
               int filaPantalla = posicions[i].getFila();
               int columna = posicions[i].getColumna();

               int posX = POS_X_TAULER + CASELLA_INICIAL_X + columna * AMPLADA_CASELLA;
               int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + filaPantalla * ALCADA_CASELLA;

               GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
           }
       }


       if ((m_fitxaSeleccionadaValida) && (mouseStatus) && (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
           (mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
           (mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
           (mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
       {
           int filaPantalla = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;
           int columna = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
           int filaTauler = N_FILES - 1 - filaPantalla;

           Posicio clicada(filaPantalla, columna);
           Fitxa fitxaClicada = m_tauler.getFitxa(filaTauler, clicada.getColumna());

           if ((columna != m_fitxaSeleccionada.getColumna()) || (filaTauler != m_fitxaSeleccionada.getFila()))
           {
               if (fitxaClicada.getTipus() != TIPUS_EMPTY && fitxaClicada.getColor() == m_jugadorActual)
               {
                   m_fitxaSeleccionadaValida = false;
               }
           }
           

           if (m_fitxaSeleccionadaValida)
           {
               Posicio moviments[16];
               int nMoviments = 0;
               m_tauler.getPosicionsPossibles(m_fitxaSeleccionada, nMoviments, moviments);

               if (nMoviments == 0)
               {
                   m_fitxaSeleccionadaValida = false;
                   m_fitxaSeleccionada = Posicio();
               }

               for (int i = 0; i < nMoviments; ++i)
               {
                   if (moviments[i].getFila() == clicada.getFila() && moviments[i].getColumna() == clicada.getColumna())
                   {
                       m_tauler.mouFitxa(m_fitxaSeleccionada, clicada);

                       int filaOrigen = 7 - m_fitxaSeleccionada.getFila();

                       Posicio posicioOriginal(filaOrigen, m_fitxaSeleccionada.getColumna());

                       m_cua.nouMoviment(posicioOriginal, clicada);

                       if (m_jugadorActual == COLOR_BLANC) 
                       {
                           m_jugadorActual = COLOR_NEGRE;
                       }
                       else 
                       {
                           m_jugadorActual = COLOR_BLANC;
                       }
                       m_fitxaSeleccionadaValida = false;
                       m_fitxaSeleccionada = Posicio();

                       m_tauler.actualitzaMovimentsValids();
                   }
               }
           }
       }
   }

   if (m_mode == MODE_JOC_REPLAY && !m_cua.buida())
   {
       if ((!m_repeticio) && (mouseStatus) && (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
           (mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
           (mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
           (mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
       {
           m_repeticio = true;
       }
       if ((m_repeticio) && (!mouseStatus) && (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
           (mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
           (mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
           (mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
       {
           Posicio origen;
           Posicio desti;

           m_cua.getOrigenDesti(origen, desti);

           int filaOrigen = 7 - origen.getFila();
           origen.setFila(filaOrigen);

           m_tauler.mouFitxa(origen, desti);

           if (m_jugadorActual == COLOR_BLANC)
               m_jugadorActual = COLOR_NEGRE;
           else 
               m_jugadorActual = COLOR_BLANC;

           m_tauler.actualitzaMovimentsValids();
           m_repeticio = false;
       }

   }

   if (m_mode == MODE_JOC_REPLAY && m_cua.buida())
   {
       int posTextX = POS_X_TAULER;
       int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 200;

       string mBuida = "No hi ha mes moviments per reprodiur";
       GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, mBuida);
       string sortirPartida = "Prem Esc per sortir de la partida";
       GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, (posTextY + 30), 0.8, sortirPartida);

   }


    bool quedenBlanques = false;
     
    for (int fila = 0; fila < 8; fila++)
    {
        for (int col = 0; col < 8; col++)
        {
            if ((m_tauler.getFitxa(fila, col).getTipus() != TIPUS_EMPTY) && m_tauler.getFitxa(fila, col).getColor() == COLOR_BLANC)
            {
                quedenBlanques = true;
            }

        }
    }

    bool quedenNegres = false;

    for (int fila = 0; fila < 8; fila++)
    {
        for (int col = 0; col < 8; col++)
        {
            if ((m_tauler.getFitxa(fila, col).getTipus() != TIPUS_EMPTY) && m_tauler.getFitxa(fila, col).getColor() == COLOR_NEGRE)
            {
                quedenNegres = true;
            }

        }
    }


    
    int posTextX = POS_X_TAULER;
    int posTextYA = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 140;
    int posTextYB = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 170;

    string modeJoc = "Nul";

    if (m_mode == MODE_JOC_NORMAL)
        modeJoc = "Normal";
    if (m_mode == MODE_JOC_REPLAY)
        modeJoc = "Replay";

    string jugadorAct = "Nul";
    if (m_jugadorActual == COLOR_BLANC)
        jugadorAct = "Blanques";
    if (m_jugadorActual == COLOR_NEGRE)
        jugadorAct = "Negres";

    string mMode = "Mode Joc: " + modeJoc;
    string mJugador = "Jugador actual: " + jugadorAct;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextYA, 0.8, mMode);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextYB, 0.8, mJugador);


    

    if (!quedenBlanques || !quedenNegres)
    {
        int posTextX = POS_X_TAULER;
        int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 200;
        if(m_mode == MODE_JOC_NORMAL)
        {
            if (quedenBlanques)
            {
                string guaynador = "les Blanques guanyen";
                GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, guaynador);
            }
            if (quedenNegres)
            {
                string guaynador = "les Negres guanyen";
                GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, guaynador);
            }
            string sortirPartida = "Prem Esc per sortir de la partida";
            GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, (posTextY + 30), 0.8, sortirPartida);

        }
        return true;
    }
    return false;
}




void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
    m_mode = mode;
    m_jugadorActual = COLOR_BLANC;
    m_fitxaSeleccionada = Posicio();
    m_fitxaSeleccionadaValida = false;
    m_partidaFinalitzada = false;
    m_fitxerMoviments = nomFitxerMoviments;
    m_tauler.inicialitza(nomFitxerTauler);
    m_tauler.actualitzaMovimentsValids();
    m_repeticio = false;

    if (m_mode == MODE_JOC_REPLAY)
    {
        m_cua.carregaDeFitxer(m_fitxerMoviments);
    }
}


void Joc::finalitza()
{
    string moviments = m_fitxerMoviments;
    if(m_mode == MODE_JOC_NORMAL)
    {
        m_cua.inicialitzaMoviments(moviments);
    }
}
