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

void Escenario::Explotar(int i, int j, int tipobomba)
{
    int alcance;
    int Contador;
    Normal *bomba;
    V *BombaV;
    Espina *BombasE;
    switch (tipobomba)
    {
    case 1:
    {
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
        V_Explote(i, j);
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

void Escenario::V_Explote(int i, int j)
{
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
                    Matriz[i - k][j - k] = new Item(0, i - k, j - k);
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
                    Matriz[i + k][j + k] = new Item(0, i + k, j + k);
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
                    Matriz[i + k][j - k] = new Item(0, i + k, j - k);
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
                    Matriz[i - k][j + k] = new Item(0, i - k, j + k);
            }
            else
            {
                k = 100;
            }
        }
        Matriz[i][j] = new Item(0, i, j);
    }
}

void Escenario::limpiarTren(vector<string> listapos)
{
    for (int i = 0; i < listapos.size(); i++)
    {
        int x, y;
        x = getPX(listapos[i]);
        y = getPY(listapos[i]);
        Matriz[x][y] = new Item(0, x, y);
    }
}

void Escenario::moverboot()
{
    for (int cx = 0; cx < 11; cx++)
    {
        for (int cy = 0; cy < 13; cy++)
        {
            if (Matriz[cx][cy]->toString() == "M")
            {
                int num = 1 + (rand() % 4);
                if (num == 1 && cx - 1 >= 0)
                {
                    if (Matriz[cx - 1][cy]->toString() == " ")
                    {
                        Item *temp = Matriz[cx][cy];
                        Item *temp2 = Matriz[cx - 1][cy];
                        Matriz[cx][cy] = temp2;
                        Matriz[cx - 1][cy] = temp;
                        cy = 100;
                    }
                    //break;
                }
                if (num == 4 && cy + 1 <= 12)
                {
                    if (Matriz[cx][cy + 1]->toString() == " ")
                    {
                        Item *temp = Matriz[cx][cy];
                        Item *temp2 = Matriz[cx][cy + 1];
                        Matriz[cx][cy] = temp2;
                        Matriz[cx][cy + 1] = temp;
                        cy = 100;
                    }
                    //break;
                }
                if (num == 2 && cy - 1 >= 0)
                {
                    if (Matriz[cx][cy - 1]->toString() == " ")
                    {
                        Item *temp = Matriz[cx][cy];
                        Item *temp2 = Matriz[cx][cy - 1];
                        Matriz[cx][cy] = temp2;
                        Matriz[cx][cy - 1] = temp;
                        cy = 100;
                    }
                    //break;
                }
                if (num == 3 && cx + 1 <= 10)
                {
                    if (Matriz[cx + 1][cy]->toString() == " ")
                    {
                        Item *temp = Matriz[cx][cy];
                        Item *temp2 = Matriz[cx + 1][cy];
                        Matriz[cx][cy] = temp2;
                        Matriz[cx + 1][cy] = temp;
                        cy = 100;
                    }
                    //break;
                }
            }
        }
    }
}

int Escenario::convertirNumero(char le)
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

int Escenario::getPX(string palabra)
{
    int x;
    x = convertirNumero(palabra[0]);
    return x;

} //Fin getX

int Escenario::getPY(string palabra)
{
    int y = 0;
    y = convertirNumero(palabra[2]);
    return y;
}
