#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"

// Joerick's #defines
#define MIN_DICE_VALUE 2
#define MAX_DICE_VALUE 12

/*

//Standard defines
#define NUM_UNIS 3
// player ID of each university
#define NO_ONE 0
#define UNI_A 1
#define UNI_B 2
#define UNI_C 3
// contents of an ARC
#define VACANT_ARC 0
#define ARC_A 1
#define ARC_B 2
#define ARC_C 3
// contents of a VERTEX
#define VACANT_VERTEX 0
#define CAMPUS_A 1
#define CAMPUS_B 2
#define CAMPUS_C 3
#define GO8_A 4
#define GO8_B 5
#define GO8_C 6
// action codes
#define PASS 0
#define BUILD_CAMPUS 1
#define BUILD_GO8 2
#define OBTAIN_ARC 3
#define START_SPINOFF 4
#define OBTAIN_PUBLICATION 5
#define OBTAIN_IP_PATENT 6
#define RETRAIN_STUDENTS 7
// disciplines
#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5
#define NUM_REGIONS 19
#define PATH_LIMIT 150
#define TRUE 1
#define FALSE 0

*/

//New game test defaults
#define DEFAULT_DISCIPLINES {2, 5, 3,\
                5, 3, 1, 4,\
                4, 1,4, 2,\
                3, 2, 0, 3,\
                5, 4, 2, 1}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
#define MOD_DICE {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}
int main (int argc, char *argv[]) {

    int disciplines[] = DEFAULT_DISCIPLINES;
   int dice[] = DEFAULT_DICE;
   Game test = newGame(disciplines,dice);

   throwDice(test,1);
   assert(getExchangeRate(test, UNI_A, STUDENT_BPS, STUDENT_MTV)==2);
   assert(getExchangeRate(test, UNI_A, STUDENT_BQN, STUDENT_MTV)==2);
   assert(getExchangeRate(test, UNI_A, STUDENT_BPS, STUDENT_MMONEY)==3);
   assert(getExchangeRate(test, UNI_A, STUDENT_BQN, STUDENT_MMONEY)==3);

   assert(getExchangeRate(test, UNI_B, STUDENT_BPS, STUDENT_BQN)==2);
   assert(getExchangeRate(test, UNI_B, STUDENT_MJ, STUDENT_BQN)==2);
   assert(getExchangeRate(test, UNI_B, STUDENT_BPS, STUDENT_MMONEY)==3);
   assert(getExchangeRate(test, UNI_B, STUDENT_BPS, STUDENT_MTV)==3);

   disposeGame(test);

   return EXIT_SUCCESS;
}