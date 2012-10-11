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

#ifndef THREADS_H
#define THREADS_H

#include "structs.h"

// constants -determine the time of our genie
const unsigned int timeOpenShop = 10000; // in UNIX time the time it will take for the genie window to open
const unsigned int timeRestockInv = 20000; // in UNIX time the time it will take to restock the inventory

// time for our shops
unsigned int lastOpenShop;
unsigned int lastChangedInv;

// SDL thread code
SDL_Thread *thread;
SDL_sem *shopLock;
unsigned int threadingAlready; // we use to make sure only ONE thread is running
//int threadExit;
unsigned int shopLocked;
unsigned int shopInvRestocking;

int threadInit();
int threadRun();
void threadCleanup();

extern int setDefaultGenieStock();
#endif
