#include "posicio.hpp"

Posicio::Posicio(const string& posicio)
{
	if (posicio.length() >= 2) 
	{
		m_columna = posicio[0] - 'a';
		m_fila = 7 - (posicio[1] - '1');
	}
	else 
	{
		m_fila = 0;
		m_columna = 0;
	}
}

string Posicio::toString() const
{
	char columna = 'a' + m_columna;
	char fila = '1' + (7 - m_fila);

	string resultat;
	resultat += columna;
	resultat += fila;

	return resultat;
}

bool Posicio::operator==(const Posicio& posicio) const
{
	bool iguals = true;

	if (m_fila != posicio.m_fila)
		iguals = false;
	if (m_columna != posicio.m_columna)
		iguals = false;

	return iguals;
}

ostream& operator<<(std::ostream& os, const Posicio& posicio) 
{
	os << char('a' + posicio.getColumna()) << char('1' + posicio.getFila());
	return os;
}
