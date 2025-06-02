#ifndef BOX2D_INTEGRATION_H
#define BOX2D_INTEGRATION_H

#include <box2d/box2d.h>

// Función auxiliar para crear un cuerpo dinámico en Box2D
inline b2Body* crearCuerpoDinamico(b2World& mundo, float x, float y, float ancho, float alto) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    b2Body* body = mundo.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(ancho / 2.0f, alto / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    return body;
}

#endif // BOX2D_INTEGRATION_H
