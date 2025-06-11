#include "personajes.h"
#include <iostream>
#include <thread>     // Para std::this_thread::sleep_for
#include <chrono>     // Para std::chrono::seconds
#include <SFML/Audio.hpp>

Personaje::Personaje(sf::Vector2f position) {
    vidas = 3;
    sprite.setPosition(position);

    // Cargar texturas pequeñas
    for (int i = 1; i <= 11; i++) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/img_finales/p_principal 1." + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando p_principal 1." << i << ".png\n";
        }
        texturasPequeno.push_back(textura);
    }

    // Cargar texturas grandes
    for (int i = 1; i <= 3; i++) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/img_finales/p_grande" + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando p_grande" << i << ".png\n";
        }
        texturasGrande.push_back(textura);
    }

    // Cargar textura de muerte
    if (!texturaMuerte.loadFromFile("assets/img/img_finales/p_muriendo.png")) {
        std::cerr << "Error cargando p_muriendo.png\n";
    }

    // Cargar sonido de muerte
    if (!bufferMuerte.loadFromFile("assets/img/sound/muerte.ogg")) {
        std::cerr << "Error cargando muriendo.ogg\n";
    }
    sonidoMuerte.setBuffer(bufferMuerte);

    // Establecer textura inicial
    if (!texturasPequeno.empty()) {
        sprite.setTexture(texturasPequeno[0]);
    }

    enReposo = true;
}

Personaje::Personaje(sf::Vector2f position, sf::Color color) : Personaje(position) {
    sprite.setColor(color);
}

void Personaje::moverIzquierda() {
    if (sprite.getPosition().x > 0)
        sprite.move(-1.5, 0);
    enReposo = false;
}

void Personaje::moverDerecha() {
    if (sprite.getPosition().x < 700)
        sprite.move(1.5, 0);
    enReposo = false;
}

void Personaje::saltar() {
    if (!saltando) {
        saltando = true;
        velocidadSalto = alturaSalto;
        enReposo = false;
        if (posicionInicial == sf::Vector2f(0, 0)) {
            posicionInicial = sprite.getPosition();
        }
    }
}

void Personaje::transformarEnGrande() {
    esGrande = true;
    frameActual = 0;
    if (!texturasGrande.empty()) {
        sprite.setTexture(texturasGrande[frameActual]);
    }
}

void Personaje::actualizarGravedad() {
    if (saltando) {
        sprite.move(0, velocidadSalto);
        velocidadSalto += gravedad;

        if (sprite.getPosition().y >= 400) {
            saltando = false;
            velocidadSalto = 0;
            enReposo = true;
        }
    }
}

void Personaje::actualizarAnimacion() {
    if (vidas <= 0) return;  // No animar si está "muerto"

    if (enReposo) {
        if (!texturasPequeno.empty()) {
            sprite.setTexture(texturasPequeno[0]);
        }
    } else {
        if (relojAnimacion.getElapsedTime().asMilliseconds() > 100) {
            const std::vector<sf::Texture>& texturas = esGrande ? texturasGrande : texturasPequeno;
            if (!texturas.empty()) {
                frameActual = (frameActual + 1) % texturas.size();
                sprite.setTexture(texturas[frameActual]);
            }
            relojAnimacion.restart();
        }
    }
}

void Personaje::dibujar(sf::RenderWindow& window) {
    window.draw(sprite);
}

int Personaje::getVidas() const {
    return vidas;
}

void Personaje::perderVida() {
    if (vidas > 0) {
        vidas--;

        if (vidas == 0) {
            // Mostrar imagen de muerte y reproducir música
            sprite.setTexture(texturaMuerte);
            sonidoMuerte.play();

            // Bloquear 3 segundos (no ideal, pero simple)
            std::this_thread::sleep_for(std::chrono::seconds(3));

            // Puedes agregar aquí: cerrar el juego, reiniciar, mostrar menú, etc.
        }
    }
}

bool Personaje::isJumpingOn(sf::RectangleShape& enemy) {
    return (sprite.getPosition().y < enemy.getPosition().y) &&
           sprite.getGlobalBounds().intersects(enemy.getGlobalBounds());
}

sf::FloatRect Personaje::getBounds() const {
    return sprite.getGlobalBounds();
}