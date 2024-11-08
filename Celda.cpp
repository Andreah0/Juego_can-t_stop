#include <iostream>
#include "colors.h"
#include "Celda.h"
#include <vector>
#include <string>
using namespace std;

Celda::Celda(){
    this->color=RESET;
    colJugadores.resize(4, RESET);
}

void Celda::marcarPosicion(string colorJugador){
    for (int i = 0; i < colJugadores.size(); i++) {
        if (colJugadores[i] == RESET) { 
            colJugadores[i] = colorJugador;
            break;
        }
    }
}

void Celda::limpiarPosicion(string colorJugador) {
    for (int i = 0; i < colJugadores.size(); i++) {
        if (colJugadores[i] == colorJugador) {  
            colJugadores[i] = RESET;  
            break;
            }
        }
    }

void Celda::mostrar(){
    for (int i = 0; i < colJugadores.size(); i++) {
        cout << colJugadores[i] << "x" << RESET;  
    }
    cout << RESET << "|";
}