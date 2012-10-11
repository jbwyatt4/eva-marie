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

#include "graphics.h"

SDL_Surface *loadImage(char *name)
{
	// Load the image using SDL Image
	
	SDL_Surface *temp = IMG_Load(name);	//IMG_load allows us to load JPGs and PNGs
	SDL_Surface *image;
	
	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);
		
		return NULL;
	}
	
/* Make the background transparent. Makes one of the colours in the image transparent. This function takes 3 arguments. The first is the image to process, the second is a flag: SDL_SRCCOLORKEY makes the 3rd argument the transparent pixel in the source image of the blit. SDL_RLEACCEL improves blitting performance, which is desirable. The third argument is the color of the pixel to make transparent, we use SDL_MapRGB for this */

/*SDL_MapRGB takes 4 arguments, the surface's pixel format and the RGB values of the colour desired. The function then returns the pixel value of the desired colour. Finally, we need to convert the loaded image to the current display's format. This is important because otherwise SDL will need to perform this conversion every time we attempt to blit the image to the screen, and this will consume a lot of CPU power and slow down our program. The function call SDL_DisplayFormat takes care of this:*/
	
	// THIS IS ONLY IF YOUR IMAGE DOESNT HAVE A TRANSPARENT BACKGROUND!

	//SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format,0, 0, 0));
	
	// Convert the image to the screen's native format
	
	image = SDL_DisplayFormat(temp);

	// Free the unconverted surface

	SDL_FreeSurface(temp);	
	
	if (image == NULL)
	{
		printf("Failed to convert image %s to native format\n", name);
		
		return NULL;
	}
	
	// Return the processed image
	
	return image;
}

/**
The second function, drawImage is used to render an SDL_Surface to the screen. Use SDL_Rect to do so.
*/
void drawImage(SDL_Surface *image, int x, int y)
{	
	/*The SDL_Rect contains 4 variables, x, y, w (width) and h (height). We set the width and height of the rectangle 
	to the width and height of the surface to be rendered and the x and y to the values passed into the function.*/
	SDL_Rect dest;
	
	// Set the blitting rectangle to the size of the src image
	dest.x = x;
	dest.y = y;
	dest.w = image->w;
	dest.h = image->h;
	
	// Blit the entire image onto the screen at coordinates x and y
	/*
		image = image to be displayed
		NULL = tells SDL to show whole image
		screen = the target surface. In this case, we target the computer screen.
		&dest = area of the target surface to render to, as specified by the values stored in the SDL_Rect. 
	*/
	
	SDL_BlitSurface(image, NULL, screen, &dest);
}

/**
for animation

loads each image into the array of sprites 
*/
void loadSprite(int index, char * name){

	// Load the image into the next slot in the sprite array
	
	if (index >= MAXIMUMSPRITE || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAXIMUMSPRITE);
		
		exit(1);
	}
	
	sprite[index].image = loadImage(name);
	
	if (sprite[index].image == NULL)
	{
		exit(1);
	}

}

/**
gets the specified sprite from the Sprite array for an entity.
*/
SDL_Surface *getSprite( int index){

	if (index >= MAXIMUMSPRITE || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAXIMUMSPRITE);
		
		exit(1);
	}
	
	return sprite[index].image;

}

/**
Self explanatory; frees up sprites.
*/
void freeSprites()
{
	int i;
	
	// Loop through the sprite bank and clear the images
	for (i=0;i<MAXIMUMSPRITE;i++) {
		if (sprite[i].image != NULL) {
			SDL_FreeSurface(sprite[i].image);
		}
	}
}

/**
load up all of the sprites that we will use in the program. Add more sprites as needed here:
*/
void loadAllSprites()
{
	loadSprite(PLAYERSPRITE, "data/world/player/playerDown.gif");
	loadSprite(PLAYERDOWNWALK, "data/world/player/playerDownWalk1.gif");
	loadSprite(PLAYERUP, "data/world/player/playerUp.gif");
	loadSprite(PLAYERUPWALK, "data/world/player/playerUpWalk1.gif");
	loadSprite(PLAYERRIGHT, "data/world/player/playerRight.gif");
	loadSprite(PLAYERRIGHTWALK, "data/world/player/playerRightWalk.gif");
	loadSprite(PLAYERLEFT, "data/world/player/playerLeft.gif");
	loadSprite(PLAYERLEFTWALK, "data/world/player/playerLeftWalk.gif");
}

/**
clears the screen
refills the image buffer for draw to use
*/
void updateScreen()
{
	// Blank the screen
	
	SDL_FillRect(screen, NULL, 0);
	
	// Swap the image buffers
	
	SDL_Flip(screen);
	
	SDL_Delay(1);
}
