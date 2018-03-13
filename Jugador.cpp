#include "Jugador.h"
#include <iostream>
#include <string>

using namespace std;

Jugador::Jugador(int tipoItem, string nombre, int estado, int tipo, int x, int y) : Item(tipoItem, x, y)
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
    if (tipo == 1)
    {
        simbolo = "*";
    }
    else
    {
        simbolo = "M";
    }
    return simbolo;
}

void Jugador::Inteligenciaartificial(int x, int y, Item ***Matriz)
{
    bool movimiento;

    if (x + 1 <= 10)
    {
        if (Matriz[x + 1][y]->toString() == " ")
        {
            this->setX(x + 1);
        }
    }
    else if (x - 1 >= 0)
    {
        if (Matriz[x - 1][y]->toString() == " ")
        {
            this->setX(x - 1);
        }
    }
    else if (y + 1 <= 12)
    {
        if (Matriz[x][y + 1]->toString() == " ")
        {
            this->setY(y + 1);
        }
    }
    else if (y - 1 >= 0)
    {
        if (Matriz[x][y - 1]->toString() == " ")
        {
            this->setY(y - 1);
        }
    }
} //fin del metodo
