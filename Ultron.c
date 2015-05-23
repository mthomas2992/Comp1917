#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"

#define INVALID 20
#define ARC_THRESH 10

//score modifiers for arc scouting
#define THD_SCORE -1
#define BPS_SCORE 1
#define BQN_SCORE 1
#define MJ_SCORE 1
#define MTV_SCORE 1
#define MMONEY_SCORE 1

typedef struct _score {
   path edge;
   int score;
} score;

typedef struct _coords {
   int x;
   int y;
} coords;

typedef struct _regions {
   int a;
   int b;
   int c;
} regions;

typedef struct _studentsstore {
   int THD;
   int BPS;
   int BQN;
   int MJ;
   int MTV;
   int MMONEY;
} studentsstore;

typedef struct _playerstore {
   int KPI;
   int arcs;
   int GO8s;
   int Campuses;
   int IPs;
   int Pubs;
   studentsstore students;
} playerstore;

typedef struct _gamestore * Gamestore;

typedef struct _gamestore {
   int turncount;
   int whoseTurn;
   playerstore Ultron;
   int mostpubs;
   int mostarcs;
   int regions[NUM_REGIONS]; //this stores the discipline
   int regionid[NUM_REGIONS]; //this stores the dice value of the region
   //going to need 2 2d int arrays to store both the arc and campus array
   path arcarray [6][11]; //size 
   int campusarray [6][11];
   regions regionarray[6][11];
} gamestore;

void Assess(Gamestore p, Game g);
action decideAction (Game g);
action ArcLogic(Gamestore p,Game g);
void assignregion(Gamestore g);

/*int main (int argc, char *argv[]) {
	//action a;
	//a=decideAction(g);
   Gamestore p=malloc(sizeof(gamestore));
   strcpy(p->arcarray[1][1],"LR");
   printf("string %s", p->arcarray[1][1]);
	return EXIT_SUCCESS;
}*/

action decideAction (Game g){
	//determine local campuses
	//build towards selected number priority
	//continue building towards preference
	//store gathered arcs in an array?
	//could use similar scan to game.c and then

	Gamestore p=malloc(sizeof(gamestore));
	Assess(p,g); // Stores the current game status in the game struct
   action actions;
   //call different functions based on current status
   if (p->Ultron->arcs<=ARC_THRESH){ //calls arc building logic in the situation more arcs are deemed needed CAN CHANGE THIS LATER BASED ON OTHER INPUT!!
      actions=ArcLogic(p,g); //arc logic determines best possible arc purchase and ensures sufficient students availible
   } //else if() add more possible actions when needed
	//input paths into logic function, determine best,translate, purchase then repeat until out of resources or arc value gets to certain point
	//Translate students for campus building, build campus in priority marked 
	//upgrade campus
	free(p);
   return actions;
}

