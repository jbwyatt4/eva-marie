/**************************************************************************
 * Copyright (C) 2010 Shreaders team at UC Merced
 * Copyright (C) 2010 Eva-marie team
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 **************************************************************************/

#ifndef DEFS_H
#define DEFS_H
/*These are the all the necessary includes for our game!
  All of our source files will include defs.h to get their necessary libraries/header files!
  Put the general include statements here! The more specific includes go in their respective header files.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"	//allows us to load JPG, PNG, etc.
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_thread.h"
#include "SDL/SDL_mixer.h"

// Video constraints
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600	// See below

// Map constraints
#define MAX_MAP_X 40		/* Assuming our tile sizes are 40x40, and window dimensions are 800x600 */
#define MAX_MAP_Y 90		/* 800/40 = 20, 600/40 = 15 */
#define TILE_SIZE 40		/* Default dimensions of our tiles: 40 by 40*/
#define SCROLL_SPEED 10		/* The rate at which we scroll through the map*/

// Player constraints
#define PLAYER_SPEED 5		/* The rate at which the player scrolls through the map*/

// Player Base stats
#define	BASE_ATTACK  20;
#define	BASE_DEFENSE  20;
#define	BASE_SPEED  20;
#define	BASE_HP  200;

// Screen constraints
#define SCREEN_WIDTH 800	/* The width of the game window*/
#define SCREEN_HEIGHT 600	/* The height of the game window*/

//Definitions for main character sprites:
#define PLAYERSPRITE 0		/*index number for the base player sprite*/
#define PLAYERDOWNWALK 1
#define PLAYERUP 2
#define PLAYERUPWALK 3
#define PLAYERRIGHT 4
#define PLAYERRIGHTWALK 5
#define PLAYERLEFT 6
#define PLAYERLEFTWALK 7
#define MAXIMUMSPRITE 8		/*the maximum number of sprites in an sprite array*/

//Definitions for animation speed:
#define ANIM_SPEED 3

//Number of treasure chests in game
#define NUM_TREASURE_CHESTS 8

//Size of Char Inventory
#define CHAR_INVENTORY_SIZE 12

// Player xp defintions
#define level1 100
#define level2 100
#define level3 100
#define level4 100

// modulaize to a remote file
#include "tiles.h"
#include "monsters.h"
#include "inventory.h"
#endif
