#include "Tren.h"
#include <iostream>
#include <string>
#include "Escenario.h"
using namespace std;

Tren::Tren(string nombre) : Escenario(nombre)
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

int Tren::convertirNumero(char le)
{
    int n = 0;

    if (le == '1')
    {
        n = 1;
    }
    else if (le == '2')
    {
        n = 2;
    }
    else if (le == '3')
    {
        n = 3;
    }
    else if (le == '4')
    {
        n = 4;
    }
    else if (le == '5')
    {
        n = 5;
    }
    else if (le == '6')
    {
        n = 6;
    }
    else if (le == '7')
    {
        n = 7;
    }
    if (le == '8')
    {
        n = 8;
    }
    else if (le == '9')
    {
        n = 9;
    }

    return n;

} //Fin de la funcion convertir nuermeo

int Tren::getPX(string palabra)
{
    int x;
    x = convertirNumero(palabra[0]);
    return x;

} //Fin getX

int Tren::getPY(string palabra)
{
    int y = 0;
    y = convertirNumero(palabra[2]);
    return y;
}

vector<string> Tren::getlistapos()
{
    return listapos;
}

vector<int> Tren::getiniciotren()
{
    return postren;
}

Tren::~Tren()
{
    cout << "tren destruido";
}

Item ***Tren::MoverTren(Item ***Matriz)
{
    int x, y;
    for (int i = 0; i < listapos.size(); i++)
    {
        x = getPX(listapos[i]);
        y = getPY(listapos[i]);
    }
}
