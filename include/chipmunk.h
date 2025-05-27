#ifndef CHIPMUNK_H
#define CHIPMUNK_H

// Definición de cpVect
typedef struct cpVect {
    float x;
    float y;
} cpVect;

// Función para crear un cpVect
static inline cpVect cpv(float x, float y) {
    cpVect v = {x, y};
    return v;
}

// Declaración de cpSpace
typedef struct cpSpace cpSpace;

// Funciones relacionadas con cpSpace
cpSpace* cpSpaceNew();
void cpSpaceFree(cpSpace* space);
void cpSpaceSetGravity(cpSpace* space, cpVect gravity);

#endif // CHIPMUNK_H
