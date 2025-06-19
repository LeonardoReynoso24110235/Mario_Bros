#ifndef ENEMIGOS_HPP
#define ENEMIGOS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Personaje;

class Enemigo {
private:
    sf::Sprite enemigoSprite;
    std::vector<sf::Texture> texturasMovimiento;
    sf::Texture texturaEnemigo1, texturaEnemigo2;

    sf::SoundBuffer saltoEnemigoBuffer;
    sf::Sound sonidoSalto;

    int direccion = -1; 
    int frameActual = 0;
    bool estaEliminado = false;
    sf::Clock relojAnimacion;

public:    
    Enemigo(sf::Vector2f position, sf::Color color, float groundLevel);
    Enemigo(sf::Vector2f position, sf::Color color);
    Enemigo(sf::Vector2f position);
    
    void Mover(sf::RenderWindow& window, float groundLevel);
    void InteractuarConJugador(Personaje& personaje);
    void VerificarColisionConPersonaje(Personaje& personaje);
    void Eliminar();
    void Dibujar(sf::RenderWindow& window);
    
    sf::FloatRect GetBounds() const;
    bool EstaActivo() const;
};

#endif 
