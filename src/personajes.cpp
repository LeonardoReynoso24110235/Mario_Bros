#include <SFML/Graphics.hpp>
#include "personajes.h"
#include <iostream>

using namespace std;

int vidas = 3; // Inicializar vidas

Personaje::Personaje(sf::Vector2f position, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(position);
    shape.setFillColor(color);
    velocityY = 0;
    isJumping = false;    
}

void Personaje::move(float offsetX) {
    shape.move(offsetX, 0);
}

void Personaje::jump() {
    if (!isJumping) {
        velocityY = -jumpStrength;
        isJumping = true;
    }
}

void Personaje::applyGravity(float gravity, float groundLevel) {
    velocityY += gravity;
    shape.move(0, velocityY);

    if (shape.getPosition().y + shape.getSize().y >= groundLevel) {
        shape.setPosition(shape.getPosition().x, groundLevel - shape.getSize().y);
        velocityY = 0;
        isJumping = false;
    }
}

void Personaje::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Personaje::getBounds() const {
    return shape.getGlobalBounds();
}

bool Personaje::isJumpingOn(const sf::RectangleShape& enemigoShape) const {
    return shape.getPosition().y + shape.getSize().y <= enemigoShape.getPosition().y;
}

void Personaje::perderVida() {
    vidas--;
    if (vidas <= 0) {
        std::cout << "Game Over" << std::endl;
        // Lógica adicional para terminar el juego
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario Bros");

    Personaje character(sf::Vector2f(400, 500), sf::Color::Red);
    const float gravity = 0.2f;
    const float groundLevel = 550.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            character.move(-5.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            character.move(5.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            character.jump();
        }

        character.applyGravity(gravity, groundLevel);

        window.clear();
        character.draw(window);
        window.display();
    }

    return 0;
}
