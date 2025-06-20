#include "Enemigo.hpp"
#include "Personaje.hpp"
#include <iostream>

Enemigo::Enemigo(sf::Vector2f position, sf::Color color, float groundLevel) {
    direccion = -1;
    estaEliminado = false;
    frameActual = 0;

    for (int i = 1; i <= 2; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/img_finales/goomba" + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando goomba" << i << ".png\n";
            continue;
        }
        texturasMovimiento.push_back(textura);
    }
   
    if (!texturasMovimiento.empty()) {
        enemigoSprite.setTexture(texturasMovimiento[0]);
       
        enemigoSprite.setPosition(position.x, groundLevel);
    } else {
        enemigoSprite.setPosition(position.x, groundLevel);
    }
   
    if (!saltoEnemigoBuffer.loadFromFile("assets/img/sound/salto.mp3")) {
        std::cerr << "Error al cargar sonido de salto enemigo.\n";
    } else {
        sonidoSalto.setBuffer(saltoEnemigoBuffer);
    }
    
    texturaEnemigo1.loadFromFile("assets/img/img_finales/goomba1.png");    
}

Enemigo::Enemigo(sf::Vector2f position, sf::Color color)
    : Enemigo(position, color, 550.f) {}

Enemigo::Enemigo(sf::Vector2f position)
    : Enemigo(position, sf::Color::Green) {}

void Enemigo::Mover(sf::RenderWindow& window, float groundLevel) {
    if (estaEliminado) return;

    if (relojAnimacion.getElapsedTime().asSeconds() > 0.2f && !texturasMovimiento.empty()) {
        frameActual = (frameActual + 1) % texturasMovimiento.size();
        enemigoSprite.setTexture(texturasMovimiento[frameActual]);
        relojAnimacion.restart();
    }

    if (enemigoSprite.getPosition().y + enemigoSprite.getGlobalBounds().height > groundLevel) {
        enemigoSprite.setPosition(enemigoSprite.getPosition().x, groundLevel - enemigoSprite.getGlobalBounds().height);
    }

    enemigoSprite.move(direccion * 0.3f, 0.f);

    if (enemigoSprite.getPosition().x <= 0 ||
        enemigoSprite.getPosition().x + enemigoSprite.getGlobalBounds().width >= window.getSize().x) {
        direccion = -direccion;
    }

    window.draw(enemigoSprite);
}

void Enemigo::InteractuarConJugador(Personaje& personaje) {
    if (estaEliminado) return;

    if (enemigoSprite.getGlobalBounds().intersects(personaje.ObtenerLimites())) {
        std::cout << "Colisión detectada entre personaje y enemigo." << std::endl;

        if (personaje.Saltar(*this)) {
            std::cout << "Personaje saltó sobre el enemigo." << std::endl;
            Eliminar();
        } else {
            std::cout << "Personaje tocó al enemigo." << std::endl;
            personaje.PerderVida();
        }
    }
}

void Enemigo::VerificarColisionConPersonaje(Personaje& personaje) {
    InteractuarConJugador(personaje);
}

void Enemigo::Eliminar() {
    estaEliminado = true;
    sonidoSalto.play();
}

void Enemigo::Dibujar(sf::RenderWindow& window) {
    if (!estaEliminado) {
        window.draw(enemigoSprite);
    }
}

sf::FloatRect Enemigo::ObtenerLimites() const {
    return enemigoSprite.getGlobalBounds();
}

bool Enemigo::ObtenerEstaActivo() const {
    return !estaEliminado;
}
