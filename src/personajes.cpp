#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "personajes.h"
#include <iostream>

using namespace std;

int vidas = 3; // Inicializar vidas

sf::Texture personajeTexture;
sf::Sprite personajeSprite;
std::vector<sf::Texture> texturasMovimientoPersonaje;
int frameActualPersonaje = 0;
sf::Clock relojAnimacionPersonaje;

Personaje::Personaje(sf::Vector2f position, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(position);
    shape.setFillColor(color);
    velocityY = 0;
    isJumping = false;

    // Cargar texturas para animaciones del personaje
    for (int i = 1; i <= 4; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/personaje_" + std::to_string(i) + ".png")) {
            std::cerr << "Error al cargar la textura personaje_" << i << ".png\n";
        }
        texturasMovimientoPersonaje.push_back(textura);
    }

    personajeSprite.setTexture(texturasMovimientoPersonaje[0]);
    personajeSprite.setPosition(position);

    // Cargar sonidos
    if (!saltoBuffer.loadFromFile("assets/sonidos/salto.mp3")) {
        std::cerr << "Error al cargar el sonido de salto.\n";
    }
    saltoSound.setBuffer(saltoBuffer);

    if (!golpearBuffer.loadFromFile("assets/sonidos/golpear.mp3")) {
        std::cerr << "Error al cargar el sonido de golpear.\n";
    }
    golpearSound.setBuffer(golpearBuffer);

    if (!correrBuffer.loadFromFile("assets/sonidos/correr.mp3")) {
        std::cerr << "Error al cargar el sonido de correr.\n";
    }
    correrSound.setBuffer(correrBuffer);
}

void Personaje::move(float offsetX) {
    personajeSprite.move(offsetX, 0);
    // Reproducir sonido de correr
    if (correrSound.getStatus() != sf::Sound::Status::Playing) {
        correrSound.play();
    }
    // Actualizar animación
    if (relojAnimacionPersonaje.getElapsedTime().asSeconds() > 0.2f) {
        frameActualPersonaje = (frameActualPersonaje + 1) % texturasMovimientoPersonaje.size();
        personajeSprite.setTexture(texturasMovimientoPersonaje[frameActualPersonaje]);
        relojAnimacionPersonaje.restart();
    }
}

void Personaje::jump() {
    if (!isJumping) {
        saltoSound.play();
        velocityY = -jumpStrength;
        isJumping = true;
    }
}

void Personaje::applyGravity(float gravity, float groundLevel) {
    velocityY += gravity;
    personajeSprite.move(0, velocityY);

    if (personajeSprite.getPosition().y + personajeSprite.getGlobalBounds().height >= groundLevel) {
        personajeSprite.setPosition(personajeSprite.getPosition().x, groundLevel - personajeSprite.getGlobalBounds().height);
        velocityY = 0;
        isJumping = false;
    }
}

void Personaje::draw(sf::RenderWindow& window) {
    window.draw(personajeSprite);
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

void Personaje::eliminarEnemigo() {
    golpearSound.play();
    // Lógica para eliminar enemigo
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