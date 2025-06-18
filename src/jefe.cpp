#include "jefe.hpp"
#include "personajes.hpp"
#include <iostream>

Jefe::Jefe(sf::Vector2f position) {
    if (!jefeTexture.loadFromFile("assets/img/img_finales/jefe.png")) {
        std::cerr << "Error al cargar jefe.png\n";
    }
    jefeSprite.setTexture(jefeTexture);
    jefeSprite.setPosition(position);

    if (!banderaTexture.loadFromFile("assets/img/img_finales/bandera.png")) {
        std::cerr << "Error al cargar bandera.png\n";
    }
    banderaSprite.setTexture(banderaTexture);
    banderaSprite.setPosition(1000, 550);
    banderaSprite.setScale(0.9f, 0.9f);  

    relojAparicion.restart();

    if (!bufferSalto.loadFromFile("assets/img/sound/salto_jefe.ogg"))
        std::cerr << "Error al cargar sonido salto_jefe.ogg\n";
    sonidoSalto.setBuffer(bufferSalto);

    if (!bufferVictoria.loadFromFile("assets/img/sound/victoria.ogg"))
        std::cerr << "Error al cargar sonido victoria.ogg\n";
    sonidoVictoria.setBuffer(bufferVictoria);
}

void Jefe::mover() {
    float velocidadMovimiento = 500.f / 3.f;  // 500 píxeles en 3 segundos
    if (relojMovimiento.getElapsedTime().asSeconds() >= 1.0f) {
        // Moverse 500 píxeles hacia adelante y hacia atrás en 3 segundos
        if (moviendoAdelante) {
            if (jefeSprite.getPosition().x < 500) {
                jefeSprite.move(velocidadMovimiento * relojMovimiento.getElapsedTime().asSeconds(), 0);  // Mover hacia la derecha
            } else {
                moviendoAdelante = false;
                relojMovimiento.restart();  // Reiniciar el reloj cuando cambie la dirección
            }
        } else {
            if (jefeSprite.getPosition().x > 0) {
                jefeSprite.move(-velocidadMovimiento * relojMovimiento.getElapsedTime().asSeconds(), 0);  // Mover hacia la izquierda
            } else {
                moviendoAdelante = true;
                relojMovimiento.restart();  // Reiniciar el reloj cuando cambie la dirección
            }
        }
    }

    // Lógica de salto
    if (enElAire) {
        velocidadY += gravedad;
        jefeSprite.move(0, velocidadY);
        if (jefeSprite.getPosition().y >= 550) {
            jefeSprite.setPosition(jefeSprite.getPosition().x, 550);  // Regresar al suelo
            enElAire = false;
            velocidadY = 0;
        }
    }
}

void Jefe::saltar() {
    if (!enElAire && relojSalto.getElapsedTime().asSeconds() >= (3 + rand() % 5)) {
        enElAire = true;
        velocidadY = -100;  // Saltar 100 píxeles hacia arriba
        sonidoSalto.play();
        relojSalto.restart();
    }
}

void Jefe::verificarColisionConPersonaje(Personaje& personaje) {
    if (relojAparicion.getElapsedTime().asSeconds() < 1.0f) return;
    if (jefeSprite.getGlobalBounds().intersects(personaje.getBounds())) {
        personaje.perderVida();
    }
}

bool Jefe::verificarColisionConBandera(Personaje& personaje) {
    return banderaSprite.getGlobalBounds().intersects(personaje.getBounds());
}

void Jefe::mostrarMensajeFinal(sf::RenderWindow& window) {
    sonidoVictoria.play();

    sf::Font font;
    if (!font.loadFromFile("assets/img/text/letraPixel.ttf")) return;

    sf::Text texto("¡Felicidades! Has ganado\nPresiona ENTER para continuar", font, 28);
    texto.setFillColor(sf::Color::White);
    texto.setStyle(sf::Text::Bold);
    texto.setPosition(window.getSize().x / 2 - texto.getGlobalBounds().width / 2,
                      window.getSize().y / 2 - texto.getGlobalBounds().height / 2);

    while (true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                return;
        }

        window.clear(sf::Color::Black);
        window.draw(texto);
        window.display();
    }
}

void Jefe::draw(sf::RenderWindow& window) {
    window.draw(jefeSprite);
    window.draw(banderaSprite);
}
