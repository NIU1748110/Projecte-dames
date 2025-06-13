#include "cuaMoviments.hpp"

void CuaMoviments::nouMoviment(Posicio origen, Posicio desti)
{
	Moviment moviment;
	moviment.afegeixPas(origen);
	moviment.afegeixPas(desti);
	m_moviments.push(moviment);
}

#include <fstream>

void CuaMoviments::inicialitzaMoviments(const string& nomFitxer)
{
	std::ofstream fitxer(nomFitxer);

	if (!fitxer.is_open())
		return;

	while (!m_moviments.empty())
	{
		Moviment m = m_moviments.front();
		m_moviments.pop();

		if (m.getNumPassos() >= 2)
		{
			fitxer << m.getPas(0).toString() << " " << m.getPas(1).toString() << endl;
		}
	}

	fitxer.close();
}

#include <fstream>

void CuaMoviments::carregaDeFitxer(const std::string& nomFitxer)
{
	std::ifstream fitxer(nomFitxer);
	if (!fitxer.is_open())
		return;

	std::string origenStr, destiStr;
	while (fitxer >> origenStr >> destiStr)
	{
		Posicio origen(origenStr);
		Posicio desti(destiStr);
		Moviment m;
		m.afegeixPas(origen);
		m.afegeixPas(desti);
		m_moviments.push(m);
	}

	fitxer.close();
}

void CuaMoviments::getOrigenDesti(Posicio& origen, Posicio& desti)
{
	origen = m_moviments.front().getPas(0);
	desti = m_moviments.front().getPas(1);
	m_moviments.pop();
}
