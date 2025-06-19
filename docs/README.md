# Mario_Bros

### Integrantes:
- Jeremy Gael Vázquez Jiménez  
- Leonardo Reynoso Arana

---

# Cetianos Bros - Videojuego

## Descripción del Proyecto

**Cetianos Bros** es un videojuego de plataformas desarrollado en **C++** usando la biblioteca **SFML**. El jugador controla a un personaje que debe recolectar monedas, derrotar enemigos y finalmente enfrentarse a un jefe para completar el juego. El estilo visual es retro, inspirado en clásicos de plataformas como *Super Mario Bros*.

El juego se desarrolla en un escenario con plataformas compuestas por bloques personalizados, donde el personaje puede caminar, saltar sobre enemigos para eliminarlos, recoger monedas y evitar los ataques del jefe final.

---

## Manual de Usuario

### Objetivo del Juego:
- Recolectar la mayor cantidad de monedas posible.
- Eliminar enemigos saltando sobre ellos.
- Sobrevivir hasta enfrentarte al jefe final y alcanzar la bandera para ganar.

### Controles:
| Tecla              | Acción                    |
|--------------------|---------------------------|
| Flecha izquierda   | Mover a la izquierda      |
| Flecha derecha     | Mover a la derecha        |
| Barra espaciadora  | Saltar                    |

### Instrucciones:
1. Inicia el juego y explora el escenario saltando entre plataformas.
2. Recoge monedas que aparecen cada 5 segundos.
3. Enemigos aparecerán cada 1 a 5 segundos. Puedes eliminarlos si les saltas encima.
4. A los 30 segundos aparecerá el jefe, quien realiza saltos y ataques.
5. Si el jefe te alcanza, perderás el juego.
6. Si logras alcanzar la bandera ganas.

---

## Características Principales

- Movimiento lateral y salto del personaje.
- Plataformas con colisión que el personaje puede pisar.
- Enemigos que aparecen aleatoriamente cada 1 a 5 segundos y pueden ser eliminados si el personaje les cae encima.
- Monedas que aparecen cada 5 segundos y se recogen al tocarlas.
- Jefe que aparece a los 30 segundos de juego y realiza saltos y ataques.
- Si el personaje es alcanzado por el jefe, pierde vidas.
- Cuando las vidas llegan a 0 o se acaba el tiempo, se muestra la pantalla de "GAME OVER".
- Sistema HUD que muestra:
  - Vidas restantes
  - Monedas recolectadas
  - Enemigos eliminados
  - Tiempo restante

---

## Condiciones de Fin del Juego

**Game Over:**
- El personaje pierde todas sus vidas.
- Se alcanza el tiempo límite (60 segundos).

**Victoria:**
- El jugador derrota al jefe final y alcanza la bandera.
- Se muestra un mensaje de victoria y termina el juego.

---

## Audio

- Música de fondo: `soundtrack.ogg`
- Música del jefe: `soundtrack_2.ogg`
- Efecto de sonido al morir: `muerte.ogg`
- Efecto de salto: `salto.ogg`
- Efecto de correr: `correr.ogg`
- Efecto de golpe: `golpear.ogg`
- Efecto de moneda: `moneda.ogg`
- Efecto de salto del jefe: `salto_jefe.ogg`
- Efecto de victoria: `victoria.ogg`

---

## Estructura del Código

- `main.cpp`: Lógica principal del juego y el ciclo principal.
- `personajes.hpp / cpp`: Control del personaje, animación, gravedad y colisiones.
- `enemigos.hpp / cpp`: Generación y comportamiento de enemigos comunes.
- `jefe.hpp / cpp`: Lógica del jefe, ataques y colisiones.
- `escenario.hpp / cpp`: Dibujo del fondo, plataformas y monedas.
- `hud.hpp / cpp`: Interfaz de usuario (tiempo, monedas).
- `puntaje.hpp / cpp`: Guardado y lectura del puntaje máximo.

---

## Recursos

- Texturas del personaje, enemigos, plataformas y monedas: `assets/img/img_finales/`
- Música y sonidos: `assets/img/sound/`
- Fuente de texto pixelada: `letraPixel.ttf`

---

## Requisitos del Sistema

**Requisitos mínimos:**
- Sistema operativo: Windows 10, Linux o macOS.
- Procesador: Intel Core i3 o equivalente.
- Memoria RAM: 4 GB.
- Tarjeta gráfica: Compatible con OpenGL 2.1.
- Resolución recomendada: 1200 x 675 píxeles.
- Espacio en disco: Al menos 200 MB libres.
- Bibliotecas requeridas: [SFML 2.5](https://www.sfml-dev.org/download.php)

**Compilador:**
- Compatible con C++17 (por ejemplo, `g++`, `clang++` o Visual Studio)

---

## Cómo Compilar

Asegúrate de tener SFML correctamente instalada y ejecuta:

```bash
make run