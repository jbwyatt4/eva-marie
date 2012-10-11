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

#include "player.h"

extern int loadSprite(char *);				//in graphics.c
extern void drawImage(SDL_Surface *, int, int);		//in graphics.c
extern SDL_Surface *getSprite(int);			//in graphics.c
extern void centerEntityOnMap(Entity *);		//in map.c
extern void checkTomap(Entity *);			//in collision.c
extern void loadAnimation(char *, Animation *);		//in animation.c
extern void doAnimation(Animation *);			//in animation.cl
extern void drawAnimation(Animation *, int, int);	//in animation.c
extern void drawString(char *,int , int , TTF_Font *, int , int );
extern void drawMenu();

/**
initializes player; puts player's coordinates at the center of the map
also sets stewie's position
*/
void initPlayer()
{ 
	player.sprite = getSprite(PLAYERSPRITE);
	
	loadEntityPos("data/charPositionData.dat", &player, &stewie);
	//player.x = SCREEN_WIDTH / 2;
	//player.y = SCREEN_HEIGHT / 2;
	player.w = player.sprite->w;
	player.h = player.sprite->h;
	player.dirX = 0;
	player.dirY = 0;
}

/**
Handles the movement for the player.
*/
void doPlayer()
{
	player.dirX = 0;
	player.dirY = 0;

	if (input.up == 1)
	{
		if(dontDisplayMap != 1 && showTitleScreen != 1){
			player.dirY -= PLAYER_SPEED;
			directionDetermine = 0;
			lastFacing = 0;
			randomBattleCheck( queryMap(player.x, player.y));
		}
	}
	
	if (input.down == 1)
	{
		if(dontDisplayMap != 1 && showTitleScreen != 1){
			player.dirY += PLAYER_SPEED;
			directionDetermine = 1;
			lastFacing = 1;
			randomBattleCheck( queryMap(player.x, player.y));
		}
	}
	
	if (input.left == 1)
	{
		if(dontDisplayMap != 1 && showTitleScreen != 1){
			player.dirX -= PLAYER_SPEED;
			directionDetermine = 2;
			lastFacing = 2;
			randomBattleCheck( queryMap(player.x, player.y));
		}
	}
	
	if (input.right == 1)
	{
		if(dontDisplayMap != 1 && showTitleScreen != 1){
			player.dirX += PLAYER_SPEED;
			directionDetermine = 3;
			lastFacing = 3;
			randomBattleCheck( queryMap(player.x, player.y));
		}
	}

	if (input.save == 1) {
		// call save function here!
		//printf("%d %d\n", player.x, player.y);
		saveCharData("char.dat");
		saveTreasureChestData("TreasureChest.dat");
	}
	
	if (input.load == 1) {
		// call load function here!
		loadCharData("char.dat");
		//printf("%d %d\n", player.x, player.y);
		//samplemap.startX = stewie.x;
		//samplemap.startY = stewie.y;
	}

	/*if (input.menu == 1){
		if(dontDisplayMap != 1)
			dontDisplayMap = 1;
		else
			dontDisplayMap = 0;	
	}*/
	
	checkToMap(&player);
	centerEntityOnMap(&player);
}

void drawPlayer()
{
	// Draw the image in the player structure, in specified coordinates

	if(directionDetermine == 0){
		doAnimation(&playerAnimUp);
		drawAnimation(&playerAnimUp, player.x - samplemap.startX, player.y - samplemap.startY);
		directionDetermine = -1;
		
	}
	else if(directionDetermine == 1){
		doAnimation(&playerAnimDown);
		drawAnimation(&playerAnimDown, player.x - samplemap.startX, player.y - samplemap.startY);
		directionDetermine = -1;
				
	}
	else if(directionDetermine ==2 ){
		doAnimation(&playerAnimLeft);
		drawAnimation(&playerAnimLeft, player.x - samplemap.startX, player.y - samplemap.startY);
		directionDetermine = -1;
		
		
	}
	else if(directionDetermine == 3){
		doAnimation(&playerAnimRight);
		drawAnimation(&playerAnimRight, player.x - samplemap.startX, player.y - samplemap.startY);
		directionDetermine = -1;
		
	}
	
	else{
		if(lastFacing == 1 || lastFacing == -1){ // -1 hasn't pressed anything yet
			player.sprite = getSprite(PLAYERSPRITE);
			drawImage(player.sprite, player.x - samplemap.startX, player.y - samplemap.startY);
		}
		else if(lastFacing == 0){
			player.sprite = getSprite(PLAYERUP);
			drawImage(player.sprite, player.x - samplemap.startX, player.y - samplemap.startY);
		}
		else if(lastFacing == 2){
			player.sprite = getSprite(PLAYERLEFT);
			drawImage(player.sprite, player.x - samplemap.startX, player.y - samplemap.startY);
		}
		else if(lastFacing == 3){
			player.sprite = getSprite(PLAYERRIGHT);
			drawImage(player.sprite, player.x - samplemap.startX, player.y - samplemap.startY);
		}
	}
}

