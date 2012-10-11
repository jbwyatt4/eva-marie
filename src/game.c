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

/**
this file holds the character save and load functions, game logic and other elements
*/

#include "game.h"

/**
Initalize monsters; resets the monsters each battle
*/
int intMonsters() {
	lv1Goop.stats.attack = 10;
	lv1Goop.stats.defense = 20;
	lv1Goop.stats.speed = 5;
	lv1Goop.stats.maxHp = 50;
	lv1Goop.stats.currentHp = 50;
	lv2Lizard.stats.attack = 70;
	lv2Lizard.stats.defense = 40;
	lv2Lizard.stats.speed = 50;
	lv2Lizard.stats.maxHp = 250;
	lv2Lizard.stats.currentHp = 250;
	lv3Multi.stats.attack = 240;
	lv3Multi.stats.defense = 140;
	lv3Multi.stats.speed = 70;
	lv3Multi.stats.maxHp = 1000;
	lv3Multi.stats.currentHp = 1000;
	stewie.stats.attack = 500;
	stewie.stats.defense = 50;
	stewie.stats.speed = 100;
	stewie.stats.maxHp = 500 + 200 * player.stats.level;
	stewie.stats.currentHp = stewie.stats.maxHp;
	return 0;
}

/**
Check Location of used Treasure Chest

0 if successful (x and y already exists i.e used treasure chest)
1 if not (x and y does not exist i.e unused treasure chest)

*/
int checkTreasureChestData(int x , int y) {
	int i;
	for (i = 0; i < NUM_TREASURE_CHESTS; i++){
		if(x == treasureChestData[i][0] && y == treasureChestData[i][1]){
			return 0;		
		}
	}
	return 1;
}

/**
Initialize player inventory set gold amount to 0 and inventory to 0. Initiazlized during new game!
*/
void initializeInventory(){
	int i;
	charInventory.goldAmt = 0;
	for(i = 0; i < CHAR_INVENTORY_SIZE; i++){
		charInventory.inventoryList[i] = 0;
	}
}

/**
Adds an item to the inventory
@param x takes in the position on the array, item type predefined in inventory.h
*/
void addItem(int x){
	charInventory.inventoryList[x]++;
}


/**
Adds Gold to the inventory
@param x is the amout of gold to be added
*/
void addGold(int x){
	if((charInventory.goldAmt + x) != 0){
		charInventory.goldAmt += x;
	}
}

/**
Buy a potion from the genie
subtracts from gold and adds the item to inventory
*/
void buyPotion(int x){
	if( x == 0 && charInventory.goldAmt >= 25 && genieStore.minorPotion > 0){
		addGold(-25);
		addItem(x);
		genieStore.minorPotion--;	
	}else if( x == 1 && charInventory.goldAmt >= 50 && genieStore.lesserPotion > 0){
		addGold(-50);
		addItem(x);
		genieStore.lesserPotion--;
	}else if( x == 2 && charInventory.goldAmt >= 75 && genieStore.greaterPotion > 0){
		addGold(-75);
		addItem(x);
		genieStore.greaterPotion--;
	}else if( x == 3 && charInventory.goldAmt >= 100 && genieStore.superPotion > 0){
		addGold(-100);
		addItem(x);
		genieStore.superPotion--;
	}

	// lock the genie store
	shopInvRestocking = 1;
	lastChangedInv = SDL_GetTicks();
}

/**
Get the amount of gold the player has
@return int the amount of gold player has
*/
int getGold(){
	return charInventory.goldAmt;
}

/**
When player collides with a treasures chest, he recieves items. Gold and potions are random but armor and weapons are in a linear order
*/
void openATreasureChest(){
	recieveGold();
	recievePotion();
	recieveItemTreasureChest();
}

/**
	random calculation of gold to be recieved can be from treasure chests or battle
*/
int recievePotion(){
	int potion = rand() % 4; 
	addItem(potion);
	return potion;
}

/**
	random calculation of gold to be recieved can be from treasure chests or battle
*/
int recieveGold(){
	int gold = rand() % 100 + 1; 
	addGold(gold);
	return gold;
}

