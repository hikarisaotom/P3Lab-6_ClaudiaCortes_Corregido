#include "Escenario.h"
#include <string>
#include <iostream>
//#include "Item.h"
/*#include "Bombas.h"
#include "Normal.h"
#include "V.h"
#include "Espina.h"*/
#include <vector>
#include <ncurses.h>
using namespace std;

Escenario::Escenario(string nombre, int tipobomba)
{
    imprimir_matriz();
    this->nombre = nombre;
    if (tipobomba == 1)//Normal
    {
        bombas.push_back(new V());
    }
    if (tipobomba == 2)//V
    {
        bombas.push_back(new V());
    }
    if (tipobomba == 3)//Espina
    {
        bombas.push_back(new Espina());
    }
    
}

Escenario::~Escenario()
{
}
void Escenario::setMatrix(Item *elemento, int i, int j)
{
    matriz[i][j] = elemento;
}
Item *** Escenario::getMatrix()
{
    return matriz;
}

void  Escenario::setNombre(string nombre)
{
    this->nombre = nombre;
}
void Escenario::setposicion(int x, int y, Item *Objeto)
{
    matriz[x][y]=Objeto;
}

Item* Escenario:: getelemento(int x, int y){
    return matriz[x][y];
}
void Escenario::imprimir_matriz(){
  matriz = new Item **[11];
  for (int i = 0; i < 11; i++)
  {
      matriz[i] = new Item *[13];
  }

  for (int i = 0; i < 11; i++)
  {
      for (int j = 0; j < 13; j++)
      {
          matriz[i][j] = new Item(i, j);
      }
  }

  for (int i = 0; i < 11; i++)
  {
      for (int j = 0; j < 13; j++)
      {
          matriz[i][j] = new Item(i, j);
      }
  }
}
/*string Escenario::toString()
{
    return "x";
}*/
