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

#include "collision.h"
/**
Checks if the movement of an entity is valid. Entity cannot walk on blocking tiles.
All tiles 200 and above are blocking
*/

void checkToMap(Entity *e)
{
	int i, x1, x2, y1, y2;

	// Test the horizontal movement first
	i = e->h > TILE_SIZE ? TILE_SIZE : e->h; // if e->h > TILE_SIZE, then TileSize is set to i, else e->h is set to i

	for (;;)
	{
		x1 = (e->x + e->dirX) / TILE_SIZE;
		x2 = (e->x + e->dirX + e->w - 1) / TILE_SIZE;
	
		y1 = (e->y) / TILE_SIZE;
		y2 = (e->y + i - 1) / TILE_SIZE;
		
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (e->dirX > 0)
			{
				// Trying to move right
		
				if ((samplemap.tile[y1][x2] >= BLOCKING) || (samplemap.tile[y2][x2] >= BLOCKING))
				{
					// Place the player as close to the solid tile as possible
					// we have a slight issue with this due to the clipping of our tiles
					e->x = x2 * TILE_SIZE;
					e->x -= e->w + 1;
					e->dirX = 0;
					checkForTreasureChest(y1, x2);
				}
			}
		
			else if (e->dirX < 0)
			{
				// Trying to move left
				if ((samplemap.tile[y1][x1] >= BLOCKING) || (samplemap.tile[y2][x1] >= BLOCKING))
				{
					// Place the player as close to the solid tile as possible
					e->x = (x1 + 1) * TILE_SIZE;
					e->dirX = 0;
					checkForTreasureChest(y1, x1);
				}
			}
		}
		
		// Exit this loop if we have tested all of the body 
		if (i == e->h)
		{
			break;
		}
		
		// Test the next few pieces of code
		
		i += TILE_SIZE;
		
		if (i > e->h)
		{
			i = e->h;
		}
	}

	// Test the vertical movement 
	
	i = e->w > TILE_SIZE ? TILE_SIZE : e->w; // if e->h > TILE_SIZE, then TileSize is set to i, else e->h is set to i
	
	for (;;)
	{
		x1 = (e->x) / TILE_SIZE;
		x2 = (e->x + i) / TILE_SIZE;
	
		y1 = (e->y + e->dirY) / TILE_SIZE;
		y2 = (e->y + e->dirY + e->h) / TILE_SIZE;
		
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (e->dirY > 0)
			{
				// Trying to move down 
				
				if ((samplemap.tile[y2][x1] >= BLOCKING) || (samplemap.tile[y2][x2] >= BLOCKING))
				{
					// Place the player as close to the solid tile as possible
					
					e->y = y2 * TILE_SIZE;
					e->y -= e->h;
					e->dirY = 0;
					checkForTreasureChest(y2, x1);
				}
			}
		
			else if (e->dirY < 0)
			{
				// Trying to move up 
		
				if ((samplemap.tile[y1][x1] >= BLOCKING) || (samplemap.tile[y1][x2] >= BLOCKING))
				{
					// Place the player as close to the solid tile as possible
					e->y = (y1 + 1) * TILE_SIZE;
					e->dirY = 0;
					checkForTreasureChest(y1, x1);
				}
			}
		}
		
		if (i == e->w)
		{
			break;
		}
		
		i += TILE_SIZE;
		
		if (i > e->w)
		{
			i = e->w;
		}
	}

	// Apply the movement

	e->x += e->dirX;
	e->y += e->dirY;

	// Check for bounds in all four directions
	if (e->x < 0)
	{
		e->x = 0;
	}
	else if (e->x + e->w >= samplemap.maxX)
	{
		e->x = samplemap.maxX - e->w - 1;
	}
	
	if (e->y < 0)
	{
		e->y = 0;
	}
	else if (e->y + e->h >= samplemap.maxY)
	{
		e->y = samplemap.maxY - e->h - 1;
	}
}


/**
Checks if we collided with a treasure chest and opens it and gives us items!
*/
void checkForTreasureChest(int y, int x){
	if((checkTreasureChestData(x ,y) == 1) && (samplemap.tile[y][x] == TRE_CLD_TILE_NUM)) {
		addTreasureChestData(x , y);
		openATreasureChest();
	}
}
