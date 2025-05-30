#include <iostream>
#include "escenario.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Implementación de las funciones relacionadas con el escenario
void Escenario::dibujarFondo() {
    // Lógica para dibujar el fondo pixeleado
}

void Escenario::dibujarPlataformas() {
    // Lógica para dibujar plataformas flotantes
}

void Escenario::colocarMonedas() {
    // Lógica para colocar monedas en el escenario
}

sf::Music backgroundMusic;

void iniciarMusicaEscenario() {
    if (!backgroundMusic.openFromFile("assets/music/escenario.ogg")) {
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