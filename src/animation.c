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

#include "animation.h"

/**
This function takes two parameters: the animation file to load and the address of the animation structure we wish to use.
This basically converts all our frames into SDL Surfaces using loadImage, and then loads all those converted frames into
the SDL_Surface array in an Animation struct.
*/
void loadAnimation(char *name, Animation *anim)
{
	// Load up the data file that describes the animation
	
	int i;
	FILE *fp = fopen(name, "rb");
	char frameName[100]; // please make sure this is large enough
	
	// exit if file for animation was not found
	if (fp == NULL)
	{
		printf("Failed to load animation file %s\n", name);
		
		exit(1);
	}
	
	// Read the frame count from the animation data file's first line into the frameCount variable of an Animation struct.
	
	fscanf(fp, "%d", &anim->frameCount);
	
	// For the array of SDL Surfaces in the Animation struct-> Allocate space for the animation
	// exit if there was a failure to allocate memory for the SDL struct
	
	anim->frame = (SDL_Surface **)malloc(anim->frameCount * sizeof(SDL_Surface *));
	
	if (anim->frame == NULL)
	{
		printf("Ran out of memory when creating the animation for %s\n", name);
		
		exit(1);
	}
	
	// Now load up each frame using the loadImage function from graphics.c 
	// Read the image locations by using fscanf on the animations data file
	
	for (i=0;i < anim->frameCount ;i++)
	{
		fscanf(fp, "%s", frameName);
		
		anim->frame[i] = loadImage(frameName);
		
		if (anim->frame[i] == NULL)
		{
			printf("Failed to load animation frame %s\n", frameName);
			
			exit(1);
		}
	}
	
	// Set the initial frame index to 0. That is the starting position for our animations.
	
	anim -> frameIndex = 0;
	
	// Set the animation counter
	
	anim -> counter = ANIM_SPEED;
}


/**
Like the name says, this frees up all the frames used in our animations after we are done with them.
*/
void freeAnimation(Animation *anim)
{
    int i;
    
    // Loop through each of the frames and free it

    if (anim->frame != NULL)
    {
        for (i=0; i < anim->frameCount ;i++)
        {
            if (anim->frame[i] != NULL)
            {
                SDL_FreeSurface(anim->frame[i]);
            }
        }
        
        free(anim->frame);
    }
}

/**
Now this function is what does the actual animations, after the frames are all loaded up and such.
This basically updates the frames in animation (by progressing through the array of frames)
*/
void doAnimation(Animation *anim)
{

    anim->counter--;			//use counter to do a countdown before we update the frame. Counter's value is adjustable.
    
    if (anim->counter <= 0)		//once counter reaches zero or less, then that's when we update the frame into a new one.
    {
        anim->frameIndex++;
        
        if (anim->frameIndex == anim->frameCount)	//set the frameIndex back to zero if it's already equal to frameCount, so animation...
        {						//...can start all over again
            anim->frameIndex = 0;
	    animationManager = 0;
        }
        
        anim->counter = ANIM_SPEED;			//then reset counter back to ANIM_SPEED, so it can do countdown again.
    }

}

/**
Uses drawImage to draw the Animation
*/
void drawAnimation(Animation *anim, int x, int y)
{
    drawImage(anim->frame[anim->frameIndex], x, y);
}


