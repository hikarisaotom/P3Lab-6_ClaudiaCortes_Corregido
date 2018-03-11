#include "Escenario.h"
#include <string>
#include <iostream>
//#include "Item.h"
/*#include "Bombas.h"
#include "Normal.h"
#include "V.h"
#include "Espina.h"*/
#include <vector>
using namespace std;

Escenario::Escenario(string nombre, int tipobomba)
{
    this->nombre = nombre;
    if (tipobomba == 1)
    {
      //  bombas.push_back(new Normal() );
    }
    if (tipobomba == 1)
    {
        bombas.push_back(new V());
    }
    if (tipobomba == 1)
    {
        bombas.push_back(new Espina());
    }
}

Escenario::~Escenario()
{
}


void  Escenario::setNombre(string nombre)
{
    this->nombre = nombre;
}

/*string Escenario::toString()
{
    return "x";
}*/
