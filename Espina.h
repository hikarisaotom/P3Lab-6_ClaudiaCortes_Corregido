#include <string>
#include <iostream>
#include "Bombas.h"
using namespace std;

#ifndef ESPINA_H
#define ESPINA_H

class Espina: public Bombas{
    private:
        string simbolo="*";
        int cantidad;
    public:
        Espina();
        Espina(string,int,int);
        string getSimbolo();
        void setSimbolo(string);
        int getCantidad();
        void setCantidad(int);
        string xxxxx();
        ~Espina();


};


#endif
