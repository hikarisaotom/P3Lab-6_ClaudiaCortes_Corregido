#include "Invisible.h"
#include <iostream>
#include <string>
//#include "Escenario.h"
using namespace std;

Invisible::Invisible(int aleatorio, int valor, int tipobomba,string S):Escenario(S,tipobomba)
{
    this->valor = valor;
    this->aleatorio = aleatorio;
}


Invisible::~Invisible()
{
}

string Invisible::xxxxx()
{
    return "x";
}
/*Escenario::setNombre(string nombre)
{
    this->nombre = nombre;
}*/
