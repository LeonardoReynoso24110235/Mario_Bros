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

Enemigo::Enemigo(sf::Vector2f position, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(position);
    shape.setFillColor(color);
    direccion = 1;
    contadorMovimiento = 0;
    eliminado = false;

    // Cargar texturas para animaciones
    for (int i = 1; i <= 4; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/enemigo_" + std::to_string(i) + ".png")) {
            std::cerr << "Error al cargar la textura enemigo_" << i << ".png\n";
        }
        texturasMovimiento.push_back(textura);
    }

    enemigoSprite.setTexture(texturasMovimiento[0]);
    enemigoSprite.setPosition(position);

    // Inicializar sonido de salto del enemigo
    if (!saltoEnemigoBuffer.loadFromFile("assets/sound/salto_enemigo.ogg")) {
        std::cerr << "Error al cargar el sonido de salto del enemigo.\n";
    }
    saltoEnemigoSound.setBuffer(saltoEnemigoBuffer);
}

bool Enemigo::isEliminado() const {
    return eliminado;
}

void Enemigo::jump() {
    saltoEnemigoSound.play();
    // Lógica de salto del enemigo
}