#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD();
    void Actualizar(int vidas, int monedas, float tiempoRestante);  
    void Dibujar(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text textoVidas;
    sf::Text textoMonedas;
    sf::Text textoEnemigos;
    sf::Text textoTiempoRestante; 
};

#endif 
