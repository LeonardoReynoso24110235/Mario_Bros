#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD();
    void actualizar(int vidas, int monedas, int enemigosMuertos, float tiempoRestante);  // Cambié la declaración aquí
    void dibujar(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text textoVidas;
    sf::Text textoMonedas;
    sf::Text textoEnemigos;
    sf::Text textoTiempoRestante;  // Agregado para mostrar el tiempo restante
};

#endif // HUD_H
