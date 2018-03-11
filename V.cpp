#include "V.h"
#include <iostream>
#include <string>

using namespace std;

V::V(string simbolo,int cont):Bombas(cont){
    this->simbolo=simbolo;
}

V::V(){
}

string V::getSimbolo(){
    return simbolo;
}

void V:: setSimbolo(string simbolo){
    this->simbolo=simbolo;
}

V::~V(){
}

string V::xxxxx()
{
    return simbolo;
}