/**
	Recieves an Item (from treasure chests) armor and weapon in linear order
@return int corresponding to item, -1 if no more items exist to give
*/
int recieveItemTreasureChest(){
	int i;
	for (i = 4; i <= 8; i++){
		if (charInventory.inventoryList[i] == 0){
			addItem(i);
			return i;		
		}
		if (charInventory.inventoryList[i+4] == 0){
			addItem(i+4);
			return i+4;		
		}
	}
	return -1;
}


/**
Tests the results of inventory via treasure chests
calls in collision.c checkForTreasureChest()
*/
void testingInventory(){
	printf("Inventory : ");
	int i;
	for (i = 0; i < CHAR_INVENTORY_SIZE; i++){
		printf("%d ", charInventory.inventoryList[i]);
	}
	printf("\nTotalGold: %d\n", getGold());
}


/**
Using Items in a characters Inventory. Items effect player stats.
baseAttack, attack, baseDefense, defense, baseSpeed, speed, maxHp, currentHp;
*/
void useItem(int x){
	if(x == 0 && charInventory.inventoryList[x] > 0){	// MINOR_HEALING_POTION adds 25% of maxHp to current health (limit is maxHp)
		player.stats.currentHp += player.stats.maxHp * 0.25;
		charInventory.inventoryList[x]--;
		if( player.stats.currentHp > player.stats.maxHp){
			player.stats.currentHp = player.stats.maxHp;	
		}
	}else if (x == 1 && charInventory.inventoryList[x] > 0){	//LESSER_HEALING_POTION adds 50% of maxHp to current health (limit is maxHp)
		player.stats.currentHp += player.stats.maxHp * 0.50;
		charInventory.inventoryList[x]--;
		if( player.stats.currentHp > player.stats.maxHp){
			player.stats.currentHp = player.stats.maxHp;	
		}
	}else if (x == 2 && charInventory.inventoryList[x] > 0){	//GREATER_HEALING_POTION adds 75% of maxHp to current health (limit is maxHp)
		player.stats.currentHp = player.stats.maxHp * 0.75;
		charInventory.inventoryList[x]--;
		if( player.stats.currentHp > player.stats.maxHp){
			player.stats.currentHp = player.stats.maxHp;	
		}
	}else if (x == 3 && charInventory.inventoryList[x] > 0){	//SUPER_HEALING_POTION adds 100% of maxHp to current health (limit is maxHp)
		player.stats.currentHp = player.stats.maxHp;
		charInventory.inventoryList[x]--;
	}else if (x == 4 && charInventory.inventoryList[x] > 0){	//SWORD_ONE gives 25 more attack
		player.stats.attack = player.stats.baseAttack;
		player.stats.attack += 25;
	}else if (x == 5 && charInventory.inventoryList[x] > 0){	//SWORD_TWO gives 50 more attack
		player.stats.attack = player.stats.baseAttack;
		player.stats.attack += 50;
	}else if (x == 6 && charInventory.inventoryList[x] > 0){	//SWORD_THREE gives 75 more attack
		player.stats.attack = player.stats.baseAttack;
		player.stats.attack += 75;
	}else if (x == 7 && charInventory.inventoryList[x] > 0){	//SWORD_FOUR gives 100 more attack
		player.stats.attack = player.stats.baseAttack;
		player.stats.attack += 100;
	}else if (x == 8 && charInventory.inventoryList[x] > 0){	//ARMOR_ONE gives 25 more defense
		player.stats.defense = player.stats.baseDefense;
		player.stats.defense += 25;
	}else if (x == 9 && charInventory.inventoryList[x] > 0){	//ARMOR_TWO gives 50 more defense
		player.stats.defense = player.stats.baseDefense;
		player.stats.defense += 50;
	}else if (x == 10 && charInventory.inventoryList[x] > 0){	//ARMOR_THREE gives 75 more defense
		player.stats.defense = player.stats.baseDefense;
		player.stats.defense += 75;
	}else if (x == 11 && charInventory.inventoryList[x] > 0){	//ARMOR_FOUR gives 100 more defense
		player.stats.defense = player.stats.baseDefense;
		player.stats.defense += 100;
	}
}

