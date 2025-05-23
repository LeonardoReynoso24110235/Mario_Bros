#include <iostream>
#include "menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Implementación de las funciones relacionadas con el menú del juego
void Menu::mostrarMenuPrincipal() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu Principal");

    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
        return;
    }

    sf::Text iniciarJuego("Iniciar Juego", font, 30);
    iniciarJuego.setPosition(300, 200);

    sf::Text salirJuego("Salir del Juego", font, 30);
    salirJuego.setPosition(300, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    std::cout << "Iniciando juego..." << std::endl;
                    window.close();
                } else if (event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Saliendo del juego..." << std::endl;
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(iniciarJuego);
        window.draw(salirJuego);
        window.display();
    }            
}