#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "personajes.h"
#include <box2d/box2d.h>

class Enemigo {
public:
    Enemigo(sf::Vector2f position, sf::Color color);
    void mover(sf::RenderWindow& window, float groundLevel);
    void interactuarConJugador(Personaje& personaje);
    void jump(); // Declarar el método para que el enemigo salte
    bool isEliminado() const;

private:
    sf::RectangleShape shape;
    int direccion; // 1: derecha, 2: salto arriba, 3: izquierda, 4: salto abajo
    int contadorMovimiento;
    bool eliminado;

    sf::Sprite enemigoSprite; // Sprite del enemigo
    std::vector<sf::Texture> texturasMovimiento; // Texturas para la animación
    int frameActual = 0; // Frame actual de la animación
    sf::Clock relojAnimacion; // Reloj para controlar la animación

    // b2World mundoEnemigos = b2World(b2Vec2(0.0f, 10.0f)); // Mundo de Box2D para los enemigos

    sf::SoundBuffer saltoEnemigoBuffer; // Buffer para el sonido de salto
    sf::Sound saltoEnemigoSound; // Sonido de salto del enemigo

    sf::Clock relojSalto; // Reloj para controlar el tiempo entre saltos del enemigo
};

#endif // ENEMIGOS_H
