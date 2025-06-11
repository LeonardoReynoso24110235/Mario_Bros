// menu.cpp
#include "menu.h"
#include "escenario.h"
#include "personajes.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem> // Para mostrar ruta actual

sf::Texture menuTexture;
sf::Sprite menuSprite;

void iniciarJuego(sf::RenderWindow& window) {
    std::cout << "Iniciando el juego..." << std::endl;

    // Crear el escenario y el personaje principal
    Escenario escenario;
    Personaje mario(sf::Vector2f(100, 300), sf::Color::Red);
    std::cout << "Escenario y personaje creados correctamente" << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "Ventana cerrada" << std::endl;
                window.close();
            }
        }

        window.clear();
        escenario.dibujar(window);
        mario.dibujar(window);  // Cambio aquí
        window.display();
        std::cout << "Dibujando escenario y personaje" << std::endl;
    }
}

void mostrarMenu() {
    // Agregar mensajes de depuración para verificar el flujo del programa
    std::cout << "Iniciando mostrarMenu()" << std::endl;

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Super CETI");
    std::cout << "Ventana creada correctamente" << std::endl;

    // Mostrar la ruta actual del ejecutable
    std::cout << "Ruta actual de ejecución: " << std::filesystem::current_path() << std::endl;

    // Verificar carga de textura del fondo
    if (!menuTexture.loadFromFile("assets/img/img_finales/fondo.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'assets/img_finales/retro.png'" << std::endl;
        return;
    }
    std::cout << "Textura del fondo cargada correctamente" << std::endl;
    menuSprite.setTexture(menuTexture);

    // Verificar carga de fuente
    sf::Font font;
    if (!font.loadFromFile("assets/img/text/pixely[1].ttf")) {
        std::cerr << "Error al cargar pixely[1].ttf" << std::endl;
        return;
    }
    std::cout << "Fuente cargada correctamente" << std::endl;

    sf::Text titulo("Super CETI Bros", font, 50);
    titulo.setPosition(200, 80);
    titulo.setFillColor(sf::Color::Yellow);

    sf::Text opciones[2];
    std::string textos[2] = { "Iniciar Juego ENTER", "Salir del Juego" };

    for (int i = 0; i < 2; ++i) {
        opciones[i].setFont(font);
        opciones[i].setString(textos[i]);
        opciones[i].setCharacterSize(36);
        opciones[i].setPosition(260, 220 + i * 60);
        opciones[i].setFillColor(sf::Color::White);
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
                // Agregar mensajes de depuración para verificar la transición al juego
                std::cout << "Tecla presionada: " << event.key.code << std::endl;
                if (event.key.code == sf::Keyboard::Enter) {
                    std::cout << "Iniciando el juego..." << std::endl;
                    iniciarJuego(window); // Iniciar el juego
                    std::cout << "Regresando al menu..." << std::endl;
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