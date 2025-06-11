#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "personajes.h"

class Enemigo {
public:
    Enemigo(sf::Vector2f position); 
    Enemigo(sf::Vector2f position, sf::Color color);
    Enemigo(sf::Vector2f position, sf::Color color, float groundLevel); 

    void mover(sf::RenderWindow& window, float groundLevel);  // Método para mover al enemigo
    void interactuarConJugador(Personaje& personaje);  // Método para interactuar con el jugador
    void jump();  // Método para saltar (si es necesario)
    void cargarImagenAleatoria();  // Método para cargar una imagen aleatoria
    bool isEliminado() const;  // Método para verificar si el enemigo ha sido eliminado
    void verificarColisionConPersonaje(Personaje& personaje); // Verifica la colisión con el personaje
    void dibujar(sf::RenderWindow& window);  // Método para dibujar al enemigo en la ventana

private:
    sf::RectangleShape shape;  // Forma de la colisión del enemigo
    sf::Sprite enemigoSprite;  // Sprite que representa visualmente al enemigo
    sf::Texture texturaEnemigo1;  // Textura del enemigo
    sf::Texture texturaEnemigo2;  // Otra textura del enemigo (si es necesario)
    std::vector<sf::Texture> texturasMovimiento;  // Lista de texturas para la animación del movimiento
    sf::Clock relojAnimacion;  // Reloj para animación
    sf::Clock relojSalto;  // Reloj para el salto
    sf::SoundBuffer saltoEnemigoBuffer;  // Buffer para el sonido del salto
    sf::Sound saltoEnemigoSound;  // Sonido del salto
    int frameActual = 0;  // Frame actual para la animación
    bool eliminado = false;  // Estado de eliminación del enemigo
    int direccion;  // Dirección en la que se mueve el enemigo
    int contadorMovimiento;  // Contador para las animaciones de movimiento
};

#endif // ENEMIGOS_H