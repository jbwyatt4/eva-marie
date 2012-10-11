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

#include "draw.h"

/**
draw.c is the source file that handles the drawing of the map
*/

/**
draws stewie on the map
*/
void drawBoss() {
	drawImage(stewie.sprite, stewie.x - samplemap.startX, stewie.y - samplemap.startY);
}

/**
main draw code
*/
void draw()
{
	if(showTitleScreen == 1){

		if (showCredits == 1) {
			drawCredits();
		} else {

			drawTitleScreen();
		}
	}
	

	else if(showBattleScreen == 1){
		
		if(battleInventoryActivated == 1){
			drawBattleInventoryScreen();		
		}
		else{	
			if(showGameOverScreen == 1){
				drawGameOver();
			}
			
			else if(showVictoryScreen != 1){
				drawBattle(battleState);
			}
			else{
				drawVictory();
				
			}
			
		}
	}

	else if(dontDisplayMap == 0){ // for the menu
		
		// Draw the map
		drawMap();

		// Draw the player
		drawPlayer();

		// draw the boss
		drawBoss();
	}

	else{
		if(inventoryActivated == 0 && showGenieScreen == 0){
			drawMenu();
		}
		else if(inventoryActivated == 1 && showGenieScreen == 0){
			drawInventoryScreen();
		}
		else if(inventoryActivated == 0 && showGenieScreen == 1){
			// lock the shop
			SDL_SemWait(shopLock);

			// draw the shop
			drawGenie();

			// as you leave the shop, set and unlock the shop
			shopLocked = 1;
			lastOpenShop = SDL_GetTicks(); // gets the time
			SDL_SemPost(shopLock);
		}
		//drawTitleScreen();
	}

	// Swap the buffers

	SDL_Flip(screen);
	
	// Sleep briefly
	
	SDL_Delay(1);
}

