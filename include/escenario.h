#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <SFML/Graphics.hpp>
#include <vector>

class Escenario {
public:
    Escenario();
    void dibujar(sf::RenderWindow& window);
    void agregarPlataforma(float x, float y);
    void generarMoneda(float x, float y);
    void actualizarMonedas();
    void incrementarPuntaje(int cantidad);

private:
    sf::Text puntajeText;
    int puntaje;
    sf::RectangleShape suelo;
    sf::Sprite escenarioSprite;
    std::vector<sf::Sprite> plataformas;
    std::vector<sf::Sprite> monedas;
    sf::Clock relojMonedas;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    sf::Texture nubeTexture;
    sf::Sprite nubeIzquierda;
    sf::Sprite nubeDerecha;
    sf::Texture bloqueTexture;
    sf::Texture monedaTexture;
    sf::Font font;
};

#endif // ESCENARIO_H