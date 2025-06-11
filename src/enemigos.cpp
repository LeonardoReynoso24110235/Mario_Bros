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

    // Lógica para mover al enemigo hacia la izquierda (con una velocidad de 0.5f)
    enemigoSprite.move(direccion * 0.5f, 0.f);  // Ajustado a velocidad 0.5f y dirección negativa para ir a la izquierda

    // Dibujar el enemigo
    window.draw(enemigoSprite);
}

Enemigo::Enemigo(sf::Vector2f position, sf::Color color, float groundLevel) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(position);
    shape.setFillColor(color);
    direccion = -1;
    contadorMovimiento = 0;
    eliminado = false;

    enemigoSprite.setPosition(position.x, groundLevel - enemigoSprite.getGlobalBounds().height);

    // Cargar texturas para animaciones
    for (int i = 1; i <= 2; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/img_finales/goomba" + std::to_string(i) + ".png")) {
            std::cerr << "Error: No se pudo cargar el recurso 'enemigo_" + std::to_string(i) + ".png'" << std::endl;
            return;
        }
        texturasMovimiento.push_back(textura);
    }

    enemigoSprite.setTexture(texturasMovimiento[0]);

    // Inicializar sonido de salto del enemigo
    if (!saltoEnemigoBuffer.loadFromFile("assets/img/sound/salto.mp3")) {
        std::cerr << "Error al cargar el sonido de salto enemigo.\n";
    }

    // Cargar texturas alternativas
    if (!texturaEnemigo1.loadFromFile("assets/img/img_finales/goomba1.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'goomba1.png'" << std::endl;
        return;
    }
    if (!texturaEnemigo2.loadFromFile("assets/img/img_finales/koopa.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'koopa.png'" << std::endl;
        return;
    }

    enemigoSprite.setTexture(texturaEnemigo1);  // Asigna la textura inicial
}

// Constructor que faltaba: recibe posición y color
Enemigo::Enemigo(sf::Vector2f position, sf::Color color)
    : Enemigo(position, color, 400.f) // Puedes ajustar el valor de groundLevel según tu juego
{}

// Constructor para solo posición, usa color verde por defecto
Enemigo::Enemigo(sf::Vector2f position)
    : Enemigo(position, sf::Color::Green)
{}

void Enemigo::interactuarConJugador(Personaje& personaje) {
    if (shape.getGlobalBounds().intersects(personaje.getBounds())) {
        if (personaje.isJumpingOn(shape)) {
            eliminado = true; // Elimina al enemigo
        } else {
            personaje.perderVida(); // Quita una vida al personaje
        }
    }
}

void Enemigo::verificarColisionConPersonaje(Personaje& personaje) {
    if (enemigoSprite.getGlobalBounds().intersects(personaje.getBounds())) {
        personaje.perderVida();
        std::cout << "Colision con el enemigo. Se perdio una vida." << std::endl;
    }
}

void Enemigo::dibujar(sf::RenderWindow& window) {
    window.draw(enemigoSprite);
}