#include "personajes.hpp"
#include <iostream>
#include <thread>     // Para std::this_thread::sleep_for
#include <chrono>     // Para std::chrono::seconds
#include <SFML/Audio.hpp>

Personaje::Personaje(sf::Vector2f position) {
    vidas = 1;
    sprite.setPosition(position);

    // Cargar texturas pequeñas
    for (int i = 1; i <= 11; i++) {
        auto textura = std::make_shared<sf::Texture>();
        if (!textura->loadFromFile("assets/img/img_finales/p_principal 1." + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando p_principal 1." << i << ".png\n";
        }
        texturasPequeno.push_back(textura);
    }


    // Crear algunas plataformas de ejemplo (esto puede variar según tu diseño)
    sf::RectangleShape plataforma(sf::Vector2f(100, 20));  // Una plataforma de 100x20 píxeles
    plataforma.setPosition(100, 500);  // Establece su posición en el escenario
    plataformas.push_back(plataforma);  // Agrega la plataforma al vector

    // Cargar texturas grandes
    for (int i = 1; i <= 3; i++) {
    auto textura = std::make_shared<sf::Texture>();
    if (!textura->loadFromFile("assets/img/img_finales/p_grande" + std::to_string(i) + ".png")) {
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
        sprite.setTexture(*texturasPequeno[0]);
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
    if (sprite.getPosition().x < 1200)
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
        sprite.setTexture(*texturasGrande[frameActual]);  // Esta es la textura correcta
    }
}

void Personaje::actualizarGravedad() {
    if (saltando) {
        sprite.move(0, velocidadSalto);
        velocidadSalto += gravedad;

        // Verificar si el personaje está tocando alguna plataforma
        for (const auto& plataforma : plataformas) {
            if (getBounds().intersects(plataforma.getGlobalBounds())) {
                // Si el personaje está tocando un bloque desde arriba, se detiene en él
                if (sprite.getPosition().y + sprite.getGlobalBounds().height <= plataforma.getPosition().y) {
                    sprite.setPosition(sprite.getPosition().x, plataforma.getPosition().y - sprite.getGlobalBounds().height);
                    saltando = false;
                    velocidadSalto = 0;
                    enReposo = true;
                }
            }

            // Control de reposo: si no se presiona ninguna tecla de movimiento, está en reposo
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                detenerMovimiento(); 
            }
        }

        // Si el personaje no está tocando plataformas y cae al suelo, detén el salto
        if (sprite.getPosition().y >= 550) {
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
        // Si está en reposo, usa la primera textura
        sprite.setTexture(*texturasPequeno[0]);
    } else {
        // Si está en movimiento, cambia entre texturas
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
            // Cambiar a la textura de muerte
            sprite.setTexture(texturaMuerte);
            
            // Reproducir el sonido de muerte
            if (sonidoMuerte.getStatus() != sf::Sound::Playing) {
                sonidoMuerte.play();
            }
        }
    }
}

bool Personaje::isJumpingOn(Enemigo& enemy) {
    // Verifica si el personaje está por encima del enemigo y está saltando
    if (saltando && getBounds().intersects(enemy.getBounds())) {
        return true;
    }
    return false;
}

sf::FloatRect Personaje::getBounds() const {
    return sprite.getGlobalBounds();
}

void Personaje::restablecer() {
    // Restablecer las vidas del personaje
    vidas = 3;  // O cualquier número inicial de vidas

    // Restablecer la posición del personaje
    sprite.setPosition(posicionInicial);

    // Puedes restablecer otros atributos si es necesario (por ejemplo, tamaño, estado de salto)
    velocidadSalto = 0;
    saltando = false;
    esGrande = false;    
}

void Personaje::perderTodasLasVidas() {
    vidas = 0;
}