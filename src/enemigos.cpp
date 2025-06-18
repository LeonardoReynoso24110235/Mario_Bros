#include "enemigos.hpp"
#include "personajes.hpp"
#include <iostream>

Enemigo::Enemigo(sf::Vector2f position, sf::Color color, float groundLevel) {
    direccion = -1;
    estaEliminado = false;
    frameActual = 0;

    // Cargar texturas para animación
    for (int i = 1; i <= 2; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/img_finales/goomba" + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando goomba" << i << ".png\n";
            continue;
        }
        texturasMovimiento.push_back(textura);
    }

    // Establecer textura inicial si se cargó al menos una
    if (!texturasMovimiento.empty()) {
        enemigoSprite.setTexture(texturasMovimiento[0]);

        // Establecer la posición del enemigo en el nivel del suelo (groundLevel)
        enemigoSprite.setPosition(position.x, groundLevel);
    } else {
        enemigoSprite.setPosition(position.x, groundLevel);  // fallback
    }

    // Cargar sonido de salto enemigo
    if (!saltoEnemigoBuffer.loadFromFile("assets/img/sound/salto.mp3")) {
        std::cerr << "Error al cargar sonido de salto enemigo.\n";
    } else {
        sonidoSalto.setBuffer(saltoEnemigoBuffer);
    }

    // Cargar otras texturas (opcional)
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

    // Ajustar posición en el suelo si se cae más allá del límite
    if (enemigoSprite.getPosition().y + enemigoSprite.getGlobalBounds().height > groundLevel) {
        enemigoSprite.setPosition(enemigoSprite.getPosition().x, groundLevel - enemigoSprite.getGlobalBounds().height);
    }

    // Movimiento lateral
    enemigoSprite.move(direccion * 0.3f, 0.f);

    // Cambiar dirección al llegar a los bordes
    if (enemigoSprite.getPosition().x <= 0 ||
        enemigoSprite.getPosition().x + enemigoSprite.getGlobalBounds().width >= window.getSize().x) {
        direccion = -direccion;
    }

    window.draw(enemigoSprite);
}

void Enemigo::interactuarConJugador(Personaje& personaje) {
    if (estaEliminado) return;

    if (enemigoSprite.getGlobalBounds().intersects(personaje.getBounds())) {
        std::cout << "Colisión detectada entre personaje y enemigo." << std::endl;

        if (personaje.isJumpingOn(*this)) {
            std::cout << "Personaje saltó sobre el enemigo." << std::endl;
            eliminar();
        } else {
            std::cout << "Personaje tocó el enemigo." << std::endl;
            personaje.perderVida();
        }
    }
}

void Enemigo::verificarColisionConPersonaje(Personaje& personaje) {
    interactuarConJugador(personaje);
}

void Enemigo::eliminar() {
    estaEliminado = true;
    sonidoSalto.play();
}

void Enemigo::dibujar(sf::RenderWindow& window) {
    if (!estaEliminado) {
        window.draw(enemigoSprite);
    }
}

sf::FloatRect Enemigo::getBounds() const {
    return enemigoSprite.getGlobalBounds();
}

bool Enemigo::estaActivo() const {
    return !estaEliminado;
}