/**
this is a copy of the draw function but for the battle screen instead
*/
void drawBattle(int monsterType) {
	
	//showBattleScreen = 1;
	SDL_FillRect(screen, NULL, 0);

	// Draw the background
	drawImage(battleDungeonImage, 0, 0);

	//Draw some texts:
	if(battleHighlighter == 0){
		drawHighlightedString("Attack", 630, 10, displayer.smallfont, 0, 0);
	} else {
		drawString("Attack", 630, 10, displayer.smallfont, 0, 0);
	}

	if(battleHighlighter == 1){
		drawHighlightedString("Guard", 630, 60, displayer.smallfont, 0, 0);
	}
	else {
		drawString("Guard", 630, 60, displayer.smallfont, 0, 0);
	}

	if(battleHighlighter == 2) {
		drawHighlightedString("Items", 630, 110, displayer.smallfont, 0, 0);
	}
	else {
		drawString("Items", 630, 110, displayer.smallfont, 0, 0);
	}

	if(battleHighlighter == 3) {
		drawHighlightedString("Run", 630, 160, displayer.smallfont, 0, 0);
	}
	else {
		drawString("Run", 630, 160, displayer.smallfont, 0, 0);
	}

	// Draw battle status
	//drawString("CurHP:", 610, 300, displayer.smallfont, 0, 0);
	drawString("HP:", 610, 320, displayer.smallfont, 0, 0);
	drawString("lvl:", 610, 340, displayer.smallfont, 0, 0);
	drawString("Exp:", 610, 360, displayer.smallfont, 0, 0);
	
	sprintf(curhp, "%d", player.stats.currentHp);
	drawString(curhp, 660, 320, displayer.smallfont, 0, 0);
	
	sprintf(curlvl, "%d", player.stats.level);
	drawString(curlvl, 660, 340, displayer.smallfont, 0, 0);

	sprintf(curexp, "%d", player.stats.exp);
	drawString(curexp, 660, 360, displayer.smallfont, 0, 0);

	

	// Draw the characters
	//// draw monster
	if(monsterType == lv1GoopNum) {
		drawImage(lv1Goop.battleSprite, 100, 130);
	}
	else if (monsterType == lv2LizardNum) {
		drawImage(lv2Lizard.battleSprite, 100, 130);
	}
	else if (monsterType == lv3MultiNum) {
		drawImage(lv3Multi.battleSprite, 100, 130);
	} 
	else if (monsterType == bossNum) {
		drawImage(stewie.battleSprite, 180, 240);
	}
	//// draw hero
	drawImage(player.battleSprite, 400, 210);
	// Draw the special effects

	// Draw the messages and corresponding animations:
	switch(batMsgDisplay){
		
		/*
			-Messaging system uses case.
			-cases 0 to 1 is when player attacks first. In case 0, player attack animation is executed, and damage to enemy is displayed
			-If enemy is still alive, we move onto case 1. Case 1 is where enemy attack animation is executed, and damage is displayed.

			-case 2 is when player uses item or defends. Only enemy attack animation and damage is displayed

			-cases 3 to 4 is when enemy attacks first. Similar concept to cases 1 and 2, except enemy moves first
		
		
		*/
		
		//case 0 - 1: player goes first
		case 0:
			if(animationManager != 0) {	
				drawAttacks(2);
			}
			atkcounter++;
			
			if(batMsgDisplay == 0){
				sprintf(dmgdisp1, "-%d", enemyDamageTaken);
				drawString(dmgdisp1, 100, 90, displayer.font, 0, 0);	
			}			
			
			if(animationManager == 0){
				didAttack = 0;
				atkcounter = 0;
				SDL_Delay(100);
				animationManager = 1;
				if(battleEnded != 1){
					batMsgDisplay = 1;
				}
				else{
					battleEnded = 0;
					showVictoryScreen = 1;				
				}
			}
			
		break;
		
			
		case 1:
	
			if(animationManager != 0) {	
				drawAttacks(1);
			}
			atkcounter++;
			
			if(batMsgDisplay == 1){
				sprintf(dmgdisp2, "-%d", playerDamageTaken);
				drawString(dmgdisp2, 400, 170, displayer.font, 0, 0);	
			}			
			
			if(animationManager == 0){
				didAttack = 0;
				atkcounter = 0;
				SDL_Delay(100);
				if(defeated != 1){
					batMsgDisplay = -1;
				}
				else{
					defeated = 0;
					showGameOverScreen = 1;
				}
			}
		
		break;
		
		//case 2: player guards, or uses item:
		case 2:
			if(animationManager != 0) {	
				drawAttacks(1);
			}
			atkcounter++;
			
			if(batMsgDisplay == 2){
				sprintf(dmgdisp2, "-%d", playerDamageTaken);
				drawString(dmgdisp2, 400, 170, displayer.font, 0, 0);	
			}			
			
			if(animationManager == 0){
				didAttack = 0;
				atkcounter = 0;
				SDL_Delay(100);
				if(defeated != 1){
					batMsgDisplay = -1;
				}
				else{
					defeated = 0;
					showGameOverScreen = 1;
				}
			}
                break;

		//case 3-4: player attacks, enemy goes first:
		case 3:
			if(animationManager != 0) {	
				drawAttacks(1);
			} atkcounter++;
			
			if(batMsgDisplay == 3){
				sprintf(dmgdisp2, "-%d", playerDamageTaken);
				drawString(dmgdisp2, 400, 170, displayer.font, 0, 0);	
			}			
			
			if(animationManager == 0){
				didAttack = 0;
				atkcounter = 0;
				SDL_Delay(100);
				
				if(defeated != 1){
					animationManager = 1;
					batMsgDisplay = 4;
				}
				else{
					defeated = 0;
					showGameOverScreen = 1;
				}
			}
		break;

		case 4:
			if(animationManager != 0) {	
				drawAttacks(2);
			}
			atkcounter++;
			
			if(batMsgDisplay == 4){
				sprintf(dmgdisp1, "-%d", enemyDamageTaken);
				drawString(dmgdisp1, 100, 90, displayer.font, 0, 0);	
			}			
			
			if(animationManager == 0){
				didAttack = 0;
				atkcounter = 0;
				SDL_Delay(100);
				if(battleEnded != 1){
					batMsgDisplay = -1;
				}
				else{
					battleEnded = 0;
					showVictoryScreen = 1;
				}
			}

		break;


		default:
		break;
	}
	
	//// menu

	//// bottem display message
	
	// Swap the buffers

	SDL_Flip(screen);
	
	// Sleep briefly
	
	SDL_Delay(1);
}

