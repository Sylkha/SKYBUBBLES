/*
 * GAME SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#ifndef GAME_SCENE_HEADER
#define GAME_SCENE_HEADER

    #include <map>
    #include <list>
    #include <memory>
    #include <vector>

    #include <basics/Atlas>
    #include <basics/Canvas>
    #include <basics/Id>
    #include <basics/Raster_Font>
    #include <basics/Scene>
    #include <basics/Texture_2D>
    #include <basics/Timer>

    #include "Sprite.hpp"

    namespace example
    {

        using basics::Atlas;
        using basics::Id;
        using basics::Timer;
        using basics::Canvas;
        using basics::Raster_Font;
        using basics::Texture_2D;

        class Game_Scene : public basics::Scene
        {

            // Estos typedefs pueden ayudar a hacer el código más compacto y claro:

            typedef std::shared_ptr < Sprite     >     Sprite_Handle;
            typedef std::vector< Sprite_Handle   >     Sprite_List;
            typedef std::shared_ptr< Texture_2D  >     Texture_Handle;
            typedef std::shared_ptr< Raster_Font >     Font_Handle;
            typedef std::shared_ptr< Atlas       >     Atlas_Handle;
            typedef basics::Graphics_Context::Accessor Context;

            /**
             * Representa el estado de la escena en su conjunto.
             */
            enum State
            {
                LOADING,
                RUNNING,
                ERROR
            };

            /**
             * Representa el estado del juego cuando el estado de la escena es RUNNING.
             */
            enum Gameplay_State
            {
                UNINITIALIZED,
                WAITING_TO_START,
                PLAYING,
            };

            struct Track     ///< El track tiene todos los beats que tendrán que salir.
            {
                struct Beat ///< Cada beat tiene constancia de cúando tendría que llegar al goal y su goal correspondiente. Además contiene información de su posición y de si ha sido tocado (activado) o no.
                {
                    float time;
                    int   goal;

                    bool activated;
                    bool visible;
                    Vector2f position;
                };

                float time_window;           ///< Segundos que queremos que esté el beat en pantalla yendo desde el spawn al goal.

                std::vector< Beat > beats;  ///< Vector de beats.

                float beat_radius;           ///< Radio de los beats para saber si colisiona con los toques en pantalla.
            };

            static Track track;

        private:

            static const int number_of_goals     = 9;           ///< Número de goals totales.

            static const int top_margin = 25;                   ///< Valor en porcentaje del márgen desde arriba.
            static const int bottom_margin = 20;                ///< Valor en porcentaje del márgen desde abajo.

            static constexpr float step = -3.141592f / float (number_of_goals - 1); ///< Valor de distancia entre los goals.

            static const char * sprites_atlas_path;

            float center_x;                                     ///< Centro del que vamos a partir para hacer el semicírculo.
            float top_y;                                        ///< Margen desde el top.
            float goal_distance;                                ///< Distancia desde ese centro a los goals.

            State          state;                               ///< Estado de la escena.
            Gameplay_State gameplay;                            ///< Estado del juego cuando la escena está RUNNING.
            bool           suspended;                           ///< true cuando la escena está en segundo plano y viceversa.

            bool           aspect_ratio_adjusted;               ///< false hasta que se ajuste el aspect ratio de la resolución

            unsigned       canvas_width;                        ///< Ancho de la resolución virtual usada para dibujar.
            unsigned       canvas_height;                       ///< Alto  de la resolución virtual usada para dibujar.

            Timer          timer;                               ///< Cronómetro usado para medir intervalos de tiempo
            float          current_time;                        ///< Lleva la cuenta del tiempo actual.

            Atlas_Handle   sprites_atlas;
            const Atlas::Slice *  slice_beat;

            Font_Handle    font;

            Sprite_Handle  spawner_sprite;                      ///< Imagen desde la cual aparecen los beats.
            Sprite_List    goal_sprites;                        ///< Dirección a la que irán los beats desde el spawner.

            Sprite_Handle  menu_button;                         ///< Botón que te lleva al menú principal.

            Texture_Handle background;
            Texture_Handle final_screen;                        ///< Aparece esta imagen al terminar el nivel junto con el score.

            bool           finished;                            ///< Se activa este booleano cuando hayamos terminado la partida.

            int            score;                               ///< Puntuación del jugador.

            std::vector< Sprite * > renderable_sprites;

        public:

            /**
             * Solo inicializa los atributos que deben estar inicializados la primera vez, cuando se
             * crea la escena desde cero.
             */
            Game_Scene();

            /**
             * Este método lo llama Director para conocer la resolución virtual con la que está
             * trabajando la escena.
             * @return Tamaño en coordenadas virtuales que está usando la escena.
             */
            basics::Size2u get_view_size () override
            {
                return { canvas_width, canvas_height };
            }

            /**
             * Aquí se inicializan los atributos que deben restablecerse cada vez que se inicia la escena.
             */
            bool initialize () override;

            /**
             * Este método lo invoca Director automáticamente cuando el juego pasa a segundo plano.
             */
            void suspend () override;

            /**
             * Este método lo invoca Director automáticamente cuando el juego pasa a primer plano.
             */
            void resume () override;

            /**
             * Este método se invoca automáticamente una vez por fotograma cuando se acumulan
             * eventos dirigidos a la escena.
             */
            void handle (basics::Event & event) override;

            /**
             * Este método se invoca automáticamente una vez por fotograma para que la escena
             * actualize su estado.
             */
            void update (float time) override;

            /**
             * Este método se invoca automáticamente una vez por fotograma para que la escena
             * dibuje su contenido.
             */
            void render (Context & context) override;

        private:

            /**
             * En este método se cargan las texturas (una cada fotograma para facilitar que la
             * propia carga se pueda pausar cuando la aplicación pasa a segundo plano).
             */
            void load_textures ();

            /**
             * En este método se crean los sprites cuando termina la carga de texturas y se colocan los goals y el spawner.
             */
            void create_sprites ();

            /**
             * En este método se le asigna la textura y posición a los goals.
             * @param sprite        Sprite al que se le va a aplicar las acciones
             * @param center_x      Centro del que va a surgir el semicírculo (Posición en eje X)
             * @param top_y         Punto en el eje Y donde va a estar el centro.
             * @param angle         Angulo de cada goal.
             * @param distance      Distancia a la que están los goals respecto al centro.
             */
            void create_goal (Sprite_Handle & sprite, float center_x, float top_y, float angle, float distance);

            /**
              *
             */
            void start_playing ();

            /**
             * Actualiza el estado del juego cuando el estado de la escena es RUNNING.
             */
            void run_simulation (float time);

            /**
             * En este método vemos las condiciones respecto al tiempo para dibujar los beats en sus posiciones correspondientes.
             */
            void render_beats (Canvas & canvas);

            void level();

        };

    }

#endif
