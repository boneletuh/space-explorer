#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "raylib.h"

#include "entities.h"
#include "physics.h"
#include "utils.h"
#include "render.h"
#include "save_and_load.h"


#define TARGET_FPS 30

#define LIGHT_GREEN (Color) {100, 255, 100, 255}


// show development information
void display_dev_info(char * text_buff, const Ship mship, const Planet * planets, const int planets_count, float time_elapsed) {
    (void)planets, (void)planets_count;

    sprintf(text_buff, "x=%.2f, y=%.2f, z=%.2f\n", mship.x, mship.y, mship.z);
    DrawText(text_buff, 0, 0, 15, LIGHT_GREEN);

    sprintf(text_buff, "vx=%.2f, vy=%.2f, vz=%.2f\n", mship.vx, mship.vy, mship.vz);
    DrawText(text_buff, 0, 20, 15, LIGHT_GREEN);

    sprintf(text_buff, "ax=%.2f, ay=%.2f, az=%.2f\n", mship.ax, mship.ay, mship.az);
    DrawText(text_buff, 0, 40, 15, LIGHT_GREEN);

    sprintf(text_buff, "rot_x=%.2f, rot_y=%.2f, rot_z=%.2f\n", mship.angle_x, mship.angle_y, mship.angle_z);
    DrawText(text_buff, 0, 60, 15, LIGHT_GREEN);

    sprintf(text_buff, "rot_vx=%.2f, rot_vy=%.2f, rot_vz=%.2f\n", mship.vangle_x, mship.vangle_y, mship.vangle_z);
    DrawText(text_buff, 0, 80, 15, LIGHT_GREEN);

    sprintf(text_buff, "rot_ax=%.2f, rot_ay=%.2f, rot_az=%.2f\n", mship.aangle_x, mship.aangle_y, mship.aangle_z);
    DrawText(text_buff, 0, 100, 15, LIGHT_GREEN);

    sprintf(text_buff, "frame time=%.2fms\n", 1e3*time_elapsed);
    DrawText(text_buff, 0, 120, 15, LIGHT_GREEN);

    sprintf(text_buff, "max frame time=%.2fms\n", 1e3/(float)TARGET_FPS);
    DrawText(text_buff, 0, 140, 15, LIGHT_GREEN);

}

Planet gen_rand_planet(void) {
    Planet planet;
    planet.x = fmod(rand_float(), 1e5), //fmod(rand_float(), WINDOW_WIDTH/2);
    planet.y = fmod(rand_float(), 1e5), //fmod(rand_float(), WINDOW_HEIGHT/2);
    planet.z = fmod(rand_float(), 1e5);
    planet.r = 100 + fmod(fabs(rand_float()), 1e5);
    planet.color = WHITE; //rand_color();
    return planet;
}

int main(int argc, char ** argv) {
	(void)argc, (void)argv;
	srand(time(NULL));
	SetTraceLogLevel(LOG_WARNING);

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "");
    SetTargetFPS(TARGET_FPS);

    // main ship, the player
    Ship mship = (Ship) {
        .x=0,  .y=0,  .z=0,
        .vx=0, .vy=0, .vz=0,
        .ax=0, .ay=0, .az=0,
        .angle_x=0, .angle_y=0, .angle_z=0,
        .vangle_x=0, .vangle_y=0, .vangle_z=0,
        .aangle_x=0, .aangle_y=0, .aangle_z=0
    };

    int planets_count = 1e4;
    Planet * planets = malloc(sizeof(Planet) * planets_count);
    for (int i = 0; i < planets_count; i++) {
        Planet planet = gen_rand_planet();
        planets[i] = planet;
        printf("x=%.3f, y=%.3f r=%.3f\n", planet.x, planet.y, planet.r);
    }

	char * text_str = calloc(1024, sizeof(char));

    bool show_dev_info = false;
    bool was_show_dev_info_key_pressed = false;
    while (!WindowShouldClose()) {
        clock_t timer = clock();

        BeginDrawing();
        ClearBackground(BLACK);

        PollInputEvents();

        // handle saving and loading the state of the game
        if (IsKeyDown(KEY_I)) {
            Game_State game_state = {
                .main_ship=mship,
                .planets=planets,
                .planets_count=planets_count
            };
            save_game_state(game_state);
        } else if (IsKeyDown(KEY_O)) {
            free(planets);
            Game_State game_state = load_game_state();
            mship = game_state.main_ship;
            planets = game_state.planets;
            planets_count = game_state.planets_count;
        }

        update_main_ship(&mship);
        render_planets(mship, planets, planets_count);

		if (IsKeyDown(KEY_F2) && !was_show_dev_info_key_pressed) {
            show_dev_info = !show_dev_info;
		}
		if (show_dev_info) {
            display_dev_info(text_str, mship, planets, planets_count, (float)(clock()-timer)/CLOCKS_PER_SEC);
		}
        was_show_dev_info_key_pressed = IsKeyDown(KEY_F2);

        EndDrawing();
    }
	free(text_str);
    free(planets);

    CloseWindow();
    return 0;
}