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