#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "personajes.h"
#include <iostream>

using namespace std;

int vidas = 3; // Inicializar vidas
int puntos = 0; // Inicializar puntos acumulados

sf::Texture personajeTexture;
sf::Sprite personajeSprite;
std::vector<sf::Texture> texturasMovimientoPersonaje;
int frameActualPersonaje = 0;
sf::Clock relojAnimacionPersonaje;

Personaje::Personaje(sf::Vector2f position, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(position);
    shape.setFillColor(color);
    velocityY = 0;
    isJumping = false;

    // Cargar texturas para animaciones del personaje
    for (int i = 1; i <= 4; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("assets/img/personaje_" + std::to_string(i) + ".png")) {
            std::cerr << "Error al cargar la textura personaje_" << i << ".png\n";
        }
        texturasMovimientoPersonaje.push_back(textura);
    }

    personajeSprite.setTexture(texturasMovimientoPersonaje[0]);
    personajeSprite.setPosition(position);

    // Cargar sonidos
    if (!saltoBuffer.loadFromFile("assets/sonidos/salto.mp3")) {
        std::cerr << "Error al cargar el sonido de salto.\n";
    }
    saltoSound.setBuffer(saltoBuffer);

    if (!golpearBuffer.loadFromFile("assets/sonidos/golpear.mp3")) {
        std::cerr << "Error al cargar el sonido de golpear.\n";
    }
    golpearSound.setBuffer(golpearBuffer);

    if (!correrBuffer.loadFromFile("assets/sonidos/correr.mp3")) {
        std::cerr << "Error al cargar el sonido de correr.\n";
    }
    correrSound.setBuffer(correrBuffer);
}

void Personaje::move(float offsetX) {
    personajeSprite.move(offsetX, 0);
    // Reproducir sonido de correr
    if (correrSound.getStatus() != sf::Sound::Status::Playing) {
        correrSound.play();
    }
    // Actualizar animación
    if (relojAnimacionPersonaje.getElapsedTime().asSeconds() > 0.2f) {
        frameActualPersonaje = (frameActualPersonaje + 1) % texturasMovimientoPersonaje.size();
        personajeSprite.setTexture(texturasMovimientoPersonaje[frameActualPersonaje]);
        relojAnimacionPersonaje.restart();
    }
}

void Personaje::jump() {
    if (!isJumping) {
        saltoSound.play();
        velocityY = -jumpStrength;
        isJumping = true;
    }
}

void Personaje::applyGravity(float gravity, float groundLevel) {
    velocityY += gravity;
    personajeSprite.move(0, velocityY);

    if (personajeSprite.getPosition().y + personajeSprite.getGlobalBounds().height >= groundLevel) {
        personajeSprite.setPosition(personajeSprite.getPosition().x, groundLevel - personajeSprite.getGlobalBounds().height);
        velocityY = 0;
        isJumping = false;
    }
}

void Personaje::draw(sf::RenderWindow& window) {
    window.draw(personajeSprite);
}

sf::FloatRect Personaje::getBounds() const {
    return shape.getGlobalBounds();
}

bool Personaje::isJumpingOn(const sf::RectangleShape& enemigoShape) const {
    return personajeSprite.getPosition().y + personajeSprite.getGlobalBounds().height <= enemigoShape.getPosition().y;
}

void Personaje::perderVida() {
    vidas--;
    if (vidas <= 0) {
        std::cout << "Game Over" << std::endl;
        // Lógica adicional para terminar el juego
    }
}

void Personaje::eliminarEnemigo(sf::RectangleShape& enemigoShape) {
    if (isJumpingOn(enemigoShape)) {
        golpearSound.play();
        enemigoShape.setPosition(-100, -100); // Mover el enemigo fuera de la pantalla
    }
}

void Personaje::recogerMoneda() {
    puntos++;
    std::cout << "Moneda recogida! Puntos: " << puntos << std::endl;
}

int Personaje::getPuntos() const {
    return puntos;
}

void Personaje::mostrarHUD(sf::RenderWindow& window, sf::Clock& relojJuego) {
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error al cargar la fuente del HUD.\n";
        return;
    }

    sf::Text vidasText;
    vidasText.setFont(font);
    vidasText.setString("Vidas: " + std::to_string(vidas));
    vidasText.setCharacterSize(20);
    vidasText.setFillColor(sf::Color::White);
    vidasText.setPosition(10, 10);

    sf::Text puntosText;
    puntosText.setFont(font);
    puntosText.setString("Puntos: " + std::to_string(puntos));
    puntosText.setCharacterSize(20);
    puntosText.setFillColor(sf::Color::White);
    puntosText.setPosition(10, 40);

    sf::Text tiempoText;
    tiempoText.setFont(font);
    tiempoText.setString("Tiempo: " + std::to_string(static_cast<int>(relojJuego.getElapsedTime().asSeconds())) + "s");
    tiempoText.setCharacterSize(20);
    tiempoText.setFillColor(sf::Color::White);
    tiempoText.setPosition(10, 70);

    window.draw(vidasText);
    window.draw(puntosText);
    window.draw(tiempoText);
}

bool Personaje::verificarTiempo(sf::Clock& relojJuego) {
    return relojJuego.getElapsedTime().asSeconds() >= 120; // Verificar si han pasado 2 minutos
}

/*
// Comentando la función main para evitar conflictos
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario Bros");

    Personaje character(sf::Vector2f(400, 500), sf::Color::Red);
    const float gravity = 0.2f;
    const float groundLevel = 550.0f;
    sf::Clock relojJuego;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            character.move(-5.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            character.move(5.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            character.jump();
        }

        character.applyGravity(gravity, groundLevel);

        window.clear();
        character.draw(window);
        character.mostrarHUD(window, relojJuego); // Mostrar HUD
        window.display();

        // Verificar tiempo límite
        if (character.verificarTiempo(relojJuego)) {
            std::cout << "Tiempo excedido. Game Over." << std::endl;
            window.close(); // Cerrar ventana al finalizar el tiempo
        }
    }

    return 0;
}
*/