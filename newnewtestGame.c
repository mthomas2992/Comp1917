#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Game.h"


// Joerick's #defines
//#define MIN_DICE_VALUE 2
//#define MAX_DICE_VALUE 12

#define DEFAULT_DISCIPLINES {2, 5, 3,\
                5, 3, 1, 4,\
                4, 1,4, 2,\
                3, 2, 0, 3,\
                5, 4, 2, 1}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

void testgetTurnNumber (void);

int main (int argc, char *argv[]) {
	testgetTurnNumber();
	return EXIT_SUCCESS;
}

void testgetTurnNumber(void){
   printf("Testing getTurnNumber\n");
   int disciplines[] = DEFAULT_DISCIPLINES;
   int dice[] = DEFAULT_DICE;
   Game test = newGame(disciplines,dice);
   assert(getTurnNumber(test) == -1);

   throwDice(test,dice[0]);
   assert(getTurnNumber(test) == 0);

   throwDice(test,dice[1]);
   assert(getTurnNumber(test) == 1);

   throwDice(test,dice[2]);
   assert(getTurnNumber(test) == 2);

   throwDice(test,dice[3]);
   assert(getTurnNumber(test) == 3);

   disposeGame(test);
   printf("getTurnNumber passed!\n");
} 