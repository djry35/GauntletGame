#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>


#define INFINITY 20000
#define NEGINFINITY -20000

typedef enum m_
{
	NONE,
	X,
	O
} Marking;

typedef struct coor_
{
	int x;
	int y;
} Coordinates;

typedef struct s_
{
	double weight;
	Coordinates point;
	Marking mark;
	struct s_** neighbors;
} Square;

typedef struct p_
{
	Square* toWin;
	struct p_* nextNode;
} Node;

typedef struct g_
{
	Square** squares;
	double status;	
	Node* listOfAINodes;
	Node* listOfHumanNodes;
} Game;

typedef struct c_
{
	Square* square;
	struct c_* nextChoice;
} Choice;

typedef struct bb_
{
	Choice* squareChoices;	
} BeginnerBot;
