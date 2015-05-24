#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

// Starting Campus positions, possibly just add onto these strings
// when creating destinations
// Note: please check over, I have bad geometry related skills
/*
#define CAMPUS_A_TOP ""
#define CAMPUS_A_BOT "RLRLRLRLRLRLLLL"
#define CAMPUS_B_LEFT "RRLRRLLLL"
#define CAMPUS_B_RIGHT "LRLRLRRLLRRR"
#define CAMPUS_C_LEFT "RRLRLLRLRRLLLL"
#define CAMPUS_C_RIGHT "LRLLRRR"
*/
#define CAMPUS_A_TOP ""
#define CAMPUS_A_BOT "RLRLRLRLRLL"
#define CAMPUS_B_LEFT "RRLRL"
#define CAMPUS_B_RIGHT "LRLRLRRLRLRL"
#define CAMPUS_C_LEFT "RRLRLLRLRL"
#define CAMPUS_C_RIGHT "LRLRL"

// Please add number of ARCS we want to achieve for EARLY_GAME
#define EARLY_GAME_ARCS 5
#define EARLY_GAME_TURNS 300

typedef struct _inventory {
	int BPS;
	int BQN;
	int MJ;
	int MTV;
	int MMONEY;
} inventory;

action decideAction_A (Game g);
//action decideAction_B (Game g);
//action decideAction_C (Game g);
inventory getInventory(Game g, int player);
path removeLastDirection(path location);
action retraintoBPSorBQN(Game g, inventory inv, int player, int studentTo);
action retraintoM(Game g, inventory inv, int player, int studentTo);
isARCLegal(Game g, path location, path direction);
inventory getInventory(Game g, int player);
path getLastARC(Game g, int player);
int checkCampusARC(Game g, path location);
int checkARC_R(Game g, path location, int player);
int checkARC_L(Game g, path location, int player);

/*
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
*/

action decideAction (Game g){
	action nextAction;
	nextAction = decideAction_A(g);
	return nextAction;
}

// Action stream for Uni A
action decideAction_A (Game g){
	action playerAction;
	
	int whichPlayer;
	whichPlayer = getWhoseTurn(g);
	
	inventory playerInv;
	playerInv = getInventory(g, whichPlayer);
	
	path destination;
	if (whichPlayer == UNI_A){
		strcpy(destination,CAMPUS_A_BOT);
	} else if (whichPlayer == UNI_B){
		strcpy(destination,CAMPUS_B_RIGHT);
	} else if (whichPlayer == UNI_C){
		strcpy(destination,CAMPUS_C_RIGHT);
	}
	int pathLength;
	pathLength = strlen(destination);
	
	if (getARCs(g,whichPlayer) <= EARLY_GAME_ARCS && getTurnNumber(g) <= EARLY_GAME_TURNS){
		if (playerInv.BPS == 1 && playerInv.BQN == 1){
			playerAction.actionCode = OBTAIN_ARC;
			destination = getLastARC(g,whichPlayer);
			
			int foundNewARC = FALSE;
			while (foundNewARC == FALSE){
				if (destination == CAMPUS_A_TOP){
					strcat(destination,"R");
					foundNewARC = TRUE;
				} else if (destination[pathLength - 1] == 'L' && isARCLegal(g,destination,'R') == TRUE){
					strcat(destination,"R");
					foundNewARC = TRUE;
				} else if (destination[pathLength - 1] == 'R' && isARCLegal(g,destination,'L') == TRUE){
					strcat(destination,"L");
					foundNewARC = TRUE;
				} else {
					destination =  removeLastDirection(destination);
					while (foundNewARC == FALSE){
						if (isARCLegal(g,destination,'R') == TRUE){
							strcat(destination,"R");
							foundNewARC = TRUE;
						} else if (isARCLegal(g,destination,'L') == TRUE){
							strcat(destination,"L");
							foundNewARC = TRUE;
						} else {
							destination =  removeLastDirection(destination);
						}
					}
				}
			}
			playerAction.destination = destination;
		} else if (playerInv.BPS == 0){
			playerAction = retraintoBPSorBQN(g,playerInv,whichPlayer,STUDENT_BPS);
		} else if (playerInv.BQN == 0){
			playerAction = retraintoBPSorBQN(g,playerInv,whichPlayer,STUDENT_BQN);		
		} else {
			playerAction.actionCode = PASS;
		}
	} else {
		if (playerInv.MJ == 1 && playerInv.MTV == 1 && playerInv.MMONEY == 1){
			playerAction.actionCode = START_SPINOFF;
		} else if (playerInv.MJ == 0){
			playerAction = retraintoM(g, playerInv,whichPlayer,STUDENT_MJ);
		} else if (playerInv.MTV == 0){
			playerAction = retraintoM(g, playerInv,whichPlayer,STUDENT_MTV);
		} else if (playerInv.MMONEY == 0){
			playerAction = retraintoM(g, playerInv,whichPlayer,STUDENT_MMONEY);
		} else {
			playerAction.actionCode = PASS;
		}
	}
	return playerAction;
}

