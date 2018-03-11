#include <string>
#include <iostream>
#include "Bombas.h"
using namespace std;

#ifndef NORMAL_H
#define NORMAL_H
class Normal : public Bombas
{
  private:
    string simbolo = "N";
    int alcance;

  public:
    Normal();
    Normal(int, int);
    //metodos accersores / mutadores
    int getAlcance();
    void setAlcance(int);
    string xxxxx();
    //Destructor
    ~Normal();
    string getSimbolo();
    void setSimbolo(string);
};

#endif
/*#include <string>
#include <iostream>
#include "Bombas.h"

using namespace std;

#ifndef NORMAL_H
#define NORMAL_H


//Inicio clase
class Normal: public Bombas{

    //Atributos
    private:
        int alcance;


    //metodos publicos
    public:
        //prototipos de metodos
        //constructor
        Normal();
        Normal(int,int);

        //metodos accersores / mutadores
        int getAlcance();
        void setAlcance(int);
        string xxxxx();
            //Destructor
            ~Normal();

};//Fin de la clase


#endif*/
