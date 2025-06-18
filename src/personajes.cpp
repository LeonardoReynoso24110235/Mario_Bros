// personajes.cpp

#include "personajes.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Audio.hpp>

Personaje::Personaje(sf::Vector2f position) {
    vidas = 3;
    sprite.setPosition(position);
    posicionInicial = position;

    for (int i = 1; i <= 11; i++) {
        auto textura = std::make_shared<sf::Texture>();
        if (!textura->loadFromFile("assets/img/img_finales/p_principal 1." + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando p_principal 1." << i << ".png\n";
        }
        texturasPequeno.push_back(textura);
    }

    if (!texturaMuerte.loadFromFile("assets/img/img_finales/p_muriendo.png")) {
        std::cerr << "Error cargando p_muriendo.png\n";
    }

    if (!bufferMuerte.loadFromFile("assets/img/sound/muerte.ogg")) {
        std::cerr << "Error cargando muriendo.ogg\n";
    }
    sonidoMuerte.setBuffer(bufferMuerte);

    if (!texturasPequeno.empty()) {
        sprite.setTexture(*texturasPequeno[0]);
    }

    enReposo = true;
    saltando = false;
    velocidadSalto = 0;
    gravedad = 0.5f;
}

void Personaje::moverIzquierda() {
    if (sprite.getPosition().x > 0)
        sprite.move(-1.5, 0);
    enReposo = false;
}

void Personaje::moverDerecha() {
    if (sprite.getPosition().x < 1200)
        sprite.move(1.5, 0);
    enReposo = false;
}

void Personaje::saltar() {
    if (!saltando) {
        saltando = true;
        velocidadSalto = -10;
        enReposo = false;
    }
}

void Personaje::actualizarGravedad() {
    if (saltando) {
        sprite.move(0, velocidadSalto);
        velocidadSalto += gravedad;

        if (sprite.getPosition().y >= 550) {
            sprite.setPosition(sprite.getPosition().x, 550);
            saltando = false;
            velocidadSalto = 0;
            enReposo = true;
        }
    }
}

void Personaje::detenerMovimiento() {
    enReposo = true;
    frameActual = 0;
}

void Personaje::actualizarAnimacion() {
    if (enReposo) {
        sprite.setTexture(*texturasPequeno[0]);
    } else {
        frameActual = (frameActual + 1) % texturasPequeno.size();
        sprite.setTexture(*texturasPequeno[frameActual]);
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
            sprite.setTexture(texturaMuerte);
            if (sonidoMuerte.getStatus() != sf::Sound::Playing) {
                sonidoMuerte.play();
            }
        }
    }
}

bool Personaje::isJumpingOn(Enemigo& enemy) {
    if (saltando && getBounds().intersects(enemy.getBounds())) {
        if (sprite.getPosition().y < enemy.getBounds().top) {
            return true;
        }
    }
    return false;
}

sf::FloatRect Personaje::getBounds() const {
    return sprite.getGlobalBounds();
}

void Personaje::restablecer() {
    vidas = 3;
    sprite.setPosition(posicionInicial);
    velocidadSalto = 0;
    saltando = false;
}

void Personaje::perderTodasLasVidas() {
    vidas = 0;
    sprite.setTexture(texturaMuerte);
    if (sonidoMuerte.getStatus() != sf::Sound::Playing) {
        sonidoMuerte.play();
    }
}

void Personaje::verificarColisionConPlataforma(const sf::FloatRect& boundsPlataforma) {
    sf::FloatRect personajeBounds = sprite.getGlobalBounds();

    if (personajeBounds.intersects(boundsPlataforma) && velocidadSalto >= 0) {
        float personajeBottom = personajeBounds.top + personajeBounds.height;
        float plataformaTop = boundsPlataforma.top;

        if (personajeBottom - 5.0f <= plataformaTop) {
            sprite.setPosition(sprite.getPosition().x, plataformaTop - personajeBounds.height);
            saltando = false;
            velocidadSalto = 0;
            enReposo = true;
        }
    }
}

void Personaje::asignarMusica(sf::Music* musica1, sf::Music* musica2) {
    soundtrack1 = musica1;
    soundtrack2 = musica2;
}

void Personaje::dibujarPlataformas(sf::RenderWindow& window) {
    for (const auto& plataforma : plataformas) {
        window.draw(plataforma);
    }
}
