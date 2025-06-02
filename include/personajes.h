#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Incluir para el manejo de audio
#include <vector> // Incluir para el uso de std::vector

class Personaje {
public:
    Personaje(sf::Vector2f position, sf::Color color);
    void move(float offsetX);
    void jump();
    void applyGravity(float gravity, float groundLevel);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const; // Devuelve los límites del personaje
    bool isJumpingOn(const sf::RectangleShape& enemigoShape) const; // Verifica si está saltando sobre un enemigo
    void perderVida(); // Reduce las vidas del personaje
    void eliminarEnemigo(sf::RectangleShape& enemigoShape); // Declarar la función para eliminar enemigos
    void recogerMoneda(); // Función para acumular puntos al recoger monedas
    int getPuntos() const; // Obtener los puntos acumulados
    void mostrarHUD(sf::RenderWindow& window, sf::Clock& relojJuego); // Mostrar HUD con vidas, puntos y tiempo
    bool verificarTiempo(sf::Clock& relojJuego); // Verificar si el tiempo límite se ha excedido

private:
    sf::RectangleShape shape;
    float velocityY;
    bool isJumping;
    const float jumpStrength = 5.0f;
    int vidas = 3; // Número de vidas del personaje
    int puntos = 0; // Puntos acumulados por el personaje

    // Sonidos y buffers
    sf::SoundBuffer saltoBuffer;
    sf::SoundBuffer golpearBuffer;
    sf::SoundBuffer correrBuffer;
    sf::Sound saltoSound;
    sf::Sound golpearSound;
    sf::Sound correrSound;

    // Animación
    std::vector<sf::Texture> texturasMovimientoPersonaje;
    int frameActualPersonaje = 0;
    sf::Sprite personajeSprite;
    sf::Clock relojAnimacionPersonaje;
};

#endif // PERSONAJES_H