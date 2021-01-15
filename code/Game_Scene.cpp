/*
 * GAME SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include "Game_Scene.hpp"
#include "Menu_Scene.hpp"

#include <cmath>
#include <cstdlib>
#include <basics/Canvas>
#include <basics/Director>
#include <basics/Texture_2D>

#include <sstream>

using namespace basics;
using namespace std;

namespace example
{
    const char * Game_Scene::sprites_atlas_path = "atlaskybubbles.sprites";

    Game_Scene::Track Game_Scene::track =
    {
        1.f,                // time window
        {
            { 13.92f,  2, false, false },    // time, goal (0 - 8)
            { 14.17f,  4, false, false },
            { 14.92f, 1, false, false },
            { 15.33f, 6, false, false },
            { 15.61f,  4, false, false },
            { 15.76f, 0, false, false },
            { 16.09f, 5, false, false },
            { 16.94f,  3, false, false },
            { 17.44f, 2, false, false },
            { 17.73f, 8, false, false },
            { 17.85f,  3, false, false },
            { 18.2f, 6, false, false },
            { 19.01f, 8, false, false },
            { 19.46f,  2, false, false },
            { 19.79f, 5, false, false },
            { 19.92f, 3, false, false },
            { 20.33f,  4, false, false },
            { 20.96f, 1, false, false },
            { 21.1f, 2, false, false },
            { 21.59f,  6, false, false },
            { 21.86f, 5, false, false },
            { 21.99f, 0, false, false },
            { 22.39f,  4, false, false },
            { 23.2f, 7, false, false },
            { 23.63f, 6, false, false },
            { 23.9f,  4, false, false },
            { 24.06f, 0, false, false },
            { 24.44f, 2, false, false },
            { 25.11f,  4, false, false },
            { 25.24f, 1, false, false },
            { 25.75f, 5, false, false },
            { 26.05f,  4, false, false },
            { 26.19f, 3, false, false },
            { 26.58f, 7, false, false },
            { 26.82f,  4, false, false },
            { 27.06f, 1, false, false },
            { 27.35f, 3, false, false },
            { 27.86f,  5, false, false },
            { 28.14f, 3, false, false },
            { 28.26f, 8, false, false },
            { 28.67f,  7, false, false },
            { 29.35f, 2, false, false },
            { 29.48f, 5, false, false },
            { 29.96f,  0, false, false },
            { 30.21f, 3, false, false },
            { 30.34f, 7, false, false },
            { 30.74f,  4, false, false },
            { 31.44f, 2, false, false },
            { 31.55f, 6, false, false },
            { 32.05f,  4, false, false },
            { 32.35f, 1, false, false },
            { 32.48f, 3, false, false },
            { 32.81f,  4, false, false },
            { 33.46f, 6, false, false },
            { 33.57f, 5, false, false },
            { 34.12f,  4, false, false },
            { 34.57f, 1, false, false },
            { 34.93f, 2, false, false },
            { 35.18f,  6, false, false },
            { 35.43f, 1, false, false },
            { 35.73f, 7, false, false },
            { 36.21f,  4, false, false },
            { 36.47f, 1, false, false },
            { 36.61f, 3, false, false },
            { 37.04f,  6, false, false },
            { 37.68f, 4, false, false },
            { 37.82f, 2, false, false },
            { 38.3f,  5, false, false },
            { 38.56f, 0, false, false },
            { 38.71f, 3, false, false },
            { 39.16f,  4, false, false },
            { 39.79f, 1, false, false },
            { 39.9f, 8, false, false },
            { 40.38f,  5, false, false },
            { 40.68f, 1, false, false },
            { 40.81f, 2, false, false },
            { 41.13f,  4, false, false },
            { 41.13f, 0, false, false },
            { 41.82f, 5, false, false },
            { 41.92f,  3, false, false },
            { 42.47f, 2, false, false },
            { 42.72f, 6, false, false },
            { 42.85f,  8, false, false },
            { 43.23f, 3, false, false },
            { 43.51f, 6, false, false },
            { 43.83f,  3, false, false },
            { 44.06f, 1, false, false },
            { 44.51f, 4, false, false },
            { 44.72f,  2, false, false },
            { 44.87f, 7, false, false },
            { 45.34f, 4, false, false },
            { 45.98f,  2, false, false },
            { 46.1f, 1, false, false },
            { 46.61f, 0, false, false },
            { 46.88f,  6, false, false },
            { 47.01f, 1, false, false },
            { 47.46f, 5, false, false },
            { 48.02f,  4, false, false },
            { 48.14f, 2, false, false },
            { 48.72f, 1, false, false },
            { 49.03f,  4, false, false },
            { 49.16f, 1, false, false },
            { 49.51f, 4, false, false },
            { 50.16f,  3, false, false },
            { 50.31f, 6, false, false },
            { 50.82f, 3, false, false },
            { 51.18f,  7, false, false },
            { 51.63f, 1, false, false },
            { 51.88f, 0, false, false },
            { 52.11f,  3, false, false },
            { 52.4f, 4, false, false },
            { 52.89f, 1, false, false },
            { 53.17f,  6, false, false },
            { 53.31f, 2, false, false },
            { 53.72f, 7, false, false },
            { 54.39f,  4, false, false },
            { 54.54f, 8, false, false },
            { 55.f, 4, false, false },
            { 55.3f,  6, false, false },
            { 55.45f, 2, false, false },
            { 55.8f, 5, false, false },
            { 56.46f,  2, false, false },
            { 56.57f, 1, false, false },
            { 57.05f, 3, false, false },
            { 57.37f,  4, false, false },
            { 57.49f, 2, false, false },
            { 57.87f, 6, false, false },
            { 58.87f,  1, false, false },
            { 58.55f, 7, false, false },
            { 58.66f, 0, false, false },
            { 59.13f,  4, false, false },
            { 59.39f, 2, false, false },
            { 59.52f, 4, false, false },
            { 59.94f,  5, false, false },
            { 60.2f, 3, false, false },
            { 60.5f, 7, false, false },
            { 60.75f,  4, false, false },
            { 61.25f, 1, false, false },
            { 61.48f, 8, false, false },
            { 61.63f,  4, false, false },
            { 62.07f, 1, false, false },
            { 62.72f, 5, false, false },
            { 62.82f,  4, false, false },
            { 63.32f, 2, false, false },
            { 63.62f, 7, false, false },
            { 63.75f,  3, false, false },
            { 64.2f, 5, false, false },
            { 64.81f, 6, false, false },
            { 64.94f,  3, false, false },
            { 65.39f, 7, false, false },
            { 65.69f, 2, false, false },
            { 65.82f,  4, false, false },
            { 66.18f, 6, false, false },
            { 66.93f, 4, false, false },
            { 67.05f,  5, false, false },
            { 67.48f, 2, false, false },
            { 67.77f, 7, false, false },
            { 67.93f,  5, false, false },
            { 68.36f, 2, false, false },
            { 68.64f, 7, false, false },
            { 68.84f,  3, false, false },
            { 69.1f, 6, false, false },
            { 69.6f, 4, false, false },
            { 69.86f,  5, false, false },
            { 70.f, 2, false, false },
            { 70.43f, 8, false, false },
            { 71.07f,  4, false, false },
            { 71.21f, 3, false, false },
            { 71.7f, 7, false, false },
            { 71.98f,  1, false, false },
            { 72.1f, 5, false, false },
            { 72.51f, 0, false, false },
            { 73.13f,  3, false, false },
            { 73.13f, 6, false, false },
            { 73.26f, 3, false, false },
            { 73.79f,  7, false, false },
            { 74.1f, 3, false, false },
            { 74.2f, 5, false, false },
            { 74.6f,  2, false, false },
            { 75.33f, 5, false, false },
            { 75.43f, 3, false, false },
            { 75.83f,  6, false, false },
            { 76.12f, 5, false, false },
            { 76.27f, 4, false, false },
            { 76.65f,  7, false, false },
            { 76.89f, 5, false, false },
            { 77.19f, 2, false, false },
            { 77.38f,  0, false, false },
            { 77.96f, 4, false, false },
            { 78.29f, 8, false, false },
            { 78.73f,  4, false, false },
            { 79.54f, 3, false, false },
            { 79.79f, 6, false, false },
            { 80.05f,  8, false, false },
            { 80.3f, 3, false, false },
            { 80.42f, 4, false, false },
            { 80.85f,  1, false, false },
            { 81.08f, 6, false, false },
            { 81.38f, 3, false, false },
            { 81.66f,  8, false, false },
            { 82.14f, 3, false, false },
            { 82.44f, 5, false, false },
            { 82.55f,  4, false, false },
            { 82.93f, 1, false, false },
            { 83.2f, 8, false, false },
            { 83.46f,  5, false, false },
            { 83.71f, 3, false, false },
            { 84.24f, 8, false, false },
            { 84.66f,  7, false, false },
            { 85.02f, 3, false, false },
            { 85.27f, 8, false, false },
            { 85.52f,  4, false, false },
            { 85.78f, 1, false, false },
            { 86.35f, 5, false, false },
            { 86.86f,  4, false, false },
            { 87.39f, 1, false, false },
            { 87.84f, 2, false, false },
            { 88.38f,  4, false, false },
            { 88.91f, 1, false, false },
            { 89.44f, 5, false, false },
            { 89.66f,  4, false, false },
            { 89.94f, 1, false, false },
            { 90.47f, 3, false, false },
            { 91.f,  4, false, false },
            { 91.57f, 1, false, false },
            { 92.05f, 8, false, false },
            { 92.31f,  5, false, false },
            { 92.59f, 1, false, false },
            { 92.84f, 4, false, false },
            { 93.11f,  3, false, false },
            { 93.32f, 1, false, false },
            { 93.6f, 7, false, false },
            { 93.9f,  4, false, false },
            { 94.17f, 1, false, false },
            { 94.68f, 3, false, false },
            { 94.88f,  5, false, false },
            { 95.03f, 2, false, false },
            { 95.39f, 8, false, false },
            { 95.67f,  6, false, false },
            { 95.96f, 4, false, false },
            { 96.25f, 6, false, false },
            { 96.5f,  3, false, false },
            { 96.75f, 1, false, false },
            { 96.98f, 8, false, false },
            { 97.1f,  4, false, false },
            { 97.46f, 1, false, false },
            { 97.71f, 4, false, false },
            { 98.f,  6, false, false },
            { 98.29f, 1, false, false },
            { 98.56f, 5, false, false },
            { 98.82f,  8, false, false },
            { 99.07f, 5, false, false },
            { 99.2f, 0, false, false },
            { 99.57f,  3, false, false },
            { 99.8f, 1, false, false },
            { 100.11f, 6, false, false },
            { 100.38f,  3, false, false },
            { 100.68f, 4, false, false },
            { 100.89f, 8, false, false },
            { 101.16f,  3, false, false },
            { 101.27f, 1, false, false },
            { 101.71f, 5, false, false },
            { 101.95f,  3, false, false },
            { 102.22f, 1, false, false },
            { 102.47f, 5, false, false },
            { 102.73f,  2, false, false },
            { 103.01f, 6, false, false },
            { 103.26f, 4, false, false },
            { 103.38f,  5, false, false },
            { 103.81f, 2, false, false },
            { 104.29f, 4, false, false },
            { 104.57f,  7, false, false },
            { 105.1f, 3, false, false },
            { 105.6f, 2, false, false },
            { 106.11f,  7, false, false },
            { 106.29f, 1, false, false },
            { 106.58f, 7, false, false },
            { 106.92f,  4, false, false },
            { 107.19f, 8, false, false },
            { 107.57f, 2, false, false },
            { 107.9f,  4, false, false },
            { 108.21f, 1, false, false },
            { 108.43f, 3, false, false },
            { 108.71f,  4, false, false },
            { 109.01f, 1, false, false },
            { 109.27f, 0, false, false },
            { 109.52f,  3, false, false },
            { 109.77f, 1, false, false },
            { 110.3f, 5, false, false },
            { 110.87f,  4, false, false },
            { 111.38f, 3, false, false },
            { 111.63f, 4, false, false },
            { 111.88f,  5, false, false },
            { 112.36f, 3, false, false },
            { 112.96f, 7, false, false },
            { 115.51f,  4, false, false },
            { 115.74f, 2, false, false },
            { 115.87f, 8, false, false },
            { 116.27f,  4, false, false },
            { 116.75f, 4, false, false },
            { 117.05f, 8, false, false },
            { 117.3f,  5, false, false },
            { 117.6f, 1, false, false },
            { 117.86f, 6, false, false },
            { 117.98f,  4, false, false },
            { 118.37f, 7, false, false },
            { 118.62f, 5, false, false },
            { 118.89f,  4, false, false },
            { 119.14f, 3, false, false },
            { 119.42f, 5, false, false },
            { 119.67f,  4, false, false },
            { 119.93f, 3, false, false },
            { 120.06f, 8, false, false },
            { 120.48f,  4, false, false },
            { 120.74f, 1, false, false },
            { 120.97f, 3, false, false },
            { 121.24f,  4, false, false },
            { 121.5f, 6, false, false },
            { 121.77f, 5, false, false },
            { 122.02f,  3, false, false },
            { 122.13f, 1, false, false },
            { 122.55f, 5, false, false },
            { 122.77f,  3, false, false },
            { 123.03f, 7, false, false },
            { 123.31f, 5, false, false },
            { 123.61f,  4, false, false },
            { 124.f, 1, false, false },
            { 124.11f, 8, false, false },
            { 124.24f,  3, false, false },
            { 124.64f, 5, false, false },
            { 124.9f, 4, false, false },
            { 125.15f,  6, false, false },
            { 125.46f, 8, false, false },
            { 125.73f, 1, false, false },
            { 125.96f,  3, false, false },
            { 126.23f, 6, false, false },
            { 126.36f, 3, false, false },
            { 126.74f,  7, false, false },
            { 127.f, 3, false, false },
            { 127.1f, 5, false, false },
            { 127.24f,  1, false, false },
            { 127.59f, 6, false, false },
            { 127.8f, 4, false, false },
            { 128.07f,  3, false, false },
            { 128.26f, 6, false, false },
            { 128.41f, 2, false, false },
            { 128.81f,  5, false, false },
            { 129.04f, 1, false, false },
            { 129.19f, 8, false, false },
            { 129.32f,  3, false, false },
            { 129.72f, 6, false, false },
            { 129.95f, 8, false, false },
            { 130.19f,  4, false, false },
            { 130.47f, 3, false, false },
            { 130.57f, 5, false, false },
            { 130.92f,  6, false, false },
            { 131.15f, 2, false, false },
            { 131.35f, 3, false, false },
            { 131.64f,  5, false, false },
            { 131.96f, 2, false, false },
            { 132.19f, 8, false, false },
            { 132.42f,  3, false, false },
            { 132.56f, 4, false, false },
            { 133.f, 8, false, false },
            { 133.25f,  5, false, false },
            { 133.39f, 3, false, false },
            { 133.82f, 6, false, false },
            { 134.05f,  4, false, false },
            { 134.33f, 1, false, false },
            { 134.58f, 8, false, false },
            { 134.71f,  6, false, false },
            { 135.07f, 1, false, false },
            { 135.34f, 7, false, false },
            { 135.57f,  4, false, false },
            { 135.87f, 0, false, false },
            { 136.13f, 4, false, false },
            { 136.4f,  3, false, false },
            { 136.65f, 6, false, false },
            { 136.78f, 3, false, false },
            { 137.16f,  6, false, false },
            { 137.44f, 7, false, false },
            { 137.67f, 3, false, false },
            { 137.92f,  7, false, false },
            { 138.22f, 1, false, false },
            { 138.47f, 2, false, false },
            { 138.74f,  4, false, false },
            { 138.87f, 1, false, false },
            { 139.27f, 8, false, false },
            { 139.53f,  4, false, false },
            { 139.73f, 1, false, false },
            { 140.01f, 6, false, false },
            { 140.29f,  4, false, false },
            { 140.57f, 2, false, false },
            { 140.86f, 8, false, false },
            { 140.97f,  4, false, false },
            { 141.32f, 3, false, false },
            { 141.58f, 8, false, false },
            { 141.87f,  4, false, false },
            { 142.41f, 4, false, false },
            { 142.66f, 8, false, false },
            { 142.93f,  5, false, false },
            { 143.04f, 6, false, false },
            { 143.42f, 2, false, false },
            { 143.71f,  6, false, false },
            { 143.82f, 1, false, false },
            { 144.22f, 6, false, false },
            { 144.47f,  3, false, false },
            { 144.77f, 2, false, false },
            { 144.98f, 8, false, false },
            { 145.11f,  4, false, false },
            { 144.56f, 1, false, false },
            { 146.04f, 5, false, false },
            { 146.27f,  4, false, false },
            { 146.62f, 5, false, false },
            { 146.85f, 6, false, false },
            { 147.13f,  4, false, false },
            { 147.25f, 8, false, false },
            { 147.6f, 3, false, false },
            { 147.9f,  4, false, false },
            { 148.13f, 2, false, false },
            { 148.4f, 7, false, false },
            { 148.71f,  3, false, false },
            { 148.94f, 1, false, false },
            { 149.17f, 6, false, false },
            { 149.42f,  3, false, false },
            { 149.69f, 1, false, false },
            { 150.23f, 8, false, false },
            { 151.1f,  4, false, false },
            { 151.49f, 6, false, false },
            { 151.64f, 2, false, false },
            { 152.24f,  4, false, false },
            { 152.55f, 3, false, false },
            { 152.83f, 0, false, false },
            { 153.08f,  4, false, false },
            { 153.35f, 3, false, false },
            { 153.63f, 1, false, false },
            { 154.13f,  7, false, false },
            { 154.42f, 4, false, false },
            { 154.66f, 8, false, false },
            { 154.94f,  4, false, false },
            { 155.24f, 2, false, false },
            { 155.63f, 4, false, false },
            { 155.98f,  5, false, false },
            { 156.25f, 2, false, false },
            { 156.74f, 1, false, false },
            { 157.f,  4, false, false },
            { 157.29f, 1, false, false },
            { 157.74f, 7, false, false },
            { 158.05f,  3, false, false },
            { 158.53f, 4, false, false },
            { 159.03f, 5, false, false },
            { 159.31f,  6, false, false },
            { 159.66f, 3, false, false },
            { 159.86f, 4, false, false },
            { 160.27f,  7, false, false },
            { 160.61f, 0, false, false },
            { 161.15f, 1, false, false },
            { 161.66f,  4, false, false },
            { 161.95f, 8, false, false },
            { 162.34f, 4, false, false },
            { 162.74f,  2, false, false },
            { 163.35f, 6, false, false },
            { 163.55f, 3, false, false },
            { 163.75f,  2, false, false },
            { 163.95f, 4, false, false },
            { 164.28f, 4, false, false },
        }
    };

    // ---------------------------------------------------------------------------------------------

    Game_Scene::Game_Scene()
    {
        // Se establece la resolución virtual (independiente de la resolución virtual del dispositivo).
        // En este caso no se hace ajuste de aspect ratio, por lo que puede haber distorsión cuando
        // el aspect ratio real de la pantalla del dispositivo sea distinto.
        canvas_width  = 1280;
        canvas_height =  720;

        // Se inicializan otros atributos:
        initialize ();

        suspended = true;
    }

    // ---------------------------------------------------------------------------------------------
    // Algunos atributos se inicializan en este método en lugar de hacerlo en el constructor porque
    // este método puede ser llamado más veces para restablecer el estado de la escena y el constructor
    // solo se invoca una vez.

    bool Game_Scene::initialize ()
    {
        state     = sprites_atlas.get () ? RUNNING : LOADING;
        suspended = false;
        gameplay  = UNINITIALIZED;
        score     = 0;

        finished = false;

        //Este bucle es porque nuestro Track es static, por lo que aunque reiniciemos el nivel, las modificaciones en las variables quedan guardadas en el juego en si.
        for(size_t i = 0; i < track.beats.size (); i++) {
            track.beats[i].activated = false;
            track.beats[i].visible = false;
        }

        timer.reset();

        return true;
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::suspend ()
    {
        suspended = true;               // Se marca que la escena ha pasado a primer plano
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::resume ()
    {
        suspended = false;              // Se marca que la escena ha pasado a segundo plano
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::handle (Event & event)
    {
        if (state == RUNNING)               // Se descartan los eventos cuando la escena está LOADING
        {
            if (gameplay == WAITING_TO_START)
            {
                start_playing ();           // Se empieza a jugar cuando el usuario toca la pantalla por primera vez
            }
            else switch (event.id)
            {
                case ID(touch-started):     // El usuario toca la pantalla
                //case ID(touch-moved):
                //case ID(touch-ended):     // El usuario deja de tocar la pantalla
                {
                    float touch_x  = *event[ID(x)].as< var::Float > ();
                    float touch_y  = *event[ID(y)].as< var::Float > ();

                    // Si toca dentro del radio de nuestro beat lo activa.
                    for(size_t i = 0; i < track.beats.size (); i++){    //Si en algún
                        if((abs(touch_x - track.beats[i].position[0]) < track.beat_radius) && (abs(touch_y - track.beats[i].position[1]) < track.beat_radius)){
                            track.beats[i].activated = true;
                            if(track.beats[i].visible == true){ //Comprobar si están activos y visibles.
                                //Cálculo del porcentaje para saber por dónde va el beat
                                float beat_percentage = current_time * 100 / track.beats[i].time;

                                if(beat_percentage <= 93 && track.beats[i].activated){   //Si el beat está antes de que sea considerado como que se le ha dado bien.
                                    //Sonido de haberle dado mal

                                }
                                else if(beat_percentage > 94 && beat_percentage <= 106 && track.beats[i].activated){     //Rango en el que si se le da está correcto.
                                    //Sonido de haberle dado bien
                                    score += 10;

                                }
                                else if(beat_percentage < 107 && track.beats[i].activated){  //Otra vez estaría fuera del rango en el que le tenemos que dar, así que estaría mal
                                    //Sonido de haberle dado mal

                                }

                            }

                        }
                    }

                    //Nos lleva al menñu principal.
                    if(abs(touch_x - menu_button->get_position_x()) < track.beat_radius && abs(touch_y - menu_button->get_position_y()) < track.beat_radius){
                        director.run_scene (shared_ptr< Scene >(new Menu_Scene));
                    }

                    break;
                }

            }
        }
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::update (float time)
    {
        if (!suspended) switch (state)
        {
            case LOADING: load_textures  ();     break;
            case RUNNING: run_simulation (time); break;
            case ERROR:   break;
        }
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::render (Context & context)
    {
        if (!suspended)
        {
            // El canvas se puede haber creado previamente, en cuyo caso solo hay que pedirlo:

            Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

            // Si no se ha creado previamente, hay que crearlo una vez:

            if (!canvas)
            {
                 canvas = Canvas::create (ID(canvas), context, {{ canvas_width, canvas_height }});
            }

            // Si el canvas se ha podido obtener o crear, se puede dibujar con él:

            if (canvas)
            {
                if (state == ERROR) canvas->set_clear_color(1.f, 0.f, 0.f);

                canvas->clear ();

                if (state == RUNNING)
                {
                    canvas->fill_rectangle ({ canvas_width / 2.f, canvas_height / 2.f }, { (float)canvas_width, (float)canvas_height }, background.get ());

                    for (auto & sprite : renderable_sprites)
                    {
                        sprite->render (*canvas);

                    }

                    //Mostramos el score: (debemos usar la librería sstream para poder convertir el score a texto convirtiéndolo en una cadena de tipo wstring)
                    std::wostringstream buffer;
                    buffer << "Score : " << score;
                    Text_Layout scoreText(*font, buffer.str());

                    canvas->draw_text ({ canvas_width / 3.5f , canvas_height/ 1.1f}, scoreText, CENTER );


                    if(finished){
                        canvas->fill_rectangle ({ canvas_width / 2.f, canvas_height / 2.f }, { (float)canvas_width / 1.3f, (float)canvas_height }, final_screen.get ());
                        canvas->draw_text ({ canvas_width / 2.f , canvas_height/ 1.2f}, scoreText, CENTER );

                        menu_button->set_position({ canvas_width / 15.f, top_y - 200});
                    }


                    render_beats(*canvas);
                }
            }
        }
    }

    // ---------------------------------------------------------------------------------------------
    // En este método solo se carga una textura por fotograma para poder pausar la carga si el
    // juego pasa a segundo plano inesperadamente. Otro aspecto interesante es que la carga no
    // comienza hasta que la escena se inicia para así tener la posibilidad de mostrar al usuario
    // que la carga está en curso en lugar de tener una pantalla en negro que no responde durante
    // un tiempo.

    void Game_Scene::load_textures ()
    {
        Graphics_Context::Accessor context = director.lock_graphics_context ();

        if (context)
        {
            sprites_atlas.reset (new Atlas(sprites_atlas_path, context));
            font.reset (new Raster_Font("fonts/impact.fnt", context));

            if (!sprites_atlas->good ())
            {
                state = ERROR;
                return;
            }

            background = Texture_2D::create (ID(background), context, "backgroundGame.png");
            final_screen = Texture_2D::create (ID(final_screen), context, "finalScreen.png");

            if (background.get ())
            {
                context->add(background);
                context->add(final_screen);
            } else
            {
                state = ERROR;
                return;
            }

            create_sprites ();

            state = RUNNING;

            timer.reset ();     //Ponemos a 0 el timer justo antes de empezar el juego.
        }
        /*if (textures.size () < textures_count)          // Si quedan texturas por cargar...
        {
            // Las texturas se cargan y se suben al contexto gráfico, por lo que es necesario disponer
            // de uno:

            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context)
            {
                // Se carga la siguiente textura (textures.size() indica cuántas llevamos cargadas):

                Texture_Data   & texture_data = textures_data[textures.size ()];
                Texture_Handle & texture      = textures[texture_data.id] = Texture_2D::create (texture_data.id, context, texture_data.path);

                // Se comprueba si la textura se ha podido cargar correctamente:

                if (texture) context->add (texture); else state = ERROR;

                // Cuando se han terminado de cargar todas las texturas se pueden crear los sprites que
                // las usarán e iniciar el juego:
            }
        }
        else
        if (timer.get_elapsed_seconds () > 1.f)         // Si las texturas se han cargado muy rápido
        {                                               // se espera un segundo desde el inicio de
            create_sprites ();                          // la carga antes de pasar al juego para que
            restart_game   ();                          // el mensaje de carga no aparezca y desaparezca
                                                        // demasiado rápido.
            state = RUNNING;
        }*/
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::create_sprites ()
    {
        center_x      = float(canvas_width) / 2.f;
        top_y         = float(100 - top_margin) * float(canvas_height) / 100.f;
        goal_distance = float(100 - top_margin - bottom_margin) * float(canvas_height) / 100.f;

        menu_button.reset(new Sprite(sprites_atlas->get_slice(ID(menu))));
        menu_button->set_position({ canvas_width / 1.5f, top_y + 100});
        renderable_sprites.push_back(menu_button.get());

        spawner_sprite.reset (new Sprite(sprites_atlas->get_slice(ID(spawner))));
        spawner_sprite->set_position({ center_x, top_y });
        renderable_sprites.push_back(spawner_sprite.get());

        goal_sprites.resize (number_of_goals);

        int index = 0;

        //Recorremos el for colocando 8 goals desde el grado 0, hasta uno antes del 180.
        for (float angle = 0.f; index < number_of_goals - 1; angle += step)
        {
            auto & sprite = goal_sprites[index++];

            create_goal(sprite, center_x, top_y, angle, goal_distance);
        }

        //Colocamos el último justo en el 180 (PI)
        create_goal(goal_sprites.back (), center_x, top_y, 3.141592f, goal_distance);

        //Asginamos slice correspondiente y el radio del beat.
        slice_beat = sprites_atlas->get_slice(ID(beat));
        track.beat_radius = slice_beat->width / 2;
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::create_goal(Sprite_Handle & sprite, float center_x, float top_y, float angle, float distance)
    {
        sprite.reset (new Sprite(sprites_atlas->get_slice(ID(goal))));

        float x = center_x + cosf (angle) * distance;
        float y = top_y    + sinf (angle) * distance;

        sprite->set_position({ x, y });

        renderable_sprites.push_back(sprite.get());
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::start_playing ()
    {
        gameplay = PLAYING;
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::run_simulation (float time)
    {
        //Ajustamos el aspect ratio
        if (!aspect_ratio_adjusted){
            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context){
                float real_aspect_ratio = float( context->get_surface_width () ) / context->get_surface_height ();

                canvas_width = unsigned( canvas_height * real_aspect_ratio );

                aspect_ratio_adjusted = true;

            }
        }
    }

    void Game_Scene::render_beats (Canvas & canvas)
    {
        //Hacemos que vayan apareciendo los beats que están dentro de un intervalo de Time_window, que son los segundos que tardará hasta llegar a su goal.
        current_time = timer.get_elapsed_seconds();
        float spawn_time   = current_time + track.time_window;

        //Cuando llegue el final de la canción
        if(current_time >= 170){
            finished = true;
        }

        //Si el tiempo en el que el beat es mayor al tiempo actual y a la vez es menor o igual al tiempo en el que tiene que recorrer la pantalla, entonces lo dibujamos durante todo su recorrido.
        for(size_t i = 0; i < track.beats.size (); i++)
        {
            auto & beat = track.beats[i];

            if (beat.time >= current_time - 2 && beat.time <= spawn_time) { //El -2 nos sirve para que sigan activos 2 segundos más del que debieran, o por el contrario solo los pintaríamos hasta que llegasen al goal.
                float angle = step * beat.goal;
                float distanceBeat = (spawn_time - beat.time) * goal_distance / track.time_window;

                float x = center_x + cosf(angle) * distanceBeat;
                float y =    top_y + sinf(angle) * distanceBeat;

                beat.position = {x, y};

                if (!beat.activated){    //Si este booleano está en true es que hemos tocado ese beat y dejamos de pintarlo
                    canvas.fill_rectangle({x, y}, {slice_beat->width / 1.5f, slice_beat->height / 1.5f}, slice_beat);
                    beat.visible = true;        //mientras esté aquí estará en true
                }
            }

        }
    }
}
