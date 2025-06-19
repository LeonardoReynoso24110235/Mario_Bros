// personajes.cpp

#include "Personaje.hpp"
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

void Personaje::MoverIzquierda() {
    if (sprite.getPosition().x > 0)
        sprite.move(-1.5, 0);
    enReposo = false;
}

void Personaje::MoverDerecha() {
    if (sprite.getPosition().x < 1200)
        sprite.move(1.5, 0);
    enReposo = false;
}

void Personaje::Saltar() {
    if (!saltando) {
        saltando = true;
        velocidadSalto = -10;
        enReposo = false;
    }
}

void Personaje::ActualizarGravedad() {
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

void Personaje::DetenerMovimiento() {
    enReposo = true;
    frameActual = 0;
}

void Personaje::ActualizarAnimacion() {
    if (enReposo) {
        sprite.setTexture(*texturasPequeno[0]);
    } else {
        frameActual = (frameActual + 1) % texturasPequeno.size();
        sprite.setTexture(*texturasPequeno[frameActual]);
    }
}

void Personaje::Dibujar(sf::RenderWindow& window) {
    window.draw(sprite);
}

int Personaje::GetVidas() const {
    return vidas;
}

void Personaje::PerderVida() {
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

bool Personaje::Saltar(Enemigo& enemy) {
    if (saltando && GetBounds().intersects(enemy.GetBounds())) {
        if (sprite.getPosition().y < enemy.GetBounds().top) {
            return true;
        }
    }
    return false;
}

sf::FloatRect Personaje::GetBounds() const {
    return sprite.getGlobalBounds();
}

void Personaje::Restablecer() {
    vidas = 3;
    sprite.setPosition(posicionInicial);
    velocidadSalto = 0;
    saltando = false;
}

void Personaje::PerderTodasLasVidas() {
    vidas = 0;
    sprite.setTexture(texturaMuerte);
    if (sonidoMuerte.getStatus() != sf::Sound::Playing) {
        sonidoMuerte.play();
    }
}

void Personaje::VerificarColisionConPlataforma(const sf::FloatRect& boundsPlataforma) {
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

void Personaje::AsignarMusica(sf::Music* musica1, sf::Music* musica2) {
    soundtrack1 = musica1;
    soundtrack2 = musica2;
}

void Personaje::DibujarPlataformas(sf::RenderWindow& window) {
    for (const auto& plataforma : plataformas) {
        window.draw(plataforma);
    }
}
