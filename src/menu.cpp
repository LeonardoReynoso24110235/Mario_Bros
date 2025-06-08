// menu.cpp
#include "menu.h"
#include "escenario.h"
#include "personajes.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Texture menuTexture;
sf::Sprite menuSprite;

void iniciarJuego(sf::RenderWindow& window) {
    // Crear el escenario y el personaje principal
    Escenario escenario;
    Personaje mario(sf::Vector2f(100, 300), sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        escenario.dibujar(window);
        mario.draw(window);
        window.display();
    }
}

void mostrarMenu() { 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super CETI");

    if (!menuTexture.loadFromFile("../assets/img_finales/fondo.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'fondo.png'" << std::endl;
        return;
    }
    sf::Font font;
    if (!font.loadFromFile("../assets/text/pixely[1].ttf")) {
        std::cerr << "Error al cargar pixely[1].ttf\n";
    }

    sf::Text titulo("Super Mario Bros", font, 50);
    titulo.setPosition(200, 80);
    titulo.setFillColor(sf::Color::Yellow);

    sf::Text opciones[2];
    std::string textos[2] = { "Iniciar Juego ENTER", "Salir del Juego" };

    for (int i = 0; i < 2; ++i) {
        opciones[i].setFont(font);
        opciones[i].setString(textos[i]);
        opciones[i].setCharacterSize(36);
        opciones[i].setPosition(260, 220 + i * 60);
    }

    int seleccion = 0;
    opciones[seleccion].setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    iniciarJuego(window); // Iniciar el juego
                } else if (event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Saliendo del juego..." << std::endl;
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(menuSprite);
        window.draw(titulo);
        for (int i = 0; i < 2; ++i) {
            window.draw(opciones[i]);
        }
        window.display();
    }
}

int main() {
    mostrarMenu();
    return 0;
}