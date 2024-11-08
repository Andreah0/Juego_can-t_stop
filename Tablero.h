#ifndef Tablero_H
#define Tablero_H
#include "Celda.h"
#include <vector>
#include <string>
using namespace std;

class Tablero{
  public:
    int guia[11]{3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    vector<vector<Celda>> tablero;
      
    Tablero();
    void Mostrar();
};
#endif 