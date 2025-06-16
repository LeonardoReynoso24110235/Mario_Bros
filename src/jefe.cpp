#include "jefe.hpp"
#include "personajes.hpp"
#include <iostream>

using namespace std;

Jefe::Jefe(sf::Vector2f position) {
    if (!jefeTexture.loadFromFile("assets/img/img_finales/jefe.png")) {
        std::cerr << "Error: No se pudo cargar 'jefe.png'\n";
        return;
    }
    jefeSprite.setTexture(jefeTexture);
    jefeSprite.setPosition(position);

    if (!bolaFuegoTexture.loadFromFile("assets/img/img_finales/bola_fuego.png")) {
        std::cerr << "Error: No se pudo cargar 'bola_fuego.png'\n";
        bolaFuegoVisible = false; // Imagen no cargada, usamos marcador visual
    } else {
        bolaFuegoVisible = true;
    }

    if (!banderaTexture.loadFromFile("assets/img/img_finales/bandera.png")) {
        std::cerr << "Error: No se pudo cargar 'bandera.png'\n";
        return;
    }
    banderaSprite.setTexture(banderaTexture);
    banderaSprite.setPosition(position.x + 100, position.y);

    relojAparicion.restart();

    if (!bufferBolaFuego.loadFromFile("assets/img/sound/bola_fuego.ogg"))
        std::cerr << "Error: No se pudo cargar 'bola_fuego.ogg'\n";
    sonidoBolaFuego.setBuffer(bufferBolaFuego);

    if (!bufferSalto.loadFromFile("assets/img/sound/salto_jefe.ogg"))
        std::cerr << "Error: No se pudo cargar 'salto_jefe.ogg'\n";
    sonidoSalto.setBuffer(bufferSalto);

    if (!bufferVictoria.loadFromFile("assets/img/sound/victoria.ogg"))
        std::cerr << "Error: No se pudo cargar 'victoria.ogg'\n";
    sonidoVictoria.setBuffer(bufferVictoria);
}

void Jefe::mover() {
    if (relojMovimiento.getElapsedTime().asSeconds() >= 1.0f) {
        jefeSprite.move(moviendoAdelante ? 100 : -100, 0);
        moviendoAdelante = !moviendoAdelante;
        relojMovimiento.restart();
    }

    if (enElAire) {
        velocidadY += gravedad;
        jefeSprite.move(0, velocidadY);
        if (jefeSprite.getPosition().y >= 550) {
            jefeSprite.setPosition(jefeSprite.getPosition().x, 550);
            enElAire = false;
            velocidadY = 0;
        }
    }
}

void Jefe::saltar() {
    if (!enElAire && relojSalto.getElapsedTime().asSeconds() >= (3 + rand() % 5)) {
        enElAire = true;
        velocidadY = velocidadSalto;
        sonidoSalto.play();
        relojSalto.restart();
    }
}

void Jefe::lanzarBolaFuego() {
    sf::Sprite bola;
    if (bolaFuegoVisible) {
        bola.setTexture(bolaFuegoTexture);
    } else {
        // Si no cargó la imagen, usar marcador rojo
        sf::Texture* dummyTexture = new sf::Texture();
        dummyTexture->create(20, 20); // Crear textura temporal
        bola.setTexture(*dummyTexture);
        bola.setColor(sf::Color::Red);
    }

    bola.setPosition(jefeSprite.getPosition().x, jefeSprite.getPosition().y + 25);
    bolasDeFuego.push_back(bola);
    sonidoBolaFuego.play();
    relojBolaFuego.restart();
}

void Jefe::actualizarBolas(sf::RenderWindow& window, Personaje& personaje) {
    if (relojBolaFuego.getElapsedTime().asSeconds() >= 4.0f) {
        lanzarBolaFuego();
    }

    for (auto& bola : bolasDeFuego) {
        bola.move(-1.5f, 0);  // Velocidad más suave
        window.draw(bola);

        if (bola.getGlobalBounds().intersects(personaje.getBounds())) {
            personaje.perderTodasLasVidas();  // Game over
        }
    }

    bolasDeFuego.erase(
        std::remove_if(bolasDeFuego.begin(), bolasDeFuego.end(),
                       [](const sf::Sprite& bola) {
                           return bola.getPosition().x < -50;
                       }),
        bolasDeFuego.end());
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
