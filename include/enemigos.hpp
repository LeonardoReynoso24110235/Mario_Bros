#ifndef ENEMIGOS_HPP
#define ENEMIGOS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Personaje;  // Declaración adelantada

class Enemigo {
private:
    sf::Sprite enemigoSprite;
    std::vector<sf::Texture> texturasMovimiento;
    sf::Texture texturaEnemigo1, texturaEnemigo2;

    sf::SoundBuffer saltoEnemigoBuffer;
    sf::Sound sonidoSalto;

    int direccion = -1; // -1: izquierda, 1: derecha
    int frameActual = 0;
    bool estaEliminado = false;
    sf::Clock relojAnimacion;

public:
    // Constructores
    Enemigo(sf::Vector2f position, sf::Color color, float groundLevel);
    Enemigo(sf::Vector2f position, sf::Color color);
    Enemigo(sf::Vector2f position);

    // Comportamiento
    void mover(sf::RenderWindow& window, float groundLevel);
    void interactuarConJugador(Personaje& personaje);
    void verificarColisionConPersonaje(Personaje& personaje);
    void eliminar();
    void dibujar(sf::RenderWindow& window);

    // Accesores
    sf::FloatRect getBounds() const;
    bool estaActivo() const;
};

#endif // ENEMIGOS_H
