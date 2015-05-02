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
// Change MAX_DICE_VALUE to 6 if two dice are rolled

int main (int argc, char *argv[]) {
	//add your tests for your section in here, 
	
	
	//BRYAN'S TESTS!
	
	//disposeGame
	printf("Testing disposeGame");
	
	//Not too sure what this does...
	
	printf("disposeGame passed!")
	
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
	printf("getTurnNumber passed!")
	
	//end Bryans Tests

	// Joerick's tests
		// Tests for throwDice and getWhoseTurn
		printf("Testing throwDice & getWhoseTurn...\n");
		Game g = newGame(DEFAULT_DISCIPLINES,DICE_VALUE);
		
		assert(getWhoseTurn(g) == 0);
		assert(getTurnNumber(g) == -1);
	
		throwDice(g,DICE_VALUE[0]);
		assert(DICE_VALUE[0] >= MIN_DICE_VALUE && DICE_VALUE[0] <= MAX_DICE_VALUE);
		assert(getWhoseTurn(g) == UNI_A);
		assert(getTurnNumber(g) == 0);
		
		throwDice(g,DICE_VALUE[1]);
		assert(DICE_VALUE[1] >= MIN_DICE_VALUE && DICE_VALUE[1] <= MAX_DICE_VALUE);
		assert(getWhoseTurn(g) == UNI_B);
		assert(getTurnNumber(g) == 1);

		throwDice(g,DICE_VALUE[2]);
		assert(DICE_VALUE[2] >= MIN_DICE_VALUE && DICE_VALUE[2] <= MAX_DICE_VALUE);
		assert(getWhoseTurn(g) == UNI_C);
		assert(getTurnNumber(g) == 2);

		throwDice(g,DICE_VALUE[3]);
		assert(DICE_VALUE[3] >= MIN_DICE_VALUE && DICE_VALUE[3] <= MAX_DICE_VALUE);
		assert(getWhoseTurn(g) == UNI_A);
		assert(getTurnNumber(g) == 3);

		throwDice(g,DICE_VALUE[4]);
		assert(DICE_VALUE[3] >= MIN_DICE_VALUE && DICE_VALUE[4] <= MAX_DICE_VALUE);
		assert(getWhoseTurn(g) == UNI_B);
		assert(getTurnNumber(g) == 4);

		throwDice(g,DICE_VALUE[5]);
		assert(DICE_VALUE[5] >= MIN_DICE_VALUE && DICE_VALUE[5] <= MAX_DICE_VALUE);
		assert(getWhoseTurn(g) == UNI_C);
		assert(getTurnNumber(g) == 5);

		throwDice(g,DICE_VALUE[6]);
		assert(DICE_VALUE[6] >= MIN_DICE_VALUE && DICE_VALUE[6] <= MAX_DICE_VALUE);
		assert(getWhoseTurn(g) == UNI_A);
		assert(getTurnNumber(g) == 6);
		printf("Tests passed\n\n");
		// End of throwDice & getWhoseTurn tests
	
	return EXIT_SUCCESS;
	
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
