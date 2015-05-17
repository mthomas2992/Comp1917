#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "Game.h"

#define INVALID 20

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define IP_GAIN 1
#define PUB_GAIN 2

#define DEFAULT_EXCHANGE 3
#define RETRAIN_EXCHANGE 2

#define DEFAULT_DISCIPLINES {2, 5, 3,\
                5, 3, 1, 4,\
                4, 1,4, 2,\
                3, 2, 0, 3,\
                5, 4, 2, 1}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
//type def struct for arc coords to return
typedef struct _coords {
   int x;
   int y;
} coords;

typedef struct _regions {
   int a;
   int b;
   int c;
} regions;

typedef struct _students {
   int THD;
   int BPS;
   int BQN;
   int MJ;
   int MTV;
   int MMONEY;
} students;

typedef struct _player {
   int KPI;
   int arcs;
   int GO8s;
   int Campuses;
   int IPs;
   int Pubs;
   students students;
} player;

typedef struct _game {
   int turncount;
   int whoseTurn;
   player player1;
   player player2;
   player player3;
   int mostpubs;
   int mostarcs;
   int regions[NUM_REGIONS]; //this stores the discipline
   int regionid[NUM_REGIONS]; //this stores the dice value of the region
   //going to need 2 2d int arrays to store both the arc and campus array
   int arcarray [5][10];
   int campusarray [5][10];
   regions regionarray[5][10];
} game;

void addStudent (Game g, int student, int player, int amount);
coords translatepath(path arc);

int main (int argc, char *argv[]) {
   printf("compiled\n");
   printf("testing\n");
   coords coord;
   coord.x=0;
   coord.y=0;
   coord=translatepath("LR");
   printf("x %d y %d\n",coord.x,coord.y);

   int disciplines[] = DEFAULT_DISCIPLINES;
   int dice[] = DEFAULT_DICE;
   Game test = newGame(disciplines,dice);
   assert(getMostARCs(test) == NO_ONE);
   assert(getTurnNumber(test) == -1);
   assert(getDiceValue(test,7) == STUDENT_THD);

   return EXIT_SUCCESS;
}
//int makeActionipubs (int action);

