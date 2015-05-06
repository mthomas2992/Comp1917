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
	path Campuseslocation[20]; //need to figure out way to store these locations and easily find the adjacent regions for student production
	path GO8slocation[20];
	path arclocation[40];
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
   
	return EXIT_SUCCESS;
}