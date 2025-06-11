#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>

class Personaje {
private:
    std::vector<sf::Texture> texturasPequeno;
    std::vector<sf::Texture> texturasGrande;
    sf::Vector2f posicionInicial;
    sf::Sprite sprite;
    int frameActual = 0;
    bool esGrande = false;
    sf::Clock relojAnimacion;
    int vidas;
    bool saltando = false;  // Flag para saber si el personaje está saltando
    bool enReposo = true;   // Flag para saber si el personaje está en reposo
    float velocidadSalto = 0;  // Velocidad de salto
    const float gravedad = 0.5f;  // Fuerza de la gravedad
    const float alturaSalto = -10.0f;  // Velocidad inicial del salto (negativo para ir hacia arriba)    
    sf::Texture texturaMuerte;
    sf::SoundBuffer bufferMuerte;
    sf::Sound sonidoMuerte;


public:
    Personaje(sf::Vector2f position);
    Personaje(sf::Vector2f position, sf::Color color);

    void moverIzquierda();
    void moverDerecha();
    void saltar();
    void transformarEnGrande();
    void actualizarGravedad();
    void actualizarAnimacion();
    void dibujar(sf::RenderWindow& window);

    int getVidas() const;
    void perderVida();
    bool isJumpingOn(sf::RectangleShape& enemy);
    sf::FloatRect getBounds() const;
};

#endif