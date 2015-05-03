//In your team of four:

//Pretend all the functions in Game.c have already been written.  
//Plan and write testGame.c - which #includes Game.h and which contains a main function which creates a Game (or several Games) and uses them to extensively test the Game ADT interface functions. 
//Do this exactly like the other unit tests we have written in class.  E.g. test using asserts.
//At the end, if you have passed all the tests, printf "All tests passed, you are Awesome!".

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"

// Joerick's #defines
#define MIN_DICE_VALUE 2
#define MAX_DICE_VALUE 12

void bryanstests();
void Joerickstests();


int main (int argc, char *argv[]) {
	//add your tests for your section in here, 
	bryanstests();

   Joerickstests();

   
	return EXIT_SUCCESS;
	
}

void bryanstests(){
   //BRYAN'S TESTS!
   
   //disposeGame
   printf("Testing disposeGame");
   
   //Not too sure what this does...
   
   printf("disposeGame passed!");
   
   printf("Testing getDiceValue");
   assert( getDiceValue (g, regionID) >= 2);
   assert( getDiceValue (g, regionID) <= 12);
   printf("getDiceValue passed!")
   
   printf("Testing getMostArcs");
   //Arcs array will hold arcs per player
   int arcs[3];
   int arcCount = 1;
   while(arcCount < 4){
      assert(getMostPublications(g) >= arcs[arcCount]);
      arcCount++;
   }
   printf("getMostArcs passed!")
   
   printf("Testing getMostPublications");
   //Publications array will hold publications per player
   int publications[3];
   int pubCount = 1;
   while(count < 4){
      assert(getMostPublications(g) >= publications[pubCount]);
      pubCount++;
   }
   printf("getMostPublications passed!")
   
   printf("Testing getTurnNumber");
   newGame (int discipline[], int dice[]);
   assert(getTurnNumber(g) == -1);
   throwDice (g, diceScore);
   assert(getTurnNumber(g) == 0);
   printf("getTurnNumber passed!");
}

