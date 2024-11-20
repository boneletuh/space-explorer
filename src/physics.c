#include <math.h>

#include "raylib.h"

#include "entities.h"


#define FRICTION 0.5
#define MSHIP_MOVEMENT_ACCELERATION 20.0*100
#define MSHIP_ROTATION_ACCELERATION 0.5

// updates the physics of a ship
// the ship is passed as a reference
void update_main_ship(Ship * ship) {
	const float dt = GetFrameTime();

	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		ship->ax = sin(ship->angle_y) * cos(ship->angle_z) * MSHIP_MOVEMENT_ACCELERATION;
		ship->ay = sin(ship->angle_x) * cos(ship->angle_z) * MSHIP_MOVEMENT_ACCELERATION;
        ship->az = cos(ship->angle_x) * cos(ship->angle_y) * MSHIP_MOVEMENT_ACCELERATION;
    } else if (IsKeyDown(KEY_RIGHT_SHIFT)) {
		ship->ax = sin(ship->angle_y) * cos(ship->angle_z) * -MSHIP_MOVEMENT_ACCELERATION;
		ship->ay = sin(ship->angle_x) * cos(ship->angle_z) * -MSHIP_MOVEMENT_ACCELERATION;
        ship->az = cos(ship->angle_x) * cos(ship->angle_y) * -MSHIP_MOVEMENT_ACCELERATION;
    } else {
		ship->ax = 0.0;
		ship->ay = 0.0;
		ship->az = 0.0;
	}

	if (IsKeyDown(KEY_W)) {
        ship->aangle_x = MSHIP_ROTATION_ACCELERATION;
    } else if (IsKeyDown(KEY_S)) {
        ship->aangle_x = -MSHIP_ROTATION_ACCELERATION;
    } else {
		ship->aangle_x = 0.0;
	}

	if (IsKeyDown(KEY_A)) {
        ship->aangle_y = -MSHIP_ROTATION_ACCELERATION;
    } else if (IsKeyDown(KEY_D)) {
        ship->aangle_y = MSHIP_ROTATION_ACCELERATION;
    } else {
		ship->aangle_y = 0.0;
	}

	if (IsKeyDown(KEY_LEFT)) {
        ship->aangle_z = -MSHIP_ROTATION_ACCELERATION;
    } else if (IsKeyDown(KEY_RIGHT)) {
        ship->aangle_z = MSHIP_ROTATION_ACCELERATION;
    } else {
		ship->aangle_z = 0.0;
	}

	// movement
	ship->vx += FRICTION * dt * -ship->vx;
	ship->vy += FRICTION * dt * -ship->vy;
	ship->vz += FRICTION * dt * -ship->vz;

	ship->vx += ship->ax * dt;
	ship->vy += ship->ay * dt;
	ship->vz += ship->az * dt;

	ship->x += ship->vx * dt;
	ship->y += ship->vy * dt;
	ship->z += ship->vz * dt;

	// orientation
	ship->vangle_x += FRICTION * dt * -ship->vangle_x;
	ship->vangle_y += FRICTION * dt * -ship->vangle_y;
	ship->vangle_z += FRICTION * dt * -ship->vangle_z;

	ship->vangle_x += ship->aangle_x * dt;
	ship->vangle_y += ship->aangle_y * dt;
	ship->vangle_z += ship->aangle_z * dt;

	ship->angle_x += ship->vangle_x * dt;
	ship->angle_y += ship->vangle_y * dt;
	ship->angle_z += ship->vangle_z * dt;

	ship->angle_x = fmod(ship->angle_x, PI*2);
	ship->angle_y = fmod(ship->angle_y, PI*2);
	ship->angle_z = fmod(ship->angle_z, PI*2);
}
