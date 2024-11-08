#ifndef Jugador_H
#define Jugador_H
#include <string>
#include <vector>
#include <utility>
#include "Tablero.h"
using namespace std;

class Jugador{
    public:
        string color;
        vector<int> dados;
        int avances[11];
        int avancesTemporales[11];
        
        Jugador(string color);
        string obtenerColor(string color);
        void iniciarTurno();
        void tirarDados();
        pair<int,int> escogerParejas();
        void ponerMarcador(Tablero* tablero, pair<int, int> filas);
        void avancesJugador(int fila);
        void avanzarMarcador(Tablero* tablero, int fila);
        bool verificarPierdeTurno(pair<int, int> filas);
        void actualizarAvances();
        void reiniciarAvances(Tablero* tablero);
        bool filasCompletadas();
        
};
#endif 