/*int main (int argc, char *argv[]) {

    //I like commenting Get used to it.
    //I don't actually know whats meant to go in our mainline really...

   return EXIT_SUCCESS;
}*/
Game newGame (int discipline[], int dice[]){
   Game g=malloc(sizeof(game)); //check this is malloced right
   g->mostarcs=NO_ONE;
   g->mostpubs=NO_ONE;
   g->turncount=-1; //terra nullius
   g->whoseTurn=NO_ONE; //terra nullius

   int i=0;
   while(i<NUM_REGIONS){ //input board into struct, might be better in a 2D array
      g->regions[i]=discipline[i];
      g->regionid[i]=dice[i];
      i++;
   }
   //initialise the game board with invalids also
   i=0;
   int z=0;
   regions r;
   r.a=INVALID;
   r.b=INVALID;
   r.c=INVALID;
   while (i<=5){ //this initialises on the y axis traverse rather then x, should be fine though
      while (z<=10){
         g->regionarray[i][z]=r;
         if ((z+i>=2)&&(z+i<=13)){ //corners of the array that should be invalid add to these numbers
            g->arcarray[i][z]=VACANT_ARC;
            g->campusarray[i][z]=VACANT_VERTEX;
         } else { //doesn't catch all the invalids, rest hardcoded
            g->arcarray[i][z]=INVALID;
            g->campusarray[i][z]=INVALID;
         }
         z++;
      }
      i++;
      z=0;
   }

   //need to intialise hardcoded array
   r.c=0;
   g->regionarray[0][2]=r;
   g->regionarray[0][3]=r;

   r.a=0;
   r.b=1;
   r.c=INVALID;
   g->regionarray[0][4]=r;
   g->regionarray[0][5]=r;

   r.a=1;
   r.b=2;
   r.c=INVALID;
   g->regionarray[0][6]=r;
   g->regionarray[0][7]=r;

   r.a=INVALID;
   g->regionarray[0][8]=r;

   r.b=3;
   g->regionarray[1][1]=r;

   r.a=0;
   g->regionarray[1][2]=r;

   r.c=4;
   g->regionarray[1][3]=r;

   r.b=1;
   g->regionarray[1][4]=r;

   r.a=5;
   g->regionarray[1][5]=r;

   r.c=2;
   g->regionarray[1][6]=r;

   r.b=6;
   g->regionarray[1][7]=r;

   r.a=INVALID;
   g->regionarray[1][8]=r;

   r.c=INVALID;
   g->regionarray[1][9]=r;

   r.a=INVALID;
   r.b=INVALID;
   r.c=7;
   g->regionarray[2][0]=r;

   r.a=3;
   g->regionarray[2][1]=r;

   r.b=8;
   g->regionarray[2][2]=r;

   r.c=4;
   g->regionarray[2][3]=r;

   r.a=9;
   g->regionarray[2][4]=r;

   r.b=5;
   g->regionarray[2][5]=r;

   r.c=10;
   g->regionarray[2][6]=r;

   r.a=6;
   g->regionarray[2][7]=r;

   r.b=11;
   g->regionarray[2][8]=r;

   r.c=INVALID;
   g->regionarray[2][9]=r;

   r.a=INVALID;
   g->regionarray[2][10]=r;

   r.b=7;
   g->regionarray[3][0]=r;

   r.c=12;
   g->regionarray[3][1]=r;

   r.a=8;
   g->regionarray[3][2]=r;

   r.b=13;
   g->regionarray[3][3]=r;

   r.c=9;
   g->regionarray[3][4]=r;

   r.a=14;
   g->regionarray[3][5]=r;

   r.b=10;
   g->regionarray[3][6]=r;

   r.c=15;
   g->regionarray[3][7]=r;

   r.a=11;
   g->regionarray[3][8]=r;

   r.b=INVALID;
   g->regionarray[3][9]=r;

   r.c=INVALID;
   g->regionarray[3][10]=r;

   r.a=12;
   g->regionarray[4][1]=r;

   r.b=16;
   g->regionarray[4][2]=r;

   r.c=13;
   g->regionarray[4][3]=r;

   r.a=17;
   g->regionarray[4][4]=r;

   r.b=14;
   g->regionarray[4][5]=r;

   r.c=18;
   g->regionarray[4][6]=r;

   r.a=15;
   g->regionarray[4][7]=r;

   r.b=INVALID;
   g->regionarray[4][8]=r;

   r.c=INVALID;
   g->regionarray[4][9]=r;

   r.a=16;
   g->regionarray[5][2]=r;
   g->regionarray[5][3]=r;

   r.b=17;
   g->regionarray[5][4]=r;

   r.a=INVALID;
   g->regionarray[5][5]=r;

   r.a=18;
   g->regionarray[5][6]=r;

   r.b=INVALID;
   g->regionarray[5][7]=r;
   g->regionarray[5][8]=r;

   //specify missed invalids
   g->arcarray[4][0]=INVALID;
   g->arcarray[5][0]=INVALID;
   g->arcarray[5][1]=INVALID;
   g->arcarray[0][9]=INVALID;
   g->arcarray[0][10]=INVALID;
   g->arcarray[1][10]=INVALID;

   g->campusarray[4][0]=INVALID;
   g->campusarray[5][0]=INVALID;
   g->campusarray[5][1]=INVALID;
   g->campusarray[0][9]=INVALID;
   g->campusarray[0][10]=INVALID;
   g->campusarray[1][10]=INVALID;

   //player one 
   g->player1.KPI=20;
   g->player1.arcs=0;
   g->player1.GO8s=0;
   g->player1.Campuses=2;
   g->player1.IPs=0;
   g->player1.Pubs=0;
   g->player1.students.THD=0;
   g->player1.students.BPS=3;
   g->player1.students.BQN=3;
   g->player1.students.MJ=0;
   g->player1.students.MTV=0;
   g->player1.students.MMONEY=0;

   //player two
   g->player2.KPI=20;
   g->player2.arcs=0;
   g->player2.GO8s=0;
   g->player2.Campuses=2;
   g->player2.IPs=0;
   g->player2.Pubs=0;
   g->player2.students.THD=0;
   g->player2.students.BPS=3;
   g->player2.students.BQN=3;
   g->player2.students.MJ=0;
   g->player2.students.MTV=0;
   g->player2.students.MMONEY=0;

   //player three
   g->player3.KPI=20;
   g->player3.arcs=0;
   g->player3.GO8s=0;
   g->player3.Campuses=2;
   g->player3.IPs=0;
   g->player3.Pubs=0;
   g->player3.students.THD=0;
   g->player3.students.BPS=3;
   g->player3.students.BQN=3;
   g->player3.students.MJ=0;
   g->player3.students.MTV=0;
   g->player3.students.MMONEY=0;

   return g;
}

void disposeGame (Game g){
   free(g);
}

