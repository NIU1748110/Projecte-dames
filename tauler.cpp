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

void Tauler::movimentsDames(Fitxa& dama, int fila, int columna)
{
    const int direccions[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

    for (int k = 0; k < 4; ++k)
    {
        int dx = direccions[k][0];
        int dy = direccions[k][1];
        int x = fila + dx;
        int y = columna + dy;
        bool haTrobatEnemic = false;
        bool continuar = esMovimentValid(x, y);

        while (continuar)
        {
            Fitxa casella = m_tauler[x][y];

            if (esCasellaBuida(x, y))
            {
                if (haTrobatEnemic)
                {
                    afegirMoviment(dama, x, y);
                    continuar = false;
                }
                else
                    afegirMoviment(dama, x, y);
            }
            else
            {
                if (esEnemic(dama, x, y) && (!haTrobatEnemic))
                    haTrobatEnemic = true;
                else
                    continuar = false;
            }

            x += dx;
            y += dy;
            continuar = continuar && esMovimentValid(x, y);
        }
    }
}

void Tauler::movimentsFitxesNormals(Fitxa& fitxa, int fila, int columna)
{
    int direccio = 0;
    if (fitxa.getColor() == COLOR_BLANC)
        direccio = 1;
    else 
        direccio = -1;

    for (int dj = -1; dj <= 1; dj += 2) 
    {
        int novaFila = fila + direccio;
        int novaCol = columna + dj;

        if (esMovimentValid(novaFila, novaCol) && esCasellaBuida(novaFila, novaCol)) 
        {
            Moviment m;
            m.afegeixPas(posicioDesDeIndexos(novaFila, novaCol));
            fitxa.afegeixMoviment(m);
        }
    }

    for (int dj = -1; dj <= 1; dj += 2) 
    {
        int filaIntermitja = fila + direccio;
        int colIntermitja = columna + dj;
        int filaDesti = fila + 2 * direccio;
        int colDesti = columna + 2 * dj;

        if (esMovimentValid(filaDesti, colDesti) && esMovimentValid(filaIntermitja, colIntermitja) && !esCasellaBuida(filaIntermitja, colIntermitja) &&
            esEnemic(fitxa, filaIntermitja, colIntermitja) && esCasellaBuida(filaDesti, colDesti)) 
        {
            Moviment m;
            m.afegeixPas(posicioDesDeIndexos(filaDesti, colDesti));
            fitxa.afegeixMoviment(m);

            verificarCapturesMultiples(fitxa, filaDesti, colDesti, m);
        }
    }
}

void Tauler::verificarCapturesMultiples(Fitxa& fitxa, int fila, int columna, Moviment& movimentActual)
{
    int direccio = 0;
    if (fitxa.getColor() == COLOR_BLANC)
        direccio = 1;
    else
        direccio = -1;
    
    for (int dj = -1; dj <= 1; dj += 2) 
    {
        int filaIntermitja = fila + direccio;
        int colIntermitja = columna + dj;
        int filaDesti = fila + 2 * direccio;
        int colDesti = columna + 2 * dj;

        if (esMovimentValid(filaDesti, colDesti) && esMovimentValid(filaIntermitja, colIntermitja) && !esCasellaBuida(filaIntermitja, colIntermitja) &&
            esEnemic(fitxa, filaIntermitja, colIntermitja) && esCasellaBuida(filaDesti, colDesti)) {

            Moviment nouMoviment = movimentActual;
            nouMoviment.afegeixPas(posicioDesDeIndexos(filaDesti, colDesti));
            fitxa.afegeixMoviment(nouMoviment);

            verificarCapturesMultiples(fitxa, filaDesti, colDesti, nouMoviment);
        }
    }
}

bool Tauler::esMovimentValid(int fila, int columna) const
{
    return ((fila >= 0) && (fila < N_FILES) && (columna >= 0) && (columna < N_COLUMNES));
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
    int fila = 7 - origen.getFila();
    int col = origen.getColumna();

    if ((fila >= 0) && (fila < N_FILES) && (col >= 0) && (col < N_COLUMNES))
    {
        Fitxa& f = m_tauler[fila][col];
        for (int i = 0; i < f.getNumMoviments(); ++i)
        {
            Moviment m = f.getMoviment(i);
            if (m.getNumPassos() > 0)
                posicionsPossibles[nPosicions++] = m.getPas(m.getNumPassos() - 1);
        }
    }
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    int fi = 7 - origen.getFila();
    int ci = origen.getColumna();
    int fd = 7 - desti.getFila();
    int cd = desti.getColumna();

    Fitxa fitxa = m_tauler[fi][ci];
    if (fitxa.getTipus() == TIPUS_EMPTY)
        return false;

    actualitzaMovimentsValids();

    int nPos;
    Posicio possibles[16];
    getPosicionsPossibles(origen, nPos, possibles);

    bool movimentTrobat = false;
    for (int i = 0; i < nPos; ++i)
    {
        if(!movimentTrobat)
        {
            if (possibles[i] == desti)
                movimentTrobat = true;
        }
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
        bool esBlancALaPrimeraFila = (fitxa.getColor() == COLOR_BLANC) && (fd == 0);
        bool esNegreALaUltimaFila = (fitxa.getColor() == COLOR_NEGRE) && (fd == 7);

        if (esBlancALaPrimeraFila || esNegreALaUltimaFila)
            m_tauler[fd][cd].convertirEnDama();
    }

    actualitzaMovimentsValids();

    for (int i = 0; i < N_FILES; ++i)
    {
        for (int j = 0; j < N_COLUMNES; ++j)
        {
            bool noEsLaFitxaMoguda = (i != fd) || (j != cd);
            bool esDelMateixColor = m_tauler[i][j].getColor() == fitxa.getColor();
            bool teCaptura = m_tauler[i][j].teCaptura();

            if (noEsLaFitxaMoguda && esDelMateixColor && teCaptura)
                m_tauler[i][j] = Fitxa();
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