/**
initiliaze player with basic stats i.e call during new game
should be called only during new game
*/
void initializePlayerStats(){
	player.stats.baseAttack = BASE_ATTACK;
	player.stats.attack = BASE_ATTACK;
	player.stats.baseDefense = BASE_DEFENSE;
	player.stats.defense = BASE_DEFENSE;	
	player.stats.baseSpeed = BASE_SPEED;
	player.stats.speed = BASE_SPEED;
	player.stats.maxHp = BASE_HP;
	player.stats.currentHp = BASE_HP;
	player.stats.exp = 0;
	player.stats.level = 0;
}

/**
function called at the end of a battle
to determine a level up
*/
void levelUp() {
	if( player.stats.level == 0 && player.stats.exp >= 2000 ) {
		player.stats.baseAttack += 20;
		player.stats.baseDefense += 20;
		player.stats.baseSpeed += 20;
		player.stats.maxHp = 200;
		player.stats.attack += 20;
		player.stats.defense += 20;
		player.stats.speed += 20;
		player.stats.level +=1;
	}
	if( player.stats.level == 1 && player.stats.exp >= 4000 ) {
		player.stats.baseAttack += 20;
		player.stats.baseDefense += 20;
		player.stats.baseSpeed += 20;
		player.stats.maxHp = 200;
		player.stats.attack += 20;
		player.stats.defense += 20;
		player.stats.speed += 20;
		player.stats.level +=1;
	}
	if( player.stats.level == 2 && player.stats.exp >= 6000 ) {
		player.stats.baseAttack += 20;
		player.stats.baseDefense += 20;
		player.stats.baseSpeed += 20;
		player.stats.maxHp = 200;
		player.stats.attack += 20;
		player.stats.defense += 20;
		player.stats.speed += 20;
		player.stats.level +=1;
	}
	if( player.stats.level == 3 && player.stats.exp >= 8000) {
		player.stats.baseAttack += 20;
		player.stats.baseDefense += 20;
		player.stats.baseSpeed += 20;
		player.stats.maxHp = 200;
		player.stats.attack += 20;
		player.stats.defense += 20;
		player.stats.speed += 20;
		player.stats.level +=1;
	}
}

/**
Animates a the slashing anime slash one. Currently on Player
*/
void doSlashOne(){
	int i;
	for (i = 0; i < 3; i++) {
		doAnimation(&slashOne);
		drawAnimation(&slashOne, 400, 210);
		SDL_Delay(100);
	}
}

/**
Animates a the slashing anime slash two. Currently on Monster
*/
void doSlashTwo(){
	int i;
	for(i = 0; i < 3; i++){
		doAnimation(&slashTwo);
		drawAnimation(&slashTwo, 100, 130);
		SDL_Delay(100);
	}
}

/**
called when the hero is killed

blacks out the screen, prints message "You've Been Shreaded!"
any keys EXITS the game
*/
void playerKilled() {
	// place holder
	printf("You've been shreaded!");
	exit(0);
}

/**
this function is called if the hero successfully ends the battle or 
run away like a chicken

monsterType determines the experience

ranAway determines if you get experience points

*/
void endBattle(int monsterType, int ranAway) {
	// called when player beats monster
	if(ranAway == 0) {
		intMonsters();
		player.stats.exp += 500;
		sprintf(expGained, "%d", 500);
		sprintf(goldGained, "%d", recieveGold());
		recievePotion();
		levelUp();
		battleEnded = 1;
		//showVictoryScreen = 1;
		//recieveGold();
		//showBattleScreen = 0;
	}
}

void lostBattle(int monsterType){
	
	intMonsters();
	defeated = 1;

}

