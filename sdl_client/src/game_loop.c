/*
 * game_loop.c
 * This file is part of HeggenVille
 *
 * Copyright (C) 2018 - Calvin T. Maxwell
 *
 * HeggenVille is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * HeggenVille is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HeggenVille. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <SDL/SDL.h>
#include "init.h"
#include "database.h"
#include "network.h"
#include "game_loop.h"
#include "input.h"
#include "update.h"
#include "display.h"
#include "audio.h"

void game_loop (void)
{
	time_scale = 0;
	prev_ticks = 0;
	cur_ticks = 0;
	player_list[0].id = 1;
	player_list[0].health = 100;
	player_list[0].pos_x = 300;
	player_list[0].sprite_state = 0;
	player_list[0].sprite_dir = UP;
	player_list[0].state_timer = IDLE_TIMER;
	
	while (1)
	{
		prev_ticks = cur_ticks;
		cur_ticks = SDL_GetTicks ();
		time_scale = (double)(cur_ticks-prev_ticks)/60.0;
	
		/* Lock Mutex on Network Read-Update */
		input ();
		update ();
		display ();
		audio ();
		/* Unlock Mutex */
	}

	return;
}

