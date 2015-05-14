#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"

#define INVALID 10

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define IP_GAIN 1
#define PUB_GAIN 2

#define DEFAULT_EXCHANGE 3
#define RETRAIN_EXCHANGE 2

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
} game;

void addStudent (Game g, int student, int player, int amount);
coords translatepath(path arc);

//int makeActionipubs (int action);

/*int main (int argc, char *argv[]) {

    //I like commenting Get used to it.
    //I don't actually know whats meant to go in our mainline really...

   return EXIT_SUCCESS;
}*/
Game newGame (int discipline[], int dice[]){ //Matt NEED TO MALLOC IN SOME STUFF
   Game g=malloc(sizeof(g));
   g->mostarcs=NO_ONE;
   g->mostpubs=NO_ONE;
   g->turncount=-1; //terra nullius
   g->whoseTurn=NO_ONE; //terra nullius
   g->xcoords=0;
   g->ycoords=0;

   int i=0;
   while(i<NUM_REGIONS){ //input board into struct, might be better in a 2D array
      g->regions[i]=discipline[i];
      g->regionid[i]=dice[i];
   }

   //initialise the game board with invalids also
   i=0;
   int z=0;
   while (i<=5){ //this initialises on the y axis traverse rather then x, should be fine though
      while (z<=10){
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
   region regionarray[5][10];
   region r;
   /*r.a= /
   r.b=
   r.c=
   regionarray[x][y]=r GEneral hardcode structure, can probably be changed for the better
   */

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

   playerindex=UNI_A
   while (playerindex<=UNI_C){
      if (player == UNI_A) {
         player *p = &g->player1;
      } else if (player == UNI_B) { //Pointer hack
         player *p = &g->player2;
      } else if (player == UNI_C) {
         player *p = &g->player3; 
      }
      
      p->KPI=20; //intialise all values
      p->arcs=0;
      p->GO8s=0;
      p->Campuses=2;
      p->IPs=0;
      p->Pubs=0;
      p->students.THD=0;
      p->students.BPS=3;
      p->students.BQN=3;
      p->students.MJ=0;
      p->students.MTV=0;
      p->students.MMONEY=0;

      playerindex++;
   }
   /*
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
   */
   return g;
}

void disposeGame (Game g){
   free(g);
}

coords translatepath(path arc){
   //needs a response for if the path is empty
   int prevycoords=-1;
   coords coord;
   int prevxcoords=2;
   int xcoords=2;
   int ycoords=0;
   int leftx=0;
   int lefty=0;
   int rightx=0;
   int righty=0;
   int backx=0;
   int backy=0;
   int tempx=0;
   int tempy=0;
   int approach=DOWN;
   int index=0;
   while(arc[index]!=NULL)){
      //determine approach 
      //There is never a possibility of changing both x and y, therefore it isn't accounted for (yeah it should error trap but its our own function)
      if (prevycoords<ycoords){
         approach=DOWN;
      } else if (prevycoords>ycoords){
         approach=UP;
      } else if (prevxcoords<xcoords){
         approach=RIGHT;
      } else if (prevxcoords>xcoords){
         approach=LEFT;
      }
      //Compressed code, uncompressed found in other file
      if (((approach==DOWN)&&((xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2==0))||((approach==DOWN)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2!=0))){ //EVENS EVENS and ODDS ODDS
         leftx=xcoords+1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==UP)&&((xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2==0))||((approach==UP)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2!=0))){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords+1;
         righty=ycoords;
      } else if (((approach==RIGHT)&&((xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2==0))||((approach==RIGHT)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2!=0))){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==LEFT)&&((xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2==0))||((approach==RIGHT)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2!=0))){
         //avoiding combining the invalid statements as they are so damn long
         leftx=INVALID; //if this happens it should be picked up by the islegalfunction
         lefty=INVALID;
         rightx=INVALID;
         righty=INVALID;
      } else if (((approach==DOWN)&&(xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2!=0))||((approach==DOWN)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2==0))){ //EVENS ODDS
         leftx=xcoords;
         lefty=ycoords+1;
         rightx=xcoords-1;
         righty=ycoords;
      } else if (((approach==UP)&&(xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2!=0))||((approach==UP)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2==0))){
         leftx=xcoords-1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords-1;
      } else if (((approach==RIGHT)&&(xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2!=0))||((approach==RIGHT)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2==0))){
         //not possible DOUBLE CHECK
         leftx=INVALID;
         lefty=INVALID;
         rightx=INVALID;
         righty=INVALID;
      } else if (((approach==LEFT)&&(xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2!=0))||((approach==LEFT)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2==0))){
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
   if (a.actioncode==OBTAIN_ARC){ //currently this assumes arcs are like vertex's and their points ARCS REPED BY THE VERTEXS THEY CONNECT
      if ((getStudents(g,player,STUDENT_BPS)>=1)&&(getStudents(g,player,STUDENT_BQN)>=1)&&(a.destination[0]!='B') && sizeof(a.destination)<=PATH_LIMIT){ //gate to ensure sufficient students & valid path
         coord=translatepath(a.destination); //translate action a and return coords in terms of x and y
         x=coord.x;
         y=coord.y;
         if (arcarray[x][y]==VACANT_VERTEX){ //SCANS SURROUNDINGS FOR OTHER MATCHING ARCS RETURNS TRUE IF ONE IS FOUND
            if (y!=0){
               w=y-1;
               if (arcarray[x][w]==getWhoseTurn(g)){ //REMOVE NEED FOR VALID POINT FUNCTION BY INITIALISING ARRAY TO HAVE AN IMPOSSIBLE VALUE (10) IN THE INVALID POINTS
                  legal=TRUE;
               }
            }
            if (y!=10){
               w=y+1;
               if (arcarray[x][w]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            }
            if (((x==3)||(x==1)||(x==5))&&(y%2==0)){ //checks for odd column, even row do some logic testing on these
               w=x-1;
               if (arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            } else if (((x==3)||(x==1)||(x==5))&&(y%2!=0)) {
               w=x+1;
               if (arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            } else if ((x==0)||(x==2)||(x==4))&&(y%2==0)){
               w=x+1;
               if (arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            } else if ((x==0)||(x==2)||(x==4))&&(y%2!=0)){
               w=x-1;
               if (arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            }
         }
         //also needs to check if a vacant arc first
      }
   } else if (a.actioncode==RETRAIN_STUDENTS){
      if ((a.disciplineFrom>=getExchangeRate(g,player,a.disciplineFrom,a.diciplineTo)) && (a.disciplineFrom!=STUDENT_THD)){ //checks not THD and above rate
         legal=TRUE;
      }
   } else if (a.actioncode==PASS){
      legal=TRUE;
   } else if (a.actioncode==START_SPINOFF){
      if((getStudents(g,player,STUDENT_MJ)>=1)&&(getStudents(g,player,STUDENT_MTV)>=1)&&(getStudents(g,player,STUDENT_MMONEY)>=1)){
         legal=TRUE;
      }
   } else if (a.actioncode==BUILD_CAMPUS){
      if ((getStudents(g,player,STUDENT_BPS)>=1)&&(getStudents(g,player,STUDENT_BQN)>=1)&&(getStudents(g,player,STUDENT_MJ)>=1)&&(getStudents(g,player,STUDENT_MTV)>=1)&& (getARC(g,a.destination)==player)){ //gate, also uses getARC
         // need to also check no campuses within surounding area using similar scanning technique to arcs
         coord=translatepath(a.destination); //translate given path into 2d array point
         x=coord.x;
         y=coord.y;
         legal=TRUE; //sets to true for proving wrong
         if (y!=0){ //Scans for nearby campus's
            w=y-1;
            if (campusarray[x][w]==getWhoseTurn(g)){ //CAN PROBS COMPILE THIS INTO ITS OWN FUNCTION CALLED SCAN WHICH TAKES location, type to scan for and returns true if one is found, false if none.
               legal=FALSE;
            }
         }
         if (y!=10){
            w=y+1;
            if (campusarray[x][w]==getWhoseTurn(g)){
               legal=FALSE;
            }
         }
         if (((x==3)||(x==1)||(x==5))&&(y%2==0)){
            w=x-1;
            if (campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if (((x==3)||(x==1)||(x==5))&&(y%2!=0)) {
            w=x+1;
            if (campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if ((x==0)||(x==2)||(x==4))&&(y%2==0)){
            w=x+1;
            if (campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if ((x==0)||(x==2)||(x==4))&&(y%2!=0)){
            w=x-1;
            if (campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         }
      }
   } else if (a.actioncode==BUILD_GO8){
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
   int numOfARCs;
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
   int numOfCampuses;
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
   return g->regionid[regionID];
}

// return the number of IP Patents the specified player currently has
int getIPs (Game g, int player) {
   int playerIPs = 0;
   if (player == UNI_A) {
      playerIPs = g->player1.IPs
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
   if (((getCampus(g,'R') == player) || (getCampus(g,'RR') == player)) && (disciplineFrom == STUDENT_MTV)) {
      exchangerate = RETRAIN_EXCHANGE;
   } else if (((getCampus(g,'LL') == player) || (getCampus(g,'LLL') == player)) && (disciplineFrom == STUDENT_MMONEY)) {
      exchangerate = RETRAIN_EXCHANGE;
   } else if (((getCampus(g,'RRRLRLRLR') == player) || (getCampus(g,'RRRLRLRLRL') == player)) && (disciplineFrom==STUDENT_BPS)) {
      exchangerate = RETRAIN_EXCHANGE;
   } else if (((getCampus(g,'LLLLRLRLRL') == player) || (getCampus(g,'LLLLRLRLRLR') == player)) && (disciplineFrom == STUDENT_MJ)) {
      exchangerate = RETRAIN_EXCHANGE;
   } else if (((getCampus(g,'RRRLRR') == player) || (getCampus(g,'RRRLRRR') == player)) && (disciplineFrom == STUDENT_BQN)){
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
            g->player1.students.MTV--:
         } else if (a.actionCode == BUILD_GO8){
            coords coord2=translatepath(a.destination);
            g->campusarray[coord2.x][coord2.y]=getWhoseTurn(g)+3;
            g->player1.GO8s++;
            g->player1.Campuses--; 
            //need to subtract
         } else if (a.actionCode == OBTAIN_ARC){
            coords coord3=translatepath(a.destination);
            g->arcarray[coord3.x][coord3.y]=getWhoseTurn(g);
            g->player1.arcs++;
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
               player1.student.BPS++;
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
         } else if (a.actionCode == BUILD_GO8){
            coords coord2=translatepath(a.destination);
            g->campusarray[coord2.x][coord2.y]=getWhoseTurn(g)+3;
            g->player2.GO8s++;
            g->player1.Campuses--;
         } else if (a.actionCode == OBTAIN_ARC){
            coords coord3=translatepath(a.destination);
            g->arcarray[coord3.x][coord3.y]=getWhoseTurn(g);
            g->player2.arcs++;
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
               player2.student.BPS++;
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
         } else if (a.actionCode == BUILD_GO8){
            coords coord2=translatepath(a.destination);
            g->campusarray[coord2.x][coord2.y]=getWhoseTurn(g)+3;
            g->player3.GO8s++;
            g->player1.Campuses--;
         } else if (a.actionCode == OBTAIN_ARC){
            coords coord3=translatepath(a.destination);
            g->arcarray[coord3.x][coord3.y]=getWhoseTurn(g);
            g->player3.arcs++;
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
               player3.student.BPS++;
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

   if((P1Pubs == 0)&&(P2Pubs == 0)&&(P3Pubs == 0)){
      mostPubsLocal = NO_ONE;
   }

   if((P1Pubs)) > (P2Pubs)){
   //Here we know player1.Pubs > player2.Pubs
      if((P1Pubs) > (P3Pubs)){
         mostPubsLocal = UNI_A;
      }else if((P1Pubs) == (P3Pubs)){
         mostPubsLocal = currentMostPubs;
      }else{
         mostPubsLocal = UNI_C;
      }
   //Here we know player2.Pubs >= player1.Pubs
   }else if(P1Pubs == P2Pubs){
      mostPubsLocal = currentMostPubs;
   }else if((P2Pubs) > (P3Pubs)){
      mostPubsLocal = UNI_B;
   }else if((P2Pubs) == (P3Pubs)){
      mostPubsLocal = currentmostPubsLocal;
   }else{
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
   return campusarray[coord.x][coord.y];
}

int getDiscipline (Game g, int regionID){
   return g->regions[regionID];
}

void throwDice (Game g, int diceScore){
   //this needs alot more logic
   g->turnCount++;
   g->whoseTurn++;

   if (g->whoseTurn > UNI_C){
       g->whoseTurn = UNI_A;
   }
   g->mostpubs=getMostPublications(g);
   g->mostarcs=getMostARCs(g);
   regions r;
   // scan through array
   int xindex=0;
   int yindex=0;
   while (xindex<=5){ //check logic
      while(yindex<=10){
         if ((campusarray[xindex][yindex]!=VACANT_VERTEX)&&(campusarray[xindex][yindex]!=INVALID)){
            r=regionarray[xindex][yindex];
            addStudent(g,r.a,campusarray[xindex][yindex]);
            addStudent(g,r.b,campusarray[xindex][yindex]);
            addStudent(g,r.c,campusarray[xindex][yindex]);
         }
         yindex++;
      }
      xindex++;
      yindex=0;
   }
   int wipeMMONNEY=0;
   int wipeMTV=0;
   int wipeMTV2=0;
   int wipeMMONNEY2=0;

   if (diceScore==7){
      if (player == UNI_A) { //1337 pointer hacking
         player *p = &g->player1; //makes the pointer equal to the memory location of player1, so you can shortcut to it with the p pointer
      } else if (player == UNI_B) {
         player *p = &g->player2;
      } else if (player == UNI_C) {
         player *p = &g->player3; 
      }
      p->students.THD=p->students.THD+p->students.MMONEY+p->students.MTV;
      p->students.MMONEY=0;
      p->students.MTV=0;
   }
}

void addStudent (Game g, int student, int player, int amount){
   if (player == UNI_A) {
      player *p = &g->player1;
   } else if (player == UNI_B) { //NO SPACES HAHAHAHA
      player *p = &g->player2;
   } else if (player == UNI_C) {
      player *p = &g->player3; 
   }

   p->students.THD += amount;
   p->students.MMONEY += amount;
   p->students.MJ += amount;
   p->students.MTV += amount;
   p->students.BQN += amount;
   p->students.BPS += amount;
}

int getARC(Game g, path pathToEdge){
   coords coord;
   coord=translatepath(pathToEdge);
   return arcarray[coord.x][coord.y];
}

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

   int currentMostArcs = g->mostArcs;
   int mostArcsLocal = NO_ONE;

   if((p1Arcs == 0)&&(p2Arcs == 0)&&(p3Arcs == 0)){
      mostArcsLocal = NO_ONE;
   }

   if((p1Arcs)) > (p2Arcs)){
   //Here we know player1.Pubs > player2.Pubs
      if((p2Arcs) > (p3Arcs)){
         mostPubsLocal = UNI_A;
      }else if((p1Arcs) == (p3Arcs)){
         mostArcsLocal = currentMostArcs;
      }else{
         mostArcsLocal = UNI_C;
      }
   //Here we know player2.Pubs >= player1.Pubs
   }else if(p1Arcs == p2Arcs){
      mostArcsLocal = currentMostArcs;
   }else if((p2Arcs) > (p3Arcs)){
      mostArcsLocal = UNI_B;
   }else if((p2Arcs) == (p3Arcs)){
      mostArcsLocal = currentmostArcs;
   }else{
      mostArcsLocal = UNI_C;
   }
   return mostArcsLocal;

}
