#ifndef POSICIO_H
#define POSICIO_H
#include <string>
#include <iostream>
using namespace std;

class Posicio
{
public:
	Posicio() : m_fila(0), m_columna(0) {}
	Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}
	Posicio(const string& posicio);
	int getFila() const { return m_fila; }
	int getColumna() const { return m_columna; }
	void setFila(int fila) { m_fila = fila; }
	void setColumna(int columna) { m_columna = columna; }
	string toString() const;
	bool operator==(const Posicio& posicio) const;

private:
	int m_columna;
	int m_fila;
};

ostream& operator<<(std::ostream& os, const Posicio& posicio);

#endif
