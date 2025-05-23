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

private:
    sf::RectangleShape shape;
    float velocityY;
    bool isJumping;
    const float jumpStrength = 5.0f;
};

#endif // PERSONAJES_H
