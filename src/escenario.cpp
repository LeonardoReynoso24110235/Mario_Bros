#include "escenario.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

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

    // Texto Monedas
    puntajeText.setFont(font);
    puntajeText.setCharacterSize(24);
    puntajeText.setFillColor(sf::Color::White);
    puntajeText.setPosition(10, 10);

    // Texto Enemigos muertos
    enemigosText.setFont(font);
    enemigosText.setCharacterSize(24);
    enemigosText.setFillColor(sf::Color::Red);
    enemigosText.setPosition(10, 40);

    // Texto Cuenta regresiva
    cuentaRegresivaText.setFont(font);  // Cambié el nombre aquí a cuentaRegresivaText
    cuentaRegresivaText.setCharacterSize(24);
    cuentaRegresivaText.setFillColor(sf::Color::Yellow);
    cuentaRegresivaText.setPosition(10, 70);

    float x = (1200 - (6 * 50)) / 2;
    agregarPlataforma(x, 450);
}

void Escenario::dibujar(sf::RenderWindow& window, float tiempoRestanteSegundos) {
    window.draw(fondoSprite);
    for (const auto& plataforma : plataformas)
        window.draw(plataforma);
    for (const auto& moneda : monedas)
        window.draw(moneda);

    // Texto Monedas
    puntajeText.setString("Monedas: " + std::to_string(puntaje));
    window.draw(puntajeText);

    // Texto Enemigos muertos
    enemigosText.setString("Enemigos derrotados: " + std::to_string(enemigosMuertos));
    window.draw(enemigosText);

    // Texto Cuenta regresiva
    int minutos = static_cast<int>(tiempoRestanteSegundos) / 60;
    int segundos = static_cast<int>(tiempoRestanteSegundos) % 60;
    std::ostringstream oss;
    oss << "Tiempo restante: " << std::setw(2) << std::setfill('0') << minutos
        << ":" << std::setw(2) << std::setfill('0') << segundos;
    cuentaRegresivaText.setString(oss.str());  // Cambié el nombre aquí a cuentaRegresivaText
    window.draw(cuentaRegresivaText);
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

void Escenario::incrementarEnemigosMuertos() {
    enemigosMuertos++;
}
