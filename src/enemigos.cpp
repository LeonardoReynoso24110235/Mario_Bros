#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "enemigos.h"
#include "personajes.h"

void Enemigo::mover(sf::RenderWindow& window, float groundLevel) {
    // Actualizar animación
    if (relojAnimacion.getElapsedTime().asSeconds() > 0.2f) {
        frameActual = (frameActual + 1) % texturasMovimiento.size();
        enemigoSprite.setTexture(texturasMovimiento[frameActual]);
        relojAnimacion.restart();
    }

    // Lógica de colisión con el suelo usando solo SFML
    if (enemigoSprite.getPosition().y + enemigoSprite.getGlobalBounds().height > groundLevel) {
        enemigoSprite.setPosition(enemigoSprite.getPosition().x, groundLevel - enemigoSprite.getGlobalBounds().height);
    }

    // Lógica para mover al enemigo (puedes agregar más lógica para dirección y velocidad)
    enemigoSprite.move(direccion * 2.f, 0.f);  // 2.f es la velocidad de movimiento

    // Dibujar el enemigo
    window.draw(enemigoSprite);
}

Enemigo::Enemigo(sf::Vector2f position, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(position);
    shape.setFillColor(color);
    direccion = 1;  // Inicia moviéndose a la derecha
    contadorMovimiento = 0;
    eliminado = false;

    // Cargar texturas para animaciones
    for (int i = 1; i <= 4; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("../assets/img_finales/koopa" + std::to_string(i) + ".png")) {
            std::cerr << "Error: No se pudo cargar el recurso 'enemigo_" + std::to_string(i) + ".png'" << std::endl;
            return;
        }
        texturasMovimiento.push_back(textura);
    }

    enemigoSprite.setTexture(texturasMovimiento[0]);
    enemigoSprite.setPosition(position);

    // Inicializar sonido de salto del enemigo
    if (!saltoEnemigoBuffer.loadFromFile("../assets/sound/salto.mp3")) {
        std::cerr << "Error al cargar el sonido de salto enemigo.\n";
    }
    if (!texturaEnemigo1.loadFromFile("../assets/img_finales/goomba.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'goomba.png'" << std::endl;
        return;
    }
    if (!texturaEnemigo2.loadFromFile("../assets/img_finales/koopa.png")) { // Usar una textura diferente
        std::cerr << "Error: No se pudo cargar el recurso 'koopa.png'" << std::endl;
        return;
    }

    enemigoSprite.setTexture(texturaEnemigo1);  // Asigna la textura inicial
}

Enemigo::Enemigo(sf::Vector2f position) : Enemigo(position, sf::Color::Green) {} // Constructor adicional

void Enemigo::interactuarConJugador(Personaje& personaje) {
    if (shape.getGlobalBounds().intersects(personaje.getBounds())) {
        if (personaje.isJumpingOn(shape)) {
            eliminado = true; // Elimina al enemigo
        } else {
            personaje.perderVida(); // Quita una vida al personaje
        }
    }
}

// Implementación del método verificarColisionConPersonaje
void Enemigo::verificarColisionConPersonaje(Personaje& personaje) {
    // Verificar si los límites del sprite del enemigo se intersectan con los del personaje
    if (enemigoSprite.getGlobalBounds().intersects(personaje.getBounds())) {
        // Si el personaje toca al enemigo y no está saltando sobre él, pierde una vida
        personaje.perderVida();
        std::cout << "Colisión con el enemigo. Se perdió una vida." << std::endl;
    }
}

// Implementación del método dibujar
void Enemigo::dibujar(sf::RenderWindow& window) {
    window.draw(enemigoSprite);  // Dibuja el sprite del enemigo en la ventana
}