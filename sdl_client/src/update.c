/*
 * update.c
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
#include "input.h"
#include "update.h"
#include "display.h"

double time_scale;
int prev_ticks;
int cur_ticks;

void update (void)
{
	/* Walk Left Input */
	if (input_left)
	{
        /* Is he already moving to the left, or is in an 'non-stop' animation */
		if (player_list[0].sprite_state == PLAYER_WALK_LEFT_1 || player_list[0].sprite_state == PLAYER_WALK_LEFT_2 || player_list[0].sprite_state == PLAYER_WALK_LEFT_3 || player_list[0].sprite_state == PLAYER_WALK_LEFT_4 || player_list[0].sprite_state == PLAYER_WALK_LEFT_5 || player_list[0].sprite_state == PLAYER_WALK_LEFT_6 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_1 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_2 || player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_1 || player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_2 || player_list[0].sprite_state == DIE_LEFT_1 || player_list[0].sprite_state == DIE_LEFT_2 || player_list[0].sprite_state == DIE_LEFT_3 || player_list[0].sprite_state == DIE_LEFT_4 || player_list[0].sprite_state == DIE_LEFT_5 || player_list[0].sprite_state == DIE_LEFT_6 || player_list[0].sprite_state == DIE_RIGHT_1 || player_list[0].sprite_state == DIE_RIGHT_2 || player_list[0].sprite_state == DIE_RIGHT_3 || player_list[0].sprite_state == DIE_RIGHT_4 || player_list[0].sprite_state == DIE_RIGHT_5 || player_list[0].sprite_state == DIE_RIGHT_6)
		{
			/* Already In Animation */
		}
		else
		{
		    /* Set his direction for later */
			player_list[0].dir_x = -2.0f;
			/* Set his animation state to the first walking sprite */
			player_list[0].sprite_state = PLAYER_WALK_LEFT_1;
			/* Reset his animation-timer */
			player_list[0].state_timer = WALK_TIMER;
			/* Set his 'animation direction' to upwards, meaning the next sprite to show is ++i */
			player_list[0].sprite_dir = UP;
		}
	}

	/* Walk Right Input */
	/* This is copy-paste from (Walk Left Input), see above */
	else if (input_right)
	{
		if (player_list[0].sprite_state == PLAYER_WALK_RIGHT_1 || player_list[0].sprite_state == PLAYER_WALK_RIGHT_2 || player_list[0].sprite_state == PLAYER_WALK_RIGHT_3 || player_list[0].sprite_state == PLAYER_WALK_RIGHT_4 || player_list[0].sprite_state == PLAYER_WALK_RIGHT_5 || player_list[0].sprite_state == PLAYER_WALK_RIGHT_6 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_1 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_2 || player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_1 || player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_2 || player_list[0].sprite_state == DIE_LEFT_1 || player_list[0].sprite_state == DIE_LEFT_2 || player_list[0].sprite_state == DIE_LEFT_3 || player_list[0].sprite_state == DIE_LEFT_4 || player_list[0].sprite_state == DIE_LEFT_5 || player_list[0].sprite_state == DIE_LEFT_6 || player_list[0].sprite_state == DIE_RIGHT_1 || player_list[0].sprite_state == DIE_RIGHT_2 || player_list[0].sprite_state == DIE_RIGHT_3 || player_list[0].sprite_state == DIE_RIGHT_4 || player_list[0].sprite_state == DIE_RIGHT_5 || player_list[0].sprite_state == DIE_RIGHT_6){}
		else
		{
			player_list[0].dir_x = 2.0f;
			player_list[0].sprite_state = PLAYER_WALK_RIGHT_1;
			player_list[0].state_timer = WALK_TIMER;
			player_list[0].sprite_dir = UP;
		}
	}
	else
	{
		if (player_list[0].sprite_state == PLAYER_IDLE_LEFT_1 || player_list[0].sprite_state == PLAYER_IDLE_LEFT_2 || player_list[0].sprite_state == PLAYER_IDLE_RIGHT_1 || player_list[0].sprite_state == PLAYER_IDLE_RIGHT_2 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_1 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_2 || player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_1 || player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_2 || player_list[0].sprite_state == DIE_LEFT_1 || player_list[0].sprite_state == DIE_LEFT_2 || player_list[0].sprite_state == DIE_LEFT_3 || player_list[0].sprite_state == DIE_LEFT_4 || player_list[0].sprite_state == DIE_LEFT_5 || player_list[0].sprite_state == DIE_LEFT_6 || player_list[0].sprite_state == DIE_RIGHT_1 || player_list[0].sprite_state == DIE_RIGHT_2 || player_list[0].sprite_state == DIE_RIGHT_3 || player_list[0].sprite_state == DIE_RIGHT_4 || player_list[0].sprite_state == DIE_RIGHT_5 || player_list[0].sprite_state == DIE_RIGHT_6){}
		else
		{
			if (player_list[0].dir_x < 0.0f)
			{
				player_list[0].sprite_state = PLAYER_IDLE_LEFT_1;
				player_list[0].dir_x = 0.0f;
			}
			else
			{
				player_list[0].sprite_state = PLAYER_IDLE_RIGHT_1;
				player_list[0].dir_x = 0.0f;
			}
			player_list[0].sprite_dir = UP;
			player_list[0].state_timer = IDLE_TIMER;
		}
	}

	/* Shoot Input */
	/* Did you shoot, and are you not in a dead-state? */
	if (input_shoot && player_list[0].target_id != -1)
	{
	    /* Check if we are already doing a 'Don't stop' animation */
		if (player_list[0].sprite_state == PLAYER_SHOOT_LEFT_1 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_2 || player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_1 || player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_2){}
		else
		{
		    /* Which way to shoot bullets */
		    /* Is his direction zero, that will be harder (not hard, but longer) to determine then */
			if (player_list[0].dir_x == 0)
			{
			    /* Soo his direction is Zero, so we need to inspect his animation_state to see which way */
				if (player_list[0].sprite_state == PLAYER_IDLE_LEFT_1 || player_list[0].sprite_state == PLAYER_IDLE_LEFT_2)
				{
					player_list[0].sprite_state = PLAYER_SHOOT_LEFT_1;
					player_list[0].state_timer = SHOOT_TIMER;
					player_list[0].sprite_dir = UP;
				}
				else if (player_list[0].sprite_state == PLAYER_IDLE_RIGHT_1 || player_list[0].sprite_state == PLAYER_IDLE_RIGHT_2)
				{
					player_list[0].sprite_state = PLAYER_SHOOT_RIGHT_1;
					player_list[0].state_timer = SHOOT_TIMER;
					player_list[0].sprite_dir = UP;
				}
			}
			/* He does have a direction, this is easy */
			else
			{
			    /* Does he looks to the left? */
				if (player_list[0].dir_x < 0)
				{
					player_list[0].sprite_state = PLAYER_SHOOT_LEFT_1;
					player_list[0].state_timer = SHOOT_TIMER;
					player_list[0].sprite_dir = UP;
				}
				else
				{
					player_list[0].sprite_state = PLAYER_SHOOT_RIGHT_1;
					player_list[0].state_timer = SHOOT_TIMER;
					player_list[0].sprite_dir = UP;
				}
			}
			/* Did we manage to shoot? And if so, which way */
			if (player_list[0].sprite_state == PLAYER_SHOOT_LEFT_1)
			{
				player_list[0].dir_x = 0.0f;
				/*
					Send to Server, added bullet
				*/
			}
			else if (player_list[0].sprite_state == PLAYER_SHOOT_RIGHT_1)
			{
				player_list[0].dir_x = 0.0f;
				/*
					Send to Server, added bullet
				*/
			}
		}
	}

	/* Player Died */
	if (player_list[0].health <= 0 && player_list[0].target_id != -1)
	{
		player_list[0].state_timer = DIE_TIMER;
		player_list[0].target_id = -1;
		if (player_list[0].dir_x == 0)
		{
				if (player_list[0].sprite_state == PLAYER_IDLE_LEFT_1 || player_list[0].sprite_state == PLAYER_IDLE_LEFT_2 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_1 || player_list[0].sprite_state == PLAYER_SHOOT_LEFT_2)
				{
					player_list[0].sprite_state = DIE_LEFT_1;
				}
				else
				{
					player_list[0].sprite_state = DIE_RIGHT_1;
				}
		}
		else
		{
				if (player_list[0].dir_x < 0)
				{
					player_list[0].sprite_state = DIE_LEFT_1;
				}
				else
				{
					player_list[0].sprite_state = DIE_RIGHT_1;
				}
		}
		player_list[0].dir_x = 0;
	}

	/* Move the player */
	player_list[0].pos_x += player_list[0].dir_x * time_scale;

	/* See if any animations need update */
	/* If they do, reset the timer and move the picture/animation one up */
	player_list[0].state_timer -= 0.1f * time_scale;
	if (player_list[0].state_timer < 0.0f)
	{
		switch (player_list[0].sprite_state)
		{
		case PLAYER_WALK_LEFT_1:
			player_list[0].sprite_dir = UP;
			player_list[0].sprite_state = PLAYER_WALK_LEFT_2;
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_LEFT_2:
			player_list[0].sprite_dir = UP;
			player_list[0].sprite_state = PLAYER_WALK_LEFT_3;
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_LEFT_3:
			player_list[0].sprite_dir = UP;
			player_list[0].sprite_state = PLAYER_WALK_LEFT_4;
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_LEFT_4:
			if (player_list[0].sprite_dir == UP)
			{
				player_list[0].sprite_state = PLAYER_WALK_LEFT_5;
			}
			else
			{
				player_list[0].sprite_state = PLAYER_WALK_LEFT_3;
			}
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_LEFT_5:
			if (player_list[0].sprite_dir == UP)
			{
				player_list[0].sprite_state = PLAYER_WALK_LEFT_6;
			}
			else
			{
				player_list[0].sprite_state = PLAYER_WALK_LEFT_4;
			}
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_LEFT_6:
			player_list[0].sprite_dir = DOWN;
			player_list[0].sprite_state = PLAYER_WALK_LEFT_5;
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_RIGHT_1:
			player_list[0].sprite_dir = UP;
			player_list[0].sprite_state = PLAYER_WALK_RIGHT_2;
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_RIGHT_2:
			player_list[0].sprite_dir = UP;
			player_list[0].sprite_state = PLAYER_WALK_RIGHT_3;
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_RIGHT_3:
			player_list[0].sprite_dir = UP;
			player_list[0].sprite_state = PLAYER_WALK_RIGHT_4;
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_RIGHT_4:
			if (player_list[0].sprite_dir == UP)
			{
				player_list[0].sprite_state = PLAYER_WALK_RIGHT_5;
			}
			else
			{
				player_list[0].sprite_state = PLAYER_WALK_RIGHT_3;
			}
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_RIGHT_5:
			if (player_list[0].sprite_dir == UP)
			{
				player_list[0].sprite_state = PLAYER_WALK_RIGHT_6;
			}
			else
			{
				player_list[0].sprite_state = PLAYER_WALK_RIGHT_4;
			}
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_WALK_RIGHT_6:
			player_list[0].sprite_dir = DOWN;
			player_list[0].sprite_state = PLAYER_WALK_RIGHT_5;
			player_list[0].state_timer = WALK_TIMER;
			break;
		case PLAYER_IDLE_LEFT_1:
			player_list[0].sprite_state = PLAYER_IDLE_LEFT_2;
			player_list[0].state_timer = IDLE_TIMER;
			break;
		case PLAYER_IDLE_LEFT_2:
			player_list[0].sprite_state = PLAYER_IDLE_LEFT_1;
			player_list[0].state_timer = IDLE_TIMER;
			break;
		case PLAYER_IDLE_RIGHT_1:
			player_list[0].sprite_state = PLAYER_IDLE_RIGHT_2;
			player_list[0].state_timer = IDLE_TIMER;
			break;
		case PLAYER_IDLE_RIGHT_2:
			player_list[0].sprite_state = PLAYER_IDLE_RIGHT_1;
			player_list[0].state_timer = IDLE_TIMER;
			break;
		case PLAYER_SHOOT_LEFT_1:
			if (player_list[0].sprite_dir == UP)
			{
				player_list[0].sprite_state = PLAYER_SHOOT_LEFT_2;
				player_list[0].state_timer = SHOOT_TIMER;
			}
			else
			{
				player_list[0].sprite_state = PLAYER_IDLE_LEFT_1;
				player_list[0].state_timer = IDLE_TIMER;
				player_list[0].sprite_dir = UP;
			}
			break;
		case PLAYER_SHOOT_LEFT_2:
			player_list[0].sprite_state = PLAYER_SHOOT_LEFT_1;
			player_list[0].state_timer = SHOOT_TIMER;
			player_list[0].sprite_dir = DOWN;
			break;
		case PLAYER_SHOOT_RIGHT_1:
			if (player_list[0].sprite_dir == UP)
			{
				player_list[0].sprite_state = PLAYER_SHOOT_RIGHT_2;
				player_list[0].state_timer = SHOOT_TIMER;
			}
			else
			{
				player_list[0].sprite_state = PLAYER_IDLE_RIGHT_1;
				player_list[0].state_timer = IDLE_TIMER;
				player_list[0].sprite_dir = UP;
			}
			break;
		case PLAYER_SHOOT_RIGHT_2:
			player_list[0].sprite_state = PLAYER_SHOOT_RIGHT_1;
			player_list[0].state_timer = SHOOT_TIMER;
			player_list[0].sprite_dir = DOWN;
			break;
		case DIE_LEFT_1:
			player_list[0].sprite_state = DIE_LEFT_2;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_LEFT_2:
			player_list[0].sprite_state = DIE_LEFT_3;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_LEFT_3:
			player_list[0].sprite_state = DIE_LEFT_4;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_LEFT_4:
			player_list[0].sprite_state = DIE_LEFT_5;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_LEFT_5:
			player_list[0].sprite_state = DIE_LEFT_6;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_LEFT_6:
			player_list[0].sprite_state = PLAYER_IDLE_RIGHT_1;
			player_list[0].state_timer = IDLE_TIMER;
			player_list[0].sprite_dir = UP;
			player_list[0].pos_x = 275;
			player_list[0].health = 100;
			player_list[0].target_id = 1;
			break;
		case DIE_RIGHT_1:
			player_list[0].sprite_state = DIE_RIGHT_2;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_RIGHT_2:
			player_list[0].sprite_state = DIE_RIGHT_3;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_RIGHT_3:
			player_list[0].sprite_state = DIE_RIGHT_4;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_RIGHT_4:
			player_list[0].sprite_state = DIE_RIGHT_5;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_RIGHT_5:
			player_list[0].sprite_state = DIE_RIGHT_6;
			player_list[0].state_timer = DIE_TIMER;
			break;
		case DIE_RIGHT_6:
			player_list[0].sprite_state = PLAYER_IDLE_LEFT_1;
			player_list[0].state_timer = IDLE_TIMER;
			player_list[0].sprite_dir = UP;
			player_list[0].pos_x = 1550;
			player_list[0].health = 100;
			player_list[0].target_id = 1;
			break;
		default:
			fprintf (stderr, "Unknown sprite_state?....\n");
			break;
		};
	}

	/* Teleport the Player */
	/* Do keep in-mind that the player coordinates are in the corner of his sprite, not his center, if not mistaken.. */
	if (player_list[0].pos_x <= 210)
	{
		player_list[0].pos_x = (1610 + (player_list[0].pos_x - 210));
	}
	else if (player_list[0].pos_x >= 1620)
	{
		player_list[0].pos_x = (220 + (player_list[0].pos_x - 1620));
	}

	/* Move the Player forward (or its an illusion, if we just move the camera in relation to the player/background, it looks like you move the player instead and the camera just "follows") */
	/* This statement means that the player will 'move' every frame, but if he isn't moving (.pos_x == 0), so it doesn't matter */
	camera_pos = player_list[0].pos_x - 200;

	return;
}

