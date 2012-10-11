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

#ifndef MAP_H
#define MAP_H
//map.h and map.c are what draws the tile map

#include "structs.h"

extern Map samplemap;

extern SDL_Surface *DUN_TILE, *WAT_TILE, *GRA_TILE, *SNO_TILE, *RED_TILE;
extern SDL_Surface *DUN_WAT_R_TILE, *DUN_WAT_L_TILE, *DUN_WAT_T_TILE, *DUN_WAT_B_TILE;
extern SDL_Surface *DUN_WAT_TR_TILE, *DUN_WAT_TL_TILE, *DUN_WAT_BR_TILE, *DUN_WAT_BL_TILE;
extern SDL_Surface *DUN_EMP_R_TILE, *DUN_EMP_L_TILE, *DUN_EMP_T_TILE, *DUN_EMP_B_TILE;
extern SDL_Surface *DUN_EMP_TR_TILE, *DUN_EMP_TL_TILE, *DUN_EMP_BR_TILE, *DUN_EMP_BL_TILE;
extern SDL_Surface *TRE_OPN_TILE, *TRE_CLD_TILE;

extern SDL_Surface *backgroundImage;
extern Input input;

extern void drawImage(SDL_Surface *, int, int);

#endif
