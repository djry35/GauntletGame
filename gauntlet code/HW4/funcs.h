void cleanMem(Game*);
int initGame(Game**);
void printBoard(Game*);
int initBBot(Game*, BeginnerBot**);
int playGame1(Game*, BeginnerBot*);
int checkGame(Square**);
Square* AIcompute1(BeginnerBot*, Square*, Game*);
bool allCovered(Square**);
