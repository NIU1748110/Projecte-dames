#ifndef CUAMOVIMENTS_H
#define CUAMOVIMENTS_H
#include <string>
#include "moviment.hpp"
#include <queue>

class CuaMoviments
{
public:
	void nouMoviment(Posicio origen, Posicio desti);
	void inicialitzaMoviments(const string& nomFitxer);
	void carregaDeFitxer(const std::string& nomFitxer);
	void getOrigenDesti(Posicio& origen, Posicio& desti);
	bool buida() { return m_moviments.empty(); }

private:
	queue<Moviment> m_moviments;
};


#endif
