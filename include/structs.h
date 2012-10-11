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

#ifndef STRUCTS_H
#define STRUCTS_H

/**
structs.h handles the dimensions of our maps.
*/
#include "defs.h"

/**
Here we hold the data to our font library.
*/

/**
We define our Map structure which contains an multidimensional array of ints. The maximum size of this 
array is defined by MAX_MAP_Y and MAX_MAP_X which are defined in defs.h.
The startX and startY variables define the starting horizontal and vertical positions when drawing our map. The mapX and mapY variables are used to limit the amount of scrolling that the map can do.
*/typedef struct Map
{
	// starting hoz and ver postions when the map is loaded
	int startX, startY;
	// used to indicated the border on the map
	int maxX, maxY;
	// our array of tiles!
	int tile[MAX_MAP_Y][MAX_MAP_X];
} Map;

/**
   Struct to maintain input from the player i.e scrolling
   Also stores input for our directions, etc.
*/
typedef struct Input
{
	// for map movement and battle and menu!
	int left, right, up, down;

	// for use in the menu(both main and in game menu)
	int save, load;

	//for the menu
	int menu;
} Input;

/**
used to create an array of sprites.
*/
typedef struct Sprites
{
	SDL_Surface *image;
} Sprites;

/**
stats is a structure to hold the monsters
information
base = without item buffs
*/
typedef struct Stats
{
	unsigned int baseAttack;
	unsigned int attack;
	unsigned int baseDefense;
	unsigned int defense;
	unsigned int baseSpeed;
	unsigned int speed;
	unsigned int maxHp;
	unsigned int currentHp;
	unsigned int exp;
	unsigned int level;
} Stats;

/*
This struct is for the actual, moving sprites on the map. Contains coordinates and pointers to the image.
*/
typedef struct Entity
{
	int x, y;		// position of the entity
	int dirX, dirY;	// movement of entity (needed to check for collision)
	int w, h;		// width and height of entity (Image)
	SDL_Surface *sprite;
	SDL_Surface *battleSprite;
	Stats stats;
} Entity;

/**
This struct is for animations.
*/
typedef struct Animation
{
    int frameCount, frameIndex, counter;
    SDL_Surface **frame;

} Animation;

/**
The character's current inventory
represented as a array except for gold.
*/
typedef struct Inventory
{
	int inventoryList[CHAR_INVENTORY_SIZE];
	unsigned int goldAmt; // the amount of gold the player has!
} Inventory;

/**
	holds the data for user changable items
	it is initalized on game creation/game loading
	this one of the two structs that are used to save
*/
typedef struct WorldData
{
	// monster blogs
	int alreadyFoughtBoss;

} WorldData;

/**
This holds all of our current battle data
it is stored in GameState as a convinece

when battlestate is initalized, all data is set to 0

having all the battle data in one struct makes it easy to move around
and clear.
*/
typedef struct BattleData {
	int texture; // this is important for determining what monster we fight as it is based on land
	int exit;
} BattleData;

/**
struct to hold game instance data
also holds game state

0 - menu
1 - world
2 - battle

*/
typedef struct GameState
{
	// for saving and loading
	// the game while the key is held down will continue
	// to load from the file which is bad
	// initalize the variables at game start up
	int alreadyLoaded;
	int alreadySaved;

	// holds the current state of the game.
	WorldData worldData;
	BattleData battleData;

} GameState;

/**
use for SDL's tt font library 
*/
typedef struct textDisplay{

	SDL_Surface *screen;
	TTF_Font *font;
	TTF_Font *smallfont;

} textDisplay;

/**
struct to hold gold and inventory of the genie store
*/
typedef struct GenieStore {
	//unsigned int storeGold;
	unsigned int minorPotion;
	unsigned int lesserPotion;
	unsigned int greaterPotion;
	unsigned int superPotion;
} GenieStore;

// here we set the definitions
GameState game;
Entity stewie;
//Entity hero;
Entity player;
GenieStore genieStore;
Inventory charInventory;

// Monster declarations
Entity lv1Goop;
Entity lv2Lizard;
Entity lv3Multi;
Entity battleMonster;

#endif
