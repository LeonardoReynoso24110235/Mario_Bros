#include "hud.hpp"
#include <iostream>

using namespace std;

HUD::HUD() {
    if (!font.loadFromFile("assets/img/text/pixely[1].ttf")) {
        std::cerr << "Error cargando fuente" << std::endl;
    }

    // Inicialización de los textos (vidas, monedas, enemigos y tiempo)
    textoVidas.setFont(font);
    textoVidas.setCharacterSize(24);
    textoVidas.setFillColor(sf::Color::White);

    textoMonedas.setFont(font);
    textoMonedas.setCharacterSize(24);
    textoMonedas.setFillColor(sf::Color::White);

    textoEnemigos.setFont(font);
    textoEnemigos.setCharacterSize(24);
    textoEnemigos.setFillColor(sf::Color::Red);

    textoTiempoRestante.setFont(font);
    textoTiempoRestante.setCharacterSize(24);
    textoTiempoRestante.setFillColor(sf::Color::Yellow);
}

void HUD::actualizar(int vidas, int monedas, int enemigosMuertos, float tiempoRestante) {
    textoVidas.setString("Vidas: " + std::to_string(vidas));
    textoMonedas.setString("Monedas: " + std::to_string(monedas));
    textoEnemigos.setString("Enemigos: " + std::to_string(enemigosMuertos));

    int minutos = static_cast<int>(tiempoRestante) / 60;
    int segundos = static_cast<int>(tiempoRestante) % 60;
    textoTiempoRestante.setString("Tiempo: " + std::to_string(minutos) + ":" + (segundos < 10 ? "0" : "") + std::to_string(segundos));
}

void HUD::dibujar(sf::RenderWindow& window) {
    window.draw(textoVidas);
    window.draw(textoMonedas);
    window.draw(textoEnemigos);
    window.draw(textoTiempoRestante);  // Dibuja el tiempo restante
}
