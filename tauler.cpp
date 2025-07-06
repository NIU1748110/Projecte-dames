#include "tauler.hpp"
void Tauler::inicialitza(const string& nomFitxer)
{
    for (int i = 0; i < N_FILES; i++)
    {
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
        int fila = pos.getFila();
        int col = pos.getColumna();

        if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
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

            int filaInterna = 7 - fila;
            m_tauler[filaInterna][col] = Fitxa(t, color);
        }
    }
    fitxer.close();
}

void Tauler::actualitzaMovimentsValids()
{
    for (int i = 0; i < N_FILES; ++i)
    {
        for (int j = 0; j < N_COLUMNES; ++j)
        {
            Fitxa& fitxa = m_tauler[i][j];
            fitxa.resetMoviments();

            if (fitxa.getTipus() == TIPUS_DAMA)
                movimentsDames(fitxa, i, j);

            else if (fitxa.getTipus() == TIPUS_NORMAL)
                movimentsFitxesNormals(fitxa, i, j);

        }
    }
}

void Tauler::movimentsDames(Fitxa& dama, int fila, int columna) {
    const int direccions[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
    ColorFitxa colorContrari;
    if (dama.getColor() == COLOR_BLANC)
        colorContrari = COLOR_NEGRE;
    else
        colorContrari = COLOR_BLANC;

    for (int i = 0; i < 4; ++i)
    {
        int dirX = direccions[i][0];
        int dirY = direccions[i][1];
        int x = fila + dirX;
        int y = columna + dirY;
        bool enemicTrobat = false;
        bool continuar = true;

        while (continuar && esMovimentValid(x, y))
        {
            if (esCasellaBuida(x, y))
            {
                if (!enemicTrobat)
                {
                    afegirMoviment(dama, x, y);
                }
                else
                {
                    Moviment m;
                    m.afegeixPas(posicioDesDeIndexos(x, y));
                    dama.afegeixMoviment(m);
                }
                x += dirX;
                y += dirY;
            }
            else
            {
                if (m_tauler[x][y].getColor() == colorContrari && !enemicTrobat)
                {
                    enemicTrobat = true;
                    int x2 = x + dirX;
                    int y2 = y + dirY;
                    if (esMovimentValid(x2, y2) && esCasellaBuida(x2, y2))
                    {
                        Moviment m;
                        m.afegeixPas(posicioDesDeIndexos(x2, y2));
                        dama.afegeixMoviment(m);
                        x = x2;
                        y = y2;
                    }
                    else
                    {
                        continuar = false;
                    }
                }
                else
                {
                    continuar = false;
                }
            }
        }
    }
}

void Tauler::movimentsFitxesNormals(Fitxa& fitxa, int fila, int columna)
{
    int direccio;
    if (fitxa.getColor() == COLOR_BLANC)
    {
        direccio = 1;
    }
    else
    {
        direccio = -1;
    }

    for (int dj = -1; dj <= 1; dj += 2)
    {
        int novaFila = fila + direccio;
        int novaCol = columna + dj;

        if (esMovimentValid(novaFila, novaCol) && esCasellaBuida(novaFila, novaCol))
        {
            afegirMoviment(fitxa, novaFila, novaCol);
        }
    }

    for (int dj = -1; dj <= 1; dj += 2)
    {
        int filaIntermedia = fila + direccio;
        int colIntermedia = columna + dj;
        int filaDesti = fila + 2 * direccio;
        int colDesti = columna + 2 * dj;

        if (esMovimentValid(filaDesti, colDesti) &&
            esMovimentValid(filaIntermedia, colIntermedia) &&
            !esCasellaBuida(filaIntermedia, colIntermedia) &&
            esEnemic(fitxa, filaIntermedia, colIntermedia) &&
            esCasellaBuida(filaDesti, colDesti))
        {

            Moviment moviment;
            moviment.afegeixPas(posicioDesDeIndexos(filaDesti, colDesti));
            fitxa.afegeixMoviment(moviment);

            verificarCapturesMultiples(fitxa, filaDesti, colDesti, moviment);
        }
    }
}

void Tauler::verificarCapturesMultiples(Fitxa& fitxa, int filaActual, int columnaActual, Moviment& movimentActual)
{
    bool trobatCaptura = false;
    int direccio;
    if (fitxa.getColor() == COLOR_BLANC)
        direccio = 1;
    else
        direccio = -1;

    for (int dj = -1; dj <= 1; dj += 2)
    {
        int filaIntermedia = filaActual + direccio;
        int colIntermedia = columnaActual + dj;
        int filaDesti = filaActual + 2 * direccio;
        int colDesti = columnaActual + 2 * dj;

        if (esMovimentValid(filaDesti, colDesti) &&
            esMovimentValid(filaIntermedia, colIntermedia) &&
            !esCasellaBuida(filaIntermedia, colIntermedia) &&
            esEnemic(fitxa, filaIntermedia, colIntermedia) &&
            esCasellaBuida(filaDesti, colDesti))
        {

            trobatCaptura = true;
            Moviment nouMoviment = movimentActual;
            nouMoviment.afegeixPas(posicioDesDeIndexos(filaDesti, colDesti));
            fitxa.afegeixMoviment(nouMoviment);

            verificarCapturesMultiples(fitxa, filaDesti, colDesti, nouMoviment);
        }
    }
}

bool Tauler::esMovimentValid(int fila, int columna) const
{
    return (fila >= 0 && fila < N_FILES && columna >= 0 && columna < N_COLUMNES);
}

bool Tauler::esCasellaBuida(int fila, int columna) const
{
    return (m_tauler[fila][columna].getTipus() == TIPUS_EMPTY);
}

bool Tauler::esEnemic(const Fitxa& fitxa, int fila, int columna) const
{
    return (m_tauler[fila][columna].getColor() != fitxa.getColor());
}

void Tauler::afegirMoviment(Fitxa& fitxa, int filaDesti, int columnaDesti)
{
    Moviment moviment;
    moviment.afegeixPas(posicioDesDeIndexos(filaDesti, columnaDesti));
    fitxa.afegeixMoviment(moviment);
}


Posicio Tauler::posicioDesDeIndexos(int filaInterna, int columna) const
{
    return Posicio(string(1, 'a' + columna) + char('1' + (filaInterna)));
}



void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
    int fila = origen.getFila();
    int col = origen.getColumna();

    if (fila < 0 || fila >= N_FILES || col < 0 || col >= N_COLUMNES)
        return;

    Fitxa& f = m_tauler[fila][col];
    for (int i = 0; i < f.getNumMoviments(); ++i)
    {
        Moviment m = f.getMoviment(i);
        if (m.getNumPassos() > 0)
            posicionsPossibles[nPosicions++] = m.getPas(m.getNumPassos() - 1);
    }
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    int fi = origen.getFila();
    int ci = origen.getColumna();
    int fd = 7 - desti.getFila();
    int cd = desti.getColumna();

    Fitxa fitxa = m_tauler[fi][ci];
    if (fitxa.getTipus() == TIPUS_EMPTY)
        return false;

    actualitzaMovimentsValids();

    bool potCapturar = false;
    int direccio = 1;
    if (fitxa.getColor() == COLOR_BLANC)
        direccio = 1;
    else
        direccio = -1;
    for (int dj = -1; dj <= 1; dj += 2)
    {
        int x = fi + direccio;
        int y = ci + dj;
        int x2 = fi + 2 * direccio;
        int y2 = ci + 2 * dj;

        if (esMovimentValid(x, y) && esMovimentValid(x2, y2) && !esCasellaBuida(x, y) &&
            m_tauler[x][y].getColor() != fitxa.getColor() && esCasellaBuida(x2, y2))
        {
            potCapturar = true;
            dj = 2;
        }
    }

    int nPos;
    Posicio possibles[16];
    getPosicionsPossibles(origen, nPos, possibles);

    bool movimentTrobat = false;
    int iPos = 0;
    while (iPos < nPos && !movimentTrobat)
    {
        if (possibles[iPos] == desti)
        {
            movimentTrobat = true;
        }
        iPos++;
    }

    if (!movimentTrobat)
        return false;

    bool esCaptura = ((fd - fi > 1) || (fi - fd > 1)) && ((cd - ci > 1) || (ci - cd > 1));

    if (esCaptura)
    {
        int df;
        if (fd > fi)
            df = 1;
        else
            df = -1;

        int dc;
        if (cd > ci)
            dc = 1;
        else
            dc = -1;

        int x = fi + df;
        int y = ci + dc;

        while (x != fd && y != cd) 
        {
            if (!esCasellaBuida(x, y) && m_tauler[x][y].getColor() != fitxa.getColor()) 
                m_tauler[x][y] = Fitxa();
            x += df;
            y += dc;
        }
    }

    m_tauler[fd][cd] = fitxa;
    m_tauler[fi][ci] = Fitxa();

    if (fitxa.getTipus() == TIPUS_NORMAL)
    {
        if ((fitxa.getColor() == COLOR_BLANC && fd == 7) || (fitxa.getColor() == COLOR_NEGRE && fd == 0)) 
            m_tauler[fd][cd].convertirEnDama();
    }

    actualitzaMovimentsValids();

    if (!esCaptura && potCapturar) 
        m_tauler[fd][cd] = Fitxa();
    else 
        if (!esCaptura) {
        bool bufarFitxa = false;
        for (int i = 0; i < N_FILES; ++i) 
        {
            for (int j = 0; j < N_COLUMNES; ++j)
            {
                if (m_tauler[i][j].getColor() == fitxa.getColor() && (i != fd || j != cd)) 
                {
                    for (int dj = -1; dj <= 1; dj += 2) 
                    {
                        int x = i + direccio;
                        int y = j + dj;
                        int x2 = i + 2 * direccio;
                        int y2 = j + 2 * dj;

                        if (esMovimentValid(x, y) && esMovimentValid(x2, y2) && !esCasellaBuida(x, y) && 
                            m_tauler[x][y].getColor() != fitxa.getColor() && esCasellaBuida(x2, y2) && !bufarFitxa) 
                        {
                            m_tauler[i][j] = Fitxa();
                            dj = 2;
                            bufarFitxa = true;
                        }
                    }
                }
            }
        }
    }

    return true;
}

string Tauler::toString() const
{
    string resultat = "";

    for (int i = N_FILES - 1; i >= 0; --i)
    {
        resultat += char('0' + (i + 1));
        resultat += ": ";

        for (int j = 0; j < N_COLUMNES; ++j)
        {
            const Fitxa& fitxa = m_tauler[i][j];
            char c = '_';

            if (fitxa.getTipus() == TIPUS_NORMAL)
            {
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
    for (int j = 0; j < N_COLUMNES; ++j)
    {
        resultat += char('a' + j);
        resultat += ' ';
    }

    return resultat;
}


Fitxa Tauler::getFitxa(int fila, int columna) const
{
    return m_tauler[fila][columna];
}
