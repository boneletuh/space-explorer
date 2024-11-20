#ifndef _H_ENTITIES_
#define _H_ENTITIES_

#include "raylib.h"

typedef struct Ship {
    float x,  y,  z;
    float vx, vy, vz;
    float ax, ay, az;
    float angle_x, angle_y, angle_z;
    float vangle_x, vangle_y, vangle_z;
    float aangle_x, aangle_y, aangle_z;
} Ship;

typedef struct Planet {
    float x,  y,  z;
    float r;
    Color color;
} Planet;

#endif // _H_ENTITIES_
