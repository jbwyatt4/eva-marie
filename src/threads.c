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

#include "threads.h"

/**********
Shopkeeper Overview
one timer to check when items and gold has been changed (10 minutes)
- resets items and gold back to default levels

second timer to check when player last opened the genie (2-5 minutes)
***********/

/****************
SDL Threading
------------
thread = SDL_CreateThread( my_thread(), NULL );
my_thread() is a function to call which contains the contents of the thread

SDL_KillThread( thread );
manually kills the thread

****************/

/**
in this function we initalize a thread and a semaphone, and set it to protect the shopkeeper varaibles

*/
int threadInit() {
	if(threadingAlready == 1) {
		printf("threadInit: SEVERE ERROR, thread init called twice\n");
		return 1;
	}
	threadingAlready = 1;
	// SUPER IMPORTANT!!!!!!!!!!!!!!!!! use threadRun and NOT threadRun(), it makes it do weird stuff
	thread = SDL_CreateThread( threadRun, NULL );

	shopLock = SDL_CreateSemaphore( 1 );
	return 0;
}

/**
The purpose of this thread is to count time
two goals: one we count from the time the genie's window was closed
and we count from the last time the inventory was changed... I may just consider the last time the window was closed
if it was not already counting down
*/
int threadRun() {
	shopLocked = 0;
	shopInvRestocking = 0;
	while(1) {
		// unlocked the shop
		if(shopLocked == 1 && SDL_GetTicks() - lastOpenShop >= timeOpenShop) {
			// lock the semaphone
			SDL_SemWait(shopLock);

			shopLocked = 0;

			// unlock the semaphone
			SDL_SemPost(shopLock);
			
		}
		// restock the inventory
		if(shopInvRestocking == 1 && SDL_GetTicks() - lastChangedInv >= timeRestockInv) {
			// lock the semaphone
			SDL_SemWait(shopLock);

			setDefaultGenieStock();
			shopInvRestocking = 0;
			

			// unlock the semaphone
			SDL_SemPost(shopLock);
		}
		//printf("threading\n");
		SDL_Delay(2500);
	}
	return 0;
}

/**
kills the thread
*/
void threadCleanup() {
	// kill the thread
	if(thread != NULL) {
		SDL_KillThread(thread);
		thread = NULL;
	}
	threadingAlready = 0; // we leave the memory clean!
	// kill the semaphone
	if(shopLock != NULL) {
		SDL_DestroySemaphore( shopLock);
		shopLock = NULL;
	}
}
