#include "Escenario.h"
#include <string>
#include <iostream>
#include "Item.h"
#include "Bombas.h"
#include "Normal.h"
#include "V.h"
#include "Espina.h"
#include <vector>
using namespace std;

Escenario::Escenario(string nombre)
{
    this->nombre = nombre;
    Matriz = new Item **[11];
    for (int i = 0; i < 11; i++)
    {
        Matriz[i] = new Item *[13];
    }

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            Matriz[i][j] = new Item(0, i, j);
        }
    }

    //Crear los obstaculos
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                Matriz[i][j] = new Item(1, i, j);
            }
        }
    }
}

Item ***Escenario::TraerMatriz()
{
    return Matriz;
}

string Escenario::getNombre()
{
    return nombre;
}

void Escenario::CambiarPosicion(Item *elemento, int i, int j)
{
    Matriz[i][j] = elemento;
}

Escenario::~Escenario()
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            delete Matriz[i][j];
            Matriz[i][j] = NULL;
        }
        delete Matriz[i];
        Matriz[i] = NULL;
    }
    delete[] Matriz;
    Matriz = NULL;
}
void Escenario::generarBomba(int Bomba_tipo)
{
  
    bool bandera = true;
    while (bandera)
    {
        int i = (rand() % 10);
        int j = (rand() % 12);
        if ((i <= 10 && i >= 0) && (j <= 12 && j >= 0))
        {
            Item *Valor_Cambiar = Matriz[i][j];
            if (Valor_Cambiar->toString() == " ")
            {
                Bombas *Bomba_Temp;
                switch (Bomba_tipo)
                {
                case 1:
                {
                    Bomba_Temp = new Normal(1, i, j, 4);
                    break;
                }
                case 2:
                {
                    Bomba_Temp = new Espina(1, i, j, 4, 0);
                    break;
                }

                case 3:
                {
                    Bomba_Temp = new V(1, i, j, 4);
                    break;
                }
                }
                Matriz[i][j] = Bomba_Temp;
                bandera = false;
                break;
            }
        }
    }
}