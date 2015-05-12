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

//type def struct for arc coords to return
typedef struct _coords {
   int x;
   int y;
} coords;

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
	//path Campuseslocation[20]; //need to figure out way to store these locations and easily find the adjacent regions for student production
	//path GO8slocation[20];
	//path arclocation[40];
	students students;
} player;

typedef struct _game {
	int turncount; //need to figure out stuff with pointers and yeah
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
} game;


int main (int argc, char *argv[]) {

    //I like commenting Get used to it.
    //I don't actually know whats meant to go in our mainline really...

	return EXIT_SUCCESS;
}
Game newGame (int discipline[], int dice[]){ //Matt NEED TO MALLOC IN SOME STUFF
	Game g;
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
   while (i<=5){
      while (z<=10){
         if ((z+i>=2)&&(z+i<=13)){
            g->arcarray[i][z]=VACANT_ARC;
            g->campusarray[i][z]=VACANT_VERTEX;
         } else {
            g->arcarray[i][z]=INVALID;
            g->campusarray[i][z]=INVALID;
         }
         z++;
      }
      i++;
      z=0;
   }

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
} //will need to write loop to initialise both arc and campus array

coords translatepath(path arc){
   //different for the odds and evens
   //different for approach
   //first determine approach
   //either up,down,left or right
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
   //g->xcoords=xcoords;
   //g->ycoords=ycoords; //stores the translated values in the struct for access //Will translate any inputted path into 2D array coords outputted to the game structure, untested as of 10/5/15 midnight - Matt
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
      if ((getStudents(g,player,STUDENT_BPS)>=1)&&(getStudents(g,player,STUDENT_BQN)>=1)){ //gate to ensure sufficient students
         //translate action a and return coords in terms of x and y
         coord=translatepath(a.destination);
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
   int students=0;
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
   int exchangerate = 3;
   if (((getCampus(g,'R') == player) || (getCampus(g,'RR') == player)) && (disciplineFrom == STUDENT_MTV)) {
      exchangerate = 2;
   } else if (((getCampus(g,'LL') == player) || (getCampus(g,'LLL') == player)) && (disciplineFrom == STUDENT_MMONEY)) {
      exchangerate = 2;
   } else if (((getCampus(g,'RRRLRLRLR') == player) || (getCampus(g,'RRRLRLRLRL') == player)) && (disciplineFrom==STUDENT_BPS)) {
      exchangerate = 2;
   } else if (((getCampus(g,'LLLLRLRLRL') == player) || (getCampus(g,'LLLLRLRLRLR') == player)) && (disciplineFrom == STUDENT_MJ)) {
      exchangerate = 2;
   } else if (((getCampus(g,'RRRLRR') == player) || (getCampus(g,'RRRLRRR') == player)) && (disciplineFrom == STUDENT_BQN)){
      exchangerate = 2;
   }
   return exchangerate;
}

void makeAction(Game g, action a){
	int currentPlayer = getWhoseTurn(g);
	player *playerPTR;
	if (currentPlayer == UNI_A){
		playerPTR = &g.player1;
	} else if (currentPlayer == UNI_B){
		playerPTR = &g.player2;
	} else if (currentPlayer == UNI_C){
		playerPTR = &g.player3;
	}

	if (isLegalAction(g,a) == TRUE){ //need to add code that modifies structs contents to keep track of player inv
		if (a.actionCode == PASS){
			throwDice();
		} else if (a.actionCode == BUILD_CAMPUS){
			//write to array camus using translate
		} else if (a.actionCode == BUILD_GO8){
		    //check campus on position then double value to recieve

		} else if (a.actionCode == OBTAIN_ARC){
		    //check
		} else if (a.actionCode == START_SPINOFF){
			g->playerPTR->students->MJ--;
			g->playerPTR->students->MTV--;
			g->playerPTR->students->MMONEY--;
			srand(time(NULL));
			int Spinoff = rand()%3;
			if (Spinoff == IP_GAIN){
				g->playerPTR->IPs++;
			} else if (Spinoff == PUB_GAIN){
				g->playerPTR->Pubs++;
			}
		} else if (a.actionCode == RETRAIN_STUDENTS){
			int exchangeRate;
			exchangeRate = getExchangeRate(g, currentPlayer, a.disciplineFrom, a.disciplineTo);
			if (a.disciplineFrom == STUDENT_BPS){
				g->playerPTR->students->BPS -= exchangeRate;
			} else if (a.disciplineFrom == STUDENT_BQN){
				g->playerPTR->students->BQN -= exchangeRate;
			} else if (a.disciplineFrom == STUDENT_MJ){
				g->playerPTR->students->MJ -= exchangeRate;
			} else if (a.disciplineFrom == STUDENT_MTV){
				g->playerPTR->students->MTV -= exchangeRate;
			} else if (a.disciplineFrom == STUDENT_MMONEY){
				g->playerPTR->students->MMONEY -= exchangeRate;
			}

			if (a.disciplineTo == STUDENT_BPS){
				player1.student.BPS++;
			} else if (a.disciplineTo == STUDENT_BQN){
				g->playerPTR->students->BQN++;
			} else if (a.disciplineTo == STUDENT_MJ){
				g->playerPTR->students->MJ++;
			} else if (a.disciplineTo == STUDENT_MTV){
				g->playerPTR->students->MTV++;
			} else if (a.disciplineTo == STUDENT_MMONEY){
				g->playerPTR->students->MMONEY++;
			}
		}
	}
}

int getMostPublications(Game g){
   /* Last Edit: CBennetts 12/5/15
   Since it was unclear how ties were resolved, i opted for the "noone has the most if its tied".
   If thats wrong, might need a few changes
   */
   mostPubs = NO_ONE;
   if(player1.Pubs > player2.Pubs){
   //Here we know player1.Pubs > player2.Pubs
      if(player1.Pubs > player3.Pubs){
         mostPubs = UNI_A;
      }else if(player1.Pubs = player3.Pubs){
         mostPubs = NO_ONE;
      }else{
         mostPubs = UNI_C;
      }
   //Here we know player2.Pubs > player1.Pubs
   }else if(player2.Pubs > player3.Pubs){
      mostPubs = UNI_B;
   }else if(player2.Pubs = player3.Pubs){
      mostPubs = NO_ONE;
   }else{
      mostPubs = UNI_C;
   }
   return mostPubs;
}

int getWhoseTurn(Game g){
   /* Last Edit: CBennetts 12/5/15
   Someone make sure to check this works, it seems too simple
   */
   whoseTurn = (turnCount%(NUM_UNIS)) + 1;
   return whoseTurn;
}

int getCampus (Game g, path pathToVertex){
   /* Last Edit: CBennetts 12/5/15
   string for the path -> needs to return whether point is occupied and who occupies it.
   contents of a VERTEX
   #define VACANT_VERTEX 0
   #define CAMPUS_A 1
   #define CAMPUS_B 2
   #define CAMPUS_C 3
   #define GO8_A 4
   #define GO8_B 5
   #define GO8_C 6
   */
   int stateOfVertex = VACANT_VERTEX;
   int x = coord.x;
   int y = coord.y;
   /*
   Here where the stuff for string -> coord convertion goes
   */
   stateOfVertex = (campusArray[x][y]);
   return stateOfVertex;
}

int getDiscipline (Game g, int regionID){
   /* Last Edit: CBennetts 12/5/15
   takes regionID and gets what discipline it generates
   eg. regionID = 2, discipline = STUDENT_MJ
   Unsure about how the disciplines are #defined.... may need some changes
   */
   int discipline = 0;
   if(regionID == 0 || regionID == 10 || regionID == 12 || regionID == 17){
      discipline = STUDENT_BQN; //Light Blue
   }else if(regionID == 1 || regionID == 3 || regionID == 15){
      discipline = STUDENT_MMONEY; // Purple
   }else if(regionID == 2 || regionID == 4 || regionID == 11 || regionID == 14){
      discipline = STUDENT_MJ; // Yellow
   }else if(regionID == 5 || regionID == 8 || regionId == 18){
      discipline = STUDENT_BPS; // Red
   }else if (regionID == 6 || regionID == 7 || regionID == 9 || regionID == 16){
      discipline = STUDENT_MTV; // Green
   }else if (regionID == 13){
      discipline = STUDENT THD; // Dark Blue
   }
   return discipline;
}



void throwDice (Game g, int diceScore){

   g->turnCount++;

   g->whoseTurn++;

   if (g->whoseTurn > UNI_C){

       g->whoseTurn = UNI_A;

   }

}

int getARC(Game g, path pathToEdge){

   coords translatedFromPath;

   translatedFromPath = translatepath(pathToEdge);

   int x;
   int y;

   x = translatedFromPath.x;
   y = translatedFromPath.y;

   return arcarray[x][y];

}

}
int getGO8s (Game g, int player){

   int returnVal;

   if(player == UNI_A){

    returnVal = g->player1.GO8s;

   }else if(player == UNI_B){

    returnVal = g->player2.GO8s;

   }else if(player == UNI_C){

    returnVal = g->player3.GO8s;

   }else{

      printf("Invalid player/game values")

   }

   return returnVal;

};

int getKPIpoints (Game g, int player){

   int returnVal;

   if(player == UNI_A){

    returnVal = g->player1.KPI;

   }else if(player == UNI_B){

    returnVal = g->player2.KPI;

   }else if(player == UNI_C){

    returnVal = g->player3.KPI;

   }else{

      printf("Invalid player/game values")

   }

   return returnVal;

};

int getMostARCs (Game g){

   int p1Arcs;
   int p2Arcs;
   int p3Arcs;

   int playerWithMostArcs;
   int mostArcs;

   p1Arcs = g->player1.arcs;
   p2Arcs = g->player2.arcs;
   p3Arcs = g->player3.arcs;

   currentMost = g->mostArcs;


   mostArcs = p1Arcs;
   playerWithMostArcs = UNI_A:

   if(p2Arcs > mostArcs){

      mostArcs = p2Arcs;
      playerWithMostArcs = UNI_B:

   }
   if(p3Arcs > mostArcs){

      mostArcs = p3Arcs;
      playerWithMostArcs = UNI_C:

   }


   return playerWithMostArcs;



}











