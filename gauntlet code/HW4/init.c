#include "structs.h"
#include "funcs.h"

int main(void)
{
	srand(time(NULL));
	Game* game;
	BeginnerBot* bBot;

	int err = initGame(&game);

	err = initBBot(game, &bBot);
	//err = initABot(game);
	//err = initMBot(game);

	err = playGame1(game, bBot);
	
	if(err == 1)
		printf("You win!\n");
	else if(err == -1)
		printf("You lose!\n");
	else if(err = INFINITY)
		printf("It's a tie!\n");
	else
		printf("WHAT?\n");

	//err = playGame2(game, aBot);
	//err = playGame3(game, mBot);

	cleanMem(game);

	return 0;
}

int initBBot(Game* game, BeginnerBot** bot)
{
	*bot = malloc(sizeof(BeginnerBot));
	BeginnerBot* bBot = *bot;
	bBot->squareChoices = NULL;
	
	int i;
	int j;
	Choice* tmp; 
	Choice* tmp2;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			tmp = malloc(sizeof(Choice));
			tmp->square = &(game->squares[i][j]);
			tmp->nextChoice = NULL;
			if(!bBot->squareChoices)
			{
				bBot->squareChoices = tmp2 = tmp;
			}
			else
			{
				tmp2->nextChoice = tmp;
				tmp2 = tmp;
			}
		}
	}
}

void cleanMem(Game* game)
{
	int i;
	int j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			free(game->squares[i][j].neighbors);
		}
		free(game->squares[i]);
	}

	free(game->squares);
	free(game);
}

int initGame(Game** game)
{
	*game = malloc(sizeof(Game));
	Game* g = *game;
	g->listOfHumanNodes = NULL;
	g->listOfAINodes = NULL;

	g->status = 0;

	g->squares = malloc(sizeof(Square*)*4);
	int i;
	for(i = 0; i < 4; i++)
	{
		g->squares[i] = malloc(sizeof(Square)*4);
	}

	int j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			g->squares[i][j].mark = NONE;
			//g->squares[i][j].mark = rand()%3;
			g->squares[i][j].point.x = i;
			g->squares[i][j].point.y = j;
			g->squares[i][j].weight = 0;
			g->squares[i][j].neighbors = malloc(sizeof(Square*)*8);
			g->squares[i][j].neighbors[0] = NULL;
			g->squares[i][j].neighbors[1] = NULL;
			g->squares[i][j].neighbors[2] = NULL;
			g->squares[i][j].neighbors[3] = NULL;
			g->squares[i][j].neighbors[4] = NULL;
			g->squares[i][j].neighbors[5] = NULL;
			g->squares[i][j].neighbors[6] = NULL;
			g->squares[i][j].neighbors[7] = NULL;
		}
	}

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(i - 1 >= 0 && j - 1 >= 0)
				g->squares[i][j].neighbors[0] = &(g->squares[i-1][j-1]);
			if(i - 1 >= 0)
				g->squares[i][j].neighbors[1] = &(g->squares[i-1][j]);
			if(i - 1 >= 0 && j + 1 < 4)
				g->squares[i][j].neighbors[2] = &(g->squares[i-1][j+1]);
			if(j - 1 >= 0)
				g->squares[i][j].neighbors[3] = &(g->squares[i][j-1]);
			if(j + 1 < 4)
				g->squares[i][j].neighbors[4] = &(g->squares[i][j+1]);
			if(i + 1 < 4 && j - 1 >= 0)
				g->squares[i][j].neighbors[5] = &(g->squares[i+1][j-1]);
			if(i + 1 < 4)
				g->squares[i][j].neighbors[6] = &(g->squares[i+1][j]);
			if(i + 1 < 4 && j + 1 < 4)
				g->squares[i][j].neighbors[7] = &(g->squares[i+1][j+1]);
		}
	}

	return 0;
}
