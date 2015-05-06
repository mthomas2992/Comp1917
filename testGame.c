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
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ,
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV,
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN,
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ,
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

//void bryanstests(void);
//void Joerickstests(void);

void testdisposeGame(void);
void testgetDiceValue(void);
void testgetMostARCs(void);
void testgetMostPublications(void);
void testgetTurnNumber(void);

void testThrowdice(void);
void testgetCampus(void);
void testgetARC(void);
void testgetWhoseTurn(void);
void testgetPublications(void);

//void getExchangeRatetests(void);
void isLegalActiontests(void);
void getStudentstest(void);
void makeActiontests(void);
void getDisciplinetests(void);
void newGametests(void);

void testGetKPIpoints (void); 
//void testGetARCs (void); 
//void testGetGO8s (void); 
//void testGetCampuses (void); 
//void testGetIPs (void); 


int main (int argc, char *argv[]) {
	//add your tests for your section in here, 
	//bryanstests();
   
   // Bryan's tests
   testdisposeGame();
   testgetDiceValue();
   testgetMostARCs();
   testgetMostPublications();
   testgetTurnNumber();

   // Joerick's tests
   testThrowdice();
   testgetCampus();
   testgetARC();
   testgetWhoseTurn();
   testgetPublications();

   newGametests();
   makeActiontests();
   getDisciplinetests();
   getStudentstest();
   isLegalActiontests();

   testGetKPIpoints();
   //testGetARCs();
   //testGetGO8s();
   //testGetCampuses();
   //testGetIPs();
   
	return EXIT_SUCCESS;
	
}

//disposeGame
void testdisposeGame(void){   
   printf("Testing disposeGame\n");
   Game test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
   disposeGame(g);
   assert(test == NULL);
   printf("disposeGame passed!\n");
}
   
//getDiceValue 
void testgetDiceValue(void){ 
   printf("Testing getDiceValue\n");
   Game test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);

   assert(getDiceValue(test,7) == STUDENT_THD);
   assert(getDiceValue(test,12) == STUDENT_MMONEY);
   assert(getDiceValue(test,11) == STUDENT_MTV);
   assert(getDiceValue(test,5) == STUDENT_BPS);
   assert(getDiceValue(test,9) == STUDENT_MJ);
   assert(getDiceValue(test,10) == STUDENT_BQN);
   
   disposeGame(test);
   printf("getDiceValue passed!\n");
}

//getMostARCs
void testgetMostARCs(void){
   printf("Testing getMostARCs\n");
   Game test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
   assert(getMostARCs = NO_ONE);

   throwdice(test,DEFAULT_DICE[0]);
   action getARC;
   getARC.actionCode = OBTAIN_ARC;
   getARC.destination = "R";
   makeAction(test,getARC);
   assert(getMostARCs(test) = UNI_A);

   throwdice(test,DEFAULT_DICE[1]);
   action getARC;
   getARC.actionCode = OBTAIN_ARC;
   getARC.destination = "RRLRL";
   makeAction(test,getARC);
   /* I'm not sure what happens if two universities have
      the same amount of ARC grants */
   assert(getMostARCs(test) == NO_ONE);
   disposeGame(g);
   printf("getMostArcs passed!\n");
}
      
//getMostPublications
void testgetMostPublications(void){
   printf("Testing getMostPublications\n");
   Game test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
   assert(getMostPublications(test) == NO_ONE);
   
   throwDice(test,DEFAULT_DICE[0]);
   makeAction(test,obtain_publication);
   assert(getMostPublications(test) == UNI_A);
   
   throwDice(test,DEFAULT_DICE[1]);
   makeAction(test,obtain_publication);
   /* Again, I'm not sure what happens when two or more
      players have the same amount of publications */
   assert(getMostPublications(test) == NO_ONE);
   
   throwDice(test,DEFAULT_DICE[2]);
   makeAction(test,obtain_publication);
   
   throwDice(test,DEFAULT_DICE[3]);
   makeAction(test,obtain_publication);
   assert(getMostPublications(test) == UNI_A);

   disposeGame(test);
   printf("getMostPublications passed!\n");
}

//getTurnNumber
void testgetTurnNumber(void){
   printf("Testing getTurnNumber\n");
   Game test = newGame (DEFAULT_DISCIPLINES,DEFAULT_DICE);
   assert(getTurnNumber(g) == -1);
   
   throwDice(test,DEFAULT_DICE[0]);
   makeAction(test,obtain_publication);
   assert(getTurnNumber(test) == 0);
   
   throwDice(test,DEFAULT_DICE[1]);
   makeAction(test,obtain_publication);
   assert(getTurnNumber(test) == 1);

   throwDice(test,DEFAULT_DICE[2]);
   makeAction(test,obtain_publication);
   assert(getTurnNumber(test) == 2);

   throwDice(test,DEFAULT_DICE[3]);
   makeAction(test,obtain_publication);
   assert(getTurnNumber(test) == 3);

   disposeGame(test);
   printf("getTurnNumber passed!\n");
}