void Assess(Gamestore p, Game g){
   p->whoseTurn=getWhoseTurn(g);
	assignregion(p); //assigns region array, assigned but needs number returns
   //assignarc(p);
	p->turncount=getTurnNumber(g);
   p->Ultron->arcs=getARCs(g,p->whoseTurn); // assigns amount of arcs currently held
	//hardcode vertex contents into arc/campus array
	//add things as needed
}
//function which scans all possible ARC locations, checks legality, scores location then returns best possible arc to build on
//can be enhanced futher on to look into future building of arcs rather then the immediate returns
action ArcLogic(Gamestore p,Game g){
   int flag=FALSE;
   int iterate=0;
   int index;
   int regioniteration[3];
   int tempscore=0;
   coords coords1;
   coords1.x=0;
   coords1.y=0;
   coords coordscheck;
   coordscheck.x=0;
   coordscheck.y=0;
   regions region;
   path edge;
   score Arcscore;
   Arcscore.score=0;
   action a;
   a.actionCode=OBTAIN_ARC;
   while (flag=FALSE){
      strcpy(edge,"RRLR"); //set initial hex column
      while (iterate<6){ //iterate through one hex, currently there is an overlap on the intial and final tested arc, however this works for the if statements, can be removed if ness
         strcpy(a.destination,edge);
         coords1=translatepath(edge);
         if (isLegalAction(g,a)==TRUE){ //check if legal then create score, then check which is higher
            region=regionarray[coords1.x][coords1.y];
            regioniteration[0]=region.a; //put into an array for easier iteration
            regioniteration[1]=region.b;
            regioniteration[2]=region.c;
            index=0;
            tempscore=0;
            while (index<=2){ //add score for each region
               if (getDiscipline(g,regioniteration[index])==STUDENT_THD){
                  tempscore=tempscore+THD_SCORE;
               } else if (getDiscipline(g,regioniteration[index])==STUDENT_BPS){
                  tempscore=tempscore+BPS_SCORE;
               } else if (getDiscipline(g,regioniteration[index])==STUDENT_BQN){
                  tempscore=tempscore+BQN_SCORE;
               } else if (getDiscipline(g,regioniteration[index])==STUDENT_MJ){
                  tempscore=tempscore+MJ_SCORE;
               } else if (getDiscipline(g,regioniteration[index])==STUDENT_MTV){
                  tempscore=tempscore+MTV_SCORE;
               } else if (getDiscipline(g,regioniteration[index])==STUDENT_MMONEY){
                  tempscore=tempscore+MMONEY_SCORE;
               }
               index++;
            }
            if (tempscore>Arcscore.score){
               strcpy(Arcscore.edge,edge); //copy string into keeping store
               Arcscore.score=tempscore; //store reigning arcs score
            }
         }
         strcat(edge,"L"); //adds an L to the end of the arc
         iterate++
      }
      coordscheck=translatepath(edge); //could probably even shorten this if needed by unifying coords system
      if ((coordscheck.x==0)&&(coordscheck.y==6)){ //column two adjust
         strcpy(edge,"RR"); //can chuck in some asserts at each of these to ensure proper translate
      } else if ((coordscheck.x==1)&&(coordscheck.y==7)){
         strcpy(edge,"LB");
      } else if ((coordscheck.x==2)&&(coordscheck.y==8)){
         strcpy(edge,"LRLB"); //using backs to keep orientation so that adding L can be used
      } else if ((coordscheck.x==3)&&(coordscheck.y==7)){
         strcpy(edge,"LRLRLB");
      } else if ((coordscheck.x==4)&&(coordscheck.y==6)){
         flag=TRUE; //finished going through it all so its done
      } else {
         strcat(edge,"BRRR");//advance to next hex, instead of just adding 2 Ls a back and 3 rights is used to preserve direction so that to iterate around the hex only lefts need to be used
      }
   }
   strcpy(a.destination,Arcscore.edge);
   return a;
}
void assignregion(Gamestore g){
   regions r;
   r.a=0;
   r.b=0;
	r.c=0;
   g->regionarray[0][2]=r;
   g->regionarray[0][3]=r;

   r.a=0;
   r.b=1;
   r.c=INVALID;
   g->regionarray[0][4]=r;
   g->regionarray[0][5]=r;

   r.a=1;
   r.b=2;
   r.c=INVALID;
   g->regionarray[0][6]=r;
   g->regionarray[0][7]=r;

   r.a=INVALID;
   g->regionarray[0][8]=r;

   r.b=3;
   g->regionarray[1][1]=r;

   r.a=0;
   g->regionarray[1][2]=r;

   r.c=4;
   g->regionarray[1][3]=r;

   r.b=1;
   g->regionarray[1][4]=r;

   r.a=5;
   g->regionarray[1][5]=r;

   r.c=2;
   g->regionarray[1][6]=r;

   r.b=6;
   g->regionarray[1][7]=r;

   r.a=INVALID;
   g->regionarray[1][8]=r;

   r.c=INVALID;
   g->regionarray[1][9]=r;

   r.a=INVALID;
   r.b=INVALID;
   r.c=7;
   g->regionarray[2][0]=r;

   r.a=3;
   g->regionarray[2][1]=r;

   r.b=8;
   g->regionarray[2][2]=r;

   r.c=4;
   g->regionarray[2][3]=r;

   r.a=9;
   g->regionarray[2][4]=r;

   r.b=5;
   g->regionarray[2][5]=r;

   r.c=10;
   g->regionarray[2][6]=r;

   r.a=6;
   g->regionarray[2][7]=r;

   r.b=11;
   g->regionarray[2][8]=r;

   r.c=INVALID;
   g->regionarray[2][9]=r;

   r.a=INVALID;
   g->regionarray[2][10]=r;

   r.b=7;
   g->regionarray[3][0]=r;

   r.c=12;
   g->regionarray[3][1]=r;

   r.a=8;
   g->regionarray[3][2]=r;

   r.b=13;
   g->regionarray[3][3]=r;

   r.c=9;
   g->regionarray[3][4]=r;

   r.a=14;
   g->regionarray[3][5]=r;

   r.b=10;
   g->regionarray[3][6]=r;

   r.c=15;
   g->regionarray[3][7]=r;

   r.a=11;
   g->regionarray[3][8]=r;

   r.b=INVALID;
   g->regionarray[3][9]=r;

   r.c=INVALID;
   g->regionarray[3][10]=r;

   r.a=12;
   g->regionarray[4][1]=r;

   r.b=16;
   g->regionarray[4][2]=r;

   r.c=13;
   g->regionarray[4][3]=r;

   r.a=17;
   g->regionarray[4][4]=r;

   r.b=14;
   g->regionarray[4][5]=r;

   r.c=18;
   g->regionarray[4][6]=r;

   r.a=15;
   g->regionarray[4][7]=r;

   r.b=INVALID;
   g->regionarray[4][8]=r;

   r.c=INVALID;
   g->regionarray[4][9]=r;

   r.a=16;
   g->regionarray[5][2]=r;
   g->regionarray[5][3]=r;

   r.b=17;
   g->regionarray[5][4]=r;

   r.a=INVALID;
   g->regionarray[5][5]=r;

   r.a=18;
   g->regionarray[5][6]=r;

   r.b=INVALID;
   g->regionarray[5][7]=r;
   g->regionarray[5][8]=r;

   //assign exisintg points, arcs do not exist in these locs but arcs can be built from them, therefore they must be stated as if they have arcs
}
coords translatepath(path arc){
   //needs a response for if the path is empty
   int prevycoords=0;
   coords coord;
   int prevxcoords=2;
   int xcoords=2;
   int ycoords=0;
   int leftx=0;
   int lefty=0;
   int rightx=0;
   int righty=0;
   int tempx=0;
   int tempy=0;
   int approach=DOWN;
   int index=0;
   while(arc[index]!=0){
      //determine approach
      //There is never a possibility of changing both x and y, therefore it isn't accounted for (yeah it should error trap but its our own function)
      if (prevycoords<ycoords||((ycoords==0)&&(index==0))){
         approach=DOWN;
      } else if (prevycoords>ycoords){
         approach=UP;
      } else if (prevxcoords<xcoords){
         approach=RIGHT;
      } else if (prevxcoords>xcoords){
         approach=LEFT;
      }
      //Compressed code, uncompressed found in other file
      if (((approach==DOWN)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2==0))||((approach==DOWN)&&(xcoords%2==1)&&(ycoords%2!=0))){ //EVENS EVENS and ODDS ODDS
         leftx=xcoords+1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==UP)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2==0))||((approach==UP)&&(xcoords%2==1)&&(ycoords%2!=0))){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords+1;
         righty=ycoords;
      } else if (((approach==RIGHT)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2==0))||((approach==RIGHT)&&(xcoords%2==1)&&(ycoords%2!=0))){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if ((approach==RIGHT)&&(xcoords%2==1)&&(ycoords%2!=0)){
         //avoiding combining the invalid statements as they are so damn long
         leftx=xcoords; //if this happens it should be picked up by the islegalfunction
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==DOWN)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2!=0))||((approach==DOWN)&&(xcoords%2==1)&&(ycoords%2==0))){ //EVENS ODDS
         leftx=xcoords;
         lefty=ycoords+1;
         rightx=xcoords-1;
         righty=ycoords;
      } else if (((approach==UP)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2!=0))||((approach==UP)&&(xcoords%2==1)&&(ycoords%2==0))){
         leftx=xcoords-1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords-1;
      } else if (((approach==RIGHT)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2!=0))||((approach==RIGHT)&&(xcoords%2==1)&&(ycoords%2==0))){
         //not possible DOUBLE CHECK
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==LEFT)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2!=0))||((approach==LEFT)&&(xcoords%2==1)&&(ycoords%2==0))){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if (((approach==LEFT)&&((xcoords==0)||(xcoords%2==0))&&(ycoords%2==0))||((approach==LEFT)&&(xcoords%2==1)&&(ycoords%2!=0))){
         leftx=xcoords;
         lefty=ycoords+1;
         rightx=xcoords;
         righty=ycoords-1;
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

/* 1. Mr Pass - starts spinoff if has resources, otherwise passes.  Why first? This is required to be the first Turk everyone submits.
2. Mr Move - Randomly makes position moves if has resources. this is important to win, logical next stage.
3. Mr know - makes moves towards better places avoiding detrimental regions. Minimises the inefficient moves
4. Mr teacher - Uses students on priority system, Makes the AI more efficient. Uses resources more effectively.
4. Ultron - Destroys all who oppose it. 


Plan for success: 
The most effective strategy appears to be one that minimises your reliance on the two students
that become useless if a 7 (the most likely roll) is rolled. This evidently means that expansion
towards better vertexes as fast as possible is the most efficient way to generate resources and points
As well as interfere with other players ability to gather points.

Summary -> spread wide, fast to the most beneficial spots as fast as possible */