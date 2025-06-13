#include "escenario.h"
#include <iostream>

Escenario::Escenario() {
    if (!fondoTexture.loadFromFile("assets/img/img_finales/fondo_final.jpg")) {
        std::cerr << "Error: No se pudo cargar fondo_final.jpg" << std::endl;
        return;
    }
    fondoSprite.setTexture(fondoTexture);

    if (!bloqueTexture.loadFromFile("assets/img/img_finales/bloque.png")) {
        std::cerr << "Error: No se pudo cargar bloque.png" << std::endl;
        return;
    }

    if (!monedaTexture.loadFromFile("assets/img/img_finales/moneda.png")) {
        std::cerr << "Error: No se pudo cargar moneda.png" << std::endl;
        return;
    }

    if (!font.loadFromFile("assets/img/text/pixely[1].ttf")) {
        std::cerr << "Error al cargar pixely[1].ttf" << std::endl;
    }
    puntajeText.setFont(font);
    puntajeText.setCharacterSize(24);
    puntajeText.setFillColor(sf::Color::White);
    puntajeText.setPosition(10, 10);
    puntaje = 0;

    float x = (1200 - (6 * 50)) / 2;
    agregarPlataforma(x, 450);
}

void Escenario::dibujar(sf::RenderWindow& window) {
    window.draw(fondoSprite);
    for (const auto& plataforma : plataformas)
        window.draw(plataforma);
    for (const auto& moneda : monedas)
        window.draw(moneda);
    puntajeText.setString("Puntaje: " + std::to_string(puntaje));
    window.draw(puntajeText);
}

void Escenario::agregarPlataforma(float x, float y) {
    for (int i = 0; i < 6; ++i) {
        sf::Sprite plataforma;
        plataforma.setTexture(bloqueTexture);
        plataforma.setPosition(x + i * 30, y);
        plataformas.push_back(plataforma);
    }
}

void Escenario::generarMoneda(float x, float y) {
    sf::Sprite moneda;
    moneda.setTexture(monedaTexture);
    moneda.setPosition(x, y);
    monedas.push_back(moneda);
}

void Escenario::actualizarMonedas(const sf::FloatRect& boundsPersonaje) {
    const float limiteInferior = 575.0f;
    monedas.erase(
        std::remove_if(monedas.begin(), monedas.end(),
            [&](sf::Sprite& moneda) {
                moneda.move(0, 5);
                bool tocandoPlataforma = false;
                for (const auto& plataforma : plataformas) {
                    if (moneda.getGlobalBounds().intersects(plataforma.getGlobalBounds())) {
                        moneda.setPosition(moneda.getPosition().x, plataforma.getPosition().y - moneda.getGlobalBounds().height);
                        tocandoPlataforma = true;
                        break;
                    }
                }
                if (!tocandoPlataforma && moneda.getPosition().y >= limiteInferior) {
                    moneda.setPosition(moneda.getPosition().x, limiteInferior - moneda.getGlobalBounds().height);
                }
                if (moneda.getGlobalBounds().intersects(boundsPersonaje)) {
                    incrementarPuntaje(1);
                    return true;
                }
                return false;
            }),
        monedas.end());
}

void Escenario::incrementarPuntaje(int cantidad) {
    puntaje += cantidad;
}
