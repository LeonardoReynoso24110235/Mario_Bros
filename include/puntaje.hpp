#ifndef PUNTAJE_HPP
#define PUNTAJE_HPP

#include <fstream>
#include <string>

class Puntaje {
public:
    static void GuardarPuntaje(int puntaje);
    static int ObtenerPuntajeMaximo();
};

#endif 
