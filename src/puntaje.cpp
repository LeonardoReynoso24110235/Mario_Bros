#include "Puntaje.hpp"

void Puntaje::GuardarPuntaje(int puntaje) {
    std::ofstream archivo("puntajes.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << puntaje << std::endl;
        archivo.close();
    }
}

int Puntaje::ObtenerPuntajeMaximo() {
    int maxPuntaje = 0;
    std::ifstream archivo("puntajes.txt");
    int puntaje;
    while (archivo >> puntaje) {
        if (puntaje > maxPuntaje) maxPuntaje = puntaje;
    }
    return maxPuntaje;
}
