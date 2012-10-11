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

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "draw.h"

// file load and save
int loadEntityPos(char * charPosFileLoc, Entity* hero, Entity* boss);

extern Map samplemap;
extern int treasureChestData[NUM_TREASURE_CHESTS][2];
extern Inventory charInventory;
extern Stats playerStats;
extern int showBattleScreen;
extern int battleState;
extern Animation slashOne;
extern Animation slashTwo;

int intMonsters();
int loadCharData(char * );
int saveCharData(char * );
int randomBattleCheck(int );
//int enterBattleState(int );
int queryMap(int , int );
int setDefaultGenieStock(); // called at game start
void playerKilled();
void endBattle(int monsterType, int ranAway);

extern Entity lv1Goop;
extern Entity lv2Lizard;
extern Entity lv3Multi;

extern Entity player;
extern Entity stewie;

extern int playerDamageTaken;
extern int enemyDamageTaken;

extern int didAttack;
extern int batMsgDisplay;

extern char *expGained, *goldGained;

extern int showVictoryScreen;
extern int battleEnded;
extern int defeated;
extern int showGameOverScreen;
extern int beatFinalBoss;

extern void doAnimation(Animation *);			//in animation.c
extern void drawAnimation(Animation *, int, int);	//in animation.c

extern Map samplemap;			//samplemap needed to align the player on the screen


#endif
