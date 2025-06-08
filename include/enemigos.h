#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "personajes.h"

class Enemigo {
public:
    Enemigo(sf::Vector2f position, sf::Color color);
    void mover(sf::RenderWindow& window, float groundLevel);
    void interactuarConJugador(Personaje& personaje);
    void jump();
    void cargarImagenAleatoria();
    bool isEliminado() const;

private:
    sf::RectangleShape shape;
    sf::Sprite enemigoSprite;
    sf::Texture texturaEnemigo1;
    sf::Texture texturaEnemigo2;
    std::vector<sf::Texture> texturasMovimiento;
    sf::Clock relojAnimacion;
    sf::Clock relojSalto;
    sf::SoundBuffer saltoEnemigoBuffer;
    sf::Sound saltoEnemigoSound;
    int frameActual = 0;
    bool eliminado = false;
    int direccion;
    int contadorMovimiento;
};

#endif // ENEMIGOS_H
