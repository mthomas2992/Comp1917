#include "Game.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define WINKPI 150
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}


int rollDice(void);

int main (int argc, char *argv[]) {
	Game g =newGame(DEFAULT_DISCIPLINES,DEFAULT_DICE);
	int player= getWhoseturn(g);
	int dicevalue=0;
	int actioncode=-1;
	path destinationpath;

	while(getkpipoints(g,player)<WINKPI){
		
		dicevalue=rollDice(); //function to return random number
		throwdice(g,dicevalue);
		player=getWhoseturn(g);

		while(input.actioncode!=PASS){
			action input;
			if (actioncode<=3 && actioncode>0){
				printf("Input Destination\n");
				scanf("%s",destinationpath);
				input.destination=destinationpath;
			} else if (actioncode== RETRAIN_STUDENTS){
				printf("Input students to transform\n");
				scanf("%d",studentsfrom);
				printf("Input students to transform to\n");
				scanf("%d",studentsto);
				input.disciplineFrom=studentsfrom;
				input.disciplineTo=studentsto;
			}
			if (isLegalaction(g,input)==TRUE){
				printf("executing action for player %d\n",player);
				makeAction(g,input);
			} else {
				printf("action is not legal\n");
			}
			printf("Player %d's turn\n",player);
			printf("Input action code\n");
			scanf("%d",&actioncode);
			input.actioncode=actioncode;
		}
	}

	return EXIT_SUCCESS;
}

int rollDice(void){
	srand(time(NULL));
	int r = rand()%11; //generates random number between 0 and 10
	r=r+2; //brings number into the range we want of 2 and 12 inclusive
	return r;
}