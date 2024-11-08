#include <iostream>
#include "colors.h"
#include "Tablero.h"
#include "Celda.h"
using namespace std;

Tablero::Tablero(){
    tablero.resize(11);
    for (int i = 0; i < 11; ++i) {
        tablero[i].resize(guia[i], Celda());  
    }
}


void Tablero::Mostrar(){
    cout << "                              TABLERO" << endl;
    for(int i = 0; i < 11; ++i) {
        int espacios = (13 - guia[i]) / 2;
        for (int s = 0; s < espacios; ++s) {
            cout << "     ";
        }
        cout << "|";
            
        for (int j = 0; j < guia[i]; ++j) {
            tablero[i][j].mostrar();  
        }

        cout << endl; 
    }
}        
    