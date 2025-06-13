#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Personaje; // Declaración adelantada

class Enemigo {
private:
    sf::Sprite enemigoSprite;
    std::vector<sf::Texture> texturasMovimiento;
    sf::Texture texturaEnemigo1, texturaEnemigo2;

    sf::SoundBuffer saltoEnemigoBuffer;
    sf::Sound sonidoSalto;

    int direccion; // -1: izquierda, 1: derecha
    bool estaEliminado;

    int frameActual;
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

    // Getter para el sprite, útil para colisiones o debug
    sf::FloatRect getBounds() const { return enemigoSprite.getGlobalBounds(); }
    bool estaActivo() const { return !estaEliminado; }
};

#endif // ENEMIGOS_H
