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

#ifndef TILES_H
#define TILES_H

/****************
Tile Definitions
*****************
Non-Blocking Tiles (0 - 499)
Blocking Tiles (500 - 1000)

******************
Naming Convention
******************
C  - Corner
R  - Right
L  - Left
T  - Top
B  - Bottom
TR - Top Right
TL - Top Left
BR - Bottom Right
BL - Bottom Left

OPN - Open
CLD - Closed

EMP - EMPTY
DUN - Dungeon
WAT - Water
GRA - Grass
SNO - Snow
RED - Red Carpet
TRE - Treasure Chest

*****************/

#define BLOCKING 500
/*
Non-Blocking Tiles (0 - 499)
*/

#define DUN_TILE_NUM 0

#define GRA_TILE_NUM 1
#define SNO_TILE_NUM 2
#define RED_TILE_NUM 3

#define DUN_WAT_R_TILE_NUM 11
#define DUN_WAT_L_TILE_NUM 12
#define DUN_WAT_T_TILE_NUM 13
#define DUN_WAT_B_TILE_NUM 14
#define DUN_WAT_TR_TILE_NUM 15
#define DUN_WAT_TL_TILE_NUM 16
#define DUN_WAT_BR_TILE_NUM 17
#define DUN_WAT_BL_TILE_NUM 18

#define DUN_TILE_LV1_NUM 101
#define DUN_TILE_LV2_NUM 102
#define DUN_TILE_LV3_NUM 103
// special for the tile that activates the boss
#define BOS_TILE_NUM 166 // 666

/*
Blocking Tiles (500 - 1000)
*/
#define EMP_TILE_NUM 500

#define DUN_EMP_R_TILE_NUM 501
#define DUN_EMP_L_TILE_NUM 502
#define DUN_EMP_T_TILE_NUM 503
#define DUN_EMP_B_TILE_NUM 504
#define DUN_EMP_TR_TILE_NUM 505
#define DUN_EMP_TL_TILE_NUM 506
#define DUN_EMP_BR_TILE_NUM 507
#define DUN_EMP_BL_TILE_NUM 508

#define WAT_TILE_NUM 510

#define TRE_CLD_TILE_NUM 520
#define TRE_OPN_TILE_NUM 521


#endif
