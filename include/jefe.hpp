#ifndef JEFE_HPP
#define JEFE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Personaje; 

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
    
    sf::Clock relojAparicion;

    sf::Clock relojMovimiento;
    sf::Clock relojSalto;
    sf::Clock relojDelta; 
    
    bool moviendoAdelante = true;
    float distanciaRecorrida = 0.f;
    float velocidadMovimiento = 500.f / 3.5f; 

    bool enElAire = false;
    float velocidadY = 0;
    float gravedad = 0.5f;
    float velocidadSalto = -15.0f;

    bool esperando = false;
    bool saltando = false;

public:
    Jefe(sf::Vector2f position);

    void Mover();
    void Saltar();
    void VerificarColisionConPersonaje(Personaje& personaje);
    bool VerificarColisionConBandera(Personaje& personaje);
    void MostrarMensajeFinal(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
};

#endif