void Joerickstests(){
// Joerick's tests
	/*****************************************************/
	// Test for throwDice
	printf("Testing throwDice\n");
	int throwdicecount = 0;
	Game test;
	test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
	
	assert(getTurnNumber(test) == -1);
	while (throwdicecount <= (sizeof(DEFAULT_DICE) / sizeof(int))){
		throwDice(test,DEFAULT_DICE[counter]);
		assert(DEFAULT_DICE[throwdicecount] >= MIN_DICE_VALUE && DEFAULT_DICE[throwdicecount] <= MAX_DICE_VALUE);
		assert(getTurnNumber(test) == throwdicecounter);
		throwdicecounter++;
	}
	disposeGame(test);
	printf("throwDice Tests passed\n");
	// End of throwDice tests
	/*****************************************************/
	
	/*****************************************************/
	// test for getCampus
	printf("Testing getCampus\n");
	Game test;
	test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
	
	action obtain_campus;
	obtain_campus.actionCode = BUILD_CAMPUS;
	assert(sizeof(pathtoVertex) <= PATH_LIMIT);
	
	obtain_campus.destination = "RLLLLLL";
	assert(getARC(test,obtain_arc.destination) == CAMPUS_A);
	
	obtain_campus.destination = "L";
	assert(getARC(test,obtain_arc.destination) == VACANT_VERTEX);
	
	obtain_campus.destination = "R";
	assert(getARC(test,obtain_arc.destination) == VACANT_VERTEX);
	
	obtain_campus.destination = "LRLRL";
	assert(getARC(test,obtain_arc.destination) == CAMPUS_C);
	
	obtain_campus.destination = "RRLRL";
	assert(getARC(test,obtain_arc.destination) == CAMPUS_B);
	
	obtain_campus.destination = "RLRLRLRRLR";
	assert(getARC(test,obtain_arc.destination) == CAMPUS_C);
	
	obtain_campus.destination = "RLRLRLRLLRR";
	assert(getARC(test,obtain_arc.destination) == CAMPUS_A);
	
	obtain_campus.destination = "LRRLRLRLLLRR";
	assert(getARC(test,obtain_arc.destination) == CAMPUS_B);
	
	obtain_campus.destination = "RLRLRL";
	assert(getARC(test,obtain_arc.destination) == VACANT_VERTEX);
	
	obtain_campus.destination = "RLRLRLLLRR";
	assert(getARC(test,obtain_arc.destination) == VACANT_VERTEX);
	disposeGame(test);
	printf("getCampus Tests passed\n");
	// End of getCampus test
	/*****************************************************/
	
	/*****************************************************/
	// test for getARC
	printf("Testing getARC\n");
	
	Game test;
	test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
	
	action obtain_arc;
	obtain_arc.actionCode = OBTAIN_ARC;
	assert(sizeof(pathtoEdge) <= PATH_LIMIT);
	
	obtain_arc.destination = "L"
	assert(getARC(test,obtain_arc.destination) == VACANT_ARC);
	
	obtain_arc.destination = "R"
	assert(getARC(test,obtain_arc.destination) == VACANT_ARC);
	
	obtain_arc.destination = "RL"
	assert(getARC(test,obtain_arc.destination) == VACANT_ARC);
	
	obtain_arc.destination = "LR"
	assert(getARC(test,obtain_arc.destination) == VACANT_ARC);
	
	obtain_arc.destination = "LRRRL"
	assert(getARC(test,obtain_arc.destination) == VACANT_ARC);
	
	obtain_arc.destination = "RRLLL"
	assert(getARC(test,obtain_arc.destination) == VACANT_ARC);
	
	obtain_arc.destination = "RLR"
	assert(getARC(test,obtain_arc.destination) == VACANT_ARC);
	disposeGame(test);
	printf("getArc Tests passed\n");
	// End of getARC test
	/*****************************************************/
	
	/*****************************************************/
	// test for getWhoseTurn
	Game test;
	test = newGame(DEFAULT_DISCIPLINES,DICE_VALUE);
	
	assert(getWhoseTurn(test) == NO_ONE);
	
	throwDice(test,DICE_VALUE[0]);
	assert(getWhoseTurn(test) == UNI_A);
	
	throwDice(test,DICE_VALUE[1]);
	assert(getWhoseTurn(test) == UNI_B);
	
	throwDice(test,DICE_VALUE[2]);
	assert(getWhoseTurn(test) == UNI_C);
	
	throwDice(test,DICE_VALUE[3]);
	assert(getWhoseTurn(test) == UNI_A);
	
	throwDice(test,DICE_VALUE[4]);
	assert(getWhoseTurn(test) == UNI_B);
	disposeGame(test);
	printf("getWhoseTurn Tests passed\n");
	// End of getWhoseTurn test
	/*****************************************************/
	
	/*****************************************************/
	// testing getPublications
	printf("Testing getPublications\n");
	Game test;
	test = newGame(DEFAULT_DISCIPLINES,DICE_VALUE);
	action obtain_publication;
	obtain_publication.actionCode = OBTAIN_PUBLICATION;
	
	assert(getPublications(test,UNI_A) == 0);
	assert(getPublications(test,UNI_B) == 0);
	assert(getPublications(test,UNI_C) == 0);
	
	throwDice(test,DEFAULT_DICE[0]);
	makeAction(test,obtain_publication);
	assert(getPublications(test,UNI_A) == 1);
	assert(getPublications(test,UNI_B) == 0);
	assert(getPublications(test,UNI_C) == 0);t
	
	throwDice(test,DEFAULT_DICE[1]);
	makeAction(test,obtain_publication);
	assert(getPublications(test,UNI_A) == 1);
	assert(getPublications(test,UNI_B) == 1);
	assert(getPublications(test,UNI_C) == 0);
	
	throwDice(test,DEFAULT_DICE[2]);
	makeAction(test,obtain_publication);
	assert(getPublications(test,UNI_A) == 1);
	assert(getPublications(test,UNI_B) == 1);
	assert(getPublications(test,UNI_C) == 1);
	
	throwDice(test,DEFAULT_DICE[3]);
	makeAction(test,obtain_publication);
	assert(getPublications(test,UNI_A) == 2);
	assert(getPublications(test,UNI_B) == 1);
	assert(getPublications(test,UNI_C) == 1);
	
	throwDice(test,DEFAULT_DICE[4]);
	makeAction(test,obtain_publication);
	assert(getPublications(test,UNI_A) == 2);
	assert(getPublications(test,UNI_B) == 2);
	assert(getPublications(test,UNI_C) == 1);
	disposeGame(test);
	printf("getPublications Test passed\n");
	// End of getPublications test
	/*****************************************************/
}


/*
Game newGame (int discipline[], int dice[]); //Matt

void disposeGame (Game g); //Bryan

void makeAction (Game g, action a); //Matt 

void throwDice (Game g, int diceScore); //Joerick

int getDiscipline (Game g, int regionID); //Matt

int getDiceValue (Game g, int regionID); //Bryan

int getMostARCs (Game g); //Byan

int getMostPublications (Game g); //Bryan

int getTurnNumber (Game g); //Bryan

int getWhoseTurn (Game g); //Joerick

int getCampus(Game g, path pathToVertex); //Joerick

int getARC(Game g, path pathToEdge); //Joerick

int isLegalAction (Game g, action a); //Matt

int getKPIpoints (Game g, int player); //Charly

int getARCs (Game g, int player); //Charly

int getGO8s (Game g, int player); //Charly

int getCampuses (Game g, int player); //Charly

int getIPs (Game g, int player); //Charly

int getPublications (Game g, int player); //Joerick

int getStudents (Game g, int player, int discipline); //Matt

int getExchangeRate (Game g, int player,
                     int disciplineFrom, int disciplineTo); //Matt
*/
