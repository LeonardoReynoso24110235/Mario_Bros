#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "personajes.h"
#include "enemigos.h"
#include "jefe.h"
#include "escenario.h"

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

    float groundLevel = 800.0f;
    float tiempoParaSiguienteEnemigo = 1 + std::rand() % 5;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float tiempoTranscurrido = relojJuego.getElapsedTime().asSeconds();
        
        if (relojGenerarMoneda.getElapsedTime().asSeconds() >= 5.0f) {
            float xAleatorio = static_cast<float>(100 + std::rand() % 1000); // posición X aleatoria
            escenario.generarMoneda(xAleatorio, 0); // aparece arriba y cae
            relojGenerarMoneda.restart();
        }

        // Generar enemigos si no ha aparecido el jefe
        if (tiempoTranscurrido < 30) {
            if (relojGenerarEnemigo.getElapsedTime().asSeconds() >= tiempoParaSiguienteEnemigo && enemigos.size() < 10) {
                enemigos.emplace_back(sf::Vector2f(300 + std::rand() % 700, groundLevel));
                relojGenerarEnemigo.restart();
                tiempoParaSiguienteEnemigo = 1 + std::rand() % 5;
            }
        }

        // Cambiar música al aparecer el jefe
        if (tiempoTranscurrido >= 30.0f && personaje.getVidas() > 0 && musicaFondo.getStatus() == sf::Music::Playing) {
            musicaFondo.stop();
            musicaJefe.play();
        }

        if (!jefeAparecido && tiempoTranscurrido >= 30) {
            jefeAparecido = true;
            musicaFondo.stop();
            musicaJefe.play();
        }

        // Controles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) personaje.moverIzquierda();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) personaje.moverDerecha();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) personaje.saltar();

        personaje.actualizarGravedad();
        personaje.actualizarAnimacion();

        escenario.actualizarMonedas();

        // Actualizar enemigos
        for (auto& enemigo : enemigos) {
            enemigo.mover(window, groundLevel);
            enemigo.interactuarConJugador(personaje);
        }

        enemigos.erase(
            std::remove_if(enemigos.begin(), enemigos.end(),
                           [](const Enemigo& e) { return !e.estaActivo(); }),
            enemigos.end()
        );

        // Jefe
        if (jefeAparecido) {
            jefe.mover();
            jefe.saltar();
            jefe.lanzarBolaFuego(window, personaje);
            jefe.verificarColisionConPersonaje(personaje);
        }

        if (jefeAparecido && jefe.verificarColisionConBandera(personaje)) {
            jefe.mostrarMensajeFinal(window);
            break;
        }

        // Verificar fin del juego
        if (personaje.getVidas() <= 0 || tiempoTranscurrido >= 60) {
            std::cout << "¡Juego terminado!" << std::endl;

            // Mostrar mensaje y verificar si el jugador quiere reiniciar o salir
            bool esperandoRespuesta = true;
            while (esperandoRespuesta) {
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
            }
        }

        // Dibujar todo
        window.clear();
        escenario.dibujar(window);
        personaje.dibujar(window);
        for (auto& enemigo : enemigos) enemigo.dibujar(window);
        if (jefeAparecido) jefe.draw(window);
        window.display();
    }

    return 0;
}
