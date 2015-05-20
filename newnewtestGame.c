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
void testGetIPs (void);
void testGetKPIpoints (void);

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

//Inputs: Game g, int player
void testGetIPs (void){
   int disciplines[] = DEFAULT_DISCIPLINES;
   int dice[] = DEFAULT_DICE;
   Game g = newGame(disciplines,dice);

   action testD;
   testD.actionCode = OBTAIN_IP_PATENT; //check legals
   int x=UNI_A;
   while (x <= UNI_C){
      throwDice (g, 2);
      makeAction (g, testD);
      assert (getIPs (g, x) == 1);
      x++;
   }
   disposeGame(g);
}

//Inputs: Game g, int player
void testGetKPIpoints (void){
   
   path path15= "RL";
   
   // return the number of ARC grants the specified player currently has
   int disciplines[] = DEFAULT_DISCIPLINES;
   int dice[] = DEFAULT_DICE;
   Game g = newGame(disciplines,dice);

   //Checked for term 1
   assert (getKPIpoints (g, UNI_A) == 20);
   assert (getKPIpoints (g, UNI_B) == 20);
   assert (getKPIpoints (g, UNI_C) == 20);

   throwDice (g, 2);
   action testA;
   testA.actionCode = OBTAIN_ARC;
   testA.destination = "R";
   makeAction (g, testA);
   assert (getKPIpoints (g, UNI_A) == 32);
   assert (getARCs (g, UNI_A) == 1);
   assert (getMostARCs (g) == UNI_A);
   assert (getARC (g, path3) == ARC_A);

   throwDice (g, 2);
   throwDice (g, 2);
   throwDice (g, 2); //Uni A turn again
   testA.destination = path15;
   makeAction (g, testA);

   action testB;
   testB.actionCode = BUILD_CAMPUS;
   testB.destination = path15;
   makeAction (g, testB);
   assert (getKPIpoints (g, UNI_A) == 42);
   assert (getARCs (g, UNI_A) == 2);
   assert (getMostARCs (g) == UNI_A);
   assert (getARC (g, path15) == ARC_A);
   assert (getCampuses (g, UNI_A) == 3);
   assert (getCampus (g, path15) == CAMPUS_A);

   assert (getGO8s (g, UNI_A) == 0);
   
   //Gives UNI_A 3 MMoneys and 2 MJS and leaves it on UNI_A's turn

   int diceAdvancer = 0;
   while (diceAdvancer <= 6){
      if (diceAdvancer < 2){
         throwDice (g, 6);
      } else {
         throwDice (g, 12);
      }
      diceAdvancer++;
   }

   action testC;
   testC.actionCode = BUILD_GO8;
   testC.destination = path15;
   makeAction (g, testC);
   assert (getGO8s (g, UNI_A) == 1);

   disposeGame (g);

}