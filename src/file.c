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

#include "game.h"

/**
load both character and boss position data

hero
0, width of screen/2

boss
height of map - 5, width of screen/2
*/
int loadEntityPos(char * charPosFileLoc, Entity* hero, Entity* boss) {
	FILE *fp;
	fp = fopen(charPosFileLoc, "rb");
	if (fp == NULL) {
		printf("loadEntity: we can't open char data!\n");
		return 1;
	}
	
	// load character data
	fscanf(fp, "%d ", &(hero->x) );
	fscanf(fp, "%d ", &(hero->y) );

	// load boss data
	fscanf(fp, "%d ", &(boss->x) );
	fscanf(fp, "%d ", &(boss->y) );

	fclose(fp);
	return 0;
}

/****
loads character data from defined string location

also loads world data

0 if successful
1 if not

*/
int loadCharData(char * fileLoc) {
	// just loads the character's position from a text stream
	FILE *fp;
	fp = fopen(fileLoc, "rb");

	// if we can't open the character save data we quit
	if ( fp == NULL) {
		printf("loadCharData: we can't open char save data!\n");
		return 1;
	}

	// read first two integers for x and y positions
	fscanf(fp, "%d ", &(player.x) );
	fscanf(fp, "%d ", &(player.y) );

	// now load the world data
	// boss flag
	fscanf(fp, "%d ", &(game.worldData.alreadyFoughtBoss) );
	
	// load player inventory
	fscanf(fp, "%d ", &(charInventory.inventoryList[0]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[1]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[2]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[3]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[4]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[5]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[6]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[7]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[8]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[9]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[10]) );
	fscanf(fp, "%d ", &(charInventory.inventoryList[11]) );
	
	// load player gold
	fscanf(fp, "%d ", &(charInventory.goldAmt) );
	
	// load character stats baseAttack, attack, baseDefense, defense, baseSpeed, speed, maxHp, currentHp

	fscanf(fp, "%d ", &(player.stats.baseAttack) );
	fscanf(fp, "%d ", &(player.stats.attack) );
	fscanf(fp, "%d ", &(player.stats.baseDefense) );
	fscanf(fp, "%d ", &(player.stats.defense) );
	fscanf(fp, "%d ", &(player.stats.baseSpeed) );
	fscanf(fp, "%d ", &(player.stats.speed) );
	fscanf(fp, "%d ", &(player.stats.maxHp) );
	fscanf(fp, "%d ", &(player.stats.currentHp) );
	fscanf(fp, "%d ", &(player.stats.exp) );
	fscanf(fp, "%d ", &(player.stats.level) );

	fclose(fp);

	return 0;
}

/****
saves character data from defined string location

also saves world data

0 if successful
1 if not

*/
int saveCharData(char * fileLoc) {
	// just loads the character's position from a text stream
	FILE *fp;

	fp = fopen(fileLoc, "wb");

	// if we can't open the character save data we quit
	if ( fp == NULL) {
		printf("saveCharData: we can't write to char save data!\n");
		return 1;
	}

	// read first two integers for x and y positions
	fprintf(fp, "%d ", player.x );
	fprintf(fp, "%d ", player.y );

	// now save the world data
	// boss flag
	fprintf(fp, "%d ", game.worldData.alreadyFoughtBoss );


	// save player inventory
	fprintf(fp, "\n%d ", charInventory.inventoryList[0]);
	fprintf(fp, "%d ", charInventory.inventoryList[1]);
	fprintf(fp, "%d ", charInventory.inventoryList[2]);
	fprintf(fp, "%d ", charInventory.inventoryList[3]);
	fprintf(fp, "%d ", charInventory.inventoryList[4]);
	fprintf(fp, "%d ", charInventory.inventoryList[5]);
	fprintf(fp, "%d ", charInventory.inventoryList[6]);
	fprintf(fp, "%d ", charInventory.inventoryList[7]);
	fprintf(fp, "%d ", charInventory.inventoryList[8]);
	fprintf(fp, "%d ", charInventory.inventoryList[9]);
	fprintf(fp, "%d ", charInventory.inventoryList[10]);
	fprintf(fp, "%d ", charInventory.inventoryList[11]);
	
	
	// load player gold
	fprintf(fp, "\n%d ", charInventory.goldAmt );


	// save character stats baseAttack, attack, baseDefense, defense, baseSpeed, speed, maxHp, currentHp

	fprintf(fp, "\n%d ", (player.stats.baseAttack) );
	fprintf(fp, "%d ", (player.stats.attack) );
	fprintf(fp, "%d ", (player.stats.baseDefense) );
	fprintf(fp, "%d ", (player.stats.defense) );
	fprintf(fp, "%d ", (player.stats.baseSpeed) );
	fprintf(fp, "%d ", (player.stats.speed) );
	fprintf(fp, "%d ", (player.stats.maxHp) );
	fprintf(fp, "%d ", (player.stats.currentHp) );
	fprintf(fp, "%d ", (player.stats.exp) );
	fprintf(fp, "%d ", (player.stats.level) );

	fclose(fp);

	return 0;
}

