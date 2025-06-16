// puntaje.h
#ifndef PUNTAJE_HPP
#define PUNTAJE_HPP

#include <fstream>
#include <string>

class Puntaje {
public:
    static void guardarPuntaje(int puntaje);
    static int obtenerPuntajeMaximo();
};

#endif // PUNTAJE_H
