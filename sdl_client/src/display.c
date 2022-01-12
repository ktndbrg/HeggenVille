/*
 * display.c
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
#include <SDL/SDL.h>
#include "init.h"
#include "database.h"
#include "display.h"

void display (void)
{
	int i;
	SDL_Rect src, dest;
	
	/* Blit The Parallax */
	src.x = camera_pos/3;
	src.y = 0;
	src.w = 480;
	src.h = 272;
	dest = src;
	dest.x = 0;
	SDL_BlitSurface (parallax, &src, p_screen, &dest);
	
	/* Blit The Map */
	src.x = camera_pos;
	src.y = 0;
	src.w = 480;
	src.h = 272;
	dest = src;
	dest.x = 0;
	SDL_BlitSurface (map, &src, p_screen, &dest);
	
	/* Blit All the Players */
	for (i = 0; i < 4; i++)
	{
		if (player_list[i].id == 0)
		{
			continue;
		}
		
		src.w = COLUMN_CELL;
		src.h = ROW_CELL;
		dest = src;
		dest.y = 180; /* The ground (220) + 40 */
		
		if (player_list[i].id == 1)
		{
			dest.x = player_list[0].pos_x - camera_pos;
		}
		else /* Network Player */
		{
			dest.x = player_list[i].pos_x - camera_pos;
		}
		
		/* Check which state/image to post */
		switch (player_list[i].sprite_state)
		{
		case PLAYER_WALK_LEFT_1:
			src.x = 0;
			src.y = 120;
			break;
		case PLAYER_WALK_LEFT_2:
			src.x = 30;
			src.y = 120;
			break;
		case PLAYER_WALK_LEFT_3:
			src.x = 60;
			src.y = 120;
			break;
		case PLAYER_WALK_LEFT_4:
			src.x = 90;
			src.y = 120;
			break;
		case PLAYER_WALK_LEFT_5:
			src.x = 120;
			src.y = 120;
			break;
		case PLAYER_WALK_LEFT_6:
			src.x = 150;
			src.y = 120;
			break;
		case PLAYER_WALK_RIGHT_1:
			src.x = 0;
			src.y = 160;
			break;
		case PLAYER_WALK_RIGHT_2:
			src.x = 30;
			src.y = 160;
			break;
		case PLAYER_WALK_RIGHT_3:
			src.x = 60;
			src.y = 160;
			break;
		case PLAYER_WALK_RIGHT_4:
			src.x = 90;
			src.y = 160;
			break;
		case PLAYER_WALK_RIGHT_5:
			src.x = 120;
			src.y = 160;
			break;
		case PLAYER_WALK_RIGHT_6:
			src.x = 150;
			src.y = 160;
			break;
		case PLAYER_IDLE_LEFT_1:
			if (player_list[i].id == 1)
			{
				src.x = 210;
				src.y = 120;
			}
			else
			{
				src.x = 0;
				src.y = 280;
			}
			break;
		case PLAYER_IDLE_LEFT_2:
			if (player_list[i].id == 1)
			{
				src.x = 240;
				src.y = 120;
			}
			else
			{
				src.x = 30;
				src.y = 280;
			}
			break;
		case PLAYER_IDLE_RIGHT_1:
			if (player_list[i].id == 1)
			{
				src.x = 210;
				src.y = 160;
			}
			else
			{
				src.x = 60;
				src.y = 280;
			}
			break;
		case PLAYER_IDLE_RIGHT_2:
			if (player_list[i].id == 1)
			{
				src.x = 240;
				src.y = 160;
			}
			else
			{
				src.x = 90;
				src.y = 280;
			}
			break;
		case PLAYER_SHOOT_LEFT_1:
			src.x = 0;
			src.y = 200;
			break;
		case PLAYER_SHOOT_LEFT_2:
			src.x = 30;
			src.y = 200;
			break;
		case PLAYER_SHOOT_RIGHT_1:
			src.x = 60;
			src.y = 200;
			break;
		case PLAYER_SHOOT_RIGHT_2:
			src.x = 90;
			src.y = 200;
			break;
		case DIE_LEFT_1:
			src.x = 0;
			src.y = 320;
			break;
		case DIE_LEFT_2:
			src.x = 30;
			src.y = 320;
			break;
		case DIE_LEFT_3:
			src.x = 60;
			src.y = 320;
			break;
		case DIE_LEFT_4:
			src.x = 90;
			src.y = 320;
			break;
		case DIE_LEFT_5:
			src.x = 120;
			src.y = 320;
			break;
		case DIE_LEFT_6:
			src.x = 150;
			src.y = 320;
			break;
		case DIE_RIGHT_1:
			src.x = 0;
			src.y = 360;
			break;
		case DIE_RIGHT_2:
			src.x = 30;
			src.y = 360;
			break;
		case DIE_RIGHT_3:
			src.x = 60;
			src.y = 360;
			break;
		case DIE_RIGHT_4:
			src.x = 90;
			src.y = 360;
			break;
		case DIE_RIGHT_5:
			src.x = 120;
			src.y = 360;
			break;
		case DIE_RIGHT_6:
			src.x = 150;
			src.y = 360;
			break;
		default:
			fprintf (stderr, "Unknown sprite_state?....\n");
			src.x = 0;
			src.y = 180;
			break;
		};
		
		SDL_BlitSurface (gooble_sprite, &src, p_screen, &dest);
	}
	
	/* Blit the Enemies */
	/* To be implemented */
	
	SDL_Flip (p_screen);
	
	return;
}
