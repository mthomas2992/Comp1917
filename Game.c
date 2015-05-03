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
	char Campuseslocation[20];
	char GO8slocation[20];
	char arclocation[40];
	students students;
} player

typedef struct _game {
	int turncount;
	player player1;
	player player2;
	player player3;
	int mostpubs;
	int mostarcs;

} game


int main (int argc, char *argv[]) {
   
	return EXIT_SUCCESS;
}