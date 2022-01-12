/*
 * database.c
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
#include "update.h"

bullet_t bullet_list[10];

enemy_t* DB_AddEnemy (void)
{
	enemy_t *node = DB_GetLastEnemy (enemy_list_root);
	if (node == NULL)
	{
		return NULL;
	}
	
	node->node = (enemy_t *) malloc (sizeof (enemy_t *));
	if (node->node == NULL)
	{
		return NULL;
	}
	
	return node->node;
}

void DB_RemoveEnemy (int id)
{
	enemy_t *node = DB_GetEnemyIDPrevious (enemy_list_root, id);
	if (node == NULL)
	{
		return;
	}
	enemy_t *temp = DB_GetEnemyID (enemy_list_root, id);
	
	node->node = temp->node;
	free (temp);
}

enemy_t* DB_GetLastEnemy (enemy_t *node)
{
	if (node->node == NULL)
	{
		return node;
	}
	else
	{
		return DB_GetLastEnemy (node->node);
	}
}

enemy_t* DB_GetEnemyID (enemy_t *node, int id)
{
	if (node != NULL)
	{
		enemy_t *temp = node->node;
		if (temp == NULL)
		{
			/* We looked through everything, NO matching ID! */
			return NULL;
		}
		else if (temp->id == id)
		{
			/* We found the Enemy */
			return temp;
		}
		else
		{
			/* Continue searching */
			return DB_GetEnemyID (temp, id);
		}
	}
	else if (node == NULL) /* We got an invalid pointer as start?.. */
	{
		return NULL;
	}
	
	return NULL; /* This shouldn't happen! */
}

enemy_t* DB_GetEnemyIDPrevious (enemy_t *node, int id)
{
	if (node != NULL)
	{
		enemy_t *temp = node->node;
		if (temp == NULL)
		{
			/* We looked through everything, NO matching ID! */
			return NULL;
		}
		else if (temp->id == id)
		{
			/* We found the Enemy */
			return node;
		}
		else
		{
			/* Continue searching */
			return DB_GetEnemyID (temp, id);
		}
	}
	else if (node == NULL) /* We got an invalid pointer as start?.. */
	{
		return NULL;
	}
	
	return NULL; /* This shouldn't happen! */
}

