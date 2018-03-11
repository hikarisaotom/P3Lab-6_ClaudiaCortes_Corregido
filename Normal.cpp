#include "Normal.h"
#include <iostream>
#include <string>

using namespace std;

//Cosntructor 1
Normal::Normal(int alcance,int cont):Bombas(cont){
    this->alcance=alcance;
}//Fin constructor

//Constructor2
Normal::Normal(){

}//Fin constructor sencillo

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
