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

#include "font.h"

/*
load a font
please call close font on exit
*/
TTF_Font *loadFont(char *name, int size) {
	// Use SDL_TTF to load the font at the specified size
	// size is the specified 'height' of the font
	TTF_Font *font = TTF_OpenFont(name, size);

	if(!font) {
		printf("loadFont: failed to open font %s: %s\n",
		name, TTF_GetError());
		exit(1);
	}
	return font;
}

/*
close a font
clean up memory
*/
void closeFont(TTF_Font * font) {
	// Close the font once we're done with it
	if(font != NULL) {
		TTF_CloseFont(font);
	}
}

/*
To actually draw the function on the screen
*/
void drawString(char *text, int x, int y, TTF_Font *font, int centerX, int centerY){

	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Color foregroundColor, backgroundColor;

	// White text on a black background
	foregroundColor.r = 255;
	foregroundColor.g = 255;
	foregroundColor.b = 255;

	backgroundColor.r = 0;
	backgroundColor.g = 0;
	backgroundColor.b = 0;

	// Use SDL_TTF to generate a string image, this returns an SDL_Surface
	surface = TTF_RenderUTF8_Shaded(font, text, foregroundColor, backgroundColor);

	if (surface == NULL) {
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());
		return;
	}

	// Blit the entire surface to the surface
	dest.x = (centerX == 1 ? (screen->w - surface->w) / 2 : x);
	dest.y = (centerY == 1 ? (screen->h - surface->h) / 2 : y);
	dest.w = surface->w;
	dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, screen, &dest);

	// Free the generated string image
	SDL_FreeSurface(surface);
}

void drawHighlightedString(char *text, int x, int y, TTF_Font *font, int centerX, int centerY){

	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Color foregroundColor, backgroundColor;

	// White text on a black background
	foregroundColor.r = 255;
	foregroundColor.g = 215;
	foregroundColor.b = 0;

	backgroundColor.r = 0;
	backgroundColor.g = 0;
	backgroundColor.b = 0;

	// Use SDL_TTF to generate a string image, this returns an SDL_Surface
	surface = TTF_RenderUTF8_Shaded(font, text, foregroundColor, backgroundColor);

	if (surface == NULL) {
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());
		return;
	}

	// Blit the entire surface to the surface
	dest.x = (centerX == 1 ? (screen->w - surface->w) / 2 : x);
	dest.y = (centerY == 1 ? (screen->h - surface->h) / 2 : y);
	dest.w = surface->w;
	dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, screen, &dest);

	// Free the generated string image
	SDL_FreeSurface(surface);
}