/**
draws menu

please use only in the draw function
*/
void drawMenu(){

	char text[10];
	
	// Blank the screen
	
	SDL_FillRect(screen, NULL, 0);
	
	// Draw some text
	
	drawString("Menu", 100, 10, displayer.font, 1, 0);
	
	if(menuHighlighter == 0) {
		drawHighlightedString("Items", 10, 100, displayer.font, 0, 0);
	} else {
		drawString("Items", 10, 100, displayer.font, 0, 0);
	}
	if(menuHighlighter == 1){
		drawHighlightedString("Genie", 10, 200, displayer.font, 0, 0);
	}
	else{
		drawString("Genie", 10, 200, displayer.font, 0, 0);
	}
	if(menuHighlighter == 2){
		drawHighlightedString("Exit", 10, 300, displayer.font, 0, 0);
	}
	else{
		drawString("Exit", 10, 300, displayer.font, 0, 0);
	}

	drawString("STATS", 500, 100, displayer.font, 0, 0);
	drawString("LVL:", 500, 150, displayer.smallfont, 0, 0);
	drawString("EXP:", 500, 200, displayer.smallfont, 0, 0);
	drawString("ATK:", 500, 250, displayer.smallfont, 0, 0);
	drawString("DEF:", 500, 300, displayer.smallfont, 0, 0);
	drawString("SPD:", 500, 350, displayer.smallfont, 0, 0);
	drawString("cHP:", 500, 400, displayer.smallfont, 0, 0);
	drawString("mHP:", 500, 450, displayer.smallfont, 0, 0);
	drawString("GOLD:", 500, 500, displayer.smallfont, 0, 0);

	// draw current level	
	sprintf(curlvl, "%d", player.stats.level);
	drawString(curlvl, 600, 150, displayer.smallfont, 0, 0);

	sprintf(curexp, "%d", player.stats.exp);
	drawString(curexp, 600, 200, displayer.smallfont, 0, 0);

	sprintf(curatk, "%d", player.stats.attack);
	drawString(curatk, 600, 250, displayer.smallfont, 0, 0);

	sprintf(curdef, "%d", player.stats.defense);
	drawString(curdef, 600, 300, displayer.smallfont, 0, 0);

	sprintf(curspd, "%d", player.stats.speed);
	drawString(curspd, 600, 350, displayer.smallfont, 0, 0);	

	sprintf(curhp, "%d", player.stats.currentHp);
	drawString(curhp, 600, 400, displayer.smallfont, 0, 0);
	
	sprintf(maxhp, "%d", player.stats.maxHp);
	drawString(maxhp, 600, 450, displayer.smallfont, 0, 0);
	
	sprintf(gold, "%d", charInventory.goldAmt);
	drawString(gold, 600, 500, displayer.smallfont, 0, 0);
	
	// Update the buffer

	SDL_Flip(screen);
	
	// Sleep briefly
	
	SDL_Delay(1);
}

/**
draws title screen

please only use in draw functions
*/
void drawTitleScreen(){
	
	char text[10];
	
	// Blank the screen
	
	SDL_FillRect(screen, NULL, 0);
	
	// Draw some text
	
	drawString("THE GAME", 100, 10, displayer.font, 1, 0);
	
	if(titleHighlighter == 0){
		drawHighlightedString("Start Shreading", 100, 400, displayer.smallfont, 1, 0);
	} else {
		drawString("Start Shreading", 100, 400, displayer.smallfont, 1, 0);
	}

	if(titleHighlighter == 1){
		drawHighlightedString("Continue Shreading", 100, 450, displayer.smallfont, 1, 0);
	}
	else {
		drawString("Continue Shreading", 100, 450, displayer.smallfont, 1, 0);
	}

	if(titleHighlighter == 2) {
		drawHighlightedString("Credits", 100, 500, displayer.smallfont, 1, 0);
	}
	else {
		drawString("Credits", 100, 500, displayer.smallfont, 1, 0);
	}

	if(titleHighlighter == 3) {
		drawHighlightedString("Quit Shreading", 100, 550, displayer.smallfont, 1, 0);
	}
	else {
		drawString("Quit Shreading", 100, 550, displayer.smallfont, 1, 0);
	}

	// Codename
	drawString("Codename: Eva-marie", 20, 80, displayer.smallfont, 1, 0);
	drawString("Version 1.0", 40, 120, displayer.smallfont, 1, 0);
	drawString("Under the GNU GPL v3", 40, 160, displayer.smallfont, 1, 0);

	// Update the buffer
	SDL_Flip(screen);
	
	// Sleep briefly
	SDL_Delay(1);	

}

