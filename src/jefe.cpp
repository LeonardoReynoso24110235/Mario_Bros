#include <SFML/Graphics.hpp>
#include <iostream>
#include "personajes.h"

class Jefe {
private:
    sf::Sprite jefeSprite;
    sf::Texture jefeTexture;
    sf::Sprite bolaFuegoSprite;
    sf::Texture bolaFuegoTexture;
    sf::Sprite banderaSprite;
    sf::Texture banderaTexture;
    sf::Clock relojMovimiento;
    sf::Clock relojBolaFuego;
    sf::Clock relojSalto;
    bool moviendoAdelante = true;

public:
    Jefe(sf::Vector2f position) {
        // Cargar textura del jefe
        if (!jefeTexture.loadFromFile("../assets/img_finales/jefe.png")) {
            std::cerr << "Error: No se pudo cargar el recurso 'jefe.png'" << std::endl;
            return;
        }
        jefeSprite.setTexture(jefeTexture);
        jefeSprite.setPosition(position);

        // Cargar textura de la bola de fuego
        if (!bolaFuegoTexture.loadFromFile("../assets/img_finales/bola_fuego.png")) {
            std::cerr << "Error: No se pudo cargar el recurso 'bola_fuego.png'" << std::endl;
            return;
        }
        bolaFuegoSprite.setTexture(bolaFuegoTexture);

        // Cargar textura de la bandera
        if (!banderaTexture.loadFromFile("../assets/img_finales/bandera.png")) {
            std::cerr << "Error: No se pudo cargar el recurso 'bandera.png'" << std::endl;
            return;
        }
        banderaSprite.setTexture(banderaTexture);
        banderaSprite.setPosition(position.x + 100, position.y); // Bandera detrás del jefe
    }

    void mover() {
        if (relojMovimiento.getElapsedTime().asSeconds() >= 1.0f) {
            if (moviendoAdelante) {
                jefeSprite.move(10, 0);
            } else {
                jefeSprite.move(-10, 0);
            }
            moviendoAdelante = !moviendoAdelante;
            relojMovimiento.restart();
        }
    }

    void lanzarBolaFuego(sf::RenderWindow& window, Personaje& personaje) {
        if (relojBolaFuego.getElapsedTime().asSeconds() >= (rand() % 6)) {
            bolaFuegoSprite.setPosition(jefeSprite.getPosition().x, jefeSprite.getPosition().y);
            bolaFuegoSprite.move(-10, 0); // Mover bola de fuego hacia la izquierda
            if (bolaFuegoSprite.getGlobalBounds().intersects(personaje.getBounds())) {
                personaje.perderVida();
            }
            window.draw(bolaFuegoSprite);
            relojBolaFuego.restart();
        }
    }

    void saltar() {
        if (relojSalto.getElapsedTime().asSeconds() >= (rand() % 9)) {
            jefeSprite.move(0, -10); // Saltar hacia arriba
            jefeSprite.move(0, 10);  // Regresar hacia abajo
            relojSalto.restart();
        }
    }

    void verificarColisionConPersonaje(Personaje& personaje) {
        if (jefeSprite.getGlobalBounds().intersects(personaje.getBounds())) {
            personaje.perderVida();
        }
    }

    bool verificarColisionConBandera(Personaje& personaje) {
        return banderaSprite.getGlobalBounds().intersects(personaje.getBounds());
    }

    void mostrarMensajeFinal(sf::RenderWindow& window) {
        sf::Texture mensajeTexture;
        sf::Sprite mensajeSprite;

        // Cargar textura del mensaje
        if (!mensajeTexture.loadFromFile("../assets/img_finales/mensaje.png")) {
            std::cerr << "Error: No se pudo cargar el recurso 'mensaje.png'" << std::endl;
            return;
        }
        mensajeSprite.setTexture(mensajeTexture);
        mensajeSprite.setPosition(window.getSize().x / 2 - mensajeSprite.getGlobalBounds().width / 2,
                                  window.getSize().y / 2 - mensajeSprite.getGlobalBounds().height / 2);

        sf::Font font;
        if (!font.loadFromFile("../assets/text/letraPixel.ttf")) {
            std::cerr << "Error al cargar letraPixel.ttf\n";
            return;
        }

        sf::Text texto("Presione Enter", font, 30);
        texto.setFillColor(sf::Color::White);
        texto.setPosition(window.getSize().x / 2 - texto.getGlobalBounds().width / 2,
                           window.getSize().y / 2 + mensajeSprite.getGlobalBounds().height / 2 + 20);

        sf::Clock reloj;
        while (reloj.getElapsedTime().asSeconds() < 2.0f) {
            window.clear();
            window.draw(mensajeSprite);
            window.draw(texto);
            window.display();
        }

        while (true) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    return; // Retornar al menú
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(jefeSprite);
        window.draw(banderaSprite);
    }
};