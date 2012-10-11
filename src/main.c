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
#include "main.h"

int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go;
	
	// Starts SDL
	
	init("Shreaders' Game: Under Development");
	
	// Call the cleanup function when the program exits 
	
	atexit(cleanup);
	
	go = 1;

	// load Characters
	stewie.sprite = loadImage("data/world/stewie_world.png");
	stewie.battleSprite = loadImage("data/battle/monsters/stewie.gif");
	player.battleSprite = loadImage("data/battle/norrisBattle.gif");
	
	// load Monsters
	lv1Goop.battleSprite = loadImage("data/battle/monsters/goopMonster.gif");
	lv2Lizard.battleSprite = loadImage("data/battle/monsters/lizardMonster.gif");
	lv3Multi.battleSprite = loadImage("data/battle/monsters/multiheadedBeast.gif");

	// Load tiles
	backgroundImage = loadImage("data/world/background.png");
	battleDungeonImage = loadImage("data/battle/dungeonFight.png");
	DUN_TILE = loadImage("data/world/DUN_TILE.png");
	WAT_TILE = loadImage("data/world/WAT_TILE.png");
	GRA_TILE = loadImage("data/world/GRA_TILE.png");
	SNO_TILE = loadImage("data/world/SNO_TILE.png");
	RED_TILE = loadImage("data/world/GRA_TILE.png");

	DUN_WAT_R_TILE = loadImage("data/world/DUN_WAT_R_TILE.png");
	DUN_WAT_L_TILE = loadImage("data/world/DUN_WAT_L_TILE.png");
	DUN_WAT_T_TILE = loadImage("data/world/DUN_WAT_T_TILE.png");
	DUN_WAT_B_TILE = loadImage("data/world/DUN_WAT_B_TILE.png");
	DUN_WAT_TR_TILE = loadImage("data/world/DUN_WAT_TR_TILE.png");
	DUN_WAT_TL_TILE = loadImage("data/world/DUN_WAT_TL_TILE.png");
	DUN_WAT_BR_TILE = loadImage("data/world/DUN_WAT_BR_TILE.png");
	DUN_WAT_BL_TILE = loadImage("data/world/DUN_WAT_BL_TILE.png");

	DUN_EMP_R_TILE = loadImage("data/world/DUN_EMP_R_TILE.png");
	DUN_EMP_L_TILE = loadImage("data/world/DUN_EMP_L_TILE.png");
	DUN_EMP_T_TILE = loadImage("data/world/DUN_EMP_T_TILE.png");
	//DUN_EMP_B_TILE = loadImage("data/world/DUN_EMP_B_TILE.png");
	DUN_EMP_TR_TILE = loadImage("data/world/DUN_EMP_TR_TILE.png");
	DUN_EMP_TL_TILE = loadImage("data/world/DUN_EMP_TL_TILE.png");
	//DUN_EMP_BR_TILE = loadImage("data/world/DUN_EMP_BR_TILE.png");
	//DUN_EMP_BL_TILE = loadImage("data/world/DUN_EMP_BL_TILE.png");

	TRE_OPN_TILE = loadImage("data/world/TRE_OPN_TILE.png");
	TRE_CLD_TILE = loadImage("data/world/TRE_CLD_TILE.png");

	//initialize some strings:
	baseatk = (char*)malloc(5 * sizeof(char)); 
	curatk= (char*)malloc(5 * sizeof(char));
	basedef= (char*)malloc(5 * sizeof(char));
	curdef= (char*)malloc(5 * sizeof(char));
	basespd= (char*)malloc(5 * sizeof(char));
	curspd= (char*)malloc(5 * sizeof(char));
	maxhp= (char*)malloc(5 * sizeof(char));
	curhp= (char*)malloc(5 * sizeof(char));
	curexp= (char*)malloc(5 * sizeof(char));
	curlvl= (char*)malloc(5 * sizeof(char));
	gold= (char*)malloc(5 * sizeof(char));

	dmgdisp1= (char*)malloc(5 * sizeof(char));
	dmgdisp2= (char*)malloc(5 * sizeof(char));
	
	potOne = (char*)malloc(5 * sizeof(char));
	potTwo = (char*)malloc(5 * sizeof(char));
	potThree = (char*)malloc(5 * sizeof(char));
	potFour = (char*)malloc(5 * sizeof(char));
	
 	potOneI = (char*)malloc(5 * sizeof(char));
	potTwoI = (char*)malloc(5 * sizeof(char));
	potThreeI = (char*)malloc(5 * sizeof(char));
	potFourI = (char*)malloc(5 * sizeof(char));
 	swordOneI = (char*)malloc(5 * sizeof(char));
 	swordTwoI = (char*)malloc(5 * sizeof(char)); 
	swordThreeI = (char*)malloc(5 * sizeof(char)); 
	swordFourI = (char*)malloc(5 * sizeof(char));
 	armorOneI = (char*)malloc(5 * sizeof(char));
	armorTwoI = (char*)malloc(5 * sizeof(char));
	armorThreeI = (char*)malloc(5 * sizeof(char));
	armorFourI = (char*)malloc(5 * sizeof(char));
	
	expGained = (char*)malloc(5 * sizeof(char));
	goldGained = (char*)malloc(5 * sizeof(char));

	// load map
	loadMap("data/maps/map01.dat");

	//load all sprites to be used:
	loadAllSprites();

	//load all animations to be used:
	loadAnimation("data/anim/playerdownanim.dat", &playerAnimDown);
	loadAnimation("data/anim/playerupanim.dat", &playerAnimUp);
	loadAnimation("data/anim/playerleftanim.dat", &playerAnimLeft);
	loadAnimation("data/anim/playerrightanim.dat", &playerAnimRight);
	// load slashes animation	
	loadAnimation("data/anim/slashone.dat", &slashOne);
	loadAnimation("data/anim/slashtwo.dat", &slashTwo);

	//load fonts:
	displayer.font = loadFont("data/font/blackWolf.ttf", 40);
	displayer.smallfont = loadFont("data/font/blackWolf.ttf", 20);
	
	//initialize player
	initPlayer();

	//load/play sounds
	//Load the music
	music = Mix_LoadMUS( "data/sounds/bg.wav" );
	
	//If there was a problem loading the music
	if(music == NULL)
	{
		printf("Main: Problem loading music: 'bg.wav'");
		exit(4);
	} 
	
	Mix_PlayMusic( music, -1 );
	
	// Loop indefinitely for game menu
	while (go == 1)
	{
		//This is for user input (aka controls). 
		getInput();

		//update player's position
		doPlayer();

		//Update the screen. Important for graphics, animations, and such.
		draw();
		
		// Sleep briefly to stop sucking up all the CPU time 
		SDL_Delay(16);
	}
	
	// Exit	
	exit(0);
}
