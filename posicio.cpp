#include "posicio.h"

Posicio::Posicio(const string& posicio)
{
	if ((posicio[0] != '\0') && (posicio[1] != '\0'))
	{
		m_fila = posicio[0] - 'a';
		m_columna = posicio[1] - '1';
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
	char fila = '1' + m_fila;

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
