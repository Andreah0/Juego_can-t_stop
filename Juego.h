#ifndef Juego_H
#define Juego_H
#include "Jugador.h"
#include "Tablero.h"
#include <string>
#include <vector>
using namespace std;

class Juego{
  public:
  
    int turno;
    string color;
    vector<Jugador> jugadores;
    
    Tablero tablero;
    
    Juego();
    void iniciarJuego();
    void turnos(int turno);
    bool finalizarJuego(int turno);
    
};
#endif 