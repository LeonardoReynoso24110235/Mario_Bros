#include <iostream>
#include "escenario.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Implementación de las funciones relacionadas con el escenario
void Escenario::dibujarFondo(sf::RenderWindow& window) {
    window.draw(escenarioSprite);
}

void Escenario::dibujarSuelo(sf::RenderWindow& window) {
    suelo.setSize(sf::Vector2f(window.getSize().x, 5));
    suelo.setPosition(0, window.getSize().y - 5);
    suelo.setFillColor(sf::Color::Green);
    window.draw(suelo);
}

void Escenario::moverEscenario(float offsetX) {
    escenarioSprite.move(offsetX, 0);
    suelo.move(offsetX, 0);
}

void Escenario::dibujarPlataformas(sf::RenderWindow& window) {
    plataformas.clear();
    sf::RectangleShape plataforma;
    plataforma.setSize(sf::Vector2f(100, 10));
    plataforma.setPosition(50, suelo.getPosition().y - 8);
    plataforma.setFillColor(sf::Color::Blue);
    plataformas.push_back(plataforma);

    for (const auto& plat : plataformas) {
        window.draw(plat);
    }
}

void Escenario::colocarMonedas(sf::RenderWindow& window) {
    if (relojMonedas.getElapsedTime().asSeconds() >= 10.0f && monedas.size() < 10) {
        sf::CircleShape moneda(5);
        moneda.setFillColor(sf::Color::Yellow);
        moneda.setPosition(rand() % window.getSize().x, 0);
        monedas.push_back(moneda);
        relojMonedas.restart();
    }

    for (auto& moneda : monedas) {
        moneda.move(0, 2); // Las monedas caen hacia abajo
        window.draw(moneda);
    }
}

sf::Music backgroundMusic;

void iniciarMusicaEscenario() {
    if (!backgroundMusic.openFromFile("assets/music/escenario.mp3")) {
        std::cerr << "Error al cargar la música del escenario.\n";
        return;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
}

sf::Texture escenarioTexture;
sf::Sprite escenarioSprite;

void iniciarEscenario(sf::RenderWindow& window) {
    // Cargar textura de fondo del escenario
    if (!escenarioTexture.loadFromFile("assets/img/escenario_fondo.png")) {
        std::cerr << "Error al cargar la textura del fondo del escenario.\n";
    }
    escenarioSprite.setTexture(escenarioTexture);

    window.clear();
    window.draw(escenarioSprite);
    window.display();
}