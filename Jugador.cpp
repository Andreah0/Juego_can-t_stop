#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <random>
#include "colors.h"
#include "Jugador.h"
#include "Tablero.h"
using namespace std;


Jugador::Jugador(string color){
    this->color=obtenerColor(color);
    this->dados.resize(4);
    for(int i=0; i<12; i++){
        avances[i]=-1;
    }
}

void Jugador::iniciarTurno(){
    for(int i=0; i<11; i++){
        avancesTemporales[i] = avances[i];
    }
}

string Jugador::obtenerColor(string color){
    map<string,string> colors;
    colors["rojo"]=RED;
    colors["azul"]=BLUE;
    colors["amarillo"]=YELLOW;
    colors["verde"]=GREEN;
    
    return colors[color];
}

void Jugador::tirarDados(){
    dados.clear(); 
    for(int i=0; i<4; i++){
        dados.push_back(1 + rand() % 6);
        cout << i+1 <<".Dado" << " (" << dados[i] << ") ";
    }
}

pair<int,int> Jugador::escogerParejas(){
    
    vector<pair<int, int>> combinacionesPosibles;
    combinacionesPosibles.push_back({dados[0]+dados[1],dados[2]+dados[3]});
    combinacionesPosibles.push_back({dados[0]+dados[2],dados[1]+dados[3]});
    combinacionesPosibles.push_back({dados[0]+dados[3],dados[1]+dados[2]});
    
    
    cout << "Elige una combinacion: " << endl;
    for(int i=0; i<combinacionesPosibles.size(); i++){
        cout << endl <<  i+1 << ".(" << combinacionesPosibles[i].first << ", " << combinacionesPosibles[i].second << ") ";
    }
    int rta;
    cin >> rta;
    
    while (rta < 1 || rta > combinacionesPosibles.size()) {
        cout << "Elección no válida. Introduce de nuevo: ";
        cin >> rta;
    }
    
    return combinacionesPosibles[rta-1];
}
void Jugador::ponerMarcador(Tablero* tablero, pair<int, int> filas) {
    int fila1 = filas.first - 2;
    int fila2 = filas.second - 2;

    // Contar cuántas filas tienen marcadores temporales
    int filasConMarcador = 0;
    for (int i = 0; i < 11; i++) {
        if (avancesTemporales[i] != avances[i]) {
            filasConMarcador++;
        }
    }

    // Caso cuando tiene exactamente 2 filas marcadas y ambas nuevas filas no tienen marcador
    if (filasConMarcador == 2 &&
        avancesTemporales[fila1] == avances[fila1] && avancesTemporales[fila2] == avances[fila2]) {
        
        int eleccion;
        cout << "Elige una fila para marcar: 1. Fila " << fila1 + 2 
             << " 2. Fila " << fila2 + 2 << endl;
        cin >> eleccion;
        
        if (eleccion == 1) {
            avanzarMarcador(tablero, fila1);
        } else {
            avanzarMarcador(tablero, fila2);
        }
        return;
    }

    // Caso cuando ya tiene 3 filas marcadas
    if (filasConMarcador == 3) {
        // Si ambas filas son iguales, solo avanza en una
        if (fila1 == fila2) {
            if (avancesTemporales[fila1] != avances[fila1]) {
                avanzarMarcador(tablero, fila1);
                avanzarMarcador(tablero, fila1);
            }
        } else {
            // Avanza en las filas ya marcadas, sin marcar una nueva
            if (avancesTemporales[fila1] != avances[fila1]) {
                avanzarMarcador(tablero, fila1);
            }
            if (avancesTemporales[fila2] != avances[fila2]) {
                avanzarMarcador(tablero, fila2);
            }
        }
        return;
    }

    // Caso general: avanzar o marcar si no hay 3 filas marcadas aún
    avanzarMarcador(tablero, fila1);
    if (fila1 != fila2) {
        avanzarMarcador(tablero, fila2);
    }
}


void Jugador::avancesJugador(int fila){
    if(fila>=0 && fila<=11){
        avancesTemporales[fila]+=1;
    } 
}

void Jugador::avanzarMarcador(Tablero* tablero, int fila) {
    if (avancesTemporales[fila] >= 0) {
        tablero->tablero[fila][avancesTemporales[fila]].limpiarPosicion(color);
        avancesJugador(fila);
    } else {
        avancesJugador(fila);
    }
    
    tablero->tablero[fila][avancesTemporales[fila]].marcarPosicion(color);
}


bool Jugador::verificarTurno(pair<int, int> filas) {
    int fila1 = filas.first - 2;
    int fila2 = filas.second - 2;

    // Contar filas que tienen marcador
    int filasConMarcador = 0;
    for (int i = 0; i < 11; i++) {
        if (avancesTemporales[i] != avances[i]) {
            filasConMarcador++;
        }
    }

    // Si ya tiene 3 filas marcadas
    if (filasConMarcador == 3) {
        bool fila1YaMarcada = (fila1 >= 0 && avancesTemporales[fila1] != avances[fila1]);
        bool fila2YaMarcada = (fila2 >= 0 && avancesTemporales[fila2] != avances[fila2]);

        if (fila1 == fila2) {
            // Si la fila seleccionada ya está marcada, puede avanzar en esa fila sin marcar una nueva
            return !fila1YaMarcada;
        } else {
            // Si ambas filas seleccionadas son nuevas, pierde el turno
            if (!fila1YaMarcada && !fila2YaMarcada) {
                return true;
            }
            // Si al menos una fila ya está marcada, puede continuar
            return false;
        }
    }

    // Si tiene exactamente 2 filas marcadas o menos, puede continuar
    return false;
}



void Jugador::reiniciarAvances(Tablero* tablero) {
    for(int i = 0; i < 11; i++) {
        // Si hubo un movimiento en esta fila durante el turno
        if(avancesTemporales[i] != avances[i]) {
            // Limpiar la posición actual
            if(avancesTemporales[i] >= 0) {
                tablero->tablero[i][avancesTemporales[i]].limpiarPosicion(color);
            }
            
            // Restaurar la posición anterior si había una
            if(avances[i] >= 0) {
                tablero->tablero[i][avances[i]].marcarPosicion(color);
            }
        }
    }
}

void Jugador::actualizarAvances(){
    for(int i = 0; i < 11; i++) {
        avances[i]=avancesTemporales[i];
    }
}

bool Jugador::filasCompletadas() {
    int guia[11] = {3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    int filaComple = 0;

    for (int i = 0; i < 11; i++) {
        if (avances[i] >= guia[i]) {
            filaComple++;
        }
        if (filaComple >= 3) {
            return true;
        }
    }
    return false;
}
