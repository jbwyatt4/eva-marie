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

#ifndef INPUT_H
#define INPUT_H

/*
  This is the header file for input.c, which handles the user input of the game.
*/

#include "structs.h"

int showCredits;
extern void drawCredits();

extern Input input;
extern Map samplemap;

extern int dontDisplayMap;
extern int titleHighlighter;
extern int battleHighlighter;
extern int menuHighlighter;
extern int showTitleScreen;
extern int showBattleScreen;
extern int inventoryActivated;
extern int battleInventoryActivated;

//int getBattleInput();
extern int didAttack;


extern int showGenieScreen;
extern int genieHighlighter;
extern int charInventoryHighlighter;
extern int battleInventoryHighlighter;
extern int showGameOverScreen;		//decides if the game ends, character death
extern int showGameVictoryScreen;	//decides if game victory after stewies death

extern Entity player;			//need to be initialized in title screen
extern GenieStore genieStore;
extern Inventory charInventory;		//need to be initialized

//Sound Stuff
extern Mix_Music *music;

// threading
extern SDL_sem *shopLock;
extern unsigned int threadingAlready; // we use to make sure only ONE thread is running
extern unsigned int shopLocked;
extern unsigned int shopInvRestocking;
extern unsigned int lastOpenShop;
extern unsigned int lastChangedInv;

//other stuff:

extern int playerDamageTaken;
extern int enemyDamageTaken;

extern int batMsgDisplay;
extern int animationManager;

extern int showVictoryScreen;
extern int battleEnded;
extern int beatFinalBoss;

extern void resetGame();

#endif