/**
credits screen

please use only in credits screen
*/
void drawCredits() {
	SDL_FillRect(screen, NULL, 0);

	drawString("John B Wyatt IV", 40 , 80, displayer.smallfont, 1, 0);
	drawString("Project lead, project designer, inital art, code maintainer, ", 40 , 120, displayer.smallfont, 1, 0);
	drawString("random encounter code, char file I/O, threading, monster logic", 80, 160, displayer.smallfont, 1, 0);
	drawString("Kemuel P Clemente",40, 200, displayer.smallfont, 1, 0);
	drawString("Internal codes, animation, menus, battles, etc.",40, 240, displayer.smallfont, 1, 0);
	drawString("Rishi Asthana", 40 , 280, displayer.smallfont, 1, 0);
	drawString("collision, character file I/O, treasure chest code, battle animation ", 40 , 320, displayer.smallfont, 1, 0);
	drawString("Trevor W Robinson", 40 , 360, displayer.smallfont, 1, 0);
	drawString("Graphic design, audio creation and code additions", 40 , 400, displayer.smallfont, 1, 0);
	drawString("Press enter to continue", 200, 480, displayer.smallfont, 1, 0);
	//drawString("", displayer.smallfont, 1, 0);
}

/**
this function draws the battle inventory screen and the stats of the character
*/
void drawBattleInventoryScreen(){
	SDL_FillRect(screen, NULL, 0);

	drawString("INVENTORY", 100, 10, displayer.font, 1, 0);
	drawString("Type", 10, 100, displayer.font, 0, 0);
	drawString("Quantity", 500, 100, displayer.font, 0, 0);

	if(battleInventoryHighlighter == 0) {
		drawHighlightedString("Potion 1", 10, 200, displayer.font, 0, 0);
	}else {
		drawString("Potion 1", 10, 200, displayer.font, 0, 0);
	}	
	if(battleInventoryHighlighter == 1) {
		drawHighlightedString("Potion 2", 10, 250, displayer.font, 0, 0);
	}else {
		drawString("Potion 2", 10, 250, displayer.font, 0, 0);
	}
	if(battleInventoryHighlighter == 2){
		drawHighlightedString("Potion 3", 10, 300, displayer.font, 0, 0);
	}else {
		drawString("Potion 3", 10, 300, displayer.font, 0, 0);
	}
	if(battleInventoryHighlighter == 3){
		drawHighlightedString("Potion 4", 10, 350, displayer.font, 0, 0);
	}else {
		drawString("Potion 4", 10, 350, displayer.font, 0, 0);
	}
	if(battleInventoryHighlighter == 4){
		drawHighlightedString("EXIT", 10, 400, displayer.font, 0, 0);
	}else {
		drawString("EXIT", 10, 400, displayer.font, 0, 0);
	}
	
	sprintf(potOne, "%d", charInventory.inventoryList[0]);
	drawString(potOne, 550, 200, displayer.font, 0, 0);
	sprintf(potTwo, "%d", charInventory.inventoryList[1]);
	drawString(potTwo, 550, 250, displayer.font, 0, 0);
	sprintf(potThree, "%d", charInventory.inventoryList[2]);
	drawString(potThree, 550, 300, displayer.font, 0, 0);
	sprintf(potFour, "%d", charInventory.inventoryList[3]);
	drawString(potFour, 550, 350, displayer.font, 0, 0);
}
/**
this function draws the inventory screen and the stats of the character
*/
void drawInventoryScreen(){

	// Blank the screen
	SDL_FillRect(screen, NULL, 0);	
	drawString("INVENTORY", 100, 10, displayer.font, 1, 0);	
	drawString("Type", 10, 100, displayer.font, 0, 0);
	drawString("Quantity", 150, 100, displayer.font, 0, 0);
	drawString("Type", 410, 100, displayer.font, 0, 0);
	drawString("Quantity", 550, 100, displayer.font, 0, 0);

	if(charInventoryHighlighter == 0) {
		drawHighlightedString("Potion 1", 10, 200, displayer.smallfont, 0, 0);
	}else {
		drawString("Potion 1", 10, 200, displayer.smallfont, 0, 0);
	}	
	if(charInventoryHighlighter == 1) {
		drawHighlightedString("Potion 2", 10, 250, displayer.smallfont, 0, 0);
	}else {
		drawString("Potion 2", 10, 250, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 2){
		drawHighlightedString("Potion 3", 10, 300, displayer.smallfont, 0, 0);
	}else {
		drawString("Potion 3", 10, 300, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 3){
		drawHighlightedString("Potion 4", 10, 350, displayer.smallfont, 0, 0);
	}else {
		drawString("Potion 4", 10, 350, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 4){
		drawHighlightedString("Sword 1", 10, 400, displayer.smallfont, 0, 0);
	}else {
		drawString("Sword 1", 10, 400, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 5){
		drawHighlightedString("Sword 2", 10, 450, displayer.smallfont, 0, 0);
	}else {
		drawString("Sword 2", 10, 450, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 6){
		drawHighlightedString("Sword 3", 420, 200, displayer.smallfont, 0, 0);
	}else {
		drawString("Sword 3", 420, 200, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 7){
		drawHighlightedString("Sword 4", 420, 250, displayer.smallfont, 0, 0);
	}else {
		drawString("Sword 4", 420, 250, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 8){
		drawHighlightedString("Armor 1", 420, 300, displayer.smallfont, 0, 0);
	}else {
		drawString("Armor 1", 420, 300, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 9){
		drawHighlightedString("Armor 2", 420, 350, displayer.smallfont, 0, 0);
	}else {
		drawString("Armor 2", 420, 350, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 10){
		drawHighlightedString("Armor 3", 420, 400, displayer.smallfont, 0, 0);
	}else {
		drawString("Armor 3", 420, 400, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 11){
		drawHighlightedString("Armor 4", 420, 450, displayer.smallfont, 0, 0);
	}else {
		drawString("Armor 4", 420, 450, displayer.smallfont, 0, 0);
	}
	if(charInventoryHighlighter == 12){
		drawHighlightedString("EXIT", 300, 500, displayer.font, 1, 0);
	}else {
		drawString("EXIT", 300, 500, displayer.font, 1, 0);
	}
	
	sprintf(potOneI, "%d", charInventory.inventoryList[0]);
	drawString(potOneI, 200, 200, displayer.smallfont, 0, 0);

	sprintf(potTwoI, "%d",charInventory.inventoryList[1]);
	drawString(potTwoI, 200, 250, displayer.smallfont, 0, 0);

	sprintf(potThreeI, "%d", charInventory.inventoryList[2]);
	drawString(potThreeI, 200, 300, displayer.smallfont, 0, 0);

	sprintf(potFourI, "%d", charInventory.inventoryList[3]);
	drawString(potFourI, 200, 350, displayer.smallfont, 0, 0);

	sprintf(swordOneI, "%d", charInventory.inventoryList[4]);
	drawString(swordOneI, 200, 400, displayer.smallfont, 0, 0);	

	sprintf(swordTwoI, "%d", charInventory.inventoryList[5]);
	drawString(swordTwoI, 200, 450, displayer.smallfont, 0, 0);

	sprintf(swordThreeI, "%d", charInventory.inventoryList[6]);
	drawString(swordThreeI, 600, 200, displayer.smallfont, 0, 0);
	
	sprintf(swordFourI, "%d", charInventory.inventoryList[7]);
	drawString(swordFourI, 600, 250, displayer.smallfont, 0, 0);

	sprintf(armorOneI, "%d", charInventory.inventoryList[8]);
	drawString(armorOneI, 600, 300, displayer.smallfont, 0, 0);

	sprintf(armorTwoI, "%d", charInventory.inventoryList[9]);
	drawString(armorTwoI, 600, 350, displayer.smallfont, 0, 0);

	sprintf(armorThreeI, "%d", charInventory.inventoryList[10]);
	drawString(armorThreeI, 600, 400, displayer.smallfont, 0, 0);

	sprintf(armorFourI, "%d", charInventory.inventoryList[11]);
	drawString(armorFourI, 600, 450, displayer.smallfont, 0, 0);	


}

/**
the delay function slows down the game
so it does not consume all the free CPU time
(a problem in old dos games)
*/
void delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}
	
	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}
	
	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}

/**
draws the individual battle animation (the slashes)
*/
void drawAttacks(int attacker){
	
	if(attacker == 1){
		doAnimation(&slashOne);
		drawAnimation(&slashOne, 400, 210);
		SDL_Delay(10);
	}

	else if(attacker == 2){
		doAnimation(&slashTwo);
		drawAnimation(&slashTwo, 100, 130);
		SDL_Delay(10);
	}

}

/**
draws the genie menu screen
*/
void drawGenie(){
	
	SDL_FillRect(screen, NULL, 0);

	drawString("Shop of the Genie of Time", 100, 10, displayer.font, 1, 0);
	drawString("Type", 10, 100, displayer.font, 0, 0);
	drawString("Price", 300, 100, displayer.font, 0, 0);
	drawString("Quantity", 500, 100, displayer.font, 0, 0);

	if(genieHighlighter == 0) {
		drawHighlightedString("Potion 1", 10, 200, displayer.font, 0, 0);
	}else {
		drawString("Potion 1", 10, 200, displayer.font, 0, 0);
	}	
	if(genieHighlighter == 1) {
		drawHighlightedString("Potion 2", 10, 250, displayer.font, 0, 0);
	}else {
		drawString("Potion 2", 10, 250, displayer.font, 0, 0);
	}
	if(genieHighlighter == 2){
		drawHighlightedString("Potion 3", 10, 300, displayer.font, 0, 0);
	}else {
		drawString("Potion 3", 10, 300, displayer.font, 0, 0);
	}
	if(genieHighlighter == 3){
		drawHighlightedString("Potion 4", 10, 350, displayer.font, 0, 0);
	}else {
		drawString("Potion 4", 10, 350, displayer.font, 0, 0);
	}
	if(genieHighlighter == 4){
		drawHighlightedString("EXIT", 10, 400, displayer.font, 0, 0);
	}else {
		drawString("EXIT", 10, 400, displayer.font, 0, 0);
	}
	
	drawString("25", 330, 200, displayer.font, 0, 0);
	drawString("50", 330, 250, displayer.font, 0, 0);
	drawString("75", 330, 300, displayer.font, 0, 0);
	drawString("100", 330, 350, displayer.font, 0, 0);
	
	sprintf(potOne, "%d", genieStore.minorPotion);
	drawString(potOne, 550, 200, displayer.font, 0, 0);
	sprintf(potTwo, "%d", genieStore.lesserPotion);
	drawString(potTwo, 550, 250, displayer.font, 0, 0);
	sprintf(potThree, "%d", genieStore.greaterPotion);
	drawString(potThree, 550, 300, displayer.font, 0, 0);
	sprintf(potFour, "%d", genieStore.superPotion);
	drawString(potFour, 550, 350, displayer.font, 0, 0);	
}

/**
Draws the screen when you die
*/
void drawGameOver(){
	SDL_FillRect(screen, NULL, 0);
	drawString("You have been Shreaded. Game Over.", 100, 10, displayer.font, 1, 1);
}

/**
draws victory screen for when a battle is won
*/
void drawVictory(){
	
	SDL_FillRect(screen, NULL, 0);
	
	// if you kill a random monster
	if(beatFinalBoss != 1){
		drawString("VICTORY!", 100, 10 ,displayer.font, 1, 0);
		drawString("Exp:", 10, 200, displayer.font, 0, 0);
		drawString(expGained, 150, 200, displayer.font, 0, 0);
		drawString("Gold:", 10, 250, displayer.font, 0, 0);
		drawString(goldGained, 150, 250, displayer.font, 0, 0);
	}
	// if you kill the boss
	else{
		drawHighlightedString("CONGRATULATIONS !!!", 100, 10, displayer.font, 1, 0);
		drawHighlightedString("You have shreaded the unshreadable,", 100, 100, displayer.smallfont, 1, 0);
		drawHighlightedString("and have proved the justice of our culture!", 100, 150, displayer.smallfont, 1, 0);
		drawHighlightedString("Now go and rest, our hero!", 100, 200, displayer.smallfont, 1, 0);
		
		
	}

}