coords translatepath(path arc){
   //needs a response for if the path is empty
   int prevycoords=0;
   coords coord;
   int prevxcoords=2;
   int xcoords=2;
   int ycoords=0;
   int leftx=0;
   int lefty=0;
   int rightx=0;
   int righty=0;
   int tempx=0;
   int tempy=0;
   int approach=DOWN;
   int index=0;
   while(arc[index]!=0){
      //determine approach 
      //There is never a possibility of changing both x and y, therefore it isn't accounted for (yeah it should error trap but its our own function)
      if (prevycoords<ycoords||((ycoords==0)&&(index==0))){
         approach=DOWN;
      } else if (prevycoords>ycoords){
         approach=UP;
      } else if (prevxcoords<xcoords){
         approach=RIGHT;
      } else if (prevxcoords>xcoords){
         approach=LEFT;
      }
      //Compressed code, uncompressed found in other file
      if (((approach==DOWN)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2==0))||((approach==DOWN)&&(xcoords%2==1)&&(ycoords%2!=0))){ //EVENS EVENS and ODDS ODDS
         leftx=xcoords+1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==UP)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2==0))||((approach==UP)&&(xcoords%2==1)&&(ycoords%2!=0))){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords+1;
         righty=ycoords;
      } else if (((approach==RIGHT)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2==0))||((approach==RIGHT)&&(xcoords%2==1)&&(ycoords%2!=0))){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==LEFT)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2==0))||((approach==RIGHT)&&(xcoords%2==1)&&(ycoords%2!=0))){
         //avoiding combining the invalid statements as they are so damn long
         leftx=INVALID; //if this happens it should be picked up by the islegalfunction
         lefty=INVALID;
         rightx=INVALID;
         righty=INVALID;
      } else if (((approach==DOWN)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2!=0))||((approach==DOWN)&&(xcoords%2==1)&&(ycoords%2==0))){ //EVENS ODDS
         leftx=xcoords;
         lefty=ycoords+1;
         rightx=xcoords-1;
         righty=ycoords;
      } else if (((approach==UP)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2!=0))||((approach==UP)&&(xcoords%2==1)&&(ycoords%2==0))){
         leftx=xcoords-1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords-1;
      } else if (((approach==RIGHT)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2!=0))||((approach==RIGHT)&&(xcoords%2==1)&&(ycoords%2==0))){
         //not possible DOUBLE CHECK
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==LEFT)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2!=0))||((approach==LEFT)&&(xcoords%2==1)&&(ycoords%2==0))){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } 

      //assuming new coords have been obtained
      if (arc[index]=='L'){
         prevxcoords=xcoords;
         prevycoords=ycoords;
         xcoords=leftx;
         ycoords=lefty;
      } else if (arc[index]=='R'){
         prevxcoords=xcoords;
         prevycoords=ycoords;
         xcoords=rightx;
         ycoords=righty;
      } else if (arc[index]=='B'){
         tempx=xcoords;
         tempy=ycoords;
         xcoords=prevxcoords;
         ycoords=prevycoords;
         prevxcoords=tempx;
         prevycoords=tempy;
      }
      index++;
   }

   coord.x=xcoords;
   coord.y=ycoords;

   return coord;
}

