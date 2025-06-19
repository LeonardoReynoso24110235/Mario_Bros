#include "Hud.hpp"
#include <iostream>

using namespace std;

HUD::HUD() {
    if (!font.loadFromFile("assets/img/text/pixely[1].ttf")) {
        std::cerr << "Error cargando fuente" << std::endl;
    }

    // Configurar estilo común
    int fontSize = 24;
    float marginTop = 10;
    float marginLeft = 10;
    float spacing = 30;

    // Vidas
    textoVidas.setFont(font);
    textoVidas.setCharacterSize(fontSize);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(marginLeft, marginTop);

    // Monedas
    textoMonedas.setFont(font);
    textoMonedas.setCharacterSize(fontSize);
    textoMonedas.setFillColor(sf::Color::White);
    textoMonedas.setPosition(marginLeft, marginTop + spacing);

    // Tiempo restante
    textoTiempoRestante.setFont(font);
    textoTiempoRestante.setCharacterSize(fontSize);
    textoTiempoRestante.setFillColor(sf::Color::White);
    textoTiempoRestante.setPosition(marginLeft, marginTop + 3 * spacing);
}

void HUD::Actualizar(int vidas, int monedas, int enemigosMuertos, float tiempoRestante) {
    //textoVidas.setString("Vidas: " + std::to_string(vidas));
    //textoMonedas.setString("Monedas: " + std::to_string(monedas));    

    int minutos = static_cast<int>(tiempoRestante) / 60;
    int segundos = static_cast<int>(tiempoRestante) % 60;
    textoTiempoRestante.setString("Tiempo restante: " + std::to_string(minutos) + ":" + (segundos < 10 ? "0" : "") + std::to_string(segundos));
}

void HUD::Dibujar(sf::RenderWindow& window) {
    window.draw(textoVidas);
    window.draw(textoMonedas);
    window.draw(textoEnemigos);
    window.draw(textoTiempoRestante);
}