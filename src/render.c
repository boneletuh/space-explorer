#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "raylib.h"

#include "entities.h"
#include "utils.h"
#include "render.h"


void render_planets(const Ship mship, const Planet * planets, const int planets_count) {
    for (int i = 0; i < planets_count; i++) {
        const Planet planet = planets[i];
        // https://en.wikipedia.org/wiki/3D_projection#Mathematical_formula
        float render_x = cos(mship.angle_y)*(sin(mship.angle_z)*(planet.y-mship.y) + cos(mship.angle_z)*(planet.x-mship.x)) - sin(mship.angle_y)*(planet.z-mship.z);
        float render_y = sin(-mship.angle_x)*(cos(mship.angle_y)*(planet.z-mship.z) + sin(mship.angle_y)*(sin(mship.angle_z)*(planet.y-mship.y) + cos(mship.angle_z)*(planet.x-mship.x))) + cos(-mship.angle_x)*(cos(mship.angle_z)*(planet.y-mship.y) - sin(mship.angle_z)*(planet.x-mship.x));
        float render_z = cos(-mship.angle_x)*(cos(mship.angle_y)*(planet.z-mship.z) + sin(mship.angle_y)*(sin(mship.angle_z)*(planet.y-mship.y) + cos(mship.angle_z)*(planet.x-mship.x))) - sin(-mship.angle_x)*(cos(mship.angle_z)*(planet.y-mship.y) - sin(mship.angle_z)*(planet.x-mship.x));
        float projected_x = render_x/render_z;
        float projected_y = render_y/render_z;
        DrawCircle(
            projected_x * WINDOW_WIDTH + WINDOW_WIDTH/2,
            -projected_y * WINDOW_HEIGHT + WINDOW_HEIGHT/2,
            planet.r/render_z,
            planet.color
        );
    }
}
