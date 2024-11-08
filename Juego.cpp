#include <iostream>
#include "colors.h"
#include "Juego.h"
#include "Tablero.h"
#include "Jugador.h"
#include <string>
#include <vector>
using namespace std;

Juego::Juego() {
    srand(time(0)); //cada vez que se crea un objeto se incializa el genarador de numeros
	vector<string> colores= {"rojo", "azul", "verde", "amarillo"};
	for(int i=0; i<4; i++) {
		jugadores.push_back(Jugador(colores[i]));
		cout << "Jugador " << i+1 << ": " << colores[i];
	}
}

void Juego::iniciarJuego() {
	while(!finalizarJuego(turno)) {
		for (int i = 0; i < jugadores.size(); i++) {
			cout << "Turno del jugador " << jugadores[i].color << endl;
			turnos(i);
		}
	}
}

void Juego::turnos(int turno) {

	bool continuarTurno=true;
	jugadores[turno].iniciarTurno();

	while(continuarTurno) {
    	jugadores[turno].tirarDados();
    	pair<int, int> filas= jugadores[turno].escogerParejas();
    	jugadores[turno].ponerMarcador(&tablero, filas);
        tablero.Mostrar();
        
        if (jugadores[turno].verificarPierdeTurno(filas)) {
            cout << "El jugador pierde el turno.\n";
            jugadores[turno].reiniciarAvances(&tablero);
            return;
        }
        int rta;
        cout << "Quiere continuar con el turno? (1. Si / 0. No)";cin >> rta;
        if(rta!=1){
            jugadores[turno].actualizarAvances();
            break;
        }
	}
}


bool Juego::finalizarJuego(int turno) {
    return jugadores[turno].filasCompletadas();
}