/**
Using a small fraction of probability... ideally once every ten spaces.
We check against the map type to see what kind of enemy has a chance to hit the
player

In the future this function can be modified to use a sperate map to more
intelligent determine enemies.

if 0 is returned, function executed properly

need to implement font functions to handle fonts better

----
Monsters
+++++
Monster levels are determined by 1X for level 1
2X, 3X and so on, X9 should be for the special monster

The boss holds a special number
666

*/
int randomBattleCheck(int mapType) {
	// generate random number
	int randomVal = rand() % 1000 + 1; // choose a random number from 1 to 1000 (range of 999)

	// put this for here for now
	intMonsters();

	//printf("%d ", mapType);
	// I noticed the random code slows down the down key significantly, maybe the timer could be adjusted to be more realstic based on the
	// algrothem provided on sdl tutorials website

	// I got the time down to that of Pokemon and final fantasy

	if( mapType == DUN_TILE_LV1_NUM ) {
			
		if(randomVal >= 990 && randomVal < 993) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv1 Type1 encountered!\n");
			//enterBattleState(10);
			battleState = 10;
		}
		else if (randomVal >= 993 && randomVal < 996) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv1 Type2 encountered!\n");
			//enterBattleState(10);
			battleState = 10;
		}		
		else if (randomVal >= 996 && randomVal < 999) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv1 Type3 encountered!\n");
			//enterBattleState(10);
			battleState = 10;
		} // this is for a case of an overly powerful monster - very rare
		else if( randomVal == 1000) {
			showBattleScreen = 1;
			printf("randomBattleCheck: SPECIAL! Monster Lv1 encountered!\n");
			//enterBattleState(10);
			battleState = 10;
		}

	}
	else if( mapType == DUN_TILE_LV2_NUM ) {

		if(randomVal >= 990 && randomVal < 993) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv2 Type1 encountered!\n");
			//enterBattleState(20);
			battleState = 20;
		}
		else if (randomVal >= 993 && randomVal < 996) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv2 Type2 encountered!\n");
			//enterBattleState(20);
			battleState = 20;
		}		
		else if (randomVal >= 996 && randomVal < 999) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv2 Type3 encountered!\n");
			//enterBattleState(20);
			battleState = 20;
		} // this is for a case of an overly powerful monster - very rare
		else if( randomVal == 1000) {
			showBattleScreen = 1;
			printf("randomBattleCheck: SPECIAL! Monster Lv2 encountered!\n");
			//enterBattleState(20);
			battleState = 20;
		}

	}
	else if( mapType == DUN_TILE_LV3_NUM ) {
		
		if(randomVal >= 990 && randomVal < 993) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv3 Type1 encountered!\n");
			//enterBattleState(30);
			battleState = 30;
		}
		else if (randomVal >= 993 && randomVal < 996) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv3 Type2 encountered!\n");
			//enterBattleState(30);
			battleState = 30;
		}		
		else if (randomVal >= 996 && randomVal < 999) {
			showBattleScreen = 1;
			printf("randomBattleCheck: Monster Lv3 Type3 encountered!\n");
			//enterBattleState(30);
			battleState = 30;
		} // this is for a case of an overly powerful monster - very rare
		else if( randomVal == 1000) {
			showBattleScreen = 1;
			printf("randomBattleCheck: SPECIAL! Monster Lv3 encountered!\n");
			//enterBattleState(30);
			battleState = 30;
		}

	}
	// Boss code
	else if (mapType == RED_TILE_NUM /*BOS_TILE_NUM*/ /*&& game.worldData.alreadyFoughtBoss == 0*/) {
		
		// to take the boss off the map
		game.worldData.alreadyFoughtBoss = 1;

		showBattleScreen = 1;
		// fight him!
		//enterBattleState(666);
		battleState = bossNum;
	}
	else if( mapType == DUN_TILE_NUM ) {
		printf("0 tile is decaparcated\n");
		/*if(randomVal >= 990 && randomVal < 993) {
			showBattleScreen = 1;
			//printf("randomBattleCheck: Monster Lv1 Type1 encountered!\n");
			//enterBattleState(10);
			battleState = 10;
		}
		else if (randomVal >= 993 && randomVal < 996) {
			showBattleScreen = 1;
			//printf("randomBattleCheck: Monster Lv1 Type2 encountered!\n");
			//enterBattleState(20);
			battleState = 20;
		}		
		else if (randomVal >= 996 && randomVal < 999) {
			showBattleScreen = 1;
			//printf("randomBattleCheck: Monster Lv1 Type3 encountered!\n");
			//enterBattleState(30);
			battleState = 30;
		}*/ // this is for a case of an overly powerful monster - very rare
		/*else if( randomVal == 1000) {
			showBattleScreen = 1;
			printf("randomBattleCheck: SPECIAL! Monster Lv1 encountered!\n");
			//enterBattleState(10);
			battleState = 40;
		}*/

	}

	return 0;
}

