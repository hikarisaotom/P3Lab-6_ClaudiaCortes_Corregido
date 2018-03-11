#include <string>
#include <iostream>
#include "Item.h"
#include "Bombas.h"
#include "Normal.h"
#include "V.h"
#include "Espina.h"
#include <vector>
using namespace std;

#ifndef ESCENARIO_H
#define ESCENARIO_H

class Escenario
{
  private:
    string nombre;
    Item *** matriz;
    vector<Bombas *> bombas;

  public:
    Escenario(string, int);
    Escenario();
    virtual string xxxxx()=0;
    void setNombre(string);
    void setposicion(int, int, Item *);
    Item* getelemento(int,int);
    void imprimir_matriz();
    void setMatrix(Item *, int, int);
    Item ***getMatrix();
    ~Escenario();
};
#endif
