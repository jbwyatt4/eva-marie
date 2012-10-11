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

#include "init.h"

/**
Initalization function for the game engine.
Initalizes random number generator and SDL

Error Codes
0 - a_ok
1 - SDL_Init Error
2 - SDL Set Video Mode Error
3 - SDL_ttf True Type Library Error

the error codes were never used :-(
*/
void init(char *title)
{
	// Random Number generation
	// random number seed, needed every time we use random numbers
	srand( time(NULL));

	// set default store stock
	setDefaultGenieStock();

	// initalize the threads
	if( threadInit() == 1) {
		exit(4);
	}

	// Initialise SDL Video

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		
		exit(1);
	}
	
	// Open a 640 x 480 screen. SDL_HWPALETTE tells computer to use video memory instead of software memory
	screen = SDL_SetVideoMode(800, 600, 0, SDL_HWPALETTE | SDL_DOUBLEBUF);	//The SDL_DOUBLEBUF flag tells SDL to use double buffering
										//when displaying moving images!
	
	if (screen == NULL)
	{
		printf("Couldn't set screen mode to 800 x 600: %s\n", SDL_GetError());

		exit(2);
	}
	
	// Set the screen title
	
	SDL_WM_SetCaption(title, NULL);

	// Initalize the font library
	if(TTF_Init() == -1) {
		printf("SDL Initalization Error\nTTF_Init: %s", TTF_GetError());
		exit(3);
	}

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
	{
		printf("SDL Initialization Error\nMixer Failure: %s\n", Mix_GetError());
		exit(4);
	}
 
}

/**
reset game
*/
void resetGame() {
	// genie
	setDefaultGenieStock();
	// stats
	initializePlayerStats(); // maybe duplicate
	// inventory
	initializeInventory();
	// position
	loadEntityPos("data/charPositionData.dat", &player, &stewie);
}

/**
ALL SDL surfaces must be freed after they have been used! Only exception is the surface used to create the SDL window.
That one is freed by SDL_Quit()!
*/
void cleanup()
{
	// Kill the thread
	threadCleanup();

	// Free the tiles and background image
	if (DUN_TILE != NULL){
		SDL_FreeSurface(DUN_TILE);
	}
	if (WAT_TILE != NULL){
		SDL_FreeSurface(WAT_TILE);
	}
	if (GRA_TILE != NULL){
		SDL_FreeSurface(GRA_TILE);
	}
	if (SNO_TILE != NULL){
		SDL_FreeSurface(SNO_TILE);
	}
	if (RED_TILE != NULL){
		SDL_FreeSurface(RED_TILE);
	}
	if (DUN_WAT_R_TILE != NULL){
		SDL_FreeSurface(DUN_WAT_R_TILE);
	}
	if (DUN_WAT_L_TILE != NULL){
		SDL_FreeSurface(DUN_WAT_L_TILE);
	}
	if (DUN_WAT_T_TILE != NULL){
		SDL_FreeSurface(DUN_WAT_T_TILE);
	}
	if (DUN_WAT_B_TILE != NULL){
		SDL_FreeSurface(DUN_WAT_B_TILE);
	}
	if (DUN_WAT_TR_TILE != NULL){
		SDL_FreeSurface(DUN_WAT_TR_TILE);
	}
	if (DUN_WAT_TL_TILE != NULL){
		SDL_FreeSurface(DUN_WAT_TL_TILE);
	}
	if (DUN_WAT_BR_TILE != NULL){
		SDL_FreeSurface(DUN_WAT_BR_TILE);
	}
	if (DUN_WAT_BL_TILE != NULL){
		SDL_FreeSurface(DUN_WAT_BL_TILE);
	}
	if (DUN_EMP_R_TILE != NULL){
		SDL_FreeSurface(DUN_EMP_R_TILE);
	}
	if (DUN_EMP_L_TILE != NULL){
		SDL_FreeSurface(DUN_EMP_L_TILE);
	}
	/*if (DUN_EMP_B_TILE != NULL){
		SDL_FreeSurface(DUN_EMP_B_TILE);
	}*/
	if (DUN_EMP_T_TILE != NULL){
		SDL_FreeSurface(DUN_EMP_T_TILE);
	}
	if (DUN_EMP_TR_TILE != NULL){
		SDL_FreeSurface(DUN_EMP_TR_TILE);
	}
	if (DUN_EMP_TL_TILE != NULL){
		SDL_FreeSurface(DUN_EMP_TL_TILE);
	}
	/*if (DUN_EMP_BR_TILE != NULL){
		SDL_FreeSurface(DUN_EMP_BR_TILE);
	}
	if (DUN_EMP_BL_TILE != NULL){
		SDL_FreeSurface(DUN_EMP_BL_TILE);
	}*/
	if (TRE_OPN_TILE != NULL){
		SDL_FreeSurface(TRE_OPN_TILE);
	}
	if (TRE_CLD_TILE != NULL){
		SDL_FreeSurface(TRE_CLD_TILE);
	}
	
	if (stewie.sprite != NULL){
		SDL_FreeSurface(stewie.sprite);
	}
	if (backgroundImage != NULL){
		SDL_FreeSurface(backgroundImage);
	}

	// Shut down the font library
	TTF_Quit();

	//free animation:
	freeAnimation(&playerAnimUp);
	freeAnimation(&playerAnimDown);
	freeAnimation(&playerAnimLeft);
	freeAnimation(&playerAnimRight);
	freeAnimation(&slashOne);
	freeAnimation(&slashTwo);

	free(potOne);
	free(potTwo);
	free(potThree);
	free(potFour);

	free(baseatk); 
	free(curatk);
	free(basedef);
	free(curdef);
	free(basespd);
	free(curspd);
	free(maxhp);
	free(curhp);
	free(curexp);
	free(curlvl);
	free(gold);

	free(dmgdisp1);
	free(dmgdisp2);
	
 	free(potOneI);
	free(potTwoI);
	free(potThreeI);
	free(potFourI);
 	free(swordOneI);
 	free(swordTwoI); 
	free(swordThreeI); 
	free(swordFourI);
 	free(armorOneI);
	free(armorTwoI);
	free(armorThreeI);
	free(armorFourI);
	
	//Free the sound effects
	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}

	//Quit SDL_mixer
	Mix_CloseAudio(); 

	// Shut down SDL
	SDL_Quit();
}
