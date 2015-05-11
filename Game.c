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

typedef struct _students{
	int THD;
	int BPS;
	int BQN;
	int MJ;
	int MTV;
	int MMONEY;
} students

typedef struct _player{
	int KPI;
	int arcs;
	int GO8s;
	int Campuses;
	int IPs;
	int Pubs;
	//path Campuseslocation[20]; //need to figure out way to store these locations and easily find the adjacent regions for student production
	//path GO8slocation[20];
	//path arclocation[40];
	students students;
} player

typedef struct _Game {
	int turncount;
	int whoseTurn;
	player player1;
	player player2;
	player player3;
	int mostpubs;
	int mostarcs;
	int regions[NUM_REGIONS];
	int regionid[NUM_REGIONS];
   //going to need 2 2d int arrays to store both the arc and campus array
   int arcarray [5][10];
   int campusarray [5][10];
   int xcoords;
   int ycoords;
} Game


int main (int argc, char *argv[]) {

    //I like commenting Get used to it.
    //I don't actually know whats meant to go in our mainline really...

	return EXIT_SUCCESS;
}
Game newGame (int discipline[], int dice[]){ //Matt NEED TO MALLOC IN SOME STUFF
	Game g;
   g.mostarcs=NO_ONE;
   g.mostpubs=NO_ONE;
   g.turncount=-1; //terra nullius
   g.whoseTurn=NO_ONE; //terra nullius
   g.xcoords=0;
   g.ycoords=0;

   int i=0;
   while(i<NUM_REGIONS){ //input board into struct, might be better in a 2D array
      g.regions[i]=discipline[i];
      g.regionid[i]=dice[i];
   }
   
   //initialise the game board with invalids also
   i=0;
   int z=0;
   while (i<=5){
      while (z<=10){
         if ((z+i>=2)&&(z+i<=13)){
            g.arcarray[i][z]=VACANT_ARC;
            g.campusarray[i][z]=VACANT_VERTEX;
         } else {
            g.arcarray[i][z]=INVALID;
            g.campusarray[i][z]=INVALID;
         }
         z++;
      }
      i++;
      z=0;
   }
   
   //specify missed invalids
   g.arcarray[4][0]=INVALID;
   g.arcarray[5][0]=INVALID;
   g.arcarray[5][1]=INVALID;
   g.arcarray[0][9]=INVALID;
   g.arcarray[0][10]=INVALID;
   g.arcarray[1][10]=INVALID;

   g.campusarray[4][0]=INVALID;
   g.campusarray[5][0]=INVALID;
   g.campusarray[5][1]=INVALID;
   g.campusarray[0][9]=INVALID;
   g.campusarray[0][10]=INVALID;
   g.campusarray[1][10]=INVALID;  


   //player one
   g.player1.KPI=20;
   g.player1.arcs=0;
   g.player1.GO8s=0;
   g.player1.Campuses=2;
   g.player1.IPs=0;
   g.player1.Pubs=0;
   g.player1.students.THD=0;
   g.player1.students.BPS=3;
   g.player1.students.BQN=3;
   g.player1.students.MJ=0;
   g.player1.students.MTV=0;
   g.player1.students.MMONEY=0;

   //player two
   g.player2.KPI=20;
   g.player2.arcs=0;
   g.player2.GO8s=0;
   g.player2.Campuses=2;
   g.player2.IPs=0;
   g.player2.Pubs=0;
   g.player2.students.THD=0;
   g.player2.students.BPS=3;
   g.player2.students.BQN=3;
   g.player2.students.MJ=0;
   g.player2.students.MTV=0;
   g.player2.students.MMONEY=0;

   //player three
   g.player3.KPI=20;
   g.player3.arcs=0;
   g.player3.GO8s=0;
   g.player3.Campuses=2;
   g.player3.IPs=0;
   g.player3.Pubs=0;
   g.player3.students.THD=0;
   g.player3.students.BPS=3;
   g.player3.students.BQN=3;
   g.player3.students.MJ=0;
   g.player3.students.MTV=0;
   g.player3.students.MMONEY=0;

   return g;
} //will need to write loop to initialise both arc and campus array

