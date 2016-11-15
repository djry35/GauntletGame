#include "structs.h"
#include "funcs.h"


int playGame1(Game* game, BeginnerBot* bBot)
{
	while(1)
	{
		printBoard(game);
	
		printf("Select your square (you are X): \n");
		printf("Row (0-3): ");
		int row, column;
		scanf("%d", &row);
		printf("Column (0-3): ");
		scanf("%d", &column);

		if(row == -1) break;

		game->squares[row][column].mark = X;
			
		int c = updateGame(game, &(game->squares[row][column]), X);
		
		if(c != 0) return c;

		Square* AIsquare = AIcompute1(bBot, &(game->squares[row][column]), game);	
		AIsquare->mark = O;
		
		c = updateGame(game, AIsquare, O);
		
		if(c != 0) return c;

	}
	
	return 0;
}

int updateGame(Game* game, Square* justMarked, Marking m)
{	
	Node* justMoved, *other;

	if(m == O)
	{
		justMoved = game->listOfAINodes;
		other = game->listOfHumanNodes;
	}
	else
	{	
		justMoved = game->listOfHumanNodes;
		other = game->listOfAINodes;
	}

	Node* tmp = justMoved;
	Node* prev = tmp;
	Node* next;
	if(tmp)
		next = tmp->nextNode;
	
	while(tmp)
	{
		//check if justMarked matches a win 
		if(tmp->toWin == justMarked && m == O)
			return -1;
		else if(tmp->toWin == justMarked && m == X)
			return 1;

		tmp = tmp->nextNode;
	}

	//figure out if any new win cons came up, add to list
	int i;
	for(i = 0; i < 8; i++)
	{
		if(justMarked->neighbors[i])
		{
			if(justMarked->neighbors[i]->mark == m)
			{
				if(justMarked->neighbors[7-i] && justMarked->neighbors[7-i]->mark == NONE)
				{
					Node* new = justMoved;
					while(new)
					{
						if(new->toWin == justMarked->neighbors[7-i])
						{
							break;
						}
						new = new->nextNode;
					}
					if(!new)
					{
						new = malloc(sizeof(Node));
						new->toWin = justMarked->neighbors[7-i];
						new->nextNode = justMoved;
						justMoved = new;
					}	
					
				}

				if(justMarked->neighbors[i]->neighbors[i] && justMarked->neighbors[i]->neighbors[i]->mark == NONE)
				{
					Node* new = justMoved;
					while(new)
					{
						if(new->toWin == justMarked->neighbors[i]->neighbors[i])
						{
							break;
						}
						new = new->nextNode;
					}
					if(!new)
					{
						new = malloc(sizeof(Node));
						new->toWin = justMarked->neighbors[i]->neighbors[i];
						new->nextNode = justMoved;
						justMoved = new;
					}	
				}

				//do one more case for sandwitched spot. 
				//check neighbors[i]->neighbors[i] for all of them?
				//and then neighbors[i] is blank
			}
		}
	}
	
	tmp = prev = other;
	if(tmp)
		next = tmp->nextNode;

	while(tmp)
	{
		//check if justMarked blocks a win
		//update other to remove matching node
		//
		//Every node in the list of win cons will be unique, 
		//so once we find it we're good. 
		if(tmp->toWin == justMarked)
		{
			if(tmp == other)
			{
				other = other->nextNode;
				free(tmp);
			}
			else
			{
				prev->nextNode = next;
				free(tmp);
			}

			break;
		}
		else
		{
			prev = tmp;
			tmp = tmp->nextNode;
			if(tmp)
				next = tmp->nextNode;
		}
	}

	//update game with updated lists.
	if(m == X)
	{
		game->listOfHumanNodes = justMoved;
		game->listOfAINodes = other;
	}
	else
	{
		game->listOfAINodes = justMoved;
		game->listOfHumanNodes = other;
	}

	
	//calculate status here. This is from heuristic, probably.
	int numAIWinSpots = 0, numHumanWinSpots = 0;

	//I believe this is cat's game.
	//(can you have one be NULL and the other not?)
	if(!justMoved && !other && allCovered(game->squares))
		return INFINITY;
	
	return 0;
}

bool allCovered(Square** squares)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(squares[i][j].mark == NONE)
				return false;
		}
	}

	return true;
}

Square* AIcompute1(BeginnerBot* bBot, Square* s, Game* game)
{
	Node* oppNode = game->listOfHumanNodes;
	Node* AINode = game->listOfAINodes;

	if(AINode)
		return AINode->toWin;
	else if(oppNode)
		return oppNode->toWin;
	else
	{
		Choice* tmp = bBot->squareChoices;
		while(tmp->square->mark != NONE)
		{
			bBot->squareChoices = bBot->squareChoices->nextChoice;
			free(tmp);
			tmp = bBot->squareChoices;
		}
		return tmp->square;
	}

	//can't get here. 
	return NULL;
}

void printBoard(Game* game)
{
	printf("----------Board--------------\n");
	printf("state: %f (negative = AI is winning)\n\n", game->status);

	int w = 4, h = 4;
	int x, y;
	int i = -1, j = -1; 
	Square** squares = game->squares;

	for(y = 0; y < h; y++)
	{
		i++;
		printf("\n");
		for(x = 0; x < w; x++)
		{
			printf("+---");
		}
		printf("+\n");
		for(x = 0; x < w; x++)
		{
			j++;
			if(squares[i][j].mark == NONE)
				printf("|   ");
			else if(squares[i][j].mark == X)
				printf("| X ");
			else
				printf("| O ");
		}
		printf("|");
		j = -1;
	}
	printf("\n");
	for(x = 0; x < w; x++)
	{
		printf("+---");
	}
	printf("+\n\n\n");

}
