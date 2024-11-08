#ifndef Celda_H
#define Celda_H
#include "colors.h"
#include <vector>
#include <string>
using namespace std;

class Celda{
  public:
    string color;
    vector<string> colJugadores;
    
    Celda();
    void marcarPosicion(string colorJugador);
    void limpiarPosicion(string colorJugador);
    void mostrar();
};



#endif