#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <SFML/Graphics.hpp>

class Personaje {
public:
    Personaje(sf::Vector2f position, sf::Color color); // Constructor original
    Personaje(sf::Vector2f position); // Constructor adicional para solo la posición

    void moverIzquierda();
    void moverDerecha();
    void saltar();
    int getVidas() const;
    void perderVida();
    void dibujar(sf::RenderWindow& window);

    bool isJumpingOn(sf::RectangleShape& enemy); // Método para verificar si el personaje está saltando sobre el enemigo
    sf::FloatRect getBounds() const; // Método para obtener las dimensiones del personaje

private:
    sf::RectangleShape personajeShape;
    sf::Sprite personajeSprite;
    int vidas;
};

#endif // PERSONAJES_H