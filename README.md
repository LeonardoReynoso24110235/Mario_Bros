# Mario_Bros
Intregantes 
Jeremy Gael Vazquez Jimenes
Leonardo Reynoso Arana

# Cetianos Bros - Videojuego

## Descripción del Proyecto

**Cetianos Bros** es un videojuego de plataformas desarrollado en **C++** usando la biblioteca **SFML**. El jugador controla a un personaje que debe recolectar monedas, derrotar enemigos y finalmente enfrentarse a un jefe para completar el juego. El estilo visual es retro, inspirado en clásicos de plataformas como *Super Mario Bros*.

El juego se desarrolla en un escenario con plataformas compuestas por bloques personalizados, en donde el personaje puede caminar, saltar sobre enemigos para eliminarlos, recoger monedas y evitar al jefe.

---

## Características Principales

- ✅ Movimiento lateral y salto del personaje.
- ✅ Plataformas con colisión que el personaje puede pisar.
- ✅ Enemigos que aparecen aleatoriamente cada 1 a 5 segundos y pueden ser eliminados si el personaje les cae encima.
- ✅ Monedas que aparecen cada 5 segundos y se recogen al tocarlas.
- ✅ Jefe que aparece a los 30 segundos de juego, salta.
- ✅ Si el personaje es alcanzado por el jefe directamente, pierde vidas.
- ✅ Cuando las vidas llegan a 0, el personaje muere, se muestra la pantalla de "GAME OVER".
- ✅ Sistema HUD que muestra: 
  - Monedas recolectadas
  - Tiempo restante

---

## Condiciones de Fin del Juego

- 🟥 **Game Over**:
  - El personaje pierde todas sus vidas.
  - Se alcanza el tiempo límite (60 segundos).
  
- ✅ **Victoria**:
  - El jugador derrota al jefe final y alcanza la bandera.
  - Se muestra un mensaje de victoria y termina el juego.

---

## Audio

- 🎵 Música de fondo: `soundtrack.ogg`
- 🎵 Música del jefe: `soundtrack_2.ogg`
- 🎵 Efecto de sonido al morir: `muerte.ogg`
- 🎵 Efecto de salto `salto.ogg`

---

## Estructura del Código

- `main.cpp`: Lógica principal del juego y el ciclo principal.
- `personajes.hpp/cpp`: Controla el movimiento, animación, gravedad y colisión del personaje.
- `enemigos.hpp/cpp`: Generación y comportamiento de enemigos comunes.
- `jefe.hpp/cpp`: Comportamiento del jefe, incluyendo sus ataques y colisiones.
- `escenario.hpp/cpp`: Dibujo del fondo, plataformas y monedas.
- `hud.hpp/cpp`: Interfaz del jugador (tiempo, monedas).
- `puntaje.hpp/cpp`: Guardado y lectura del puntaje máximo.

---

## Recursos

- Texturas del personaje, enemigos, plataformas y monedas.
- Música y sonidos en `assets/img/sound/`.
- Fuente pixelada para textos: `letraPixel.ttf`.

---