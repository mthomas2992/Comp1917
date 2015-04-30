Game newGame (int discipline[], int dice[]); //Matt

void disposeGame (Game g); //Bryan

void makeAction (Game g, action a); //Matt 

void throwDice (Game g, int diceScore); //Joerick

int getDiscipline (Game g, int regionID); //Matt

int getDiceValue (Game g, int regionID); //Bryan

int getMostARCs (Game g); //Byan

int getMostPublications (Game g); //Bryan

int getTurnNumber (Game g); //Bryan

int getWhoseTurn (Game g); //Joerick

int getCampus(Game g, path pathToVertex); //Joerick

int getARC(Game g, path pathToEdge); //Joerick

int isLegalAction (Game g, action a); //Matt

int getKPIpoints (Game g, int player); //Charly

int getARCs (Game g, int player); //Charly

int getGO8s (Game g, int player); //Charly

int getCampuses (Game g, int player); //Charly

int getIPs (Game g, int player); //Charly

int getPublications (Game g, int player); //Joerick

int getStudents (Game g, int player, int discipline); //Matt

int getExchangeRate (Game g, int player,
                     int disciplineFrom, int disciplineTo); //Matt