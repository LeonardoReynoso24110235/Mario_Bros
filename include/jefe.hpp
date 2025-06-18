#ifndef JEFE_HPP
#define JEFE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Personaje;  // Declaración adelantada para evitar dependencias circulares

class Jefe {
private:
    sf::Texture jefeTexture;
    sf::Sprite jefeSprite;
    sf::Texture banderaTexture;
    sf::Sprite banderaSprite;

    sf::SoundBuffer bufferSalto;
    sf::Sound sonidoSalto;
    sf::SoundBuffer bufferVictoria;
    sf::Sound sonidoVictoria;

    // Nueva variable para el control del tiempo de aparición del jefe
    sf::Clock relojAparicion;  

    // Relojes de movimiento y salto
    sf::Clock relojMovimiento;
    sf::Clock relojSalto;

    // Variables de movimiento
    bool moviendoAdelante = true;
    bool enElAire = false;
    float velocidadY = 0;
    float gravedad = 0.5f;
    float velocidadSalto = -15.0f;

public:
    Jefe(sf::Vector2f position);

    void mover();
    void saltar();
    void verificarColisionConPersonaje(Personaje& personaje);
    bool verificarColisionConBandera(Personaje& personaje);
    void mostrarMensajeFinal(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif
