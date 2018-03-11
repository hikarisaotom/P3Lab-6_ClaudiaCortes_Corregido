#include <string>
#include <iostream>
#include "Item.h"
using namespace std;

#ifndef BOMBAS_H
#define BOMBAS_H

class Bombas : public Item
{

    private:
    int contador;

  public:
    Bombas();
    Bombas(int);
    int getContador();
    void setContador(int);
    virtual string xxxxx()=0;
    ~Bombas();

}; //Fin de la clase

#endif
