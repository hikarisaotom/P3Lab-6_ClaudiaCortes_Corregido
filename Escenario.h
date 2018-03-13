#include <string>
#include <iostream>
#include <vector>
#include <vector>
#include "Item.h"
#include "Bombas.h"
#include "Normal.h"
#include "V.h"
#include "Espina.h"

using namespace std;

#ifndef ESCENARIO_H
#define ESCENARIO_H

class Escenario
{
private:
  string nombre;
  Item ***Matriz;
  vector<Bombas *> listaBombas;

public:
  Escenario(string);
  virtual string getNombre();
  void CambiarPosicion(Item *, int, int);
  Item ***TraerMatriz();
  void CrearBomba(int);
  void generarBomba(int);
  void Explotar(int, int, int);
  void V_Explote(int, int);
  void moverboot();
  int convertirNumero(char);
  int getPX(string);
  int getPY(string);
  void limpiarTren(vector<string>);

  ~Escenario();
};

#endif
