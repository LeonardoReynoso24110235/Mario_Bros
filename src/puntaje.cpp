// puntaje.cpp
#include "puntaje.hpp"

void Puntaje::guardarPuntaje(int puntaje) {
    std::ofstream archivo("puntajes.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << puntaje << std::endl;
        archivo.close();
    }
}

int Puntaje::obtenerPuntajeMaximo() {
    int maxPuntaje = 0;
    std::ifstream archivo("puntajes.txt");
    int puntaje;
    while (archivo >> puntaje) {
        if (puntaje > maxPuntaje) maxPuntaje = puntaje;
    }
    return maxPuntaje;
}
