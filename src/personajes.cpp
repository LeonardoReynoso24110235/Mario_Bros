#include "personajes.h"
#include <SFML/Graphics.hpp>

Personaje::Personaje(sf::Vector2f position, sf::Color color) {
    personajeShape.setSize(sf::Vector2f(50, 50));
    personajeShape.setPosition(position);
    personajeShape.setFillColor(color);
    vidas = 3;  // Valor predeterminado de vidas
}

Personaje::Personaje(sf::Vector2f position) : Personaje(position, sf::Color::White) {} // Constructor adicional

void Personaje::moverIzquierda() {
    personajeShape.move(-5, 0); // Mover hacia la izquierda
}

void Personaje::moverDerecha() {
    personajeShape.move(5, 0); // Mover hacia la derecha
}

void Personaje::saltar() {
    personajeShape.move(0, -10); // Simulación de salto
}

int Personaje::getVidas() const {
    return vidas;
}

void Personaje::perderVida() {
    if (vidas > 0) {
        vidas--;
    }
}

void Personaje::dibujar(sf::RenderWindow& window) {
    window.draw(personajeShape); // Dibuja el personaje en la ventana
}

bool Personaje::isJumpingOn(sf::RectangleShape& enemy) {
    // Lógica para verificar si el personaje está saltando sobre el enemigo
    // El personaje debe estar por encima del enemigo y colisionar con él
    return (personajeShape.getPosition().y < enemy.getPosition().y) && 
           personajeShape.getGlobalBounds().intersects(enemy.getGlobalBounds());
}

sf::FloatRect Personaje::getBounds() const {
    return personajeShape.getGlobalBounds(); // Devuelve las dimensiones del personaje
}