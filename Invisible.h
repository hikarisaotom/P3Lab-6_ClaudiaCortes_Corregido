#include <string>
#include <iostream>
#include "Item.h"
#include "Escenario.h"
#include "Bombas.h"
#include <vector>
using namespace std;

#ifndef INVISIBLE_H
#define INVISIBLE_H

class Invisible : public Escenario
{
  private:
    /*string nombre;
    Item *matriz[11][13];
    vector<Bombas *> bombas;*/
    int aleatorio;
    int valor;

  public:
    Invisible(int, int, int,string); /*ale,valor,tipo bomba,string*/
    //Invisible();
    string xxxxx();
        //void setNombre(string);

        ~Invisible();
};
#endif
