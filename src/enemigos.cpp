#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// #include <box2d/box2d.h> // Usar la versión moderna de Box2D
#include "enemigos.h"
#include "personajes.h"

// Implementación de las funciones relacionadas con los enemigos
void Enemigo::mover(sf::RenderWindow& window, float groundLevel) {
    // Actualizar animación
    if (relojAnimacion.getElapsedTime().asSeconds() > 0.2f) {
        frameActual = (frameActual + 1) % texturasMovimiento.size();
        enemigoSprite.setTexture(texturasMovimiento[frameActual]);
        relojAnimacion.restart();
    }

    // --- Código de Box2D eliminado/comentado ---
    // b2BodyDef bodyDef;
    // bodyDef.type = b2_dynamicBody;
    // bodyDef.position.Set(enemigoSprite.getPosition().x, enemigoSprite.getPosition().y);
    // b2Body* body = mundoEnemigos.CreateBody(&bodyDef);
    // b2PolygonShape dynamicBox;
    // dynamicBox.SetAsBox(enemigoSprite.getGlobalBounds().width / 2.0f, enemigoSprite.getGlobalBounds().height / 2.0f);
    // b2FixtureDef fixtureDef;
    // fixtureDef.shape = &dynamicBox;
    // fixtureDef.density = 1.0f;
    // fixtureDef.friction = 0.3f;
    // body->CreateFixture(&fixtureDef);
    // mundoEnemigos.Step(1.0f / 60.0f, 6, 2);
    // enemigoSprite.setPosition(body->GetPosition().x, body->GetPosition().y);
    // ------------------------------------------

    // Lógica de colisión con el suelo usando solo SFML
    if (enemigoSprite.getPosition().y + enemigoSprite.getGlobalBounds().height > groundLevel) {
        enemigoSprite.setPosition(enemigoSprite.getPosition().x, groundLevel - enemigoSprite.getGlobalBounds().height);
    }

    window.draw(enemigoSprite);
}

void Enemigo::interactuarConJugador(Personaje& personaje) {
    if (shape.getGlobalBounds().intersects(personaje.getBounds())) {
        if (personaje.isJumpingOn(shape)) {
            eliminado = true; // Elimina al enemigo
        } else {
            personaje.perderVida(); // Quita una vida al personaje
        }
    }
}

Enemigo::Enemigo(sf::Vector2f position, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(position);
    shape.setFillColor(color);
    direccion = 1;
    contadorMovimiento = 0;
    eliminado = false;

    // Cargar texturas para animaciones
    for (int i = 1; i <= 4; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("../assets/img_finales/koopa" + std::to_string(i) + ".png")) {
            std::cerr << "Error: No se pudo cargar el recurso 'enemigo_" + std::to_string(i) + ".png'" << std::endl;
            return;
        }
        texturasMovimiento.push_back(textura);
    }

    enemigoSprite.setTexture(texturasMovimiento[0]);
    enemigoSprite.setPosition(position);

    // Inicializar sonido de salto del enemigo
    if (!saltoEnemigoBuffer.loadFromFile("../assets/sound/salto.mp3")) {
        std::cerr << "Error al cargar el sonido de salto enemigo.\n";
    }
    if (!texturaEnemigo1.loadFromFile("../assets/img_finales/goomba.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'goomba.png'" << std::endl;
        return;
    }
    if (!texturaEnemigo1.loadFromFile("../assets/img_finales/koopa.png")) {
        std::cerr << "Error: No se pudo cargar el recurso 'koopa.png'" << std::endl;
        return;
    }

    enemigoSprite.setTexture(texturaEnemigo1);
}

// Si quieres usar Box2D 3.x, debes usar la nueva API basada en IDs y componentes, que es mucho más compleja y diferente.
// Por ejemplo, para crear un cuerpo en Box2D 3.x:
//
// #include <box2d/box2d.h>
// b2WorldDef worldDef;
// b2WorldId worldId = b2CreateWorld(&worldDef);
// b2BodyDef bodyDef = b2DefaultBodyDef();
// bodyDef.type = b2_dynamicBody;
// bodyDef.position = {x, y};
// b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
// b2Polygon box = b2MakeBox(halfWidth, halfHeight);
// b2ShapeDef shapeDef = b2DefaultShapeDef();
// b2CreatePolygonShape(worldId, bodyId, &shapeDef, &box);
// ...
//
// Sin embargo, adaptar todo tu código a la nueva API requiere una reestructuración importante.
//