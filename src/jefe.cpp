#include "Jefe.hpp"
#include "Personaje.hpp"
#include <iostream>

Jefe::Jefe(sf::Vector2f position) {
    if (!jefeTexture.loadFromFile("assets/img/img_finales/jefe.png")) {
        std::cerr << "Error al cargar jefe.png\n";
    }
    jefeSprite.setTexture(jefeTexture);
    jefeSprite.setPosition(position);

    if (!banderaTexture.loadFromFile("assets/img/img_finales/Bandera2.png")) {
        std::cerr << "Error al cargar bandera.png\n";
    }
    banderaSprite.setTexture(banderaTexture);
    banderaSprite.setPosition(1000, 525);    

    relojAparicion.restart();

    if (!bufferSalto.loadFromFile("assets/img/sound/salto_jefe.ogg"))
        std::cerr << "Error al cargar sonido salto_jefe.ogg\n";
    sonidoSalto.setBuffer(bufferSalto);

    if (!bufferVictoria.loadFromFile("assets/img/sound/victoria.ogg"))
        std::cerr << "Error al cargar sonido victoria.ogg\n";
    sonidoVictoria.setBuffer(bufferVictoria);
}

void Jefe::Mover() {
    float tiempoTranscurrido = relojMovimiento.getElapsedTime().asSeconds();
    
    if (saltando) {
        velocidadY += gravedad;
        jefeSprite.move(0, velocidadY);
        if (jefeSprite.getPosition().y >= 520) {
            jefeSprite.setPosition(jefeSprite.getPosition().x, 520);
            enElAire = false;
            saltando = false;
            relojMovimiento.restart();  
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
            float velocidad = 500.0f / 1.5f; 
            float dx = velocidad * relojDelta.restart().asSeconds();
            if (!moviendoAdelante) dx = -dx;

            float nuevaX = jefeSprite.getPosition().x + dx;
            
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

void Jefe::Saltar() {
    if (!enElAire && relojSalto.getElapsedTime().asSeconds() >= (3 + rand() % 5)) {
        enElAire = true;
        velocidadY = -10;  
        sonidoSalto.play();
        relojSalto.restart();
    }
}

void Jefe::VerificarColisionConPersonaje(Personaje& personaje) {
    if (relojAparicion.getElapsedTime().asSeconds() < 1.0f) return;
    if (jefeSprite.getGlobalBounds().intersects(personaje.GetBounds())) {
        personaje.PerderVida();
    }
}

bool Jefe::VerificarColisionConBandera(Personaje& personaje) {
    return banderaSprite.getGlobalBounds().intersects(personaje.GetBounds());
}

void Jefe::MostrarMensajeFinal(sf::RenderWindow& window) {
    sonidoVictoria.play();

    sf::Font font;
    if (!font.loadFromFile("assets/img/text/letraPixel.ttf")) return;

    sf::Text texto("Felicidades\n\n Has ganado\n\n\nPresiona ENTER para continuar", font, 28);
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

void Jefe::Draw(sf::RenderWindow& window) {
    window.draw(jefeSprite);
    window.draw(banderaSprite);
}
