#ifndef ESCENARIO_HPP
#define ESCENARIO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Personaje.hpp"  

class Escenario {
private:
    sf::Texture fondoTexture, bloqueTexture, monedaTexture;
    sf::Sprite fondoSprite;
    std::vector<sf::Sprite> plataformas;
    std::vector<sf::Sprite> monedas;

    sf::Font font;
    sf::Text puntajeText;
    sf::Text enemigosText;
    sf::Text cuentaRegresivaText;  

    int puntaje = 0;
    int enemigosMuertos = 0;
    sf::Clock relojCuentaRegresiva;
    int duracionInicial = 120; 

public:
    Escenario();
    void Dibujar(sf::RenderWindow& window, float tiempoRestanteSegundos); 
    void AgregarPlataforma(float x, float y);
    void GenerarMoneda(float x, float y);
    void ActualizarMonedas(const sf::FloatRect& boundsPersonaje);
    void IncrementarPuntaje(int cantidad);    
    int ObtenerMonedasRecogidas() const { return puntaje; }
    int ObtenerEnemigosMuertos() const { return enemigosMuertos; }
    int ObtenerTiempoRestante();  
    const std::vector<sf::Sprite>& ObtenerPlataformas() const;
    void VerificarColisionConPlataformas(Personaje& personaje);  
    void Actualizar(float deltaTime, Personaje& personaje);
};

#endif
