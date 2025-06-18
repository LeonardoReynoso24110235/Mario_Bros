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
    int vidas = 3;
    bool saltando = false;
    bool enReposo = true;
    bool enPlataforma = false; 

    float velocidadSalto = 0.0f;
    float gravedad = 0.5f;
    float alturaSalto = -10.0f;

    sf::Vector2f posicionInicial;

    std::vector<std::shared_ptr<sf::Texture>> texturasPequeno;
    int frameActual = 0;

    sf::Texture texturaMuerte;
    sf::SoundBuffer bufferMuerte;
    sf::Sound sonidoMuerte;

    std::vector<sf::RectangleShape> plataformas;
    sf::Music* soundtrack1 = nullptr;
    sf::Music* soundtrack2 = nullptr;

public:
    Personaje(sf::Vector2f position);
    Personaje(sf::Vector2f position, sf::Color color);

    void moverIzquierda();
    void moverDerecha();
    void saltar();
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
    void dibujarPlataformas(sf::RenderWindow& window);  // Mantener solo esta declaración
    void setEnPlataforma(bool estado);
    void setPosicionY(float y);
    void setVelocidadY(float velocidadY);
    void asignarMusica(sf::Music* musica1, sf::Music* musica2);
    void verificarColisionConPlataforma(const sf::FloatRect& plataformaBounds);
};

#endif // PERSONAJES_HPP
