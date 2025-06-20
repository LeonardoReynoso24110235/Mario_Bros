#ifndef PERSONAJES_HPP
#define PERSONAJES_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

#include "Enemigo.hpp"

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

    void MoverIzquierda();
    void MoverDerecha();
    void Saltar();
    void ActualizarGravedad();
    void ActualizarAnimacion();
    void Dibujar(sf::RenderWindow& window);
    int ObtenerVidas() const;
    void PerderVida();
    void Restablecer();
    sf::FloatRect ObtenerLimites() const;
    bool Saltar(Enemigo& enemy);
    void DetenerMovimiento(); 
    void PerderTodasLasVidas();
    void DibujarPlataformas(sf::RenderWindow& window);  // Mantener solo esta declaración
    void SaberEnPlataforma(bool estado);
    void SaberPosicionY(float y);
    void SaberVelocidadY(float velocidadY);
    void AsignarMusica(sf::Music* musica1, sf::Music* musica2);
    void VerificarColisionConPlataforma(const sf::FloatRect& plataformaBounds);
};

#endif 