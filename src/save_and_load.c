#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "entities.h"

#include "save_and_load.h"
#include "utils.h"

#define PLANETS_FILE "./saved_state_files/planets.txt"
#define MSHIP_FILE "./saved_state_files/main_ship.txt"


void save_game_state(const Game_State game_state) {
	clock_t timer = clock();
	// save the state of main ship
	Ship mship = game_state.main_ship;

	FILE * mship_file = fopen(MSHIP_FILE, "wb");

	fprintf(mship_file, "x=%f\n", (float)mship.x);
	fprintf(mship_file, "y=%f\n", (float)mship.y);
	fprintf(mship_file, "z=%f\n", (float)mship.z);
	fprintf(mship_file, "vx=%f\n", (float)mship.vx);
	fprintf(mship_file, "vy=%f\n", (float)mship.vy);
	fprintf(mship_file, "vz=%f\n", (float)mship.vz);
	fprintf(mship_file, "ax=%f\n", (float)mship.ax);
	fprintf(mship_file, "ay=%f\n", (float)mship.ay);
	fprintf(mship_file, "az=%f\n", (float)mship.az);
	fprintf(mship_file, "rot_x=%f\n", (float)mship.angle_x);
	fprintf(mship_file, "rot_y=%f\n", (float)mship.angle_y);
	fprintf(mship_file, "rot_z=%f\n", (float)mship.angle_z);
	fprintf(mship_file, "vrot_x=%f\n", (float)mship.vangle_x);
	fprintf(mship_file, "vrot_y=%f\n", (float)mship.vangle_y);
	fprintf(mship_file, "vrot_z=%f\n", (float)mship.vangle_z);
	fprintf(mship_file, "arot_x=%f\n", (float)mship.aangle_x);
	fprintf(mship_file, "arot_y=%f\n", (float)mship.aangle_y);
	fprintf(mship_file, "arot_z=%f\n", (float)mship.aangle_z);

	fclose(mship_file);

	// save the state of the planets
	Planet * planets = game_state.planets;
	int planets_count = game_state.planets_count;

	FILE * planets_file = fopen(PLANETS_FILE, "wb");

	fprintf(planets_file, "planets count=%d\n\n", planets_count);
	for (int i = 0; i < planets_count; i++) {
		Planet planet = planets[i];
		fprintf(planets_file, "x=%f\n", planet.x);
		fprintf(planets_file, "y=%f\n", planet.y);
		fprintf(planets_file, "z=%f\n", planet.z);
		fprintf(planets_file, "r=%f\n", planet.r);
		fprintf(planets_file, "color=%X\n", (planet.color.r<<16) | (planet.color.g<<8) | planet.color.b);
		fprintf(planets_file, "end=planet\n");
		fprintf(planets_file, "\n");
	}

	fclose(planets_file);

	printf("save time=%f\n", (double)(clock()-timer)/CLOCKS_PER_SEC);
}

