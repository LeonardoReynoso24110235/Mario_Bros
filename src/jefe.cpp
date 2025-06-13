#include "jefe.h"
#include "personajes.h"

// Constructor
Jefe::Jefe(sf::Vector2f position) {
    // Cargar textura del jefe
    if (!jefeTexture.loadFromFile("assets/img/img_finales/jefe.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'jefe.png'" << std::endl;
        return;
    }
    jefeSprite.setTexture(jefeTexture);
    jefeSprite.setPosition(position);

    // Cargar textura de la bola de fuego
    if (!bolaFuegoTexture.loadFromFile("assets/img/img_finales/bola_fuego.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'bola_fuego.png'" << std::endl;
        return;
    }
    bolaFuegoSprite.setTexture(bolaFuegoTexture);

    // Cargar sonido de bola de fuego
    if (!bufferBolaFuego.loadFromFile("assets/img/sound/bola_fuego.mp3")) {
        std::cerr << "Error: No se pudo cargar 'bola_fuego.ogg'\n";
    }
    sonidoBolaFuego.setBuffer(bufferBolaFuego);

    // Cargar sonido de salto del jefe
    if (!bufferSalto.loadFromFile("assets/img/sound/salto_jefe.mp3")) {
        std::cerr << "Error: No se pudo cargar 'salto_jefe.ogg'\n";
    }
    sonidoSalto.setBuffer(bufferSalto);


    // Cargar textura de la bandera
    if (!banderaTexture.loadFromFile("assets/img/img_finales/howl.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'bandera.png'" << std::endl;
        return;
    }
    banderaSprite.setTexture(banderaTexture);
    banderaSprite.setPosition(position.x + 100, position.y); // Bandera detrás del jefe
}

// Implementación de los métodos
void Jefe::mover() {
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

void Jefe::lanzarBolaFuego(sf::RenderWindow& window, Personaje& personaje) {
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

void Jefe::saltar() {
    if (relojSalto.getElapsedTime().asSeconds() >= (rand() % 9)) {
        jefeSprite.move(0, -10); // Saltar hacia arriba
        jefeSprite.move(0, 10);  // Regresar hacia abajo
        relojSalto.restart();
    }
}

void Jefe::verificarColisionConPersonaje(Personaje& personaje) {
    if (jefeSprite.getGlobalBounds().intersects(personaje.getBounds())) {
        personaje.perderVida();
    }
}

bool Jefe::verificarColisionConBandera(Personaje& personaje) {
    return banderaSprite.getGlobalBounds().intersects(personaje.getBounds());
}

void Jefe::mostrarMensajeFinal(sf::RenderWindow& window) {
    sf::Texture mensajeTexture;
    sf::Sprite mensajeSprite;

    // Cargar textura del mensaje
    if (!mensajeTexture.loadFromFile("assets/img/img_finales/bandera.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'bandera.png'" << std::endl;
        return;
    }

    // Cargar sonido de victoria
    if (!bufferVictoria.loadFromFile("assets/img/sound/victoria.ogg")) {
        std::cerr << "Error: No se pudo cargar 'victoria.ogg'\n";
    }
    sonidoVictoria.setBuffer(bufferVictoria);

    mensajeSprite.setTexture(mensajeTexture);
    mensajeSprite.setPosition(window.getSize().x / 2 - mensajeSprite.getGlobalBounds().width / 2,
                              window.getSize().y / 2 - mensajeSprite.getGlobalBounds().height / 2);

    sf::Font font;
    if (!font.loadFromFile("assets/img/text/letraPixel.ttf")) {
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

void Jefe::draw(sf::RenderWindow& window) {
    window.draw(jefeSprite);
    window.draw(banderaSprite);
}