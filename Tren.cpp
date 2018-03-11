#include "Tren.h"
#include <iostream>
#include <string>
#include "Escenario.h"
using namespace std;

Tren::Tren(string nombre, int tipobomba) : Escenario(nombre, tipobomba)
{
    postren.push_back(2);
    postren.push_back(4);
    /*DERECHA */
    listapos.push_back("2-5");
    listapos.push_back("2-6");
    listapos.push_back("2-7");
    listapos.push_back("2-8");
    /*ABAJO*/
    listapos.push_back("3-8");
    listapos.push_back("4-8");
    listapos.push_back("5-8");
    listapos.push_back("6-8");
    listapos.push_back("7-8");
    /*IZQUIERDA*/
    listapos.push_back("7-7");
    listapos.push_back("7-6");
    listapos.push_back("7-5");
    listapos.push_back("7-4");
}

string Tren::xxxxx(){
    return "";
}

    Tren::~Tren()
{
    cout<<"tren destruido";
}