/**
first this reduces the map to units of the tile size

then the map returns the tile size
-1 if error

notice this function assumes collosion
*/
int queryMap(int x, int y) {
	//  negative case
	if (x < 0 || y < 0) {
		return -1;
	}	
	// 0 to map size in x and y case
	x = x / TILE_SIZE;
	y = y / TILE_SIZE;

	//printf("%d, %d, %d\n", x, y, samplemap.tile[y][x]);
	return samplemap.tile[y][x];
}

/**
This function is called many times
once at initalization of game, once at game load
and many times by the thread
*/
int setDefaultGenieStock() {
	//genieStore.storeGold = 1000;
	genieStore.minorPotion = 10;
	genieStore.lesserPotion = 5;
	genieStore.greaterPotion = 2;
	genieStore.superPotion = 1;
}

/**
Calculates and applies an attack by the first entity against the second entity
the return value is whatever the damage

The third variable is a true/false option that determines if the defender is defending
cuts damage in half
-
the function returns the total damage to hp (for graphics and menu reporting)
0 if zero
-1 if error
*/
int calcAttack(Entity *attacker, Entity *defender, int defending) {
	int damage;
	// need to add armor and weapons
	damage = (*attacker).stats.attack - (*defender).stats.defense;
	if(defending == 1 && damage > 0) {
		damage = damage/2;
	}

	if(damage >= 0) {
		if(damage < (*defender).stats.currentHp){
			(*defender).stats.currentHp -= damage;
		}
		else{
			(*defender).stats.currentHp = 0;
		}
		return damage;
	}
	else {
		return 0;
	}
}

/**
determines based on speed rating who goes first

0 determines hero goes first (who also wins a tie)
1 determines monster goes first
*/
int whoGoesFirst(Entity hero, Entity monster) {
	if (hero.stats.speed >= monster.stats.speed) {
		return 1;
	}
	return 0;
}

