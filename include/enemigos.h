#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <SFML/Graphics.hpp>
#include "personajes.h"

class Enemigo {
public:
    Enemigo(sf::Vector2f position, sf::Color color);
    void mover(sf::RenderWindow& window, float groundLevel);
    void interactuarConJugador(Personaje& personaje);
    bool isEliminado() const;

private:
    sf::RectangleShape shape;
    int direccion; // 1: derecha, 2: salto arriba, 3: izquierda, 4: salto abajo
    int contadorMovimiento;
    bool eliminado;
};

#endif // ENEMIGOS_H