/*
// Action stream for Uni A
action decideAction_A (Game g){
	action playerAction;
	inventory playerInv;
	playerInv = getInventory(g, UNI_A);
	path destination;
	strcpy(destination,CAMPUS_A_TOP);
	int pathLength;
	
	if (getARCs(g,UNI_A) <= EARLY_GAME){
		if (playerInv.BPS == 1 && playerInv.BQN == 1){
			playerAction.actionCode = OBTAIN_ARC;
			destination = getLastARC(g,UNI_A);
			pathLength = strlen(destination);
			
			int foundNewARC = FALSE;
			while (foundNewARC == FALSE){
				if (destination == ""){
					strcat(destination,"R");
					foundNewARC = TRUE;
				} else if (destination[pathLength - 1] == 'L' && isARCLegal(g,destination,'R')){
					strcat(destination,"R");
					foundNewARC = TRUE;
				} else if (destination[pathLength - 1] == 'R' && isARCLegal(g,destination,'L')){
					strcat(destination,"L");
					foundNewARC = TRUE;
				} else {
					destination =  removeLastDirection(destination);
				}
			}
			playerAction.destination = destination;
		} else if (playerInv.BPS == 0){
			playerAction = retraintoBPSorBQN(g,playerInv,UNI_A,STUDENT_BPS);
		} else if (playerInv.BQN == 0){
			playerAction = retraintoBPSorBQN(g,playerInv,UNI_A,STUDENT_BQN);		
		} else {
			playerAction.actionCode = PASS;
		}
	} else {
		if (playerInv.MJ == 1 && playerInv.MTV == 1 && playerInv.MMONEY == 1){
			playerAction.actionCode = START_SPINOFF;
		} else if (playerInv.MJ == 0){
			playerAction = retraintoM(g, playerInv,UNI_A,STUDENT_MJ);
		} else if (playerInv.MTV == 0){
			playerAction = retraintoM(g, playerInv,UNI_A,STUDENT_MTV);
		} else if (playerInv.MMONEY == 0){
			playerAction = retraintoM(g, playerInv,UNI_A,STUDENT_MMONEY);
		} else {
			playerAction.actionCode = PASS;
		}
	}
	return playerAction;
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
*/

// Removes last direction in a path
path removeLastDirection(path location){
	path temp;
	int n;
	n = (strlen(location) - 1);
	strncpy(temp,location,n);
	return temp;
}

// Determines the action struct to be used for a retrain into BPS/BQN
action retraintoBPSorBQN(Game g, inventory inv, int player, int studentTo){
	action retrainAction;
	retrainAction.actionCode = RETRAIN_STUDENTS;
	retrainAction.disciplineTo = studentTo;
	if (inv.MJ >= 2 && getExchangeRate(g,player,STUDENT_MJ,studentTo) == 2){
		retrainAction.disciplineFrom = STUDENT_MJ;
	} else if (inv.MTV >= 2 && getExchangeRate(g,player,STUDENT_MTV,studentTo) == 2){
		retrainAction.disciplineFrom = STUDENT_MTV;
	} else if (inv.MMONEY >= 2 && getExchangeRate(g,player,STUDENT_MMONEY,studentTo) == 2){
		retrainAction.disciplineFrom = STUDENT_MMONEY;
	} else if (inv.MJ >= 3 && getExchangeRate(g,player,STUDENT_MJ,studentTo) == 3){
		retrainAction.disciplineFrom = STUDENT_MJ;
	} else if (inv.MTV >= 3 && getExchangeRate(g,player,STUDENT_MTV,studentTo) == 3){
		retrainAction.disciplineFrom = STUDENT_MTV;
	} else if (inv.MMONEY >= 3 && getExchangeRate(g,player,STUDENT_MMONEY,studentTo) == 3){
		retrainAction.disciplineFrom = STUDENT_MMONEY;
	} else if (inv.BQN >= 3 && studentTo != STUDENT_BQN && getExchangeRate(g,player,STUDENT_BQN,studentTo) == 2){
		retrainAction.disciplineFrom = STUDENT_BQN;
	} else if (inv.BPS >= 3 && studentTo != STUDENT_BPS && getExchangeRate(g,player,STUDENT_BPS,studentTo) == 2){
		retrainAction.disciplineFrom = STUDENT_BPS;
	} else if (inv.BQN >= 4 && studentTo != STUDENT_BQN && getExchangeRate(g,player,STUDENT_BQN,studentTo) == 3){
		retrainAction.disciplineFrom = STUDENT_BQN;
	} else if (inv.BPS >= 4 && studentTo != STUDENT_BPS && getExchangeRate(g,player,STUDENT_BPS,studentTo) == 3){
		retrainAction.disciplineFrom = STUDENT_BPS;
	} else {
		retrainAction.actionCode = PASS;
	}
	return retrainAction;
}

