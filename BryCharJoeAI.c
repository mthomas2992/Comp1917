/*
 *  Mr Pass.  Brain the size of a planet!
 *
 *  Proundly Created by Richard Buckland
 *  Share Freely Creative Commons SA-BY-NC 3.0.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

action decideAction (Game g) {
	action nextAction;
	if (isSpinoffLegal(g) == TRUE){
		nextAction.actionCode = START_SPINOFF;
	} else {
		nextAction.actionCode = PASS;
	}
	return nextAction;
}

void isSpinoffLegal(Game g){
	action Spinoff;
	spinoff.actionCode = START_SPINOFF;
	return isLegalAction(g, Spinoff);
}

// Joerick
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "mechanicalTurk.h"

// Starting Campus positions, possibly just add onto these strings
// when creating destinations
// Note: please check over, I have bad geometry related skills
#define CAMPUS_A_TOP ""
#define CAMPUS_A_BOT "RLRLRLRLRLL"
#define CAMPUS_B_LEFT "RRLRL"
#define CAMPUS_B_RIGHT "LRLRLRRLRLRL"
#define CAMPUS_C_LEFT "RRLRLLRLRL"
#define CAMPUS_C_RIGHT "LRLRL"
#define TRUE 1
#define FALSE 0

typedef struct _inventory {
	int BPS;
	int BQN;
	int MJ;
	int MTV;
	int MMONEY
} inventory;

action decideAction_A (Game g);
action decideAction_B (Game g);
action decideAction_C (Game g);
inventory getInventory(Game g, int player);

action decideAction (Game g){
	action nextAction;
	int whichPlayer = getWhoseTurn(g);
	if (whichPlayer == UNI_A){
		nextAction = decideAction_A(g);
	} else if (whichPlayer == UNI_B){
		nextAction = decideAction_B(g);
	} else if (whichPlayer == UNI_C){
		nextAction = decideAction_C(g);
	}
}

// Action stream for Uni A
action decideAction_A (Game g){
	action playerA;
	inventory player;
	path destination;
	strcat(destination,CAMPUS_A_TOP);
	int pathLength;
	player = getInventory(g, UNI_A);

	if (player.BPS == 1 && player.BQN == 1){
		playerA.actionCode = OBTAIN_ARC;
		destination = getLastARC(g,UNI_A);
		pathLength = strlen(destination);

		if (destination[pathLength - 1] == "R"){
			strcat(destination,"L");
		} else if (destination[pathLength - 1] == "L"){
			strcat(destination,"R");
		}

		playerA.destination = CAMPUS_A_TOP
	}
}

// Action stream for Uni B
action decideAction_B (Game g){
	inventory player;
	player = getInventory(g, UNI_B);
}

// Action stream for Uni C
action decideAction_C (Game g){
	inventory player;
	player = getInventory(g, UNI_C);
}

// Returns player Inventory
inventory getInventory(Game g, int player){
	inventory currentPlayer;
	currentPlayer.BPS = getStudents(g, player,STUDENT_BPS);
	currentPlayer.BQN = getStudents(g, player,STUDENT_BQN);
	currentPlayer.MJ = getStudents(g, player,STUDENT_MJ);
	currentPlayer.MTV = getStudents(g, player,STUDENT_MTV);
	currentPlayer.MMONEY = getStudents(g, player,STUDENT_MMONEY);
	return currentPlayer;
}

// From starting ARC position, follows created arcs until the end of
// the ARC tail??? is found
///////////////////////////////////////////////////////////
//Important: Assumes that ARCs only stem from one campus.//
///////////////////////////////////////////////////////////
path getLastARC(Game g, int player){
	path LastARC;
	if (player == UNI_A){
		if (checkCampusARC(g,CAMPUS_A_TOP) == TRUE){
			strcpy(LastARC,CAMPUS_A_TOP);
		} else {
			strcpy(LastARC,CAMPUS_A_BOT);
		}

	} else if (player == UNI_B){
		if (checkCampusARC(g,CAMPUS_B_LEFT) == TRUE){
			strcpy(LastARC,CAMPUS_B_LEFT);
		} else {
			strcpy(LastARC,CAMPUS_B_RIGHT);
		}

	} else if (player == UNI_C){
		if (checkCampusARC(g,CAMPUS_C_LEFT) == TRUE){
			strcpy(LastARC,CAMPUS_C_LEFT);
		} else {
			strcpy(LastARC,CAMPUS_C_RIGHT);
		}
	}
	int noMoreARCs = FALSE;
	while (noMoreARCs == FALSE){
		if (checkARC_R(g,LastARC,player) == TRUE){
			strcat(LastARC,"R");
		} else if (checkARC_L(g,LastARC,player) == TRUE){
			strcat(LastARC,"L");
		} else {
			noMoreARCs = TRUE;
		}
	}
	return LastARC;
}

// Returns Boolean value to see whether ARCS have been made on a certain
// Campus.
///////////////////////////////////////////////////////
// Important: Only used for initial campus positions.//
///////////////////////////////////////////////////////
int checkCampusARC(Game g, path location){
	int status = FALSE;
	path Rcheck;
	strcpy(Rcheck, location);
	strcat(Rcheck, "R");
	path Lcheck;
	strcpy(Lcheck, location);
	strcat(Lcheck, "L")

	if (getARC(g, Rcheck) != 0){
		status = TRUE;
	} else if (getARC(g, Lcheck) != 0){
		status = TRUE;
	}
	return status;
}

// Checks whether Right path belongs to player
int checkARC_R(Game g, path location, int player){
	int status = FALSE;
	path Rcheck;
	strcpy(Rcheck, location);
	strcat(Rcheck, "R");

	if (getARC(g, Rcheck) == player){
		status = TRUE;
	}
	return status;
}

// Checks whether Left path belongs to player
int checkARC_L(Game g, path location, int player){
	int status = FALSE;
	path Lcheck;
	strcpy(Lcheck, location);
	strcat(Lcheck, "L");

	if (getARC(g, Lcheck) == player){
		status = TRUE;
	}
	return status;
}
