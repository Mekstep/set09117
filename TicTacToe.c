#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//Niall Swan 40207307

//board squares
enum { NOUGHTS, CROSSES, BORDER, EMPTY };
enum { HUMANWIN, COMPWIN, DRAW };

//playable board locations
const int ConvertTo25[9] = 
{	
	6,7,8,
	11,12,13,
	16,17,18
	
};

//set up the board
void InitialiseBoard(int *board) 
{
	int index = 0;
	
	for(index = 0; index < 25; ++index) 
	{
		
		board[index] = BORDER;
	}
	
	//get playable locations
	for(index = 0; index < 9; ++index) 
	{
		
		board[ConvertTo25[index]] = EMPTY;
	}	
}

//print the board
void PrintBoard(const int *board) 
{
	int index = 0;
	char pieces[] = "OX|-";
	printf("\nBoard:\n");
	
	//print squares
	for(index = 0; index < 9; ++index) 
	{
		
		//create a new line after every 3 squares
		if(index!=0 && index%3==0) 
		{
			
			printf("\n");
		}
		
		printf("%4c",pieces[board[ConvertTo25[index]]]);
	}
	
	printf("\n");
}

int HasEmpty(const int *board) 
{
	int index = 0;
	
	for(index = 0; index < 9; ++index) 
	{
		if( board[ConvertTo25[index]] == EMPTY) return 1;
	}
	return 0;
}


void MakeMove(int *board, const int sq, const side) 
{
	board[sq] = side;
}


//players move
int GetPlayerMove(const int *board) 
{	
	//user inserted move
	char userInput[4];
	
	int moveOk = 0;
	int move = -1;
	
	while (moveOk == 0) 
	{
	
		//prompt
		printf("Please enter a move from 1 to 9:");		
		
		//get input
		fgets(userInput, 3, stdin);
		
		//flush removes remaining values if player enters a long string 
		fflush(stdin);
		
		//invalid input
		if(strlen(userInput) != 2) 
		{
			printf("Invalid strlen()\n");
			continue;			
		}
		
		//if input is not a number error
		if( sscanf(userInput, "%d", &move) != 1) 
		{
			move = -1;
			printf("Invalid sscanf()\n");
			continue;
		}
		
		//if move is not between 1 and 9 error
		if( move < 1 || move > 9) 
		{
			move = -1;
			printf("Invalid range\n");
			continue;
		}
		
		move--; //zero indexing
		
		//is the board empty at selected position
		if( board[ConvertTo25[move]]!=EMPTY) 
		{
			move=-1;
			printf("Square not available\n");
			continue;
		}
		moveOk = 1;
	}
	
	//print move
	printf("Making Move...%d\n",(move+1));
	
	//return move
	return ConvertTo25[move];
}

//AI move
int GetCompMove(const int *board)
{
	int index = 0;
	int numFree = 0;
	int availableMoves[9];
	int randMove = 0;
	
	//for all the playable spaces on the board
	for(index = 0; index < 9; ++index)
	{
		//find empty locations on the board
		if(board[ConvertTo25[index]] == EMPTY)
		{
			//add to available moves
			availableMoves[++numFree] = ConvertTo25[index];
		};
	}
	
	//get random move from available moves
	randMove = (rand() % numFree);
	
	//return random move
	return availableMoves[randMove];
}

//run the game
void RunGame() {

	int GameOver = 0;
	int Side = NOUGHTS;
	int LastMoveMade = 0;
	
	//declare board
	int board[25];
	//initialise board
	InitialiseBoard(&board[0]);
	//print board
	PrintBoard(&board[0]);
	
		while(!GameOver) 
		{
			if(Side==NOUGHTS) 
			{		
				// get player 1 move
				LastMoveMade = GetPlayerMove(&board[0]);
				MakeMove(&board[0], LastMoveMade, Side);
				Side = CROSSES;
				PrintBoard(&board[0]);
			} 
			else 
			{
				// get player 2 move
				LastMoveMade = GetPlayerMove(&board[0]);
				MakeMove(&board[0], LastMoveMade, Side);
				Side = NOUGHTS;
				PrintBoard(&board[0]);
			}

		}
		
		//draw
		if(!HasEmpty(board))
		{
			printf("Game over! \n");
			GameOver = 1;
			printf("It's a draw\n");
		}
		
	
}

int main() {		
	
	srand(time(NULL));
	RunGame();
		
	return 0;
}






