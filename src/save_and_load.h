#ifndef _H__SAVE_AND_LOAD_
#define _H__SAVE_AND_LOAD_

#include "entities.h"

typedef struct Game_State {
	Planet * planets;
	int planets_count;
	Ship main_ship;
} Game_State;

void save_game_state(const Game_State game_state);
Game_State load_game_state(void);

#endif // _H__SAVE_AND_LOAD_