// Determines the action struct to be used for a retrain into M
// For BQN/BPS, only checks if the exact amount for exchange
// For M, checks for exchange + 1
action retraintoM(Game g, inventory inv, int player, int studentTo){
	action retrainAction;
	retrainAction.actionCode = RETRAIN_STUDENTS;
	retrainAction.disciplineTo = studentTo;
	if (inv.BPS >= 2 && getExchangeRate(g,player,STUDENT_BPS,studentTo) == 2){
		retrainAction.disciplineFrom = STUDENT_BPS;		
	} else if (inv.BQN >= 2 && getExchangeRate(g,player,STUDENT_BQN,studentTo) == 2){
		retrainAction.disciplineFrom = STUDENT_BQN;		
	} else if (inv.BPS >= 3 && getExchangeRate(g,player,STUDENT_BPS,studentTo) == 3){
		retrainAction.disciplineFrom = STUDENT_BPS;		
	} else if (inv.BQN >= 3 && getExchangeRate(g,player,STUDENT_BQN,studentTo) == 3){
		retrainAction.disciplineFrom = STUDENT_BQN;		
	} else if (player.MJ >= 3 && getExchangeRate(g,player,STUDENT_MJ,studentTo) == 2 && studentTo != STUDENT_MJ){
		retrainAction.disciplineFrom = STUDENT_MJ;
	} else if (inv.MTV >= 3 && getExchangeRate(g,player,STUDENT_MTV,studentTo) == 2 && studentTo != STUDENT_MTV){
		retrainAction.disciplineFrom = STUDENT_MTV;		
	} else if (inv.MMONEY >= 3 && getExchangeRate(g,player,STUDENT_MMONEY,studentTo) == 2 && studentTo != STUDENT_MMONEY){
		retrainAction.disciplineFrom = STUDENT_MMONEY;		
	} else if (inv.MJ >= 4 && getExchangeRate(g,player,STUDENT_MJ,studentTo) == 3 && studentTo != STUDENT_MJ){
		retrainAction.disciplineFrom = STUDENT_MJ;		
	} else if (inv.MTV >= 4 && getExchangeRate(g,player,STUDENT_MTV,studentTo) == 3 && studentTo != STUDENT_MTV){
		retrainAction.disciplineFrom = STUDENT_MTV;
	} else if (inv.MMONEY >= 4 && getExchangeRate(g,player,STUDENT_MMONEY,studentTo) == 3 && studentTo != STUDENT_MMONEY){
		retrainAction.disciplineFrom = STUDENT_MMONEY;
	} else {
		retrainAction.actionCode = PASS;
	}
	return retrainAction;
}

// Checks whether it is legal to create an ARC in a certain direction
int isARCLegal(Game g, path location, path direction){
	action isLegal;
	isLegal.actionCode = OBTAIN_ARC;
	path destination = location;
	strcat(destination,direction);
	isLegal.destination = destination;
	
	return isLegalAction(g,isLegal);
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
//Also, assumes that there is only a line of ARCs, in    //
//the case where the ARCs branch off, the right branch   //
//is favoured                                            //
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
	strcat(Lcheck, "L");
	
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
