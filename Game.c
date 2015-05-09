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
}

//test
