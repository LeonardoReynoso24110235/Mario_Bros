#include <iostream>
#include "carga.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

// Implementación de las funciones relacionadas con la carga de recursos
void Carga::cargarRecursos() {
    // Lógica para cargar imágenes, sonidos y otros recursos
}

void Carga::mostrarPantallaCarga(sf::RenderWindow& window) {
    // Crear un texto para mostrar "Cargando..."
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    sf::Text textoCarga("Cargando...", font, 30);
    textoCarga.setFillColor(sf::Color::White);
    textoCarga.setPosition(300, 250);

    // Dibujar la pantalla de carga
    window.clear(sf::Color::Black);
    window.draw(textoCarga);
    window.display();

    // Esperar 1 segundo
    sf::sleep(sf::seconds(1));
}
