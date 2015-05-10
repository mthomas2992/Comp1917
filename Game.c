#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"

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

typedef struct _game {
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
} game


int main (int argc, char *argv[]) {

    //I like commenting Get used to it.
    //I don't actually know whats meant to go in our mainline really...

	return EXIT_SUCCESS;
}
Game newGame (int discipline[], int dice[]){ //Matt NEED TO MALLOC IN SOME STUFF
	game g;
   g.mostarcs=NO_ONE;
   g.mostpubs=NO_ONE;
   g.turncount=-1; //terra nullius
   g.whoseTurn=NO_ONE; //terra nullius

   int i=0;
   while(i<NUM_REGIONS){
      g.regions[i]=discipline[i];
      g.regionid[i]=dice[i];
   }

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

}

int isLegalAction (Game g, action a){
   int legal =FALSE;
   int x=0;
   int y=0;
   int w=0;

   if (a.actioncode==OBTAIN_ARC){
      //translate action a and return coords in terms of x and y
      translatepath(a.destination);
      x=g.xcoords;
      y=g.ycoords;
      //input translated coords into function that checks array, scans surrounding coords for other arc values, if any are a match then return legal
      if (arcarray[x][y]==VACANT_VERTEX){ //SCANS SURROUNDINGS FOR OTHER MATCHING ARCS RETURNS TRUE IF ONE IS FOUND
         //first check one below and one above, then the one to either the left or the right if its not on the edge
         //have a function to check legal values, ensure no segment faults
         if (y!=0){
            w=y-1;
            if (arcarray[x][w]==getWhoseTurn(g)){ //REMOVE NEED FOR VALID POINT FUNCTION BY INITIALISING ARRAY TO HAVE AN IMPOSSIBLE VALUE IN THE INVALID POINTS
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
         } else { // checks for even column, odd row
            w=x+1;
            if (arcarray[w][y]==getWhoseTurn(g)){
               legal=TRUE;
            }
         }
      }
      //also needs to check if a vacant arc first

   }

}
