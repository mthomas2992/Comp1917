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

//New game test defaults
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ,
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV,
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN,
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ,
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

void bryanstests(void);
void Joerickstests(void);

void getExchangeRatetests(void);
void isLegalActiontests(void);
void getStudentstest(void);
void makeActiontests(void);
void getDisciplinetests(void);
void newGametests(void);

int main (int argc, char *argv[]) {
	//add your tests for your section in here, 
	bryanstests();

   Joerickstests();

   newGametests();

   makeActiontests();

   getDisciplinetests();
   
	return EXIT_SUCCESS;
	
}

void bryanstests(void){
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

void Joerickstests(void){
// Joerick's tests
   /*****************************************************/
   // Test for throwDice
   printf("Testing throwDice");
   int throwdicecount = 0;
   Game test;
   test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
   
   assert(getTurnNumber(test) == -1);
   
   while (throwdicecount <= (sizeof(DEFAULT_DICE) / sizeof(int))){
      throwDice(test,DEFAULT_DICE[counter]);
      assert(DEFAULT_DICE[throwdicecount] >= MIN_DICE_VALUE && DEFAULT_DICE[throwdicecount] <= MAX_DICE_VALUE);
      assert(getTurnNumber(test) == throwdicecounter);
   }
   disposegame(test);
   printf("throwDice Tests passed\n");
   // End of throwDice tests
   /*****************************************************/
   
   /*****************************************************/
   // test for getWhoseTurn
   Game g = newGame(DEFAULT_DISCIPLINES,DICE_VALUE);
   
   assert(getWhoseTurn(g) == NO_ONE);

   throwDice(g,DICE_VALUE[0]);
   assert(getWhoseTurn(g) == UNI_A);
   
   throwDice(g,DICE_VALUE[1]);
   assert(getWhoseTurn(g) == UNI_B);

   throwDice(g,DICE_VALUE[2]);
   assert(getWhoseTurn(g) == UNI_C);

   throwDice(g,DICE_VALUE[3]);
   assert(getWhoseTurn(g) == UNI_A);
   
   throwDice(g,DICE_VALUE[4]);
   assert(getWhoseTurn(g) == UNI_B);
   disposeGame(g);
   printf("getWhoseTurn Tests passed\n");
   // End of getWhoseTurn test
   /*****************************************************/
   
   /*****************************************************/
   // testing getPublications
   printf("Testing getPublications\n");
   Game test;
   test = newGame(DEFAULT_DISCIPLINES,DICE_VALUE);
   action obtain_publication;
   obtain_pubcliaation.actionCode = OBTAIN_PUBLICATION;
   
   assert(getPublications(test,UNI_A) == 0);
   assert(getPublications(test,UNI_B) == 0);
   assert(getPublications(test,UNI_C) == 0);
   
   throwDice(test,DEFAULT_DICE[0]);
   makeAction(test,obtain_publication);
   assert(getPublications(test,UNI_A) == 1);
   assert(getPublications(test,UNI_B) == 0);
   assert(getPublications(test,UNI_C) == 0);
   
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

void newGametests(void){
   int disciplines[] = DEFAULT_DISCIPLINES;
   int dice[] = DEFAULT_DICE;
   Game gnt =newGame (disciplines, dice);
   
   //ensure starting values are completley empty
   assert(getMostARCs(gnt)==0);
   assert(getMostPublications(gnt)==0);
   assert(getTurnNumber(gnt)==-1); // first turn is identified as -1
   assert(getWhoseTurn(gnt)==NO_ONE);

   //check that each player is at the initial for all their values
   int playerx=UNI_A;
   int diciplinecheck=STUDENT_THD;
   while (playerx<=UNI_C){
      assert(getKPIpoints(gnt,playerx)==0);
      assert(getARCs(gnt,playerx)==0);
      assert(getGO8s(gnt,playerx)==0);
      assert(getCampuses(gnt,playerx)==0);
      assert(getIPs(gnt,playerx)==0):
      assert(getPublications(gnt,playerx)==0);
      while(diciplinecheck<=STUDENT_MMONEY){
         if ((diciplinecheck==STUDENT_BPS) || (diciplinecheck==STUDENT_BQN)){
            assert(getStudents(gnt,playerx,diciplinecheck)==3);
         } else if (diciplinecheck==STUDENT_THD) {
            assert(getStudents(gnt,playerx,diciplinecheck)==0);
         } else{
            assert(getStudents(gnt,playerx,diciplinecheck)==1);
         }
         diciplinecheck++
      }
      playerx++;
      diciplinecheck==STUDENT_THD;
   }

   //Vertex generator/checker VERY VERY VERY DODGY ONLY CHECKS CONSTANT LEFTS
   int pathcount=0;
   path pathtest;  //unsure about syntax
   while (pathcount<PATH_LIMIT){
      pathtest[pathcount]='L';
      assert(getCampus(gnt,pathtest)==VACANT_VERTEX);
      pathcount++
   }

   //check exchange rate for all players
   int diciplinecheck2=1;
   int diciplinecheck3=1;
   playerx=UNI_A;
   while (playerx<=UNI_C){
      while(diciplinecheck2<=STUDENT_MMONEY){
         while(diciplinecheck3<=STUDENT_MMONEY){
            assert(getExchangeRate(gnt,playerx,diciplinecheck2,diciplinecheck3)==3);
            diciplinecheck3++;
         }
         diciplinecheck2++;
         diciplinecheck3=1;
      }
      playerx++;
      diciplinecheck2=1;
      diciplinecheck3=1;
   }
   disposeGame(gnt);
} //Needs checking once functional

void makeActiontests(void){
   int disciplinesdt[] = DEFAULT_DISCIPLINES;
   int dicedt[] = DEFAULT_DICE;
   
   //test arc actions - currently not player specific
   Game gat =newGame (disciplines, dice);

   int playeronecheck=0;
   int playertwocheck=0;
   int playerthreecheck=0;
   int totalarcs=0;
   int totalarcsafter=0;

   playeronecheck=getARCs(gat,UNI_A);
   playertwocheck=getARCs(gat,UNI_B);
   playerthreecheck=getARCs(gat,UNI_C);
   totalarcs=playerthreecheck+playertwocheck+playeronecheck;
   
   assert(totalarcs==0);
   throwDice(gat,1);
   makeAction(gat,OBTAIN_ARC);
  
   playeronecheck=getARCs(gat,UNI_A);
   playertwocheck=getARCs(gat,UNI_B);
   playerthreecheck=getARCs(gat,UNI_C);
   totalarcsafter=playerthreecheck+playertwocheck+playeronecheck;
   assert((totalarcs+1)==totalarcsafter);

   disposeGame(gat);

   //test campus build actions
   Game gat2 = newGame(disciplines, dice); //start new game just to be sure

   int player1checkC=0;
   int player2checkC=0;
   int player3checkC=0;
   int totalcampus=0;
   int totalcampusafter=0;

   player1checkC=getCampuses(gat2,UNI_A);
   player2checkC=getCampuses(gat2,UNI_B);
   player3checkC=getCampuses(gat2,UNI_C);
   totalcampus=player1checkC+player2checkC+player3checkC;

   assert(totalcampus==0);
   throwDice(gat2,1);
   makeAction(gat,BUILD_CAMPUS);

   player1checkC=getCampuses(gat2,UNI_A);
   player2checkC=getCampuses(gat2,UNI_B);
   player3checkC=getCampuses(gat2,UNI_C);
   totalcampusafter=player1checkC+player2checkC+player3checkC;

   assert((totalcampus+1)==totalcampusafter);  
} //currently not player specific tests

void getDisciplinetests(void){
   int disciplinesdt[] = DEFAULT_DISCIPLINES;
   int dicedt[] = DEFAULT_DICE;
   Game gdt =newGame (disciplines, dice);

   //check that it can read the given arrays
   int dt=0;
   while (dt<=NUM_REGIONS){
      assert(getDiscipline(gdt,diciplinesdt[dt])==diciplinesdt[dt]);
      dt++;
   }
} //can be elaborated on for more thorough testing

void getStudentstest(void){
   int disciplines[] = DEFAULT_DISCIPLINES;
   int dice[] = DEFAULT_DICE;
   Game gst =newGame (disciplines, dice);

   //check if the function gets students at all
   int playery=UNI_A;
   int diciplinecheckstu=STUDENT_THD;
   while (playery<=UNI_C){
      while(diciplinecheckstu<=STUDENT_MMONEY){
         assert(getStudents(gst,playery,diciplinecheckstu)>=0);
         diciplinecheckstu++;
      }
      playery++;
   }

   //find way to generate data to test this on
   disposeGame(gst);
} //only tests for zeros at the moment

void isLegalActiontests(void){

}

void getExchangeRatetests(void){

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
cannot go back on first arc road

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
