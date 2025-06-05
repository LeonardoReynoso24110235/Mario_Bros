#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <SFML/Graphics.hpp>
#include <vector>

class Escenario {
public:
    void dibujarFondo(sf::RenderWindow& window); // Dibujar el fondo del escenario
    void dibujarSuelo(sf::RenderWindow& window); // Dibujar el suelo
    void moverEscenario(float offsetX); // Mover el escenario junto con el personaje
    void dibujarPlataformas(sf::RenderWindow& window); // Dibujar plataformas flotantes
    void colocarMonedas(sf::RenderWindow& window); // Colocar monedas en el escenario
    void agregarBloqueInteractivo(sf::RenderWindow& window); // Agregar bloque interactivo

private:
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
};

#endif // ESCENARIO_H