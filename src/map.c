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

#include "map.h"

/**
map.c handles reading the map from a data file (and converting the 0 and 1s to the proper tiles)
*/

/**
loadMap takes the filename of the map we wish to load. The data file is a very simple text file containing 0s and 1s to describe the map layout.

Right now:

A 0 denotes a floor tile and 1 denotes stewie. Note that we must include either a space or carriage return between the digits so that scanf treats them as individual numbers and not one large number. Once we have successfully opened the file, we read in the map data one row at a time, one column at time. Once we are done we close the file. This gives us a multidimensional array containing our map data

*/
void loadMap(char *name)
{
	int x, y;
	FILE *fp;

	fp = fopen(name, "rb");

	// If we can't open the map then exit
	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);

		exit(1);
	}

	// Read the data from the file into the map
	for (y=0;y<MAX_MAP_Y;y++)
	{
		for (x=0;x<MAX_MAP_X;x++)
		{
			fscanf(fp, "%d", &samplemap.tile[y][x]);
		}
	}

    	// Set the start coordinates
    	samplemap.startX = samplemap.startY = 0;
    
    	// Set the maximum scroll position of the map
    	samplemap.maxX = MAX_MAP_X * TILE_SIZE;
    	samplemap.maxY = MAX_MAP_Y * TILE_SIZE;

	// Close the file afterwards
	fclose(fp);
}


/**
Draws the map according to startX and startY
*/
void drawMap()
{
	// what does x, & y do; mapX, mapY? x1, x2, y1, y2?
    int x, y, mapX, x1, x2, mapY, y1, y2;

    mapX = samplemap.startX / TILE_SIZE;
    x1 = (samplemap.startX % TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    
    mapY = samplemap.startY / TILE_SIZE;
    y1 = (samplemap.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    
    // Draw the background
	
    drawImage(backgroundImage, 0, 0);

    // Draw the map starting at the startX and startY
    for (y=y1;y<y2;y+=TILE_SIZE)
    {
        mapX = samplemap.startX / TILE_SIZE;
        
        for (x=x1;x<x2;x+=TILE_SIZE)
        {
   	    	if (samplemap.tile[mapY][mapX] == DUN_TILE_NUM) {
                	drawImage(DUN_TILE, x, y);
            	}  
		if(samplemap.tile[mapY][mapX] == WAT_TILE_NUM) {
			drawImage(WAT_TILE, x, y);
	   	}  
		if(samplemap.tile[mapY][mapX] == GRA_TILE_NUM) {
			drawImage(GRA_TILE, x, y);
	   	}  
		if(samplemap.tile[mapY][mapX] == SNO_TILE_NUM) {
			drawImage(SNO_TILE, x, y);
	    	}
		if(samplemap.tile[mapY][mapX] == RED_TILE_NUM) {
		drawImage(RED_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_WAT_R_TILE_NUM) {
			drawImage(DUN_WAT_R_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_WAT_L_TILE_NUM) {
			drawImage(DUN_WAT_L_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_WAT_T_TILE_NUM) {
			drawImage(DUN_WAT_T_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_WAT_B_TILE_NUM) {
			drawImage(DUN_WAT_B_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_WAT_TR_TILE_NUM) {
			drawImage(DUN_WAT_TR_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_WAT_TL_TILE_NUM) {
			drawImage(DUN_WAT_TL_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_WAT_BR_TILE_NUM) {
			drawImage(DUN_WAT_BR_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_WAT_BL_TILE_NUM) {
			drawImage(DUN_WAT_BL_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_EMP_R_TILE_NUM) {
			drawImage(DUN_EMP_R_TILE, x, y);
	  	}  
		if(samplemap.tile[mapY][mapX] == DUN_EMP_L_TILE_NUM) {
			drawImage(DUN_EMP_L_TILE, x, y);
	   	}  
		if(samplemap.tile[mapY][mapX] == DUN_EMP_T_TILE_NUM) {
			drawImage(DUN_EMP_T_TILE, x, y);
	    	}
		/*  if(samplemap.tile[mapY][mapX] == DUN_EMP_B_TILE_NUM) {
			drawImage(DUN_EMP_B_TILE, x, y);
	    	}*/  
		if(samplemap.tile[mapY][mapX] == DUN_EMP_TR_TILE_NUM) {
			drawImage(DUN_EMP_TR_TILE, x, y);
	    	}  
		if(samplemap.tile[mapY][mapX] == DUN_EMP_TL_TILE_NUM) {
			drawImage(DUN_EMP_TL_TILE, x, y);
	    	}
		/*if(samplemap.tile[mapY][mapX] == DUN_EMP_BR_TILE_NUM) {
			drawImage(DUN_EMP_BR_TILE, x, y);
	    	} 
		if(samplemap.tile[mapY][mapX] == DUN_EMP_BL_TILE_NUM) {
			drawImage(DUN_EMP_BL_TILE, x, y);
	    	}*/  
		if(samplemap.tile[mapY][mapX] == DUN_TILE_LV1_NUM) {
			drawImage(DUN_TILE, x, y);
	    	}
		if(samplemap.tile[mapY][mapX] == DUN_TILE_LV2_NUM) {
			drawImage(DUN_TILE, x, y);
	    	}
		if(samplemap.tile[mapY][mapX] == DUN_TILE_LV3_NUM) {
			drawImage(DUN_TILE, x, y);
	    	}
		if(samplemap.tile[mapY][mapX] == TRE_CLD_TILE_NUM) {
			if(checkTreasureChestData(mapX, mapY) == 1){
				drawImage(TRE_CLD_TILE, x, y);		
			}else{
				drawImage(TRE_OPN_TILE, x, y);
			}
	    	}
            mapX++;
        }
        mapY++;
    }
}
        
 


/**
Displays the map according to Entities position.
i.e should always display entity in the center unless at the edge of the map
*/void centerEntityOnMap(Entity *e)
{
	samplemap.startX = e->x - (SCREEN_WIDTH / 2);
	// left bound check
	if (samplemap.startX < 0)
	{
		samplemap.startX = 0;
	}
	// right bound check
	else if (samplemap.startX + SCREEN_WIDTH >= samplemap.maxX)
	{
		samplemap.startX = samplemap.maxX - SCREEN_WIDTH;
	}
	
	samplemap.startY = e->y - (SCREEN_HEIGHT / 2);
	// up bound check
	if (samplemap.startY < 0)
	{
		samplemap.startY = 0;
	}
	// bottom bound check
	else if (samplemap.startY + SCREEN_HEIGHT >= samplemap.maxY)
	{
		samplemap.startY = samplemap.maxY - SCREEN_HEIGHT;
	}
}
