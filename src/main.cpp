#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "personajes.h"
#include "enemigos.h"
#include "jefe.h"
#include "escenario.h"

int main() {
    // Crear la ventana del juego
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cetianos Bros");

    // Instanciar objetos del escenario y personajes
    Escenario escenario;
    Personaje personaje(sf::Vector2f(100, 500));  // Ubicación inicial del personaje

    // Inicializar el reloj de tiempo para 2 minutos
    sf::Clock relojJuego;
    bool jefeAparecido = false;

    // Vector de enemigos
    std::vector<Enemigo> enemigos;

    // Instanciar jefe (pero no lo mostramos hasta el minuto 1:30)
    Jefe jefe(sf::Vector2f(600, 400));  // Posición inicial del jefe

    // Sonido de fondo
    sf::Music musicaFondo;
    if (!musicaFondo.openFromFile("../assets/sound/soundtrack.mp3")) {
        std::cerr << "Error al cargar la musica de fondo" << std::endl;
        return -1;
    }
    musicaFondo.setLoop(true);
    musicaFondo.play();

    // Música 2: soundtrack_2.ogg (no la reproducimos aún)
    sf::Music musicaJefe;
    if (!musicaJefe.openFromFile("../assets/sound/soundtrack_2.ogg")) {
        std::cerr << "Error al cargar soundtrack_2.ogg" << std::endl;
        return -1;
    }
    musicaJefe.setLoop(true);

    // Definir el nivel del suelo
    float groundLevel = 500.0f; // Puedes ajustar esta altura según el diseño de tu juego

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Obtener el tiempo transcurrido
        float tiempoTranscurrido = relojJuego.getElapsedTime().asSeconds();

        // Generar enemigos cada 2 segundos hasta que se acabe el tiempo o el jugador gane
        if (tiempoTranscurrido < 120) {  // Solo mientras el tiempo no haya terminado
            if (static_cast<int>(tiempoTranscurrido) % 2 == 0 && enemigos.size() < 10) {
                enemigos.push_back(Enemigo(sf::Vector2f(300 + rand() % 200, 500)));  // Generar enemigo en posiciones aleatorias
            }
        }

        // Cambiar música al jefe solo si el jugador sigue vivo
        if (tiempoTranscurrido >= 120.0f && personaje.getVidas() > 0 && musicaFondo.getStatus() == sf::Music::Playing) {
            musicaFondo.stop();
            musicaJefe.play();
        }

        // Mostrar jefe después de 2 minutos
        if (!jefeAparecido && tiempoTranscurrido >= 120) {
            jefeAparecido = true;  // El jefe aparece después de 2:00
            musicaFondo.stop();       // Detener la música anterior
            musicaJefe.play();        // Iniciar la música del jefe
        }

        // Manejo de entradas del teclado para mover al personaje
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            personaje.moverIzquierda();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            personaje.moverDerecha();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            personaje.saltar();
        }

        // Actualizar lógica del escenario, monedas y enemigos
        escenario.actualizarMonedas();
        for (auto& enemigo : enemigos) {
            enemigo.mover(window, groundLevel); // Corregir la llamada, pasando los dos parámetros
            enemigo.verificarColisionConPersonaje(personaje);
        }

        // Verificar si el jefe debe aparecer
        if (jefeAparecido) {
            jefe.mover();
            jefe.saltar();
            jefe.lanzarBolaFuego(window, personaje);
            jefe.verificarColisionConPersonaje(personaje);
        }

        // Verificar si el personaje toca la bandera (final del nivel)
        if (jefeAparecido && jefe.verificarColisionConBandera(personaje)) {
            jefe.mostrarMensajeFinal(window);
            break;  // Fin del juego, salir del bucle
        }

        // Verificar si el jugador ha perdido
        if (personaje.getVidas() <= 0) {
            std::cout << "¡Juego terminado! Has perdido." << std::endl;
            break;  // Fin del juego, salir del bucle
        }

        // Verificar si el tiempo se ha agotado
        if (tiempoTranscurrido >= 120) {
            std::cout << "¡Tiempo agotado! Has perdido." << std::endl;
            break;  // Fin del juego, salir del bucle
        }

        // Dibujar todos los elementos
        window.clear();
        escenario.dibujar(window);
        personaje.dibujar(window);

        for (auto& enemigo : enemigos) {
            enemigo.dibujar(window);
        }

        if (jefeAparecido) {
            jefe.draw(window);
        }

        window.display();
    }

    return 0;
}