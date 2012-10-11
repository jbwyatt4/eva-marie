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

#include "input.h"

void getInput()
{
	SDL_Event event;
	
	// Loop through waiting messages and process them
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// Closing the Window or pressing Escape will exit the program 
			
			case SDL_QUIT:
				exit(0);
			break;
			/* pressing up, down, left, and right arrow keys scroll throught the map  
			 the SDLK stuff are built-in keywords corresponding to buttons 
			No more diagonal movement, only up down left right direction movement.
			When 2 or more direction keys are pressed, the first is registered.*/
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						// escape from inventory in world, or escape from genie store to inventory - dpesn't work
						if(dontDisplayMap == 1 && inventoryActivated == 1 ) {
							dontDisplayMap = 0;
							inventoryActivated = 0;
						// escape from inventory in battle
						} else if(inventoryActivated == 1) {
							inventoryActivated = 0;
						// escape from battle screen
						} else if(showBattleScreen == 1) {
							showBattleScreen = 0;
						} else {
							exit(0);
						}

					break;
					
					case SDLK_UP:

						if(showTitleScreen == 1 && titleHighlighter > 0) {
							titleHighlighter--;
						}
						else if(showBattleScreen == 1 && battleInventoryActivated == 0 && battleHighlighter > 0) {
							battleHighlighter--;
						}
						else if(showBattleScreen == 0 && dontDisplayMap == 1 && inventoryActivated == 0 && battleInventoryActivated == 0 && 								showGenieScreen == 0 && menuHighlighter > 0) {
							menuHighlighter--;
						}
						else if(showBattleScreen == 0 && dontDisplayMap == 1 && inventoryActivated == 0 && battleInventoryActivated == 0 && 								showGenieScreen == 1 && genieHighlighter > 0) {
							genieHighlighter--;
						}
						else if(showBattleScreen == 0 && dontDisplayMap == 1 && inventoryActivated == 1 && battleInventoryActivated == 0 && 								showGenieScreen == 0 && charInventoryHighlighter > 0){
							charInventoryHighlighter--;
						}
						else if(battleInventoryActivated == 1 && inventoryActivated == 0 && showGenieScreen == 0 && 								battleInventoryHighlighter > 0){
							battleInventoryHighlighter--;
						}
						else if(input.down == 0 && input.left == 0 && input.right == 0 && showBattleScreen == 0) {
							input.up = 1;
						}

					break;
					
					case SDLK_DOWN:

						if(showTitleScreen == 1 && titleHighlighter < 3) {
							titleHighlighter++;						
						}
						else if(showBattleScreen == 1 && inventoryActivated  == 0 && battleInventoryActivated == 0 && 								battleHighlighter < 3) {
							battleHighlighter++;
						}
						else if(showBattleScreen == 0 && dontDisplayMap == 1 && inventoryActivated == 0 && battleInventoryActivated == 0 && 								showGenieScreen == 0 && menuHighlighter < 2) {
							menuHighlighter++;
						}
						else if(showBattleScreen == 0 && dontDisplayMap == 1 && inventoryActivated == 0 && battleInventoryActivated == 0 && 								showGenieScreen == 1 && genieHighlighter < 4){
							genieHighlighter++;
						}
						else if(showBattleScreen == 0 && dontDisplayMap == 1 && inventoryActivated == 1 && battleInventoryActivated == 0 && 								showGenieScreen == 0 && charInventoryHighlighter < 12){
							charInventoryHighlighter++;
						}
						else if(battleInventoryActivated == 1 && inventoryActivated == 0 && showGenieScreen == 0 && 								battleInventoryHighlighter < 4){
							battleInventoryHighlighter++;
						}
						else if(input.up == 0 && input.left == 0 && input.right == 0 && showBattleScreen == 0){
							input.down = 1;
						}

						
					break;
					
					case SDLK_LEFT:
						if(showBattleScreen == 0 && showTitleScreen != 1 && input.down == 0 && input.up == 0 && input.right == 0){
							input.left = 1;
						}					
					break;
					
					case SDLK_RIGHT:
						if(showBattleScreen == 0 && showTitleScreen != 1 && input.down == 0 && input.left == 0 && input.up == 0){
							input.right = 1;
						}
					break;
		
					case SDLK_RETURN:
						//This gives functionality to "Start Sheading" option
						if(showTitleScreen == 1 && titleHighlighter == 0){
							resetGame();
							//initializePlayerStats();			// in game.c sets players base stats
							initTreasureChestData("TreasureChest.dat");	// initialized a new TreasureChest data file
							showTitleScreen = 0;
						}
						// continue title screen
						else if(showTitleScreen == 1 && titleHighlighter == 1){	
							loadCharData("char.dat");
							// loads previously saved TreasureChest data file into the game array
							loadTreasureChestData("TreasureChest.dat");	

							// this code resets the shopkeeper
							SDL_SemWait(shopLock);
							shopInvRestocking = 1;
							shopLocked = 1;
							lastOpenShop = SDL_GetTicks(); // gets the time
							lastChangedInv = SDL_GetTicks(); // for both

							SDL_SemPost(shopLock);
							// get out of title screen and goto world map
							showTitleScreen = 0;						
						}
						// credits
						else if(showTitleScreen == 1 && titleHighlighter == 2 && showCredits == 0) {
							//showTitleScreen = 0;
							showCredits = 1;
							//drawCredits();
						}					
						else if (showCredits == 1) {
							showCredits = 0;
							showTitleScreen = 1;
						}
						// exit title screen
						else if(showTitleScreen == 1 && titleHighlighter == 3){
							exit(0);			
						}
	

						//Menu functionalities:
						else if(dontDisplayMap == 1 && inventoryActivated == 0 && battleInventoryActivated == 0 && 								menuHighlighter == 0 && showGenieScreen == 0){
							inventoryActivated = 1;
						}
							// here we press enter on genie to enter the selection
						else if(dontDisplayMap == 1 && inventoryActivated == 0 && battleInventoryActivated == 0 && 								menuHighlighter == 1 && showGenieScreen == 0){
							// if the genie shop is locked don't enter
							if (shopLocked == 1) {
								
							} else {
								showGenieScreen = 1;
								menuHighlighter = 0;
							}
						} 
							//Adding exit to Menu
						else if (dontDisplayMap == 1 && inventoryActivated == 0 && battleInventoryActivated == 0 && 								menuHighlighter == 2 && showGenieScreen == 0){
							dontDisplayMap = 0;	
							menuHighlighter = 0;		
						}



						//battle functionalities:
						if(battleInventoryActivated == 0 && showBattleScreen == 1 && showGenieScreen == 0 && 								showVictoryScreen == 1){

							if(beatFinalBoss != 1){
								animationManager = 0;
								batMsgDisplay = -1;
								showBattleScreen = 0;
								showVictoryScreen = 0;
							}
							
							else{
								beatFinalBoss = 0;
								showVictoryScreen = 0;
								animationManager = 0;
								batMsgDisplay = -1;
								showBattleScreen = 0;
								showGameOverScreen = 0;
								resetGame();
								titleHighlighter = 0;
								showTitleScreen = 1;
							}
						}

						else if(battleInventoryActivated == 0 && showBattleScreen == 1 && showGenieScreen == 0 && 								showGameOverScreen == 1 && showVictoryScreen == 0){
							animationManager = 0;
							batMsgDisplay = -1;
							showBattleScreen = 0;
							showGameOverScreen = 0;
							resetGame();
							titleHighlighter = 0;
							showTitleScreen = 1;
						}
							
						else if(battleInventoryActivated == 0 && showBattleScreen == 1 && battleHighlighter == 0 && 								showGenieScreen == 0){
							//attack
							animationManager = 1;
							battleFlow(0);
						}
						else if(battleInventoryActivated == 0 && showBattleScreen == 1 && battleHighlighter == 1 && 								showGenieScreen == 0){
							//guard
							animationManager = 1;
							battleFlow(1);
							battleHighlighter = 0; //reset high lighter so it always points to attack first
						}
						else if(battleInventoryActivated == 0 && showBattleScreen == 1 && battleHighlighter == 2 && 								showGenieScreen == 0){
							battleInventoryActivated = 1;
							battleHighlighter = 0; //reset high lighter so it always points to attack first
						}
						else if(battleInventoryActivated == 0 && showBattleScreen == 1 && battleHighlighter == 3 && 								showGenieScreen == 0){	//run
							showBattleScreen = 0;					//100% chance to run
							battleHighlighter = 0;	//reset high lighter so it always points to attack first
						}

						//Char inventory functionalities
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 0 && 								showGenieScreen == 0){
							 useItem(0);	
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 1 && 								showGenieScreen == 0){
							 useItem(1);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 2 && 								showGenieScreen == 0){
							 useItem(2);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 3 && 								showGenieScreen == 0){
							 useItem(3);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 4 && 								showGenieScreen == 0){
							 useItem(4);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 5 && 								showGenieScreen == 0){
							 useItem(5);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 6 && 								showGenieScreen == 0){
							 useItem(6);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 7 && 								showGenieScreen == 0){
							 useItem(7);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 8 && 								showGenieScreen == 0){
							 useItem(8);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 9 && 								showGenieScreen == 0){
							 useItem(9);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 10 && 								showGenieScreen == 0){
							 useItem(10);
						}
						else if(inventoryActivated == 1 && battleInventoryActivated == 0 &&  charInventoryHighlighter == 11 && 								showGenieScreen == 0){
							 useItem(11);
						}						
						else if (inventoryActivated == 1 && battleInventoryActivated == 0 && charInventoryHighlighter == 12 && 								showGenieScreen == 0) {
							inventoryActivated = 0;	
							charInventoryHighlighter = 0;					
						}

						//genie shop functionalities
						else if(battleInventoryActivated == 0 && inventoryActivated == 0 && showGenieScreen == 1 && 								genieHighlighter == 0){
							 buyPotion(0);
						}
						else if(battleInventoryActivated == 0 && inventoryActivated == 0 && showGenieScreen == 1 && 								genieHighlighter == 1){
							 buyPotion(1);
						}
						else if(battleInventoryActivated == 0 && inventoryActivated == 0 && showGenieScreen == 1 && 								genieHighlighter == 2){
							buyPotion(2);
						}
						else if(battleInventoryActivated == 0 && inventoryActivated == 0 && showGenieScreen == 1 && 								genieHighlighter == 3){
							 buyPotion(3);
						}
						else if(battleInventoryActivated == 0 && inventoryActivated == 0 && showGenieScreen == 1 && 								genieHighlighter == 4){
							genieHighlighter = 0;
							showGenieScreen = 0;
						}

						//battle inventory functionalities
						else if(battleInventoryActivated == 1 && inventoryActivated == 0 && showGenieScreen == 0 && battleInventoryHighlighter == 0){
							 useItem(0);
						}
						else if(battleInventoryActivated == 1 && inventoryActivated == 0 && showGenieScreen == 0 && battleInventoryHighlighter == 1){
							useItem(1);;
						}
						else if(battleInventoryActivated == 1 && inventoryActivated == 0 && showGenieScreen == 0 && battleInventoryHighlighter == 2){
							useItem(2);
						}
						else if(battleInventoryActivated == 1 && inventoryActivated == 0 && showGenieScreen == 0 && battleInventoryHighlighter == 3){
							 useItem(3);
						}
						else if(battleInventoryActivated == 1 && inventoryActivated == 0 && showGenieScreen == 0 && battleInventoryHighlighter == 4){
							battleInventoryHighlighter = 0;
							battleInventoryActivated = 0;
						}
						

					break;
					
					case SDLK_s:
						input.save = 1;
					break;
					
					case SDLK_l:
						input.load = 1;
					break;

					// menu code
					case SDLK_m:
						input.menu = 1;
						/*if(dontDisplayMap != 1) {
							dontDisplayMap = 1;
						}
						else if(dontDisplayMap == 1 && inventoryActivated == 1) {
							inventoryActivated = 0;
						}
						else {
							dontDisplayMap = 0;
						}*/
						if(dontDisplayMap == 0) {
							dontDisplayMap = 1;
						}
					break;

					//If a was pressed:
					case SDLK_a:
						//If there is no music playing
						if( Mix_PlayingMusic() == 0 )
						{
							//Play the music
							if( Mix_PlayMusic( music, -1 ) == -1 )
							{
								printf("Playing Music");
							}
						} 
						else {
							//If the music is paused
							if( Mix_PausedMusic() == 1 )
							{
								//Resume the music
								Mix_ResumeMusic();
							}
							//If the music is playing
							else
							{
								//Pause the music
								Mix_PauseMusic();
							}
						} 

					default:
					break;
				}
			break;
			
			// case KEYUP is to determine if button isn't being pressed anymore (if it's "up")
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						input.up = 0;
					break;
					
					case SDLK_DOWN:
						input.down = 0;
					break;
					
					case SDLK_LEFT:
						input.left = 0;
					break;
					
					case SDLK_RIGHT:
						input.right = 0;
					break;

					case SDLK_s:
						//alreadySaved = 0;
						input.save = 0;
					break;
					
					case SDLK_l:
						//alreadyLoaded = 0;
						input.load = 0;
					break;

					case SDLK_m:
						input.menu = 0;
					
					default:
					break;
				}
			break;
		}
	}
}


/**
gets input for the battle menu screen
0 if no errors

int getBattleInput() {
	SDL_Event event;
	
	// Loop through waiting messages and process them 
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// Closing the Window or pressing Escape will exit the program 
			
			case SDL_QUIT:
				exit(0);
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						showBattleScreen = 0;
						game.battleData.exit = 1;
						return 0; // need to exit
					break;
					
					case SDLK_UP:
						if(showBattleScreen == 1 && battleHighlighter > 0){
							battleHighlighter--;
							printf("\nBattle highlighter up!\n");
						}
					break;
					
					case SDLK_DOWN:
						if(showBattleScreen == 1 && battleHighlighter < 0){
							battleHighlighter++;
							printf("\nBattle highlighter down!\n");
						}
					break;
					
					case SDLK_LEFT:
					break;
					
					case SDLK_RIGHT:
					break;
					

					default:
					break;
				}
			break;
			
			//case KEYUP is to determine if button isn't being pressed anymore (if it's "up")
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
					break;
					
					case SDLK_DOWN:
					break;
					
					case SDLK_LEFT:
					break;
					
					case SDLK_RIGHT:
					break;

					default:
					break;

				}
			break;
		}
	}

	return 0;
}
*/
