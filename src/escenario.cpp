#include "Escenario.hpp"
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
    
    puntajeText.setFont(font);
    puntajeText.setCharacterSize(20);
    puntajeText.setFillColor(sf::Color::Yellow);
    puntajeText.setPosition(10, 10);    

    cuentaRegresivaText.setFont(font);
    cuentaRegresivaText.setCharacterSize(20);
    cuentaRegresivaText.setFillColor(sf::Color::White);
    cuentaRegresivaText.setPosition(1000, 10);

    AgregarPlataforma(300, 500);
    AgregarPlataforma(330, 500);
    AgregarPlataforma(360, 500);
    AgregarPlataforma(390, 500);
    AgregarPlataforma(420, 500);

    AgregarPlataforma(700, 500);
    AgregarPlataforma(730, 500);
    AgregarPlataforma(760, 500);

    AgregarPlataforma(800, 475);
    AgregarPlataforma(830, 445);
    AgregarPlataforma(860, 415);
}

void Escenario::Dibujar(sf::RenderWindow& window, float tiempoRestanteSegundos) {
    window.draw(fondoSprite);

    for (const auto& plataforma : plataformas) {
        window.draw(plataforma);
    }

    for (const auto& moneda : monedas) {
        window.draw(moneda);
    }

    puntajeText.setString("Monedas Acumuladas: " + std::to_string(puntaje));    

    int tiempoRestante = static_cast<int>(tiempoRestanteSegundos);
    //cuentaRegresivaText.setString("Tiempo: " + std::to_string(tiempoRestante));

    window.draw(puntajeText);
    window.draw(enemigosText);
    window.draw(cuentaRegresivaText);
}

void Escenario::AgregarPlataforma(float x, float y) {
    sf::Sprite bloque;
    bloque.setTexture(bloqueTexture);
    bloque.setPosition(x, y);
    plataformas.push_back(bloque);
}

void Escenario::GenerarMoneda(float x, float y) {
    sf::Sprite moneda;
    moneda.setTexture(monedaTexture);
    moneda.setPosition(x, y);
    monedas.push_back(moneda);
}

void Escenario::ActualizarMonedas(const sf::FloatRect& boundsPersonaje) {
    for (auto& moneda : monedas) {        
        if (moneda.getPosition().y < 550) {
            moneda.move(0, 1); 
        }
        
        if (moneda.getGlobalBounds().intersects(boundsPersonaje)) {
            IncrementarPuntaje(1);
            moneda.setPosition(-100, -100);  // Oculta la moneda
        }
    }
}

void Escenario::IncrementarPuntaje(int cantidad) {
    puntaje += cantidad;
}

int Escenario::GetTiempoRestante() {
    return duracionInicial - relojCuentaRegresiva.getElapsedTime().asSeconds();
}

const std::vector<sf::Sprite>& Escenario::GetPlataformas() const {
    return plataformas;
}

void Escenario::VerificarColisionConPlataformas(Personaje& personaje) {
    for (const auto& plataforma : plataformas) {
        personaje.VerificarColisionConPlataforma(plataforma.getGlobalBounds());
    }
}

void Escenario::Actualizar(float deltaTime, Personaje& personaje) {
    ActualizarMonedas(personaje.GetBounds());
    VerificarColisionConPlataformas(personaje);
}
