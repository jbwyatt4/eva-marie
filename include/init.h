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

#ifndef INIT_H
#define INIT_H

/*
   This is the header file for init.c, the file that contains all
   the video-related stuff.
*/
#include "structs.h"

void resetGame();

extern SDL_Surface *screen;
extern SDL_Surface *DUN_TILE, *WAT_TILE, *GRA_TILE, *SNO_TILE, *RED_TILE;
extern SDL_Surface *DUN_WAT_R_TILE, *DUN_WAT_L_TILE, *DUN_WAT_T_TILE, *DUN_WAT_B_TILE;
extern SDL_Surface *DUN_WAT_TR_TILE, *DUN_WAT_TL_TILE, *DUN_WAT_BR_TILE, *DUN_WAT_BL_TILE;
extern SDL_Surface *DUN_EMP_R_TILE, *DUN_EMP_L_TILE, *DUN_EMP_T_TILE, *DUN_EMP_B_TILE;
extern SDL_Surface *DUN_EMP_TR_TILE, *DUN_EMP_TL_TILE, *DUN_EMP_BR_TILE, *DUN_EMP_BL_TILE;
extern SDL_Surface *TRE_OPN_TILE, *TRE_CLD_TILE;

extern SDL_Surface *battleDungeonImage, *backgroundImage;
extern Animation playerAnimUp, playerAnimDown, playerAnimLeft, playerAnimRight;
extern Animation slashOne, slashTwo;

extern char *potOne, *potTwo, *potThree, *potFour;
//Sound Stuff
extern Mix_Music *music;

// battle stats
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
//for displaying inventory quantities
extern char *potOneI, *potTwoI, *potThreeI, *potFourI;
extern char *swordOneI, *swordTwoI, *swordThreeI, *swordFourI;
extern char *armorOneI, *armorTwoI, *armorThreeI, *armorFourI;

extern void freeAnimation(Animation *);
extern void initializePlayerStats();
extern void initTreasureChestData();

#endif
