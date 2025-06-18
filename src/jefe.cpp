#include "jefe.hpp"
#include "personajes.hpp"
#include <iostream>

Jefe::Jefe(sf::Vector2f position) {
    if (!jefeTexture.loadFromFile("assets/img/img_finales/jefe.png")) {
        std::cerr << "Error al cargar jefe.png\n";
    }
    jefeSprite.setTexture(jefeTexture);
    jefeSprite.setPosition(position);

    if (!banderaTexture.loadFromFile("assets/img/img_finales/bandera_4.png")) {
        std::cerr << "Error al cargar bandera.png\n";
    }
    banderaSprite.setTexture(banderaTexture);
    banderaSprite.setPosition(1000, 450);    

    relojAparicion.restart();

    if (!bufferSalto.loadFromFile("assets/img/sound/salto_jefe.ogg"))
        std::cerr << "Error al cargar sonido salto_jefe.ogg\n";
    sonidoSalto.setBuffer(bufferSalto);

    if (!bufferVictoria.loadFromFile("assets/img/sound/victoria.ogg"))
        std::cerr << "Error al cargar sonido victoria.ogg\n";
    sonidoVictoria.setBuffer(bufferVictoria);
}

void Jefe::mover() {
    float tiempoTranscurrido = relojMovimiento.getElapsedTime().asSeconds();

    // Movimiento horizontal controlado
    if (saltando) {
        // Fase de salto
        velocidadY += gravedad;
        jefeSprite.move(0, velocidadY);
        if (jefeSprite.getPosition().y >= 520) {
            jefeSprite.setPosition(jefeSprite.getPosition().x, 520);
            enElAire = false;
            saltando = false;
            relojMovimiento.restart();  // Inicia nuevo ciclo
        }
    } else if (esperando) {
        if (tiempoTranscurrido >= 0.5f) {
            esperando = false;
            saltando = true;
            velocidadY = velocidadSalto;
            sonidoSalto.play();
            relojMovimiento.restart();
        }
    } else {
        if (tiempoTranscurrido < 2.0f) {
            // Movimiento horizontal (2 segundos)
            float velocidad = 500.0f / 2.0f;  // 200 píxeles en 2 segundos
            float dx = velocidad * relojDelta.restart().asSeconds();
            if (!moviendoAdelante) dx = -dx;

            float nuevaX = jefeSprite.getPosition().x + dx;

            // Limitar para que no se salga
            if (nuevaX >= 800 && nuevaX <= 1200 - jefeSprite.getGlobalBounds().width) {
                jefeSprite.move(dx, 0);
            }
        } else {
            moviendoAdelante = !moviendoAdelante;
            esperando = true;
            relojMovimiento.restart();
        }
    }
}

void Jefe::saltar() {
    if (!enElAire && relojSalto.getElapsedTime().asSeconds() >= (3 + rand() % 5)) {
        enElAire = true;
        velocidadY = -10;  // Saltar 10 píxeles hacia arriba
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