int isLegalAction (Game g, action a){
   int legal=FALSE;
   int x=0; //NEED TO CONSIDER HOW TO ACTUALLY BUILD AN ARC
   int y=0;
   int w=0;
   int player = getWhoseTurn(g);
   coords coord;
   if (a.actionCode==OBTAIN_ARC){ //currently this assumes arcs are like vertex's and their points ARCS REPED BY THE VERTEXS THEY CONNECT
      if ((getStudents(g,player,STUDENT_BPS)>=1)&&(getStudents(g,player,STUDENT_BQN)>=1)&&(a.destination[0]!='B') && sizeof(a.destination)<=PATH_LIMIT){ //gate to ensure sufficient students & valid path
         coord=translatepath(a.destination); //translate action a and return coords in terms of x and y
         x=coord.x;
         y=coord.y;
         if (g->arcarray[x][y]==VACANT_VERTEX){ //SCANS SURROUNDINGS FOR OTHER MATCHING ARCS RETURNS TRUE IF ONE IS FOUND
            if (y!=0){
               w=y-1;
               if (g->arcarray[x][w]==getWhoseTurn(g)){ //REMOVE NEED FOR VALID POINT FUNCTION BY INITIALISING ARRAY TO HAVE AN IMPOSSIBLE VALUE (10) IN THE INVALID POINTS
                  legal=TRUE;
               }
            }
            if (y!=10){
               w=y+1;
               if (g->arcarray[x][w]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            }
            if (((x==3)||(x==1)||(x==5))&&(y%2==0)){ //checks for odd column, even row do some logic testing on these
               w=x-1;
               if (g->arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            } else if (((x==3)||(x==1)||(x==5))&&(y%2!=0)) {
               w=x+1;
               if (g->arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            } else if (((x==0)||(x==2)||(x==4))&&(y%2==0)){
               w=x+1;
               if (g->arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            } else if (((x==0)||(x==2)||(x==4))&&(y%2!=0)){
               w=x-1;
               if (g->arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            }
         }
         //also needs to check if a vacant arc first
      }
   } else if (a.actionCode==RETRAIN_STUDENTS){
      if ((a.disciplineFrom>=getExchangeRate(g,player,a.disciplineFrom,a.disciplineTo)) && (a.disciplineFrom!=STUDENT_THD)){ //checks not THD and above rate
         legal=TRUE;
      }
   } else if (a.actionCode==PASS){
      legal=TRUE;
   } else if (a.actionCode==START_SPINOFF){
      if((getStudents(g,player,STUDENT_MJ)>=1)&&(getStudents(g,player,STUDENT_MTV)>=1)&&(getStudents(g,player,STUDENT_MMONEY)>=1)){
         legal=TRUE;
      }
   } else if (a.actionCode==BUILD_CAMPUS){
      if ((getStudents(g,player,STUDENT_BPS)>=1)&&(getStudents(g,player,STUDENT_BQN)>=1)&&(getStudents(g,player,STUDENT_MJ)>=1)&&(getStudents(g,player,STUDENT_MTV)>=1)&& (getARC(g,a.destination)==player)){ //gate, also uses getARC
         // need to also check no campuses within surounding area using similar scanning technique to arcs
         coord=translatepath(a.destination); //translate given path into 2d array point
         x=coord.x;
         y=coord.y;
         legal=TRUE; //sets to true for proving wrong
         if (y!=0){ //Scans for nearby campus's
            w=y-1;
            if (g->campusarray[x][w]==getWhoseTurn(g)){ //CAN PROBS COMPILE THIS INTO ITS OWN FUNCTION CALLED SCAN WHICH TAKES location, type to scan for and returns true if one is found, false if none.
               legal=FALSE;
            }
         }
         if (y!=10){
            w=y+1;
            if (g->campusarray[x][w]==getWhoseTurn(g)){
               legal=FALSE;
            }
         }
         if (((x==3)||(x==1)||(x==5))&&(y%2==0)){
            w=x-1;
            if (g->campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if (((x==3)||(x==1)||(x==5))&&(y%2!=0)) {
            w=x+1;
            if (g->campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if ((x%2==0)&&(y%2==0)){
            w=x+1;
            if (g->campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if ((x%2==0)&&(y%2!=0)){
            w=x-1;
            if (g->campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         }
      }
   } else if (a.actionCode==BUILD_GO8){
      if ((getStudents(g,player,STUDENT_MJ)>=2)&&(getStudents(g,player,STUDENT_MMONEY)>=3)&&(player==getCampus(g,a.destination))){
         legal=TRUE;
      } //uses getcampus function
   }
   return legal;
}

int getStudents (Game g, int player, int discipline){ //Don't like this code, to bulky for me
   int students=0; //Can be simplified using pointer hack if need be
   if (player==UNI_A){
      if (discipline==STUDENT_THD){
         students=g->player1.students.THD;
      } else if (discipline==STUDENT_BPS){
         students=g->player1.students.BPS;
      } else if (discipline==STUDENT_BQN){
         students=g->player1.students.BQN;
      } else if (discipline==STUDENT_MJ){
         students=g->player1.students.MJ;
      } else if (discipline==STUDENT_MTV){
         students=g->player1.students.MTV;
      } else if (discipline==STUDENT_MMONEY){
         students=g->player1.students.MMONEY;
      }
   } else if (player==UNI_B){
      if (discipline==STUDENT_THD){
         students=g->player2.students.THD;
      } else if (discipline==STUDENT_BPS){
         students=g->player2.students.BPS;
      } else if (discipline==STUDENT_BQN){
         students=g->player2.students.BQN;
      } else if (discipline==STUDENT_MJ){
         students=g->player2.students.MJ;
      } else if (discipline==STUDENT_MTV){
         students=g->player2.students.MTV;
      } else if (discipline==STUDENT_MMONEY){
         students=g->player2.students.MMONEY;
      }
   } else if (player==UNI_C){
      if (discipline==STUDENT_THD){
         students=g->player3.students.THD;
      } else if (discipline==STUDENT_BPS){
         students=g->player3.students.BPS;
      } else if (discipline==STUDENT_BQN){
         students=g->player3.students.BQN;
      } else if (discipline==STUDENT_MJ){
         students=g->player3.students.MJ;
      } else if (discipline==STUDENT_MTV){
         students=g->player3.students.MTV;
      } else if (discipline==STUDENT_MMONEY){
         students=g->player3.students.MMONEY;
      }
   }

   return students;
}

int getARCs(Game g, int player){
   int numOfARCs=0;
   if (player == UNI_A){
      numOfARCs = g->player1.arcs;
   } else if (player == UNI_B){
      numOfARCs = g->player2.arcs;
   } else if (player == UNI_C){
      numOfARCs = g->player3.arcs;
   }
   return numOfARCs;
}

int getCampuses(Game g, int player){
   int numOfCampuses=0;
   if (player == UNI_A){
      numOfCampuses = g->player1.Campuses;
   } else if (player == UNI_B){
      numOfCampuses = g->player2.Campuses;
   } else if (player == UNI_C){
      numOfCampuses = g->player3.Campuses;
   }
   return numOfCampuses;
}

// return the number of Publications the specified player currently has
int getPublications (Game g, int player) {
   int playerPublications = 0;
   if (player == UNI_A) {
      playerPublications = g->player1.Pubs;
   } else if (player == UNI_B) {
      playerPublications = g->player2.Pubs;
   } else if (player == UNI_C) {
      playerPublications = g->player3.Pubs;
   }
   return playerPublications;
}

// return the current turn number of the game -1,0,1, ..
int getTurnNumber (Game g) {
   return g->turncount;
}

// what dice value produces students in the specified region?
// 2..12
int getDiceValue (Game g, int regionID) {
   printf("here2\n");
   int y=regionID;
   int x= g->regions[y];
   return x;
}

// return the number of IP Patents the specified player currently has
int getIPs (Game g, int player) {
   int playerIPs = 0;
   if (player == UNI_A) {
      playerIPs = g->player1.IPs;
   } else if (player == UNI_B) {
      playerIPs = g->player2.IPs;
   } else if (player == UNI_C) {
      playerIPs = g->player3.IPs;
   }
   return playerIPs;
}

// return how many students of discipline type disciplineFrom
// the specified player would need to retrain in order to get one
// student of discipline type disciplineTo.  This will depend
// on what retraining centers, if any, they have a campus at.
int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo) {
   int exchangerate = DEFAULT_EXCHANGE; //checks if campuses are on retrain areas, if they are sets it lower
   if (((getCampus(g,"R") == player) || (getCampus(g,"RR") == player)) && (disciplineFrom == STUDENT_MTV)) {
      exchangerate = RETRAIN_EXCHANGE;
   } else if (((getCampus(g,"LL") == player) || (getCampus(g,"LLL") == player)) && (disciplineFrom == STUDENT_MMONEY)) {
      exchangerate = RETRAIN_EXCHANGE;
   } else if (((getCampus(g,"RRRLRLRLR") == player) || (getCampus(g,"RRRLRLRLRL") == player)) && (disciplineFrom==STUDENT_BPS)) {
      exchangerate = RETRAIN_EXCHANGE;
   } else if (((getCampus(g,"LLLLRLRLRL") == player) || (getCampus(g,"LLLLRLRLRLR") == player)) && (disciplineFrom == STUDENT_MJ)) {
      exchangerate = RETRAIN_EXCHANGE;
   } else if (((getCampus(g,"RRRLRR") == player) || (getCampus(g,"RRRLRRR") == player)) && (disciplineFrom == STUDENT_BQN)){
      exchangerate = RETRAIN_EXCHANGE;
   }
   return exchangerate;
}

void makeAction(Game g, action a){
   int currentPlayer = getWhoseTurn(g);
   if (getWhoseTurn(g)==UNI_A){ //could simplify with pointer hack
      if (isLegalAction(g,a) == TRUE){ //need to add code that modifies structs contents to keep track of player inv
         if (a.actionCode == PASS){
            //throwDice(); //this is apparently called by the interface
         } else if (a.actionCode == BUILD_CAMPUS){
            coords coord1=translatepath(a.destination);
            g->campusarray[coord1.x][coord1.y]=getWhoseTurn(g); //holding back on simplifying to decide on pointer hack
            g->player1.Campuses++;

            g->player1.students.BPS--; //need to subtract values from player
            g->player1.students.BQN--;
            g->player1.students.MJ--;
            g->player1.students.MTV--;
         } else if (a.actionCode == BUILD_GO8){
            coords coord2=translatepath(a.destination);
            g->campusarray[coord2.x][coord2.y]=getWhoseTurn(g)+3;
            g->player1.GO8s++;
            g->player1.Campuses--; 
            g->player1.students.MJ=g->player2.students.MJ-2;
            g->player1.students.MMONEY= g->player2.students.MMONEY-3;
         } else if (a.actionCode == OBTAIN_ARC){
            coords coord3=translatepath(a.destination);
            g->arcarray[coord3.x][coord3.y]=getWhoseTurn(g);
            g->player1.arcs++;
            g->player1.students.BPS--; //need to subtract values from player
            g->player1.students.BQN--;
         } else if (a.actionCode == START_SPINOFF){
            g->player1.students.MJ--;
            g->player1.students.MTV--;
            g->player1.students.MMONEY--;
            srand(time(NULL));
            int Spinoff = rand()%3; //need to check if one must be added
            if (Spinoff == IP_GAIN){
               g->player1.IPs++;
            } else if (Spinoff >= PUB_GAIN){
               g->player1.Pubs++;
            }
         } else if (a.actionCode == RETRAIN_STUDENTS){
            int exchangeRate;
            exchangeRate = getExchangeRate(g, currentPlayer, a.disciplineFrom, a.disciplineTo);
            if (a.disciplineFrom == STUDENT_BPS){ //checks all and modifies all
               g->player1.students.BPS -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_BQN){
               g->player1.students.BQN -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MJ){
               g->player1.students.MJ -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MTV){
               g->player1.students.MTV -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MMONEY){
               g->player1.students.MMONEY -= exchangeRate;
            }

            if (a.disciplineTo == STUDENT_BPS){
               g->player1.students.BPS++;
            } else if (a.disciplineTo == STUDENT_BQN){
               g->player1.students.BQN++;
            } else if (a.disciplineTo == STUDENT_MJ){
               g->player1.students.MJ++;
            } else if (a.disciplineTo == STUDENT_MTV){
               g->player1.students.MTV++;
            } else if (a.disciplineTo == STUDENT_MMONEY){
               g->player1.students.MMONEY++;
            }
         }
      }
   } else if (getWhoseTurn(g)==UNI_B){
      if (isLegalAction(g,a) == TRUE){ //need to add code that modifies structs contents to keep track of player inv
         if (a.actionCode == PASS){
            //throwDice(); //check this do we actually call it or is it called by the interface
         } else if (a.actionCode == BUILD_CAMPUS){
            coords coord1=translatepath(a.destination);
            g->campusarray[coord1.x][coord1.y]=getWhoseTurn(g);
            g->player2.Campuses++;

            g->player2.students.BPS--; //need to subtract values from player
            g->player2.students.BQN--;
            g->player2.students.MJ--;
            g->player2.students.MTV--;
         } else if (a.actionCode == BUILD_GO8){
            coords coord2=translatepath(a.destination);
            g->campusarray[coord2.x][coord2.y]=getWhoseTurn(g)+3;
            g->player2.GO8s++;
            g->player2.Campuses--;

            //2mjs 3 mmonneys
            g->player2.students.MJ=g->player2.students.MJ-2;
            g->player2.students.MMONEY= g->player2.students.MMONEY-3;

         } else if (a.actionCode == OBTAIN_ARC){
            coords coord3=translatepath(a.destination);
            g->arcarray[coord3.x][coord3.y]=getWhoseTurn(g);
            g->player2.arcs++;
            g->player2.students.BPS--; //need to subtract values from player
            g->player2.students.BQN--;
         } else if (a.actionCode == START_SPINOFF){
            g->player2.students.MJ--;
            g->player2.students.MTV--;
            g->player2.students.MMONEY--;
            srand(time(NULL));
            int Spinoff = rand()%3; //need to check if one must be added
            if (Spinoff == IP_GAIN){
               g->player2.IPs++;
            } else if (Spinoff >= PUB_GAIN){
               g->player2.Pubs++;
            }
         } else if (a.actionCode == RETRAIN_STUDENTS){
            int exchangeRate;
            exchangeRate = getExchangeRate(g, currentPlayer, a.disciplineFrom, a.disciplineTo);
            if (a.disciplineFrom == STUDENT_BPS){ //checks all and modifies all
               g->player2.students.BPS -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_BQN){
               g->player2.students.BQN -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MJ){
               g->player2.students.MJ -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MTV){
               g->player2.students.MTV -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MMONEY){
               g->player2.students.MMONEY -= exchangeRate;
            }

            if (a.disciplineTo == STUDENT_BPS){
               g->player2.students.BPS++;
            } else if (a.disciplineTo == STUDENT_BQN){
               g->player2.students.BQN++;
            } else if (a.disciplineTo == STUDENT_MJ){
               g->player2.students.MJ++;
            } else if (a.disciplineTo == STUDENT_MTV){
               g->player2.students.MTV++;
            } else if (a.disciplineTo == STUDENT_MMONEY){
               g->player2.students.MMONEY++;
            }
         }
      }
   } else if (getWhoseTurn(g)==UNI_B){
      if (isLegalAction(g,a) == TRUE){ //need to add code that modifies structs contents to keep track of player inv
         if (a.actionCode == PASS){
            //throwDice(); //check this do we actually call it or is it called by the interface
         } else if (a.actionCode == BUILD_CAMPUS){
            coords coord1=translatepath(a.destination);
            g->campusarray[coord1.x][coord1.y]=getWhoseTurn(g);
            g->player3.Campuses++;

            g->player3.students.BPS--; //need to subtract values from player
            g->player3.students.BQN--;
            g->player3.students.MJ--;
            g->player3.students.MTV--;
         } else if (a.actionCode == BUILD_GO8){
            coords coord2=translatepath(a.destination);
            g->campusarray[coord2.x][coord2.y]=getWhoseTurn(g)+3;
            g->player3.GO8s++;
            g->player3.Campuses--;
            g->player3.students.MJ=g->player2.students.MJ-2;
            g->player3.students.MMONEY= g->player2.students.MMONEY-3;
         } else if (a.actionCode == OBTAIN_ARC){
            coords coord3=translatepath(a.destination);
            g->arcarray[coord3.x][coord3.y]=getWhoseTurn(g);
            g->player3.arcs++;
            g->player3.students.BPS--; //need to subtract values from player
            g->player3.students.BQN--;
         } else if (a.actionCode == START_SPINOFF){
            g->player3.students.MJ--;
            g->player3.students.MTV--;
            g->player3.students.MMONEY--;
            srand(time(NULL));
            int Spinoff = rand()%3; //need to check if one must be added
            if (Spinoff == IP_GAIN){
               g->player3.IPs++;
            } else if (Spinoff >= PUB_GAIN){
               g->player3.Pubs++;
            }
         } else if (a.actionCode == RETRAIN_STUDENTS){
            int exchangeRate;
            exchangeRate = getExchangeRate(g, currentPlayer, a.disciplineFrom, a.disciplineTo);
            if (a.disciplineFrom == STUDENT_BPS){ //checks all and modifies all
               g->player3.students.BPS -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_BQN){
               g->player3.students.BQN -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MJ){
               g->player3.students.MJ -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MTV){
               g->player3.students.MTV -= exchangeRate;
            } else if (a.disciplineFrom == STUDENT_MMONEY){
               g->player3.students.MMONEY -= exchangeRate;
            }

            if (a.disciplineTo == STUDENT_BPS){
               g->player3.students.BPS++;
            } else if (a.disciplineTo == STUDENT_BQN){
               g->player3.students.BQN++;
            } else if (a.disciplineTo == STUDENT_MJ){
               g->player3.students.MJ++;
            } else if (a.disciplineTo == STUDENT_MTV){
               g->player3.students.MTV++;
            } else if (a.disciplineTo == STUDENT_MMONEY){
               g->player3.students.MMONEY++;
            }
         }
      }
   }
}

int getMostPublications(Game g){
   int P1Pubs = g->player1.Pubs;
   int P2Pubs = g->player2.Pubs;
   int P3Pubs = g->player3.Pubs;

   int currentMostPubs = g->mostpubs;
   int mostPubsLocal = NO_ONE;

   if ((P1Pubs == 0)&&(P2Pubs == 0)&&(P3Pubs == 0)){
      mostPubsLocal = NO_ONE;
   }

   if ((P1Pubs) > (P2Pubs)) {
   //Here we know player1.Pubs > player2.Pubs
      if((P1Pubs) > (P3Pubs)){
         mostPubsLocal = UNI_A;
      }else if((P1Pubs) == (P3Pubs)){
         mostPubsLocal = currentMostPubs;
      }else{
         mostPubsLocal = UNI_C;
      }
   //Here we know player2.Pubs >= player1.Pubs
   } else if(P1Pubs == P2Pubs){
      mostPubsLocal = currentMostPubs;
   } else if((P2Pubs) > (P3Pubs)){
      mostPubsLocal = UNI_B;
   } else if((P2Pubs) == (P3Pubs)){
      mostPubsLocal = currentMostPubs;
   } else{
      mostPubsLocal = UNI_C;
   }
   return mostPubsLocal;
}

int getWhoseTurn(Game g){
   /* Last Edit: CBennetts 12/5/15
   Someone make sure to check this works, it seems too simple
   */
   //int turnCountLocal = g->turncount;
   //int whoseTurn = ((turnCountLocal)%(NUM_UNIS)) + 1;
   //Its even simpler with our game struct
   return g->whoseTurn;
}

int getCampus (Game g, path pathToVertex){
   coords coord;
   coord=translatepath(pathToVertex);
   return g->campusarray[coord.x][coord.y];
}

int getDiscipline (Game g, int regionID){
   return g->regions[regionID];
}

void throwDice (Game g, int diceScore){
   //this needs alot more logic
   g->turncount++;
   g->whoseTurn++;

   if (g->whoseTurn > UNI_C){
       g->whoseTurn = UNI_A;
   }
   int player=getWhoseTurn(g);
   g->mostpubs=getMostPublications(g);
   g->mostarcs=getMostARCs(g);
   regions r;
   // scan through array
   int xindex=0;
   int yindex=0;
   int discipline=INVALID;
   while (xindex<=5){ //check logic
      while(yindex<=10){
         if ((g->campusarray[xindex][yindex]!=VACANT_VERTEX)&&(g->campusarray[xindex][yindex]!=INVALID)){
            r=g->regionarray[xindex][yindex]; //this regions array needs to be written
            if (g->regionid[r.a]==diceScore){
               discipline=g->regions[r.a];
               addStudent(g,discipline,g->campusarray[xindex][yindex],1);
            } else if (g->regionid[r.b]==diceScore){
               discipline=g->regions[r.b];
               addStudent(g,discipline,g->campusarray[xindex][yindex],1);
            } else if (g->regionid[r.c]==diceScore){
               discipline=g->regions[r.c];
               addStudent(g,discipline,g->campusarray[xindex][yindex],1);
            }
         }
         yindex++;
      }
      xindex++;
      yindex=0;
   }

   if (diceScore==7){
      if (player == UNI_A) { //1337 pointer hacking
         g->player1.students.THD=g->player1.students.THD+g->player1.students.MMONEY+g->player1.students.MTV;
         g->player1.students.MMONEY=0;
         g->player1.students.MTV=0;
      } else if (player == UNI_B) {
         g->player2.students.THD=g->player2.students.THD+g->player2.students.MMONEY+g->player2.students.MTV;
         g->player2.students.MMONEY=0;
         g->player2.students.MTV=0;
      } else if (player == UNI_C) {
         g->player3.students.THD=g->player3.students.THD+g->player3.students.MMONEY+g->player3.students.MTV;
         g->player3.students.MMONEY=0;
         g->player3.students.MTV=0;
      }
   }
}

void addStudent (Game g, int student, int player, int amount){
   if (player == UNI_A){
      if (student == STUDENT_THD){
         g->player1.students.THD += amount;
      } else if (student == STUDENT_MMONEY){
         g->player1.students.MMONEY += amount;
      } else if (student == STUDENT_MJ){
         g->player1.students.MJ += amount;
      } else if (student == STUDENT_MTV){
         g->player1.students.MTV += amount;
      } else if (student == STUDENT_BQN){
         g->player1.students.BQN += amount;
      } else if (student == STUDENT_BPS){
         g->player1.students.BPS += amount;
      }
   }
   if (player == UNI_B){
      if (student == STUDENT_THD){
         g->player2.students.THD += amount;
      } else if (student == STUDENT_MMONEY){
         g->player2.students.MMONEY += amount;
      } else if (student == STUDENT_MJ){
         g->player2.students.MJ += amount;
      } else if (student == STUDENT_MTV){
         g->player2.students.MTV += amount;
      } else if (student == STUDENT_BQN){
         g->player2.students.BQN += amount;
      } else if (student == STUDENT_BPS){
         g->player2.students.BPS += amount;
      }
   }
   if (player == UNI_C){
      if (student == STUDENT_THD){
         g->player3.students.THD += amount;
      } else if (student == STUDENT_MMONEY){
         g->player3.students.MMONEY += amount;
      } else if (student == STUDENT_MJ){
         g->player3.students.MJ += amount;
      } else if (student == STUDENT_MTV){
         g->player3.students.MTV += amount;
      } else if (student == STUDENT_BQN){
         g->player3.students.BQN += amount;
      } else if (student == STUDENT_BPS){
         g->player3.students.BPS += amount;
      }
   }
}

int getARC(Game g, path pathToEdge){
   coords coord;
   coord=translatepath(pathToEdge);
   return g->arcarray[coord.x][coord.y];
}

int getGO8s (Game g, int player){
   int returnVal=INVALID;
   if (player == UNI_A){
    returnVal = g->player1.GO8s;
   } else if(player == UNI_B){
    returnVal = g->player2.GO8s;
   } else if(player == UNI_C){
    returnVal = g->player3.GO8s;
   }
   return returnVal;

}

int getKPIpoints (Game g, int player){
   int returnVal=0;
   //int playerindex=UNI_A;
   //10 kpi for campus
   //20 kpi for go8
   //2 kpi per arc
   // 10 kpi for most arcs
   //10 kpi for most pubs
   //10 kpi for IP's
   //therefore (lol I am acting like this is some kind of discrete maths proof)
   //Simplifying this into a function that only operates on one player
   returnVal=returnVal+10*getCampuses(g,player);
   returnVal=returnVal+20*getGO8s(g,player);
   returnVal=returnVal+2*getARCs(g,player);
   if (getMostPublications(g)==player){
      returnVal=returnVal+10;
   }
   if (getMostARCs(g)==player){
      returnVal=returnVal+10;
   }
   returnVal=returnVal+10*getIPs(g,player);
   int playerindex=getWhoseTurn(g);
   if (playerindex==UNI_A){
      g->player1.KPI=returnVal;
   } else if (playerindex==UNI_B){
      g->player2.KPI=returnVal;
   } else if (playerindex==UNI_C){
      g->player3.KPI=returnVal;
   }
   returnVal=0;
   return returnVal;
}

int getMostARCs (Game g){
   int p1Arcs = g->player1.arcs;
   int p2Arcs = g->player2.arcs;
   int p3Arcs = g->player3.arcs;

   int currentMostArcs = g->mostarcs;
   int mostArcsLocal = NO_ONE;

   if((p1Arcs == 0)&&(p2Arcs == 0)&&(p3Arcs == 0)){
      mostArcsLocal = NO_ONE;
   }

   if((p1Arcs) > (p2Arcs)){
   //Here we know player1.Pubs > player2.Pubs
      if((p2Arcs) > (p3Arcs)){
         mostArcsLocal = UNI_A;
      } else if((p1Arcs) == (p3Arcs)){
         mostArcsLocal = currentMostArcs;
      } else {
         mostArcsLocal = UNI_C;
      }
   //Here we know player2.Pubs >= player1.Pubs
   } else if (p1Arcs == p2Arcs) {
      mostArcsLocal = currentMostArcs;
   } else if ((p2Arcs) > (p3Arcs)){
      mostArcsLocal = UNI_B;
   } else if ((p2Arcs) == (p3Arcs)){
      mostArcsLocal = currentMostArcs;
   } else {
      mostArcsLocal = UNI_C;
   }
   return mostArcsLocal;

}
