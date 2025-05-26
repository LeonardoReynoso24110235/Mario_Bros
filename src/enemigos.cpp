#include <iostream>
#include <SFML/Graphics.hpp>
#include "enemigos.h"
#include "personajes.h"

// Implementación de las funciones relacionadas con los enemigos
void Enemigo::mover(sf::RenderWindow& window, float groundLevel) {
    if (direccion == 1) {
        shape.move(4.0f, 0);
        contadorMovimiento++;
        if (contadorMovimiento >= 4) {
            direccion = 2; // Cambia a saltar
            contadorMovimiento = 0;
        }
    } else if (direccion == 2) {
        shape.move(0, -3.0f);
        contadorMovimiento++;
        if (contadorMovimiento >= 3) {
            direccion = 3; // Cambia a moverse a la izquierda
            contadorMovimiento = 0;
        }
    } else if (direccion == 3) {
        shape.move(-4.0f, 0);
        contadorMovimiento++;
        if (contadorMovimiento >= 4) {
            direccion = 4; // Cambia a saltar
            contadorMovimiento = 0;
        }
    } else if (direccion == 4) {
        shape.move(0, 3.0f);
        contadorMovimiento++;
        if (contadorMovimiento >= 3) {
            direccion = 1; // Vuelve a moverse a la derecha
            contadorMovimiento = 0;
        }
    }

    // Asegura que el enemigo no caiga por debajo del suelo
    if (shape.getPosition().y + shape.getSize().y > groundLevel) {
        shape.setPosition(shape.getPosition().x, groundLevel - shape.getSize().y);
    }

    window.draw(shape);
}

void Enemigo::interactuarConJugador(Personaje& personaje) {
    if (shape.getGlobalBounds().intersects(personaje.getBounds())) {
        if (personaje.isJumpingOn(shape)) {
            eliminado = true; // Elimina al enemigo
        } else {
            personaje.perderVida(); // Quita una vida al personaje
        }
    }
}

Enemigo::Enemigo(sf::Vector2f position, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(position);
    shape.setFillColor(color);
    direccion = 1;
    contadorMovimiento = 0;
    eliminado = false;
}

bool Enemigo::isEliminado() const {
    return eliminado;
}