// the Game_States.planets will have a malloc() allocated array
Game_State load_game_state(void) {
	clock_t timer = clock();

	Game_State game_state;

	int line_num;

	// load the state of the main ship
	char * mship_file_contents = read_file_contents(MSHIP_FILE);
	Ship mship = {
		.x=0, .y=0, .z=0,
		.vx=0, .vy=0, .vz=0,
		.ax=0, .ay=0, .az=0,
		.angle_x=0, .angle_y=0, .angle_z=0,
        .vangle_x=0, .vangle_y=0, .vangle_z=0,
        .aangle_x=0, .aangle_y=0, .aangle_z=0
	};

	line_num = 0;
	while (mship_file_contents[line_num] != '\0') {
		char line_buff[256] = {0};
		int line_length;
		int i;
		for (i = 0; mship_file_contents[line_num+i] != '\n'; i++) {
			line_buff[i] = mship_file_contents[line_num+i];
		}
		line_length = i;
		line_num += i +1;
		// skip empty lines
		if (line_length == 0) {
			continue;
		}

		char param_buff[64] = {0};
		int param_length = 0;
		for (i = 0; line_buff[i] != '='; i++) {
			param_buff[i] = line_buff[i];
		}
		param_length = i;

		char value_buff[64] = {0};
		for (i = 0; i < line_length - (param_length+1); i++) {
			value_buff[i] = line_buff[param_length+1 + i];
		}

		if (strcmp(param_buff, "x") == 0) {
			mship.x = atof(value_buff);
		} else if (strcmp(param_buff, "y") == 0) {
			mship.y = atof(value_buff);
		} else if (strcmp(param_buff, "z") == 0) {
			mship.z = atof(value_buff);
		} else if (strcmp(param_buff, "vx") == 0) {
			mship.vx = atof(value_buff);
		} else if (strcmp(param_buff, "vy") == 0) {
			mship.vy = atof(value_buff);
		} else if (strcmp(param_buff, "vz") == 0) {
			mship.vz = atof(value_buff);
		} else if (strcmp(param_buff, "ax") == 0) {
			mship.ax = atof(value_buff);
		} else if (strcmp(param_buff, "ay") == 0) {
			mship.ay = atof(value_buff);
		} else if (strcmp(param_buff, "az") == 0) {
			mship.az = atof(value_buff);
		} else if (strcmp(param_buff, "rot_x") == 0) {
			mship.angle_x = atof(value_buff);
		} else if (strcmp(param_buff, "rot_y") == 0) {
			mship.angle_y = atof(value_buff);
		} else if (strcmp(param_buff, "rot_z") == 0) {
			mship.angle_z = atof(value_buff);
		} else if (strcmp(param_buff, "vrot_x") == 0) {
			mship.vangle_x = atof(value_buff);
		} else if (strcmp(param_buff, "vrot_y") == 0) {
			mship.vangle_y = atof(value_buff);
		} else if (strcmp(param_buff, "vrot_z") == 0) {
			mship.vangle_z = atof(value_buff);
		} else if (strcmp(param_buff, "arot_x") == 0) {
			mship.aangle_x = atof(value_buff);
		} else if (strcmp(param_buff, "arot_y") == 0) {
			mship.aangle_y = atof(value_buff);
		} else if (strcmp(param_buff, "arot_z") == 0) {
			mship.aangle_z = atof(value_buff);
		} else {
			printf("unkown paramenter in line:%d, with name (%s)\n", line_num, param_buff);
			exit(1);
		}
	}
	free(mship_file_contents);

	game_state.main_ship = mship;

	// load the state of the planets
	char * planets_file_contents = read_file_contents(PLANETS_FILE);
	Planet * planets;
	int planets_count;

	int planet_idx = 0;
	line_num = 0;
	while (planets_file_contents[line_num] != '\0') {
		char line_buff[256] = {0};
		int line_length;
		int i;
		for (i = 0; planets_file_contents[line_num+i] != '\n'; i++) {
			line_buff[i] = planets_file_contents[line_num+i];
		}
		line_length = i;
		line_num += i +1;
		// skip empty lines
		if (line_length == 0) {
			continue;
		}

		char param_buff[64] = {0};
		int param_length = 0;
		for (i = 0; line_buff[i] != '='; i++) {
			param_buff[i] = line_buff[i];
		}
		param_length = i;

		char value_buff[64] = {0};
		for (i = 0; i < line_length - (param_length+1); i++) {
			value_buff[i] = line_buff[param_length+1 + i];
		}

		if (strcmp(param_buff, "planets count") == 0) {
			planets_count = atoi(value_buff);
			planets = malloc(sizeof(Planet) * planets_count);
		} else if (strcmp(param_buff, "x") == 0) {
			float val = atof(value_buff);
			planets[planet_idx].x = val;
		} else if (strcmp(param_buff, "y") == 0) {
			planets[planet_idx].y = atof(value_buff);
		} else if (strcmp(param_buff, "z") == 0) {
			planets[planet_idx].z = atof(value_buff);
		} else if (strcmp(param_buff, "r") == 0) {
			planets[planet_idx].r = atof(value_buff);
		} else if (strcmp(param_buff, "color") == 0) {
			unsigned color = strtol(value_buff, NULL, 16);
			planets[planet_idx].color.r = 0xff&(color>>16);
			planets[planet_idx].color.g = 0xff&(color>>8);
			planets[planet_idx].color.b = 0xff&(color);
			planets[planet_idx].color.a = 0xff;
		} else if (strcmp(param_buff, "end") == 0) {
			planet_idx++;
		} else {
			printf("unkown paramenter in line:%d, with name (%s)\n", line_num, param_buff);
			exit(1);
		}
	}
	free(planets_file_contents);

	game_state.planets = planets;
	game_state.planets_count = planets_count;

	printf("load time=%f\n", (double)(clock()-timer)/CLOCKS_PER_SEC);

	return game_state;
}