#ifndef PERSONAJES_HPP
#define PERSONAJES_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

#include "enemigos.hpp"

class Personaje {
private:
    sf::Sprite sprite;
    int vidas = 1;
    bool saltando = false;
    bool enReposo = true;
    bool esGrande = false;

    float velocidadSalto = 0.0f;
    float gravedad = 0.5f;
    float alturaSalto = -10.0f;

    sf::Vector2f posicionInicial;

    std::vector<std::shared_ptr<sf::Texture>> texturasPequeno;
    std::vector<std::shared_ptr<sf::Texture>> texturasGrande;
    int frameActual = 0;

    sf::Texture texturaMuerte;
    sf::SoundBuffer bufferMuerte;
    sf::Sound sonidoMuerte;

    std::vector<sf::RectangleShape> plataformas;

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
    void restablecer();
    sf::FloatRect getBounds() const;
    bool isJumpingOn(Enemigo& enemy);
    void detenerMovimiento(); 
    void perderTodasLasVidas();
};

#endif // PERSONAJES_H