/****
Initializes a Treasure Chest Map file and 2D array

0 if successful
1 if not

*/
int initTreasureChestData(char * fileLoc) {
	remove(fileLoc); // remove previously existing Treasure chest data file

	// Create a new Treasure chest data file
	FILE *fp;

	fp = fopen(fileLoc, "wb");

	// if we can't open the character save data we quit
	if ( fp == NULL) {
		printf("initTreasureChestData: we can't open Treasure chest Data!\n");
		return 1;
	}
	// initialize all coordinates to -1,-1 as in unused
	int i;
	for (i = 0; i < NUM_TREASURE_CHESTS; i++){
		treasureChestData[i][0] = -1;
		treasureChestData[i][1] = -1;
	}
	saveTreasureChestData(fileLoc);
	return 0;
}

/****
saves treasure chest data to the file i.e when the save is hit

0 if successful
1 if not

*/
int saveTreasureChestData(char * fileLoc) {
	FILE *fp;
	int i;
	fp = fopen(fileLoc, "wb");
	// if we can't open the character save data we quit
	if ( fp == NULL) {
		printf("saveTreasureChestData: we can't open Treasure chest Data!\n");
		return 1;
	}
	for (i = 0; i < NUM_TREASURE_CHESTS; i++){
		fprintf(fp, "%d ", treasureChestData[i][0] );
		fprintf(fp, "%d\n", treasureChestData[i][1] );
	}
	fclose(fp);
	return 0;
}

/****
Loads saved treasure chest data from the file i.e when the game is continued

0 if successful
1 if not

*/
int loadTreasureChestData(char * fileLoc) {
	FILE *fp;

	fp = fopen(fileLoc, "rb");
	printf("2\n");
	// if we can't open the character save data we quit
	if ( fp == NULL) {
		printf("loadTreasureChestData: we can't open Treasure chest Data!\n");
		initTreasureChestData(fileLoc);
		return 1;
	}
	int i;
 	for(i = 0; feof(fp) == 0; i++){
		fscanf(fp, "%d ", &treasureChestData[i][0] );
		fscanf(fp, "%d ", &treasureChestData[i][1] );
	}
	fclose(fp);
	return 0;
}

/****
adds recently opened treasure chest data after checking if it was used i.e when the game is continued

0 if successful
1 if not

*/
int addTreasureChestData(int x , int y) {
	int i;
	if(checkTreasureChestData(x , y) == 1){
		for (i = 0; i < NUM_TREASURE_CHESTS; i++){
			if(treasureChestData[i][0] == -1 && treasureChestData[i][1] == -1){
				treasureChestData[i][0] = x;
				treasureChestData[i][1] = y;
				return 0;			
			}
		}
	}
	return 1;
}

