#ifndef ESCENARIO_HPP
#define ESCENARIO_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Escenario {
private:
    sf::Texture fondoTexture, bloqueTexture, monedaTexture;
    sf::Sprite fondoSprite;
    std::vector<sf::Sprite> plataformas;
    std::vector<sf::Sprite> monedas;

    sf::Font font;
    sf::Text puntajeText;
    sf::Text enemigosText;
    sf::Text cuentaRegresivaText;  // Cambié el nombre aquí a cuentaRegresivaText

    int puntaje = 0;
    int enemigosMuertos = 0;
    sf::Clock relojCuentaRegresiva;
    int duracionInicial = 120; // 2 minutos en segundos

public:
    Escenario();
    void dibujar(sf::RenderWindow& window, float tiempoRestanteSegundos); 
    void agregarPlataforma(float x, float y);
    void generarMoneda(float x, float y);
    void actualizarMonedas(const sf::FloatRect& boundsPersonaje);
    void incrementarPuntaje(int cantidad);
    void incrementarEnemigosMuertos();
    int getMonedasRecogidas() const { return puntaje; }
    int getEnemigosMuertos() const { return enemigosMuertos; }
    int getTiempoRestante();  // tiempo restante en segundos
};

#endif
