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
                listaBombas.push_back(Bomba_Temp);
                bandera = false;
                break;
            }
        }
    }
}

void Escenario::CrearBomba(int tipobomba)
{
    Bombas *Bomba_Temp;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (Matriz[i][j]->toString() == "*")
            {
                if (j + 1 <= 12)
                {
                    if (Matriz[i][j + 1]->toString() == " ")
                    {
                        if (tipobomba == 1)
                        {
                            Bomba_Temp = new Normal(1, i, j + 1, 4);
                        }
                        if (tipobomba == 2)
                        {
                            Bomba_Temp = new Espina(1, i, j + 1, 4, 0);
                        }
                        if (tipobomba == 3)
                        {
                            Bomba_Temp = new V(1, i, j + 1, 4);
                        }
                        Matriz[i][j + 1] = Bomba_Temp;
                        listaBombas.push_back(Bomba_Temp);
                        break;
                    }
                }
                if (i + 1 <= 10)
                {
                    if (Matriz[i + 1][j]->toString() == " ")
                    {
                        if (tipobomba == 1)
                        {
                            Bomba_Temp = new Normal(1, i + 1, j, 4);
                        }
                        if (tipobomba == 2)
                        {
                            Bomba_Temp = new Espina(1, i + 1, j, 4, 0);
                        }
                        if (tipobomba == 3)
                        {
                            Bomba_Temp = new V(1, i + 1, j, 4);
                        }
                        Matriz[i + 1][j] = Bomba_Temp;
                        listaBombas.push_back(Bomba_Temp);
                        break;
                    }
                }
                if (j - 1 >= 0)
                {
                    if (Matriz[i][j - 1]->toString() == " ")
                    {
                        if (tipobomba == 1)
                        {
                            Bomba_Temp = new Normal(1, i, j - 1, 4);
                        }
                        if (tipobomba == 2)
                        {
                            Bomba_Temp = new Espina(1, i, j - 1, 4, 0);
                        }
                        if (tipobomba == 3)
                        {
                            Bomba_Temp = new V(1, i, j - 1, 4);
                        }
                        Matriz[i][j - 1] = Bomba_Temp;
                        listaBombas.push_back(Bomba_Temp);
                        break;
                    }
                }
                if (i - 1 >= 0)
                {
                    if (Matriz[i - 1][j]->toString() == " ")
                    {
                        if (tipobomba == 1)
                        {
                            Bomba_Temp = new Normal(1, i - 1, j, 4);
                        }
                        if (tipobomba == 2)
                        {
                            Bomba_Temp = new Espina(1, i - 1, j, 4, 0);
                        }
                        if (tipobomba == 3)
                        {
                            Bomba_Temp = new V(1, i - 1, j, 4);
                        }
                        Matriz[i - 1][j] = Bomba_Temp;
                        listaBombas.push_back(Bomba_Temp);
                        break;
                    }
                }
            }
        }
    }
}

void Escenario::Explotar(int i, int j,int tipobomba)
{
    int alcance;
    int Contador;
    Normal *bomba;
    V *BombaV;
    Espina *BombasE;
    switch (tipobomba)
    {
    case 1:{
        bomba = dynamic_cast<Normal *>(Matriz[i][j]);
        bomba->setContador(bomba->getContador() - 1);
        Contador = bomba->getContador();
        alcance = bomba->getAlcance();
        break;
    }
    case 2:
    {
        Espina *BombasE;
        BombasE = dynamic_cast<Espina *>(Matriz[i][j]);
        BombasE->setContador(BombasE->getContador() - 1);
        alcance = 100;
        Contador = BombasE->getContador();
         break;
    }
    case 3:
    {
     /*   V *BombaV;
        BombaV = dynamic_cast<V *>(Matriz[i][j]);
        BombaV->setContador(BombaV->getContador() - 1);
       alcance = 100;
        break;*/
        V_Explote(i,j);
    }
}
    
  
   

    if (Contador == 0)
    {
        if (i - alcance >= 0)
            for (int k = 1; k <= alcance; k++)
            {
                if (Matriz[i - k][j]->toString() != "O")
                    Matriz[i - k][j] = new Item(0, i - k, j);
                else
                    k = 100;
            }
        if (i + alcance <= 10)
            for (int k = 1; k <= alcance; k++)
            {
                if (Matriz[i + k][j]->toString() != "O")
                    Matriz[i + k][j] = new Item(0, i + k, j);
                else
                    k = 100;
            }

        if (j - alcance >= 0)
            for (int k = 1; k <= alcance; k++)
            {
                if (Matriz[i][j - k]->toString() != "O")
                    Matriz[i][j - k] = new Item(0, i, j - k);
                else
                    k = 100;
            }

        if (j + alcance <= 12)
            for (int k = 1; k <= alcance; k++)
            {
                if (Matriz[i][j + k]->toString() != "O")
                    Matriz[i][j - k] = new Item(0, i, j + k);
                else
                    k = 100;
            }
        Matriz[i][j] = new Item(0, i, j);
    }
}

void Escenario::V_Explote(int i, int j){
    V *bomba;
    bomba = dynamic_cast<V *>(Matriz[i][j]);
    bomba->setContador(bomba->getContador() - 1);
    int alcance = 100;
    if (bomba->getContador() == 0)
    {
        for (int k = 1; k <= alcance; k++)
        {
            if ((i - k >= 0) && (j - k >= 0))
            {
                if (Matriz[i - k][j - k]->toString() != "O")
                   Matriz[i - k][j - k]=new Item(0, i - k, j - k);
            }
            else
            {
                k = 100;
            }
        }

        for (int k = 1; k <= alcance; k++)
        {
            if ((i + k <= 10) && (j + k <= 12))
            {

                if (Matriz[i + k][j + k]->toString() != "O")
                   Matriz[i + k][j + k]=new Item(0, i + k, j + k);
            }
            else
            {
                k = 100;
            }
        }

        for (int k = 1; k <= alcance; k++)
        {
            if ((j - k >= 0) && (i + k <= 10))
            {
                if (Matriz[i + k][j - k]->toString() != "O")
                  Matriz[i + k][j - k]=new Item(0, i + k, j - k);
            }
            else
            {
                k = 100;
            }
        }

        for (int k = 1; k <= alcance; k++)
        {
            if ((j + k <= 12) && (i - k >= 0))
            {
                if (Matriz[i - k][j + k]->toString() != "O")
                    Matriz[i - k][j + k]=new Item(0, i - k, j + k);

            }
            else
            {
                k = 100;
            }
        }
        Matriz[i][j]=new Item(0, i, j);
    }
}

void Escenario::limpiarTren(){
    
}
