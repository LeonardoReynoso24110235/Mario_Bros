#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "enemigos.h"
#include "personajes.h"
#include "escenario.h"
#include <vector>

// Las funciones de Enemigo están implementadas en enemigos.cpp, no aquí.

// Comentado para evitar múltiples definiciones de `main`
/*
int main() {
    // Tu código para el juego aquí

    return 0;
}
*/

Escenario::Escenario() {
    // Cargar fondo
    if (!fondoTexture.loadFromFile("../assets/img_finales/fondo.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'imagen.png'" << std::endl;
        return;
    }
    fondoSprite.setTexture(fondoTexture);

    // Cargar textura de bloque
    if (!bloqueTexture.loadFromFile("../assets/img_finales/bloque.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'bloque.png'" << std::endl;
        return;
    }

    // Cargar textura de moneda
    if (!monedaTexture.loadFromFile("assets/img_finales/moneda.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'moneda.png'" << std::endl;
        return;
    }

    // Cargar fuente para el puntaje
    if (!font.loadFromFile("../assets/text/pixely[1].ttf")) {
        std::cerr << "Error al cargar pixely[1].ttf\n";
    }
    puntajeText.setFont(font);
    puntajeText.setCharacterSize(24);
    puntajeText.setFillColor(sf::Color::White);
    puntajeText.setPosition(10, 10);
    puntaje = 0;
}

void Escenario::dibujar(sf::RenderWindow& window) {
    // Dibujar el fondo
    window.draw(fondoSprite);

    // Dibujar las plataformas
    for (const auto& plataforma : plataformas) {
        window.draw(plataforma);
    }

    // Dibujar las monedas
    for (const auto& moneda : monedas) {
        window.draw(moneda);
    }

    // Dibujar el puntaje
    puntajeText.setString("Puntaje: " + std::to_string(puntaje));
    window.draw(puntajeText);
}

void Escenario::agregarPlataforma(float x, float y) {
    sf::Sprite plataforma;
    plataforma.setTexture(bloqueTexture);
    plataforma.setPosition(x, y);
    plataformas.push_back(plataforma);
}

void Escenario::generarMoneda(float x, float y) {
    sf::Sprite moneda;
    moneda.setTexture(monedaTexture);
    moneda.setPosition(x, y);
    monedas.push_back(moneda);
}

void Escenario::actualizarMonedas() {
    for (auto& moneda : monedas) {
        moneda.move(0, 5); // Mover monedas hacia abajo
    }
}

void Escenario::incrementarPuntaje(int cantidad) {
    puntaje += cantidad;
}