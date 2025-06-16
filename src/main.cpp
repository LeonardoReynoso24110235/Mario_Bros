#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "personajes.hpp"
#include "enemigos.hpp"
#include "jefe.hpp"
#include "escenario.hpp"
#include "hud.hpp"
#include "puntaje.hpp"

HUD hud;

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 675), "Cetianos Bros");

    Escenario escenario;
    Personaje personaje(sf::Vector2f(100, 550));
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::Clock relojJuego;
    sf::Clock relojGenerarEnemigo;
    sf::Clock relojGenerarMoneda;
    bool jefeAparecido = false;

    std::vector<Enemigo> enemigos;
    Jefe jefe(sf::Vector2f(1000, 550));

    sf::Music musicaFondo;
    if (!musicaFondo.openFromFile("assets/img/sound/soundtrack.ogg")) return -1;
    musicaFondo.setLoop(true);
    musicaFondo.play();

    sf::Music musicaJefe;
    if (!musicaJefe.openFromFile("assets/img/sound/soundtrack_2.ogg")) return -1;
    musicaJefe.setLoop(true);

    float groundLevel = 700.0f;
    float tiempoParaSiguienteEnemigo = 1 + std::rand() % 5;
    float tiempoTranscurrido = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        tiempoTranscurrido = relojJuego.getElapsedTime().asSeconds();

        // Generar moneda
        if (relojGenerarMoneda.getElapsedTime().asSeconds() >= 5.0f) {
            float xAleatorio = static_cast<float>(100 + std::rand() % 1000);
            escenario.generarMoneda(xAleatorio, 0);
            relojGenerarMoneda.restart();
        }

        // Generar enemigos si aún no aparece el jefe
        if (tiempoTranscurrido < 30) {
            if (relojGenerarEnemigo.getElapsedTime().asSeconds() >= tiempoParaSiguienteEnemigo && enemigos.size() < 10) {
                enemigos.emplace_back(sf::Vector2f(300 + std::rand() % 700, groundLevel));
                relojGenerarEnemigo.restart();
                tiempoParaSiguienteEnemigo = 1 + std::rand() % 5;
            }
        }

        if (tiempoTranscurrido >= 30.0f && personaje.getVidas() > 0 && musicaFondo.getStatus() == sf::Music::Playing) {
            musicaFondo.stop();
            musicaJefe.play();
        }

        if (!jefeAparecido && tiempoTranscurrido >= 30) {
            jefeAparecido = true;
        }

        // Controles del personaje
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) personaje.moverIzquierda();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) personaje.moverDerecha();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) personaje.saltar();

        personaje.actualizarGravedad();
        personaje.actualizarAnimacion();

        escenario.actualizarMonedas(personaje.getBounds());

        for (auto& enemigo : enemigos) {
            enemigo.mover(window, groundLevel);
            enemigo.interactuarConJugador(personaje);
        }

        enemigos.erase(
            std::remove_if(enemigos.begin(), enemigos.end(),
                           [](const Enemigo& e) { return !e.estaActivo(); }),
            enemigos.end()
        );

        if (jefeAparecido) {
            jefe.mover();
            jefe.saltar();
            jefe.actualizarBolas(window, personaje);
            jefe.verificarColisionConPersonaje(personaje);
        }

        if (jefeAparecido && jefe.verificarColisionConBandera(personaje)) {
            jefe.mostrarMensajeFinal(window);
            break;
        }

        // Verificar Game Over
        if (personaje.getVidas() <= 0 || tiempoTranscurrido >= 60) {
            sf::Font font;
            if (!font.loadFromFile("assets/img/text/letraPixel.ttf")) {
                std::cerr << "Error cargando fuente." << std::endl;
            }

            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("¡GAME OVER!");
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(400, 250);

            sf::Text restartText;
            restartText.setFont(font);
            restartText.setString("Presiona ENTER para reiniciar, ESC para salir.");
            restartText.setCharacterSize(20);
            restartText.setFillColor(sf::Color::White);
            restartText.setPosition(350, 320);

            bool esperandoRespuesta = true;
            while (esperandoRespuesta && window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        esperandoRespuesta = false;
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    personaje.restablecer();
                    enemigos.clear();
                    jefeAparecido = false;
                    relojJuego.restart();
                    relojGenerarEnemigo.restart();
                    break;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                    break;
                }

                window.clear();
                window.draw(gameOverText);
                window.draw(restartText);
                window.display();
            }
        }

        // Actualizar HUD
        hud.actualizar(personaje.getVidas(), escenario.getMonedasRecogidas(), escenario.getEnemigosMuertos(), 120 - tiempoTranscurrido);

        // Dibujo único por frame
        window.clear();
        escenario.dibujar(window, 120 - tiempoTranscurrido);
        personaje.dibujar(window);
        for (auto& enemigo : enemigos) enemigo.dibujar(window);
        if (jefeAparecido) jefe.draw(window);
        hud.dibujar(window);
        window.display();
    }

    Puntaje::guardarPuntaje(personaje.getVidas() * 3);
    std::cout << "Puntaje maximo: " << Puntaje::obtenerPuntajeMaximo() << std::endl;

    return 0;
}
