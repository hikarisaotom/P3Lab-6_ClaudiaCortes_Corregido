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
    Item *matriz[11][13];
    vector<Bombas *> bombas;

  public:
    Escenario(string, int);
    Escenario();
    virtual string xxxxx()=0;
    void setNombre(string);

    ~Escenario();
};
#endif
