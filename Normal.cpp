#include "Normal.h"
#include <iostream>
#include <string>

using namespace std;
//Constructor2
Normal::Normal():Bombas()
{

} //Fin constructor sencillo

//Cosntructor 1
Normal::Normal(int alcance,int cont):Bombas(cont){
    this->alcance=alcance;
}//Fin constructor


int Normal::getAlcance(){
    return alcance;
}

void Normal:: setAlcance(int alcance){

    this->alcance=alcance;

}

Normal::~Normal(){

    cout<<"La instancia de Normal fue eliminada";

}

string Normal::xxxxx(){
    
}

string Normal::getSimbolo()
{
    return simbolo;
}

void Normal::setSimbolo(string simbolo)
{
    this->simbolo = simbolo;
}
