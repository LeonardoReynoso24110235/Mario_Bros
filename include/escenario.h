#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <SFML/Graphics.hpp>
#include <vector>

class Escenario {
private:
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;

    sf::Texture bloqueTexture;
    std::vector<sf::Sprite> plataformas;

    sf::Texture monedaTexture;
    std::vector<sf::Sprite> monedas;

    sf::Font font;
    sf::Text puntajeText;
    int puntaje;

public:
    Escenario();
    void dibujar(sf::RenderWindow& window);
    void agregarPlataforma(float x, float y);
    void generarMoneda(float x, float y);
    void actualizarMonedas(const sf::FloatRect& boundsPersonaje);
    void incrementarPuntaje(int cantidad);
};

#endif // ESCENARIO_H