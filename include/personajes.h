#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <SFML/Graphics.hpp>

class Personaje {
public:
    Personaje(sf::Vector2f position, sf::Color color);
    void move(float offsetX);
    void jump();
    void applyGravity(float gravity, float groundLevel);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const; // Devuelve los límites del personaje
    bool isJumpingOn(const sf::RectangleShape& enemigoShape) const; // Verifica si está saltando sobre un enemigo
    void perderVida(); // Reduce las vidas del personaje

private:
    sf::RectangleShape shape;
    float velocityY;
    bool isJumping;
    const float jumpStrength = 5.0f;
    int vidas = 3; // Número de vidas del personaje
};

#endif // PERSONAJES_H
