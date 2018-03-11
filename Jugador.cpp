#include "Jugador.h"
#include <iostream>
#include <string>

using namespace std;

Jugador::Jugador(string nombre, int estado, int tipo)
{
    this->nombre = nombre;
    this->estado = estado;
    this->tipo = tipo;
}
Jugador::Jugador()
{
}

string Jugador::getNombre()
{
    return nombre;
}

void Jugador::setNombre(string nombre)
{

    this->nombre = nombre;
}

int Jugador::getEstado()
{
    return estado;
}

void Jugador::setEstado(int estado)
{

    this->estado = estado;
}

int Jugador::getTipo()
{
    return tipo;
}

void Jugador::setTipo(int tipo)
{

    this->tipo = tipo;
}

Jugador::~Jugador()
{
}

string Jugador::toString()
{
    return simbolo;
}