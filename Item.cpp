
#include "Item.h"
#include <iostream>
#include <string>

using namespace std;

Item::Item(int x, int y)
{
    if(x==0&y==0){
        tipo=1;
    }else{
        tipo=2;
    }
    this->x = x;
    this->y = y;
}

Item::Item()
{
}

int Item::getX()
{
    return x;
}

void Item::setX(int x)
{

    this->x = x;
}

int Item::getY()
{
    return y;
}

void Item::setY(int y)
{

    this->y = y;
}

Item::~Item()
{
}

string Item::toString()
{
    if (tipo == 1)
        return "O";
    else
        return " ";
}
