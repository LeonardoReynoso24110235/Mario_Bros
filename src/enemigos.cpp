#include "enemigos.h"
#include "personajes.h"
#include <iostream>

Enemigo::Enemigo(sf::Vector2f position, sf::Color color, float groundLevel) {
    direccion = -1;
    estaEliminado = false;
    frameActual = 0;

    // Cargar texturas para animación
    for (int i = 1; i <= 2; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/img_finales/goomba" + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando goomba" << i << ".png" << std::endl;
            continue;
        }
        texturasMovimiento.push_back(textura);
    }

    // Establecer textura inicial si se cargó correctamente
    if (!texturasMovimiento.empty()) {
        enemigoSprite.setTexture(texturasMovimiento[0]);
    }

    // Posición del enemigo
    enemigoSprite.setPosition(position.x, groundLevel - enemigoSprite.getGlobalBounds().height);

    // Cargar sonido de salto del enemigo
    if (!saltoEnemigoBuffer.loadFromFile("assets/img/sound/salto.mp3")) {
        std::cerr << "Error al cargar sonido de salto enemigo.\n";
    } else {
        sonidoSalto.setBuffer(saltoEnemigoBuffer);
    }

    // Cargar texturas extra (aunque actualmente no se usan)
    texturaEnemigo1.loadFromFile("assets/img/img_finales/goomba1.png");
    texturaEnemigo2.loadFromFile("assets/img/img_finales/koopa.png");
}

Enemigo::Enemigo(sf::Vector2f position, sf::Color color)
    : Enemigo(position, color, 550.f) {}

Enemigo::Enemigo(sf::Vector2f position)
    : Enemigo(position, sf::Color::Green) {}

void Enemigo::mover(sf::RenderWindow& window, float groundLevel) {
    if (estaEliminado) return;

    // Animación
    if (relojAnimacion.getElapsedTime().asSeconds() > 0.2f && !texturasMovimiento.empty()) {
        frameActual = (frameActual + 1) % texturasMovimiento.size();
        enemigoSprite.setTexture(texturasMovimiento[frameActual]);
        relojAnimacion.restart();
    }

    // Mantener al enemigo en el suelo
    if (enemigoSprite.getPosition().y + enemigoSprite.getGlobalBounds().height > groundLevel) {
        enemigoSprite.setPosition(enemigoSprite.getPosition().x, groundLevel - enemigoSprite.getGlobalBounds().height);
    }

    // Movimiento lateral
    enemigoSprite.move(direccion * 0.2f, 0.f);

    // Rebotar en los bordes de la ventana
    if (enemigoSprite.getPosition().x <= 0 || enemigoSprite.getPosition().x + enemigoSprite.getGlobalBounds().width >= window.getSize().x) {
        direccion = -direccion;
    }

    window.draw(enemigoSprite);
}

void Enemigo::interactuarConJugador(Personaje& personaje) {
    if (estaEliminado) return;

    if (enemigoSprite.getGlobalBounds().intersects(personaje.getBounds())) {
        if (personaje.isJumpingOn(*this)) {
            this->eliminar();
        } else {
            personaje.perderVida();
        }
    }
}

void Enemigo::eliminar() {
    estaEliminado = true;
    sonidoSalto.play();
}

void Enemigo::verificarColisionConPersonaje(Personaje& personaje) {
    interactuarConJugador(personaje);
}

void Enemigo::dibujar(sf::RenderWindow& window) {
    if (!estaEliminado)
        window.draw(enemigoSprite);
}
