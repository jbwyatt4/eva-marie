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

/**
player.h handles the stuff related to the player, such as input, sprite array, etc.
*/

#include "structs.h"

extern Entity player;			//This is the character we will be controlling in our game.
extern Input input;			// Input struct for the input of the player entity.
extern Sprites sprites[MAXIMUMSPRITE];	//make an array for each of the sprites of an entity. 
extern Map samplemap;			//samplemap needed to align the player on the screen

//for the animations:
extern Animation playerAnimUp;		//Animation structs for the corresponding direction.
extern Animation playerAnimDown;
extern Animation playerAnimLeft;
extern Animation playerAnimRight;
extern int directionDetermine;			//up = 0, down = 1, left = 2, right = 3
extern int lastFacing;
extern textDisplay displayer;
extern int dontDisplayMap;
extern int showTitleScreen;

// for the battle functionality
extern int queryMap(int , int );

