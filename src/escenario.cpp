// escenario.cpp

#include "escenario.hpp"
#include <iostream>

Escenario::Escenario() {
    if (!fondoTexture.loadFromFile("assets/img/img_finales/fondo_final.jpg")) {
        std::cerr << "Error cargando fondo_final.jpg\n";
    }
    fondoSprite.setTexture(fondoTexture);

    if (!bloqueTexture.loadFromFile("assets/img/img_finales/bloque.png")) {
        std::cerr << "Error cargando bloque.png\n";
    }

    if (!monedaTexture.loadFromFile("assets/img/img_finales/moneda.png")) {
        std::cerr << "Error cargando moneda.png\n";
    }

    if (!font.loadFromFile("assets/img/text/letraPixel.ttf")) {
        std::cerr << "Error cargando letraPixel.ttf\n";
    }

    // Configuración de textos
    puntajeText.setFont(font);
    puntajeText.setCharacterSize(20);
    puntajeText.setFillColor(sf::Color::Yellow);
    puntajeText.setPosition(10, 10);

    enemigosText.setFont(font);
    enemigosText.setCharacterSize(20);
    enemigosText.setFillColor(sf::Color::Red);
    enemigosText.setPosition(10, 40);

    cuentaRegresivaText.setFont(font);
    cuentaRegresivaText.setCharacterSize(20);
    cuentaRegresivaText.setFillColor(sf::Color::White);
    cuentaRegresivaText.setPosition(1000, 10);

    // Agregar plataformas manuales
    agregarPlataforma(300, 500);
    agregarPlataforma(400, 500);
    agregarPlataforma(500, 500);
    agregarPlataforma(700, 500);
    agregarPlataforma(800, 500);
    agregarPlataforma(900, 500);
}

void Escenario::dibujar(sf::RenderWindow& window, float tiempoRestanteSegundos) {
    window.draw(fondoSprite);

    for (const auto& plataforma : plataformas) {
        window.draw(plataforma);
    }

    for (const auto& moneda : monedas) {
        window.draw(moneda);
    }

    puntajeText.setString("Monedas Acumuladas: " + std::to_string(puntaje));
    enemigosText.setString("Enemigos Eliminados: " + std::to_string(enemigosMuertos));

    int tiempoRestante = static_cast<int>(tiempoRestanteSegundos);
    cuentaRegresivaText.setString("Tiempo: " + std::to_string(tiempoRestante));

    window.draw(puntajeText);
    window.draw(enemigosText);
    window.draw(cuentaRegresivaText);
}

void Escenario::agregarPlataforma(float x, float y) {
    sf::Sprite bloque;
    bloque.setTexture(bloqueTexture);
    bloque.setPosition(x, y);
    plataformas.push_back(bloque);
}

void Escenario::generarMoneda(float x, float y) {
    sf::Sprite moneda;
    moneda.setTexture(monedaTexture);
    moneda.setPosition(x, y);
    monedas.push_back(moneda);
}

void Escenario::actualizarMonedas(const sf::FloatRect& boundsPersonaje) {
    for (auto& moneda : monedas) {
        // Simula gravedad
        if (moneda.getPosition().y < 550) {
            moneda.move(0, 1); 
        }

        // Recolecta la moneda
        if (moneda.getGlobalBounds().intersects(boundsPersonaje)) {
            incrementarPuntaje(1);
            moneda.setPosition(-100, -100);  // Oculta la moneda
        }
    }
}

void Escenario::incrementarPuntaje(int cantidad) {
    puntaje += cantidad;
}

void Escenario::incrementarEnemigosMuertos() {
    enemigosMuertos++;
}

int Escenario::getTiempoRestante() {
    return duracionInicial - relojCuentaRegresiva.getElapsedTime().asSeconds();
}

const std::vector<sf::Sprite>& Escenario::getPlataformas() const {
    return plataformas;
}

void Escenario::verificarColisionConPlataformas(Personaje& personaje) {
    for (const auto& plataforma : plataformas) {
        personaje.verificarColisionConPlataforma(plataforma.getGlobalBounds());
    }
}

void Escenario::actualizar(float deltaTime, Personaje& personaje) {
    actualizarMonedas(personaje.getBounds());
    verificarColisionConPlataformas(personaje);
}