/**
this code determines the flow of the battle code
*/
void battleFlow(int defends){
	
	if( battleState == lv1GoopNum && whoGoesFirst(player, lv1Goop) == 1 ){
		
		//when player attacks:
		if(defends == 0){
			batMsgDisplay = 0;
			enemyDamageTaken = calcAttack(&player, &lv1Goop, 0);
			if(lv1Goop.stats.currentHp <= 0){
				lv1Goop.stats.currentHp = 0;
				endBattle(lv1GoopNum, 0);
			}
			didAttack = 1;
			playerDamageTaken = calcAttack(&lv1Goop, &player, 0);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv1GoopNum);
			}
		
		}
		//when player defends:
		else if(defends == 1)	{
			batMsgDisplay = 2;
			playerDamageTaken = calcAttack(&lv1Goop, &player, 1);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv1GoopNum);
			}
		}
	}

	else if( battleState == lv1GoopNum && whoGoesFirst(player, lv1Goop) == 0 ){
		
		//when player attacks:
		if(defends == 0){
			batMsgDisplay = 3;
			playerDamageTaken = calcAttack(&lv1Goop, &player, 0);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv1GoopNum);
			}
			enemyDamageTaken = calcAttack(&player, &lv1Goop, 0);
			if(lv1Goop.stats.currentHp <= 0){
				lv1Goop.stats.currentHp = 0;
				endBattle(lv1GoopNum, 0);
			}
			didAttack = 1;
		}
		//when player defends:
		else if(defends == 1)	{
			batMsgDisplay = 2;
			playerDamageTaken = calcAttack(&lv1Goop, &player, 1);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv1GoopNum);
			}
		}
	}

	else if( battleState == lv2LizardNum && whoGoesFirst(player, lv2Lizard) == 1 ){
		
		//when player attacks:
		if(defends == 0){
			batMsgDisplay = 0;
			enemyDamageTaken = calcAttack(&player, &lv2Lizard, 0);
			if(lv2Lizard.stats.currentHp <= 0){
				lv2Lizard.stats.currentHp = 0;
				endBattle(lv2LizardNum, 0);
			}
			didAttack = 1;
			playerDamageTaken = calcAttack(&lv2Lizard, &player, 0);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv2LizardNum);
			}
		}
		//when player defends:
		else if(defends == 1)	{
			batMsgDisplay = 2;
			playerDamageTaken = calcAttack(&lv2Lizard, &player, 1);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv2LizardNum);
			}
		}
	}

	else if( battleState == lv2LizardNum && whoGoesFirst(player, lv2Lizard) == 0 ){
		
		//when player attacks:
		if(defends == 0){
			batMsgDisplay = 3;
			playerDamageTaken = calcAttack(&lv2Lizard, &player, 0);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv2LizardNum);
			}
			enemyDamageTaken = calcAttack(&player, &lv2Lizard, 0);
			if(lv2Lizard.stats.currentHp <= 0){
				lv2Lizard.stats.currentHp = 0;
				endBattle(lv2LizardNum, 0);
			}
			didAttack = 1;
		}
		//when player defends:
		else if(defends == 1)	{
			batMsgDisplay = 2;
			playerDamageTaken = calcAttack(&lv2Lizard, &player, 1);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv2LizardNum);
			}
		}
	}

	if( battleState == lv3MultiNum && whoGoesFirst(player, lv3Multi) == 1 ){
		
		//when player attacks:
		if(defends == 0){
			batMsgDisplay = 0;
			enemyDamageTaken = calcAttack(&player, &lv3Multi, 0);
			if(lv3Multi.stats.currentHp <= 0){
				lv3Multi.stats.currentHp = 0;
				endBattle(lv3MultiNum, 0);
			}
			didAttack = 1;
			playerDamageTaken = calcAttack(&lv3Multi, &player, 0);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv3MultiNum);
			}
		}
		//when player defends:
		else if(defends == 1)	{
			batMsgDisplay = 2;
			playerDamageTaken = calcAttack(&lv3Multi, &player, 1);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv3MultiNum);
			}
		}
	}

	else if( battleState == lv3MultiNum && whoGoesFirst(player, lv3Multi) == 0 ){
		
		//when player attacks:
		if(defends == 0){
			batMsgDisplay = 3;
			playerDamageTaken = calcAttack(&lv3Multi, &player, 0);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv3MultiNum);
			}
			enemyDamageTaken = calcAttack(&player, &lv3Multi, 0);
			if(lv3Multi.stats.currentHp <= 0){
				lv3Multi.stats.currentHp = 0;
				endBattle(lv3MultiNum, 0);
			}
			didAttack = 1;
		}
		//when player defends:
		else if(defends == 1)	{
			batMsgDisplay = 2;
			playerDamageTaken = calcAttack(&lv3Multi, &player, 1);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv3MultiNum);
			}
		}
	}

	if( battleState == bossNum && whoGoesFirst(player, stewie) == 1 ){
		
		//when player attacks:
		if(defends == 0){
			batMsgDisplay = 0;
			enemyDamageTaken = calcAttack(&player, &stewie, 0);
			if(stewie.stats.currentHp <= 0){
				stewie.stats.currentHp = 0;
				beatFinalBoss = 1;
				endBattle(bossNum, 0);
			}
			didAttack = 1;
			playerDamageTaken = calcAttack(&stewie, &player, 0);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv3MultiNum);
			}
		}
		//when player defends:
		else if(defends == 1)	{
			batMsgDisplay = 2;
			playerDamageTaken = calcAttack(&stewie, &player, 1);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv3MultiNum);
			}
		}
	}

	else if( battleState == bossNum && whoGoesFirst(player, stewie) == 0 ){
		
		//when player attacks:
		if(defends == 0){
			batMsgDisplay = 3;
			playerDamageTaken = calcAttack(&stewie, &player, 0);
			// if player's hp reaches 0
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv3MultiNum);
			}
			enemyDamageTaken = calcAttack(&player, &stewie, 0);
			// if the boss reaches 0
			if(stewie.stats.currentHp <= 0){
				stewie.stats.currentHp = 0;
				beatFinalBoss = 1;
				endBattle(bossNum, 0);
			}
			//printf("%d",stewie.stats.currentHp);
			didAttack = 1;
		}
		//when player defends:
		else if(defends == 1)	{
			batMsgDisplay = 2;
			playerDamageTaken = calcAttack(&stewie, &player, 1);
			if(player.stats.currentHp <= 0){
				player.stats.currentHp = 0;
				lostBattle(lv3MultiNum);
			}
			// the boss cannot be harmed if the player doesn't attack-put in 

		}
	}
}

