/*
 * init.c
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
#include <errno.h>
#include <SDL/SDL.h>
#include "init.h"
#include "database.h"
#include "network.h"

int camera_pos;
SDL_Surface *p_screen;
SDL_Surface *map;
SDL_Surface *parallax;
SDL_Surface *gooble_sprite;
player_t player_list[4];
enemy_t *enemy_list_root;

void init (void)
{
	init_sdl ();
	init_database ();
	//network ();
	
	return;
}

void init_sdl (void)
{
	if (SDL_Init (SDL_INIT_VIDEO) != 0)
	{
		fprintf (stderr, "ERROR, SDL_Init: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	atexit (SDL_Quit);

	p_screen = NULL;
	if ((p_screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGTH, BPP, VIDEO_SDL_FLAGS)) == NULL)
	{
		fprintf (stderr, "ERROR, SDL_SetVideoMode: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	SDL_WM_SetCaption (WINDOW_CAPTION, WINDOW_CAPTION);

	/* Load the Map BMP into memory */
	SDL_Surface *temp = NULL;
	temp = SDL_LoadBMP ("gamedata/map.bmp");
	if (temp == NULL)
	{
		fprintf (stderr, "Error loading map image: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	SDL_SetColorKey (temp, SDL_SRCCOLORKEY | SDL_RLEACCEL, (Uint16) SDL_MapRGB (temp->format, 0, 0, 255));
	map = SDL_DisplayFormat (temp);
	if (map == NULL)
	{
		fprintf (stderr, "Error displayformat map image: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	SDL_FreeSurface (temp);
	/* Parallax */
	temp = SDL_LoadBMP ("gamedata/parallax.bmp");
	if (temp == NULL)
	{
		fprintf (stderr, "Error loading parallax image: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	parallax = SDL_DisplayFormat (temp);
	if (parallax == NULL)
	{
		fprintf (stderr, "Error displayformat parallax image: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	SDL_FreeSurface (temp);
	
	/* Gooble Sprite */
	temp = SDL_LoadBMP ("gamedata/gooble_sprite.bmp");
	if (temp == NULL)
	{
		fprintf (stderr, "Error loading gooble_sprite image: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	SDL_SetColorKey (temp, SDL_SRCCOLORKEY | SDL_RLEACCEL, (Uint16) SDL_MapRGB (temp->format, 0, 0, 255));
	gooble_sprite = SDL_DisplayFormat (temp);
	if (gooble_sprite == NULL)
	{
		fprintf (stderr, "Error displayformat gooble_sprite image: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	SDL_FreeSurface (temp);

	return;
}

void init_database (void)
{
	/* Get memory for the Root node (player_list, which is a linked list) */
	/* Something to remember, Linux will free all malloc's after an exit (), windos will not! */
	/* That's bullshit, but I believe it */
	
	enemy_list_root = NULL;
	enemy_list_root = (enemy_t *) malloc (sizeof (enemy_t *));
	if (enemy_list_root == NULL)
	{
		fprintf (stderr, "Error Malloc 'enemy_list_root', errno: %s\n", strerror (errno));
		exit (EXIT_FAILURE);
	}
	enemy_list_root->id = 0;
	
	return;
}