void translatepath(path arc){
   //different for the odds and evens
   //different for approach
   //first determine approach
   //either up,down,left or right
   int prevycoords=-1;
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
   index=0; //need to determine the null value for end of string
   while(arc[index]!=NULL){
      //determine approach
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
         //avoiding combinging the invalid statements as they are so damn long
         leftx=INVALID;
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
   g.xcoords=xcoords;
   g.ycoords=ycoords; //stores the translated values in the struct for access //Will translate any inputted path into 2D array coords outputted to the game structure, untested as of 10/5/15 midnight - Matt
}

int isLegalAction (Game g, action a){
   int legal=FALSE;
   int x=0; //NEED TO CONSIDER HOW TO ACTUALLY BUILD AN ARC
   int y=0;
   int w=0;
   int player = getWhoseTurn(g);
   if (a.actioncode==OBTAIN_ARC){ //currently this assumes arcs are like vertex's and their points ARCS REPED BY THE VERTEXS THEY CONNECT
      if ((getStudents(g,player,STUDENT_BPS)>=1)&&(getStudents(g,player,STUDENT_BQN)>=1)){ //gate to ensure sufficient students
         //translate action a and return coords in terms of x and y
         translatepath(a.destination);
         x=g.xcoords;
         y=g.ycoords;
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
      if (a.disciplineFrom>=getExchangeRate(g,player,a.disciplineFrom,a.diciplineTo)){
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
         translatepath(a.destination); //translate given path into 2d array point
         x=g.xcoords;
         y=g.ycoords;
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
   int students=0; 
   if (player==UNI_A){
      if (discipline==STUDENT_THD){
         students=g.player1.students.THD;
      } else if (discipline==STUDENT_BPS){
         students=g.player1.students.BPS;
      } else if (discipline==STUDENT_BQN){
         students=g.player1.students.BQN;
      } else if (discipline==STUDENT_MJ){
         students=g.player1.students.MJ;
      } else if (discipline==STUDENT_MTV){
         students=g.player1.students.MTV;
      } else if (discipline==STUDENT_MMONEY){
         students=g.player1.students.MMONEY;
      }
   } else if (player==UNI_B){
      if (discipline==STUDENT_THD){
         students=g.player2.students.THD;
      } else if (discipline==STUDENT_BPS){
         students=g.player2.students.BPS;
      } else if (discipline==STUDENT_BQN){
         students=g.player2.students.BQN;
      } else if (discipline==STUDENT_MJ){
         students=g.player2.students.MJ;
      } else if (discipline==STUDENT_MTV){
         students=g.player2.students.MTV;
      } else if (discipline==STUDENT_MMONEY){
         students=g.player2.students.MMONEY;
      }
   } else if (player==UNI_C){
      if (discipline==STUDENT_THD){
         students=g.player3.students.THD;
      } else if (discipline==STUDENT_BPS){
         students=g.player3.students.BPS;
      } else if (discipline==STUDENT_BQN){
         students=g.player3.students.BQN;
      } else if (discipline==STUDENT_MJ){
         students=g.player3.students.MJ;
      } else if (discipline==STUDENT_MTV){
         students=g.player3.students.MTV;
      } else if (discipline==STUDENT_MMONEY){
         students=g.player3.students.MMONEY;
      }
   }

   return students;
}

int getARCs(Game g, int player){
	int numOfARCs;
	if (player == UNI_A){
		numOfARCs = g.player1.arcs;
	} else if (player == UNI_B){
		numOfARCs = g.player2.arcs;
	} else if (player == UNI_C){
		numOfARCs = g.player3.arcs;
	}
	return numOfARCs;
}

int getCampuses(Game g, int player){
	int numOfCampuses;
	if (player == UNI_A){
		numOfCampuses = g.player1.Campuses;
	} else if (player == UNI_B){
		numOfCampuses = g.player2.Campuses;
	} else if (player == UNI_C){
		numOfCampuses = g.player3.Campuses;
	}
	return numOfCampuses;
}
