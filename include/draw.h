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

#ifndef DRAW_H
#define DRAW_H

#include "structs.h"

extern SDL_Surface *screen;
extern textDisplay displayer;
extern int dontDisplayMap;
extern int showTitleScreen;
extern int showBattleScreen;
extern int titleHighlighter;
extern int battleHighlighter;
extern int menuHighlighter;
extern int battleState;
extern int inventoryActivated;
extern int battleInventoryActivated;
extern Animation slashOne;
extern Animation slashTwo;
extern int didAttack;
extern int atkcounter;
extern int showVictoryScreen;
extern Map samplemap;			//samplemap needed to align the player on the screen

extern int showGenieScreen;
extern int genieHighlighter;
extern int charInventoryHighlighter;
extern int battleInventoryHighlighter;
extern int showGameOverScreen;		//decides if the game ends, character death
extern int showGameVictoryScreen;	//decides if game victory after stewies death
extern int showCredits;

extern int playerDamageTaken;
extern int enemyDamageTaken;

extern Entity player;			
extern GenieStore genieStore;
extern Inventory charInventory;		//need to be initialized

// draw functions
void drawBoss();
void drawCredits();
void drawCredits();

// battle state functions
void drawBattle(int );
void drawAttacks(int );
void drawGenie();

//for displaying character's stats and whatnot:
extern char *baseatk;
extern char *curatk;
extern char *basedef;
extern char *curdef;
extern char *basespd;
extern char *curspd;
extern char *maxhp;
extern char *curhp;
extern char *curexp;
extern char *curlvl;
extern char *gold;

extern char *dmgdisp1;
extern char *dmgdisp2;

extern char *potOne, *potTwo, *potThree, *potFour;
extern char *potOneI, *potTwoI, *potThreeI, *potFourI;
extern char *swordOneI, *swordTwoI, *swordThreeI, *swordFourI;
extern char *armorOneI, *armorTwoI, *armorThreeI, *armorFourI;
extern char *expGained, *goldGained;


extern int batMsgDisplay;
extern int animationManager;
extern int battleEnded;
extern int defeated;
extern int beatFinalBoss;

extern int showGameOverScreen;		//decides if the game ends, character death
extern int showGameVictoryScreen;	//decides if game victory after stewies death

// threads
extern SDL_sem *shopLock;
extern unsigned int threadingAlready; // we use to make sure only ONE thread is running
extern unsigned int shopLocked;
extern unsigned int shopInvRestocking;
extern unsigned int lastOpenShop;
extern unsigned int lastChangedInv;


extern SDL_Surface *battleDungeonImage;

extern void drawPlayer(void);
extern void drawMap(void); // map.c
extern void drawHighlightedString(char *, int , int , TTF_Font *, int , int );
extern void drawString(char *, int , int , TTF_Font *, int , int );
void drawMenu();
void drawTitleScreen();
void drawBattleInventoryScreen();
void drawInventoryScreen();
void drawVictory();
void drawGameOver();

#endif
