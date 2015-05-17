      /* UNCOMPRESSED CODE
      //determine options
      if ((approach==DOWN)&&((xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2==0)){ //EVENS EVENS
         leftx=xcoords+1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords+1;
      } else if ((approach==UP)&&((xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2==0)){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords+1;
         righty=ycoords;
      } else if ((approach==RIGHT)&&((xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2==0)){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if ((approach==LEFT)&&((xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2==0)){
         //not possible RETURN INVALID somehow??
         leftx=INVALID;
         lefty=INVALID;
         rightx=INVALID;
         righty=INVALID;         
      } else if ((approach==DOWN)&&(xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2!=0)){ //EVENS ODDS
         leftx=xcoords;
         lefty=ycoords+1;
         rightx=xcoords-1;
         righty=ycoords;
      } else if ((approach==UP)&&(xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2!=0)){
         leftx=xcoords-1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords-1;
      } else if ((approach==RIGHT)&&(xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2!=0)){
         //not possible DOUBLE CHECK
         leftx=INVALID;
         lefty=INVALID;
         rightx=INVALID;
         righty=INVALID;
      } else if ((approach==LEFT)&&(xcoords==0)||(xcoords==2)||(xcoords==4))&&(ycoords%2!=0)){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if ((approach==DOWN)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2==0)){ //ODDS EVENS
         leftx=xcoords;
         lefty=ycoords+1;
         rightx=xcoords-1;
         righty=ycoords;
      } else if ((approach==UP)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2==0)){
         leftx=xcoords-1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords-1;
      } else if ((approach==RIGHT)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2==0)){
         //not possible
         leftx=INVALID;
         lefty=INVALID;
         rightx=INVALID;
         righty=INVALID;
      } else if ((approach==LEFT)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2==0)){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if ((approach==DOWN)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2!=0)){ //ODDS ODDS
         leftx=xcoords+1;
         lefty=ycoords;
         rightx=xcoords;
         righty=ycoords+1;
      } else if ((approach==UP)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2!=0)){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords+1;
         righty=ycoords;
      } else if ((approach==RIGHT)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2!=0)){
         leftx=xcoords;
         lefty=ycoords-1;
         rightx=xcoords;
         righty=ycoords+1;
      } else if ((approach==RIGHT)&&((xcoords==3)||(xcoords==1)||(xcoords==5))&&(ycoords%2!=0)){
         //not possible
         leftx=INVALID;
         lefty=INVALID;
         rightx=INVALID;
         righty=INVALID;         
      } */



//Prior to pointer hacking

            if (player == UNI_A){
      if (student == STUDENT_THD){
         g->player1.students.THD += amount;
      } else if (student == STUDENT_MMONEY){
         g->player1.students.MMONEY += amount;
      } else if (student == STUDENT_MJ){
         g->player1.students.MJ += amount;
      } else if (student == STUDENT_MTV){
         g->player1.students.MTV += amount;
      } else if (student == STUDENT_BQN){
         g->player1.students.BQN += amount;
      } else if (student == STUDENT_BPS){
         g->player1.students.BPS += amount;
      }
   }
   if (player == UNI_B){
      if (student == STUDENT_THD){
         g->player2.students.THD += amount;
      } else if (student == STUDENT_MMONEY){
         g->player2.students.MMONEY += amount;
      } else if (student == STUDENT_MJ){
         g->player2.students.MJ += amount;
      } else if (student == STUDENT_MTV){
         g->player2.students.MTV += amount;
      } else if (student == STUDENT_BQN){
         g->player2.students.BQN += amount;
      } else if (student == STUDENT_BPS){
         g->player2.students.BPS += amount;
      }
   }
   if (player == UNI_C){
      if (student == STUDENT_THD){
         g->player3.students.THD += amount;
      } else if (student == STUDENT_MMONEY){
         g->player3.students.MMONEY += amount;
      } else if (student == STUDENT_MJ){
         g->player3.students.MJ += amount;
      } else if (student == STUDENT_MTV){
         g->player3.students.MTV += amount;
      } else if (student == STUDENT_BQN){
         g->player3.students.BQN += amount;
      } else if (student == STUDENT_BPS){
         g->player3.students.BPS += amount;
      }
   }

//get most arcs prev
   /*
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
   */
   //Using Corey's logic as it accounts for simultaneous matchings

   /*int playerindex=UNI_A;
   while (playerindex<=UNI_C){
      if (playerindex == UNI_A) {
         player *p = &g->player1;
      } else if (playerindex == UNI_B) { //Pointer hack
         player *p = &g->player2;
      } else if (playerindex == UNI_C) {
         player *p = &g->player3; 
      }
      
      p->KPI=20; //intialise all values
      p->arcs=0;
      p->GO8s=0;
      p->Campuses=2;
      p->IPs=0;
      p->Pubs=0;
      p->students.THD=0;
      p->students.BPS=3;
      p->students.BQN=3;
      p->students.MJ=0;
      p->students.MTV=0;
      p->students.MMONEY=0;

      playerindex++;
   }*/