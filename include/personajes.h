#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <SFML/Graphics.hpp>

class Personaje {
private:
    sf::RectangleShape personajeShape;
    int vidas;
    float velocidadY;
    bool enSuelo;

public:
    Personaje(sf::Vector2f position);
    void moverIzquierda();
    void moverDerecha();
    void saltar();
    void actualizarGravedad();
    void actualizarAnimacion();
    void dibujar(sf::RenderWindow& window);
    int getVidas() const;
    void restablecer();
    sf::FloatRect getBounds() const;
};

#endif // PERSONAJES_H