#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Personaje.hpp"
#include "Enemigo.hpp"
#include "Jefe.hpp"
#include "Escenario.hpp"
#include "Hud.hpp"
#include "Puntaje.hpp"
#include <locale>
#include <clocale>

int main() {
    std::setlocale(LC_ALL, "es_ES.UTF-8");
    sf::RenderWindow window(sf::VideoMode(1200, 675), "Cetianos Bros");

    HUD hud;
    Escenario escenario;
    Personaje personaje(sf::Vector2f(100, 550));
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::Clock relojJuego;
    sf::Clock relojGenerarEnemigo;
    sf::Clock relojGenerarMoneda;
    bool jefeAparecido = false;

    std::vector<Enemigo> enemigos;
    Jefe jefe(sf::Vector2f(800, 550));

    sf::Music musicaFondo;
    if (!musicaFondo.openFromFile("assets/img/sound/soundtrack.ogg")) return -1;
    musicaFondo.setLoop(true);
    musicaFondo.play();

    sf::Music musicaJefe;
    if (!musicaJefe.openFromFile("assets/img/sound/soundtrack_2.ogg")) return -1;
    musicaJefe.setLoop(true);

    personaje.AsignarMusica(&musicaFondo, &musicaJefe); 

    float groundLevel = 600.0f;
    float tiempoParaSiguienteEnemigo = 1 + std::rand() % 5;
    float tiempoTranscurrido = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        tiempoTranscurrido = relojJuego.getElapsedTime().asSeconds();

        if (relojGenerarMoneda.getElapsedTime().asSeconds() >= 5.0f) {
            float xAleatorio = static_cast<float>(100 + std::rand() % 1000);
            escenario.GenerarMoneda(xAleatorio, 0);
            relojGenerarMoneda.restart();
        }

        if (tiempoTranscurrido < 30) {
            if (relojGenerarEnemigo.getElapsedTime().asSeconds() >= tiempoParaSiguienteEnemigo && enemigos.size() < 10) {
                enemigos.emplace_back(sf::Vector2f(300 + std::rand() % 700, groundLevel));
                relojGenerarEnemigo.restart();
                tiempoParaSiguienteEnemigo = 1 + std::rand() % 5;
            }
        }

        if (tiempoTranscurrido >= 30.0f && personaje.ObtenerVidas() > 0 && musicaFondo.getStatus() == sf::Music::Playing) {
            musicaFondo.stop();
            musicaJefe.play();
        }

        if (!jefeAparecido && tiempoTranscurrido >= 30) {
            jefeAparecido = true;
        }

        if (personaje.ObtenerVidas() > 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) personaje.MoverIzquierda();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) personaje.MoverDerecha();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) personaje.Saltar();
        }

        personaje.ActualizarGravedad();
        escenario.VerificarColisionConPlataformas(personaje); 
        personaje.ActualizarAnimacion();

        escenario.ActualizarMonedas(personaje.ObtenerLimites()); // <- Cambiado

        for (auto& enemigo : enemigos) {
            enemigo.Mover(window, groundLevel);
            enemigo.InteractuarConJugador(personaje);
        }

        enemigos.erase(
            std::remove_if(enemigos.begin(), enemigos.end(),
                           [](const Enemigo& e) { return !e.ObtenerEstaActivo(); }), // <- Cambiado
            enemigos.end()
        );

        if (jefeAparecido) {
            jefe.Mover();
            jefe.Saltar();            
            jefe.VerificarColisionConPersonaje(personaje);            
        }

        if (jefeAparecido && jefe.VerificarColisionConBandera(personaje)) {
            jefe.MostrarMensajeFinal(window);
            break;
        }

        if ((personaje.ObtenerVidas() <= 0 || tiempoTranscurrido >= 120)) {
            if (personaje.ObtenerVidas() > 0) {
                personaje.PerderTodasLasVidas();  
            }

            sf::Font font;
            if (!font.loadFromFile("assets/img/text/letraPixel.ttf")) {
                std::cerr << "Error cargando fuente." << std::endl;
            }

            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("GAME OVER");
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(400, 250);

            sf::Text restartText;
            restartText.setFont(font);
            restartText.setString("Presiona ENTER para reiniciar, \n\nESC para salir.");
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
                    personaje.Restablecer();
                    enemigos.clear();
                    jefeAparecido = false;
                    relojJuego.restart();
                    relojGenerarEnemigo.restart();
                    musicaFondo.play();
                    musicaJefe.stop();
                    break;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                    break;
                }

                window.clear();
                escenario.Dibujar(window, 120 - tiempoTranscurrido);
                personaje.Dibujar(window);
                window.draw(gameOverText);
                window.draw(restartText);
                window.display();
            }
        }

       hud.Actualizar(personaje.ObtenerVidas(), escenario.ObtenerMonedasRecogidas(), 120 - tiempoTranscurrido);

        window.clear();
        escenario.Dibujar(window, 120 - tiempoTranscurrido);
        if (jefeAparecido) jefe.Dibujar(window);
        personaje.DibujarPlataformas(window);
        personaje.Dibujar(window);
        for (auto& enemigo : enemigos) enemigo.Dibujar(window);        
        hud.Dibujar(window);
        window.display();
    }    

    Puntaje::GuardarPuntaje(personaje.ObtenerVidas() * 3);
    std::cout << "Puntaje maximo: " << Puntaje::ObtenerPuntajeMaximo() << std::endl;

    return 0;
}