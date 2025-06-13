#ifndef JEFE_H
#define JEFE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

// Declaración anticipada de la clase Personaje
class Personaje;

class Jefe {
private:
    sf::Sprite jefeSprite;
    sf::Texture jefeTexture;
    sf::Sprite bolaFuegoSprite;
    sf::Texture bolaFuegoTexture;
    sf::Sprite banderaSprite;
    sf::Texture banderaTexture;
    sf::Clock relojMovimiento;
    sf::Clock relojBolaFuego;
    sf::Clock relojSalto;
    sf::SoundBuffer bufferBolaFuego;
    sf::SoundBuffer bufferSalto;
    sf::Sound sonidoBolaFuego;
    sf::Sound sonidoSalto;
    sf::SoundBuffer bufferVictoria;
    sf::Sound sonidoVictoria;
    bool moviendoAdelante = true;

public:
    Jefe(sf::Vector2f position);
    
    void mover();
    void lanzarBolaFuego(sf::RenderWindow& window, Personaje& personaje);
    void saltar();
    void verificarColisionConPersonaje(Personaje& personaje);
    bool verificarColisionConBandera(Personaje& personaje);
    void mostrarMensajeFinal(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif // JEFE_H
