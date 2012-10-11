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

#ifndef MAIN_H
#define MAIN_H

#include "structs.h"

//SDL surfaces are used for various video/graphics-related stuff? I dunno...
SDL_Surface *screen;

SDL_Surface *DUN_TILE, *WAT_TILE, *GRA_TILE, *SNO_TILE, *RED_TILE;
SDL_Surface *DUN_WAT_R_TILE, *DUN_WAT_L_TILE, *DUN_WAT_T_TILE, *DUN_WAT_B_TILE;
SDL_Surface *DUN_WAT_TR_TILE, *DUN_WAT_TL_TILE, *DUN_WAT_BR_TILE, *DUN_WAT_BL_TILE;
SDL_Surface *DUN_EMP_R_TILE, *DUN_EMP_L_TILE, *DUN_EMP_T_TILE, *DUN_EMP_B_TILE;
SDL_Surface *DUN_EMP_TR_TILE, *DUN_EMP_TL_TILE, *DUN_EMP_BR_TILE, *DUN_EMP_BL_TILE;
SDL_Surface *TRE_OPN_TILE, *TRE_CLD_TILE;

SDL_Surface *SLASH_A1, *SLASH_A2, *SLASH_A3, *SLASH_B1, *SLASH_B2, *SLASH_B3;

SDL_Surface *battleDungeonImage, *backgroundImage;
Map samplemap;
Input input;
Sprites sprite[MAXIMUMSPRITE];

//Declare Animation structs here.
Animation playerAnimUp;
Animation playerAnimDown;
Animation playerAnimLeft;
Animation playerAnimRight;
Animation slashOne;
Animation slashTwo;

int directionDetermine = -1;
int lastFacing = -1;

//for text display
textDisplay displayer;
int dontDisplayMap = 0;
int menuHighlighter = 0;
int inventoryActivated = 0;
int battleInventoryActivated = 0;
int showVictoryScreen= 0;

int showTitleScreen = 1;
int titleHighlighter = 0;		//ranges from 0 to 3. 0 = Start Shreading, 1 = Continue, 2 = credits, 3 = quit

int showBattleScreen = 0;
int battleHighlighter = 0;		//ranges from 0 to 3. 0 = attack, 1 = guard, 2 = items, 3 = run
int battleState = 0;

int didAttack = 0;
int atkcounter = 0;

int showGenieScreen = 0;
int genieHighlighter = 0;
int charInventoryHighlighter = 0;
int battleInventoryHighlighter = 0;

int showGameOverScreen = 0;		//decides if the game ends, character death
int showGameVictoryScreen = 0;		//decides if game victory after stewies death

//for displaying the character's stats and whatnot:
char *baseatk; 
char *curatk;
char *basedef;
char *curdef;
char *basespd;
char *curspd;
char *maxhp;
char *curhp;
char *curexp;
char *curlvl;
char *gold;

char *dmgdisp1;
char *dmgdisp2;

//battle message display:
int batMsgDisplay = -1;
char *expGained;
char *goldGained;

//for displaying genie shop quantities and whatnot:
char *potOne, *potTwo, *potThree, *potFour;
//for displaying inventory quantities and whatnot:
char *potOneI, *potTwoI, *potThreeI, *potFourI;
char *swordOneI, *swordTwoI, *swordThreeI, *swordFourI;
char *armorOneI, *armorTwoI, *armorThreeI, *armorFourI;

//Holds treasure chest data
int treasureChestData[NUM_TREASURE_CHESTS][2];

//holds the damage taken:
int playerDamageTaken;
int enemyDamageTaken;

//Sound Stuff
extern Mix_Music *music;

//some useful stuff:
int animationManager = 1;
int battleEnded = 0;
int defeated = 0;
int beatFinalBoss = 0;

// externs

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern SDL_Surface *loadImage(char *);	//This function's in graphics.c
extern void updateScreen(void);
extern void draw(void);
extern void delay(unsigned int);
extern void loadMap(char *);
extern void loadAllSprites(void);
extern void doPlayer(void);
extern void initPlayer(void);
extern void loadAnimation(char *, Animation *);
extern void doAnimation(Animation *);
extern TTF_Font *loadFont(char *, int);
extern void drawString(char *,int , int , TTF_Font *, int , int );


#endif
