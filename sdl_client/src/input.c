/*
 * input.c
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

#include <SDL/SDL.h>
#include "init.h"
#include "database.h"
#include "input.h"

void client_close (void);

unsigned char *keystate;
unsigned char input_left;
unsigned char input_right;
unsigned char input_use;
unsigned char input_shoot;

void input (void)
{
	input_left = 0; input_right = 0; input_use = 0; input_shoot = 0;

	SDL_PumpEvents ();
	keystate = SDL_GetKeyState (NULL);

	if (keystate[SDLK_ESCAPE])
	{
		client_close ();
	}
	if (keystate[SDLK_a])
	{
		input_left = 1;
	}
	if (keystate[SDLK_LEFT])
	{
		input_left = 1;
	}
	if (keystate[SDLK_d])
	{
		input_right = 1;
	}
	if (keystate[SDLK_RIGHT])
	{
		input_right = 1;
	}
	if (keystate[SDLK_e])
	{
		input_use = 1;
	}
	if (keystate[SDLK_f])
	{
		input_use = 1;
	}
	if (keystate[SDLK_SPACE])
	{
		input_shoot = 1;
	}
	if (keystate[SDLK_RETURN])
	{
		input_shoot = 1;
	}
	if (keystate[SDLK_q])
	{
		player_list[0].health = 0;
	}

	return;
}