//throwDice
void testThrowdice(void){
   printf("Testing throwDice\n");
   Game test;
   test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
   
   assert(getTurnNumber(test) == -1);
   
   throwDice(test,DEFAULT_DICE[0]);
   assert(DEFAULT_DICE[0] >= MIN_DICE_VALUE);
   assert(DEFAULT_DICE[0] <= MAX_DICE_VALUE);
   assert(getTurnNumber(test) == 0);

   throwDice(test,DEFAULT_DICE[1]);
   assert(DEFAULT_DICE[1] >= MIN_DICE_VALUE);
   assert(DEFAULT_DICE[1] <= MAX_DICE_VALUE);
   assert(getTurnNumber(test) == 1);

   throwDice(test,DEFAULT_DICE[2]);
   assert(DEFAULT_DICE[2] >= MIN_DICE_VALUE);
   assert(DEFAULT_DICE[2] <= MAX_DICE_VALUE);
   assert(getTurnNumber(test) == 2);

   throwDice(test,DEFAULT_DICE[3]);
   assert(DEFAULT_DICE[3] >= MIN_DICE_VALUE);
    assert(DEFAULT_DICE[3] <= MAX_DICE_VALUE);
   assert(getTurnNumber(test) == 3);

   throwDice(test,DEFAULT_DICE[4]);
   assert(DEFAULT_DICE[4] >= MIN_DICE_VALUE);
    assert(DEFAULT_DICE[4] <= MAX_DICE_VALUE);
   assert(getTurnNumber(test) == 4);

   throwDice(test,DEFAULT_DICE[5]);
   assert(DEFAULT_DICE[5] >= MIN_DICE_VALUE);
    assert(DEFAULT_DICE[5] <= MAX_DICE_VALUE);
   assert(getTurnNumber(test) == 5);

   throwDice(test,DEFAULT_DICE[6]);
   assert(DEFAULT_DICE[6] >= MIN_DICE_VALUE);
    assert(DEFAULT_DICE[6] <= MAX_DICE_VALUE);
   assert(getTurnNumber(test) == 6);

   throwDice(test,DEFAULT_DICE[7]);
   assert(DEFAULT_DICE[7] >= MIN_DICE_VALUE);
    assert(DEFAULT_DICE[7] <= MAX_DICE_VALUE);
   assert(getTurnNumber(test) == 7);
   
   disposeGame(test);
   printf("throwDice Tests passed\n");

//getCampus
void testgetCampus(void){
   printf("Testing getCampus\n");
   Game test;
   test = newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
   
   action obtain_campus;
   obtain_campus.actionCode = BUILD_CAMPUS;
   assert(sizeof(pathtoVertex) <= PATH_LIMIT);
   
   obtain_campus.destination = "RLLLLLL";
   assert(getCampus(test,obtain_campus.destination) == CAMPUS_A);
   
   obtain_campus.destination = "L";
   assert(getCampus(test,obtain_campus.destination) == VACANT_VERTEX);
   
   obtain_campus.destination = "R";
   assert(getCampus(test,obtain_campus.destination) == VACANT_VERTEX);
   
   obtain_campus.destination = "LRLRL";
   assert(getCampus(test,obtain_campus.destination) == CAMPUS_C);
   
   obtain_campus.destination = "RRLRL";
   assert(getCampus(test,obtain_campus.destination) == CAMPUS_B);
   
   obtain_campus.destination = "RLRLRLRRLR";
   assert(getCampus(test,obtain_campus.destination) == CAMPUS_C);
   
   obtain_campus.destination = "RLRLRLRLLRR";
   assert(getCampus(test,obtain_campus.destination) == CAMPUS_A);
   
   obtain_campus.destination = "LRRLRLRLLLRR";
   assert(getCampus(test,obtain_campus.destination) == CAMPUS_B);
   
   obtain_campus.destination = "RLRLRL";
   assert(getCampus(test,obtain_campus.destination) == VACANT_VERTEX);
   
   obtain_campus.destination = "RLRLRLLLRR";
   assert(getCampus(test,obtain_campus.destination) == VACANT_VERTEX);
   disposeGame(test);
   printf("getCampus Tests passed\n");
}

//getARC
void testgetARC(void){
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
}

//getWhoseTurn
void testgetWhoseTurn(void){
   printf("Testing getWhoseTurn\n");
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
}

//getPublications
void testgetPublications(void){
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
}

//Matts tests
void newGametests(void){
   int disciplinesgt[] = DEFAULT_DISCIPLINES;
   int dicegt[] = DEFAULT_DICE;
   Game gnt =newGame (disciplinesgt, dicegt);
   
   //ensure starting values are completley empty
   assert(getMostARCs(gnt)==0);
   assert(getMostPublications(gnt)==0);
   assert(getTurnNumber(gnt)==-1); // first turn is identified as -1
   assert(getWhoseTurn(gnt)==NO_ONE);

   //check that each player is at the initial for all their values
   int playerx=UNI_A;
   int diciplinecheck=STUDENT_THD;
   while (playerx<=UNI_C){
      assert(getKPIpoints(gnt,playerx)==20);
      assert(getARCs(gnt,playerx)==0);
      assert(getGO8s(gnt,playerx)==0);
      assert(getCampuses(gnt,playerx)==2);
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

   //Vertex generator/checker VERY VERY VERY DODGY ONLY CHECKS CONSTANT LEFTS COMMENTED OUT DUE TO POSSIBLE EXTREME LOGIC ERRORS
   /*int pathcount=0;
   path pathtest;  //unsure about syntax
   while (pathcount<PATH_LIMIT){
      pathtest[pathcount]='L';
      assert(getCampus(gnt,pathtest)==VACANT_VERTEX);
      pathcount++
   }*/

   //check exchange rate for all players
   int diciplinecheck2=1;
   int diciplinecheck3=1;
   playerx=UNI_A;
   while (playerx<=UNI_C){
      while(diciplinecheck2<=STUDENT_MMONEY){
         while(diciplinecheck3<=STUDENT_MMONEY){
            assert(getExchangeRate(gnt,playerx,diciplinecheck2,diciplinecheck3)==3); //assumes default exchange rate is 3
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
} //Needs checking once functional add getwhose turn test CHECKED

void makeActiontests(void){
   int disciplinesat[] = DEFAULT_DISCIPLINES;
   int diceat[] = DEFAULT_DICE;
   
   //test arc actions - currently not player specific
   Game gat =newGame (disciplinesat, diceat);

   int playeronecheck=0;
   int playertwocheck=0;
   int playerthreecheck=0;
   int totalarcs=0;
   int totalarcsafter=0;

   playeronecheck=getARCs(gat,UNI_A);
   playertwocheck=getARCs(gat,UNI_B);
   playerthreecheck=getARCs(gat,UNI_C);
   totalarcs=playerthreecheck+playertwocheck+playeronecheck;
   
   assert(totalarcs==0); //check no one has started with more arcs, double checked in newGametests
   throwDice(gat,1); //advance the game once
   
   action attest1; // create an action to obtain an arc
   attest1.actionCode=OBTAIN_ARC;
   attest1.destination='L';
   makeAction(gat,attest1); //makes action, assuming that this is for player one otherwise assert will fail, no idea to know if this is right
  
   playeronecheck=getARCs(gat,UNI_A); //after action checks all players for obtained arcs, don't really need to recheck 2 and 3 at all in this function but do so anyway as error trap
   playertwocheck=getARCs(gat,UNI_B);
   playerthreecheck=getARCs(gat,UNI_C);
   totalarcsafter=playerthreecheck+playertwocheck+playeronecheck; //determine total arcs, which should be one higher
   assert((totalarcs+1)==totalarcsafter); //perform assert

   //chuck on an extra pass test
   int turn1 = getWhoseTurn(gat);
   action attest3;
   attest3.actionCode=PASS;
   makeAction(gat,attest3);
   int turn2= getWhoseTurn(gat);
   if (turn1=UNI_C){
      assert(turn2==UNI_A);
   } else {
      assert((turn1+1)==turn2);
   }


   //test campus build actions CURRENTLY COMMENTED OUT AS CANNOT BUILD CAMPUS WITHOUT ARC ROAD
   /*Game gat2 = newGame(disciplinesat, diceat); //start new game just to be sure

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
   action attest2;
   attest2.actionCode=BUILD_CAMPUS;
   attest2.destination='LR';
   makeAction(gat,attest2);

   player1checkC=getCampuses(gat2,UNI_A);
   player2checkC=getCampuses(gat2,UNI_B);
   player3checkC=getCampuses(gat2,UNI_C);
   totalcampusafter=player1checkC+player2checkC+player3checkC;

   assert((totalcampus+1)==totalcampusafter);  */
} //currently not player specific tests, fairly broad but checked in other functions CHECKED

void getDisciplinetests(void){
   int disciplinesdt[] = DEFAULT_DISCIPLINES;
   int dicedt[] = DEFAULT_DICE;
   Game gdt =newGame (disciplinesdt, dicedt);

   //check that it can read the given arrays
   int dt=0;
   while (dt<=NUM_REGIONS){
      assert(getDiscipline(gdt,diciplinesdt[dt])==diciplinesdt[dt]);
      dt++;
   }
   disposeGame(gdt);

   //Test with different board
   int disciplinesdt2[]={STUDENT_MMONEY, STUDENT_MJ, STUDENT_MTV,
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV,
                STUDENT_MTV, STUDENT_THD,STUDENT_BPS, STUDENT_BQN,
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ,
                STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   
   Game gdt2 =newGame (disciplinesdt2, dicedt);
   dt=0;
   while (dt<=NUM_REGIONS){
      assert(getDiscipline(gdt2,diciplinesdt2[dt])==diciplinesdt2[dt]);
      dt++;
   }

} //can be elaborated on for more thorough testing CHECKED

void getStudentstest(void){
   int disciplinesst[] = DEFAULT_DISCIPLINES;
   int dicest[] = DEFAULT_DICE;
   Game gst =newGame (disciplinesst, dicest);

   //Already partially checked in newGameTests when its values are at the initial
   //Check after conversion due to 7 rolled
   throwDice(gst,7);
   int playerz=UNI_A;
   int disciplinecount=0;

   while (playerz<=UNI_C){
      while (disciplinecount<=STUDENT_MMONEY){
         if ((disciplinecount==STUDENT_MMONEY)||(disciplinecount==STUDENT_MTV)){
            assert(getStudents(gst,playerz,disciplinecount)==0);
         } else if (disciplinecount==STUDENT_THD){
            assert(getStudents(gst,playerz,disciplinecount)==2);
         } else if ((disciplinecount==STUDENT_BPS)||(disciplinecount==STUDENT_BQN)){
            assert(getStudents(gst,playerz,disciplinecount)==3);
         } else {
            assert(getStudents(gst,playerz,disciplinecount)==1);
         }
         disciplinecount++;
      }
      playerz++;
      disciplinecount=0;
   }


   //find way to generate data to test this on
   disposeGame(gst);
} //limited in tests CHECKED

void isLegalActiontests(void){
   int disciplinesla[] = DEFAULT_DISCIPLINES;
   int dicela[] = DEFAULT_DICE;
   Game gla =newGame (disciplinesla, dicela);
   throwDice(gla,1);
   
   //test arc legals
   action testa;
   testa.actionCode=OBTAIN_ARC;
   testa.destination="BLRRL";

   action testb;
   testb.actionCode=OBTAIN_ARC;
   testb.destination="LLLLLLLLLLLLLLLLRRRRLRLRLL";

   action testc; //possible error here
   testc.actionCode=OBTAIN_ARC;
   testc.destination='L';

   assert(isLegalAction(gla,testa)==FALSE);
   assert(isLegalAction(gla,testb)==FALSE);
   assert(isLegalAction(gla,testc)==TRUE);

   //test retrain legals
   action testd;
   testd.actionCode=RETRAIN_STUDENTS;
   testd.disciplineFrom=STUDENT_THD;
   testd.disciplineTo=STUDENT_MMONEY;

   action teste;
   teste.actionCode=RETRAIN_STUDENTS;
   teste.disciplineFrom=STUDENT_BPS;
   teste.disciplineTo=STUDENT_MMONEY;

   action testf;
   testf.actionCode=RETRAIN_STUDENTS;
   testf.disciplineFrom=STUDENT_MTV;
   testf.disciplineTo=STUDENT_MMONEY;

   assert(isLegalAction(gla,testd)==FALSE);
   assert(isLegalAction(gla,teste)==TRUE);
   assert(isLegalAction(gla,testf)==FALSE);

   //test campus building NEEDS TESTS WHERE IT RETURNS FALSE

   action testg;
   testg.actionCode=BUILD_CAMPUS;
   testg.destination="LRRL";

   action testh;
   testh.actionCode=BUILD_CAMPUS;
   testh.destination="BLR";

   assert(isLegalAction(gla,testg)==FALSE);
   assert(isLegalAction(gla,testh)==FALSE);
   disposeGame(gla);
} //CHECKED

//void getExchangeRatetests(void){
   //intially already checked in newGametests function
   //therefore this function needs to check if this works after a retrain center is used? But how to know if a retrain center is connected

//}

//Inputs: Game g, int player
void testGetKPIpoints (void){
   // return the number of ARC grants the specified player currently has
   Game g = newGame (DEFAULT_DISCIPLINES, DEFAULT_DICE);

   assert (getKPIpoints (g, UNI_A) == 20);
   assert (getKPIpoints (g, UNI_B) == 20);
   assert (getKPIpoints (g, UNI_C) == 20);

   disposeGame(g);
}
//Inputs: Game g, int player
/*void testGetARCs (void){

} 
//Inputs: Game g, int player
void testGetGO8s (void){

}
//Inputs: Game g, int player
void testGetCampuses (void){

}
//Inputs: Game g, int player
void testGetIPs (void){

}
*/

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
