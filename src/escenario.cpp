#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "enemigos.h"
#include "personajes.h"

// Implementación de las funciones relacionadas con los enemigos
void Enemigo::mover(sf::RenderWindow& window, float groundLevel) {
    // Actualizar animación
    if (relojAnimacion.getElapsedTime().asSeconds() > 0.2f) {
        frameActual = (frameActual + 1) % texturasMovimiento.size();
        enemigoSprite.setTexture(texturasMovimiento[frameActual]);
        relojAnimacion.restart();
    }

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(enemigoSprite.getPosition().x, enemigoSprite.getPosition().y);
    b2Body* body = mundoEnemigos.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(enemigoSprite.getGlobalBounds().width / 2.0f, enemigoSprite.getGlobalBounds().height / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    mundoEnemigos.Step(1.0f / 60.0f, 6, 2);

    enemigoSprite.setPosition(body->GetPosition().x, body->GetPosition().y);

    if (enemigoSprite.getPosition().y + enemigoSprite.getGlobalBounds().height > groundLevel) {
        enemigoSprite.setPosition(enemigoSprite.getPosition().x, groundLevel - enemigoSprite.getGlobalBounds().height);
    }

    // Dibujar enemigo
    window.draw(enemigoSprite);
}

void Enemigo::interactuarConJugador(Personaje& personaje) {
    if (shape.getGlobalBounds().intersects(personaje.getBounds())) {
        if (personaje.isJumpingOn(shape)) {
            eliminado = true; // Elimina al enemigo
        } else {
            personaje.perderVida(); // Quita una vida al personaje
        }
    }
}

Enemigo::Enemigo(sf::Vector2f position) {
    // Cargar texturas para animación de movimiento
    if (!texturaEnemigo1.loadFromFile("assets/Trabajo final/goomba.png")) {
        std::cerr << "Error al cargar la textura enemigo.png\n";
    }
    if (!texturaEnemigo2.loadFromFile("assets/Trabajo final/goomba2.png")) {
        std::cerr << "Error al cargar la textura enemigo2.png\n";
    }

    texturasMovimiento.push_back(texturaEnemigo1);
    texturasMovimiento.push_back(texturaEnemigo2);

    enemigoSprite.setTexture(texturasMovimiento[0]);
    enemigoSprite.setPosition(position);
    eliminado = false;

    // Inicializar sonido de salto del enemigo
    if (!saltoEnemigoBuffer.loadFromFile("assets/sound/salto.mp3")) {
        std::cerr << "Error al cargar el sonido de salto del enemigo.\n";
    }
    saltoEnemigoSound.setBuffer(saltoEnemigoBuffer);
}

bool Enemigo::isEliminado() const {
    return eliminado;
}

void Enemigo::jump() {
    if (relojSalto.getElapsedTime().asSeconds() >= 5.0f) {
        saltoEnemigoSound.play();
        enemigoSprite.move(0, -10); // Salta 10 píxeles hacia arriba
        relojSalto.restart();
    }
}