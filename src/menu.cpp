// menu.cpp
#include "menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Texture menuTexture;
sf::Sprite menuSprite;

void mostrarMenu() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super CETI Menu");

    // Cargar textura de fondo del menú
    if (!menuTexture.loadFromFile("assets/img/menu_fondo.png")) {
        std::cerr << "Error al cargar la textura del fondo del menú.\n";
    }
    menuSprite.setTexture(menuTexture);

    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    sf::Text titulo("Super Mario Bros", font, 50);
    titulo.setPosition(200, 80);
    titulo.setFillColor(sf::Color::Yellow);

    sf::Text opciones[2];
    std::string textos[2] = { "Iniciar Juego", "Salir del Juego" };

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
                if (event.key.code == sf::Keyboard::Up) {
                    opciones[seleccion].setFillColor(sf::Color::White);
                    seleccion = (seleccion - 1 + 2) % 2;
                    opciones[seleccion].setFillColor(sf::Color::Red);
                } else if (event.key.code == sf::Keyboard::Down) {
                    opciones[seleccion].setFillColor(sf::Color::White);
                    seleccion = (seleccion + 1) % 2;
                    opciones[seleccion].setFillColor(sf::Color::Red);
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (seleccion == 0) {
                        std::cout << "Iniciando juego..." << std::endl;
                        window.close();
                    } else if (seleccion == 1) {
                        std::cout << "Saliendo del juego..." << std::endl;
                        window.close();
                    }
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