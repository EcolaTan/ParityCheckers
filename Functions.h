#ifndef FUNCTIONS
#define FUNCTIONS
#include"Types.h"

// function that generates the game board
void generateGame(boardData * board)
{
    int i, j;
    //declare 0 pieces added
    board -> beta = 0;
    board -> alpha = 0;
    
    for(i = 0; i < R; i++)
    {
        for(j = 0; j < C; j++)
        {
            //Check if square is a movable square
            if(i % 2 == j % 2)
            {
                //Check if square is a Player Alpha starting square
                if(i > 4)
                {
                    board -> board_squares[i][j] = 'A';
                    board -> alpha_squares[board -> alpha][0] = i + 1;
                    board -> alpha_squares[board -> alpha][1] = j + 1;
                    board -> alpha += 1;
                }
                //Check if square is a Player Beta starting square
                else if(i < 2)
                {
                    board -> board_squares[i][j] = 'B';
                    board -> beta_squares[board -> beta][0]= i + 1;
                    board -> beta_squares[board -> beta][1] = j + 1;
                    board -> beta += 1;
                }
                //Check if square is a free square
                else
                    board -> board_squares[i][j] = ' ';
            }
            else
                board -> board_squares[i][j] = ' ';
        }
    }
}

// function to print the board
void PrintBoard(boardData * board)
{
	int i,j;
	printf("\n");
	for(i = 0; i < R; i++)
    {
    	printf("---------------------\n");
        for(j = 0; j < C; j++)
        	printf("| %c ",board -> board_squares[i][j]);
		printf("|\n");
	}
	printf("---------------------\n");
}

//fucntion to print all possible pieces to be chosen
void PrintPossiblePieces(boardData * board,char player)
{
	int i,j;
	printf("\n----------------------");
	printf("\n|  Available Pieces  |\n");
	printf("----------------------\n");
	for(i = 0; i < R; i++)
		for(j = 0; j < C; j++)
		{
			if(board -> board_squares[i][j] == player)
				printf("|\t(%d,%d)\t     |\n",i+1,j+1);
		}		
	printf("----------------------\n");
}

// check if x and y value is inbound
int inBound(int x,int y)
{
	if(x < 0 || x > 6 || y < 0 || y > 4)
		return 0;
	return 1;
}

// check if correct piece chosen
int isPlayerPiece(boardData * board,int x, int y, char player)
{
	// if piece is for player
	if(board -> board_squares[x][y] == player)
		return 1;
	return 0;
}

//loops through all starting position of enemy and check if it is occupied by your piece
void countBases(boardData * board,int matrix[][2],int* answer,char player)
{
	int i,x,y;
	for(i = 0; i < 5; i++)
	{
		x = matrix[i][0] - 1;
		y = matrix[i][1] - 1;
		if(isPlayerPiece(board,x,y,player))
			*answer += 1;
	}
}

//check if there is already a winner
int findWinner(boardData * board, char player)
{
	int BasePiece = 0,
		temp1 = 0,
		temp2 = 0;
		
	countBases(board,board -> beta_squares,&temp1,player);
	countBases(board,board -> alpha_squares,&temp2,player);
	
	//if draw
	if((BasePiece == board -> alpha && board -> alpha) &&(BasePiece == board -> beta && board -> beta)){
		printf("\nIt is a draw");
		return 1;
	}
		
	//if player Alpha
	if(player == 'A'){
		//count 'A' in beta original positions
		countBases(board,board -> beta_squares,&BasePiece,player);
		if(board -> beta == 0 || (BasePiece == board -> alpha && board -> alpha)){
			PrintBoard(board);
			printf("\nThe winner is Alpha");
			return 1;
		}
	}
	//if player beta
	else if(player == 'B'){
		//count 'B' in alpha original positions
		countBases(board,board -> alpha_squares,&BasePiece,player);
		if(board -> alpha == 0 || (BasePiece == board -> beta && board -> beta)){
			PrintBoard(board);
			printf("\nThe winner is Beta");
			return 1;
		}
	}
	return 0;
}

//Set B is defined by the bool enum 
//check if this is the players piece
void getMovablePiece(boardData * board,int* a, int* b,int* flag,char piece)
{
	while(!*flag){
    	//ask for input
    	printf("\nChoose piece to move\n");
    	printf("Choose x coordinate: ");
    	scanf("%d",a);
    	printf("Choose y coordinate: ");
    	scanf("%d",b);
    	*a -= 1;
    	*b -= 1;
    	//check if it is inbound or not
    	*flag = inBound(*a,*b);
    	//if inbound then check if its players or not
    	if(*flag){
    		//not yours then restart coordinates and flag
	    	if(!isPlayerPiece(board,*a,*b,piece))
			{
	    		*a = -1;
	    		*b = -1;
	    		*flag = 0;
	    		printf("\nThis is not your piece please choose another!\n");
			}
		}
		else
			printf("\nCoordinates are out of range!\n");
	}
}

//check if same parity
int sameParity(int x1, int y1)
{
	if(x1 % 2 == y1 % 2)
		return 1;
	return 0;
}

//print possible moves of the player
int PrintMoves(boardData * board,int x, int y,char piece)
{
	int i,x1,y1,count = 0;
	char enemy = (piece == 'A') ? 'B' : 'A';
	
	printf("\n----------------------");
	printf("\n|  Available Moves   |\n");
	printf("----------------------\n");
	for(i = 0; i < 3; i++)
	{
		if(piece == 'A')
		{
			x1 = x+alphaMoves[i][0];
			y1 = y+alphaMoves[i][1];
		}
		else if(piece == 'B')
		{
			x1 = x+betaMoves[i][0];
			y1 = y+betaMoves[i][1];
		}
		if(inBound(x1,y1))
			if(isPlayerPiece(board,x1,y1,' ') || (isPlayerPiece(board,x1,y1,enemy) && sameParity(x1,y1)))
			{
				count += 1;
				printf("|\t(%d,%d)\t     |\n",x1+1,y1+1);
			}
	}
	if(!count)
		printf("No possible moves can be done!\n");
	else
		printf("----------------------\n");
	return count;
}

int countMoves(boardData * board,int x, int y,char piece)
{
	int i,x1,y1,count = 0;
	char enemy = (piece == 'A') ? 'B' : 'A';
	for(i = 0; i < 3; i++)
	{
		if(piece == 'A')
		{
			x1 = x+alphaMoves[i][0];
			y1 = y+alphaMoves[i][1];
		}
		else if(piece == 'B')
		{
			x1 = x+betaMoves[i][0];
			y1 = y+betaMoves[i][1];
		}
		if(inBound(x1,y1))
			if(isPlayerPiece(board,x1,y1,' ') || (isPlayerPiece(board,x1,y1,enemy) && sameParity(x1,y1)))
				count += 1;
	}
	return count;
}

//determine which case is the move
int moveCases(boardData * board,int x, int y,int c,int d,char piece)
{
	int i,x1,y1;
	
	char enemy = (piece == 'A') ? 'B' : 'A';
	
	for(i = 0; i < 3; i++)
	{
		if(piece == 'A')
		{
			x1 = x+alphaMoves[i][0];
			y1 = y+alphaMoves[i][1];
		}
		else if(piece == 'B')
		{
			x1 = x+betaMoves[i][0];
			y1 = y+betaMoves[i][1];
		}
		if(inBound(x1,y1) && x1 == c && y1 == d){
			if(isPlayerPiece(board,c,d,' '))
				return 1;
			else if(isPlayerPiece(board,c,d,enemy) && sameParity(c,d))
				return 2;
		}
	}
	printf("Invlaid move try again\n");
	return 3;
}

//get the coordinate move and process the case 
void getMove(boardData * board,int a, int b,int* c, int* d,int* flag,char piece)
{
	int moveCase;
	
	while(!*flag){
    	//ask for input
    	printf("\nCoordinate to move\n");
    	printf("Choose x coordinate: ");
    	scanf("%d",c);
    	printf("Choose y coordinate: ");
    	scanf("%d",d);
    	*c -= 1;
    	*d -= 1;
    	//check if it is inbound or not
    	*flag = inBound(*c,*d);
    	//if inbound then check if its players or not
    	if(*flag)
    		moveCase = moveCases(board,a, b,*c,*d,piece);
			if(moveCase == 3)
				*flag = 0;
	}
	//case 1 if space is empty
	if(moveCase == 1){
		board -> board_squares[a][b] = ' ';
		board -> board_squares[*c][*d] = piece;
	}
	
	//case 2 if space is occupied by enemy
	else if(moveCase == 2){
		board -> board_squares[a][b] = ' ';
		board -> board_squares[*c][*d] = piece;
		if(piece == 'A')
			board -> beta -= 1;
		else if(piece == 'B')
			board -> alpha -= 1;
	}
}

/* Game Functions */
void NextPlayerMove(boardData * board, bool aTurn, bool * over)
{
    /* Variables */ 
    //Is Valid Move?    
    int a = -1,
		b = -1,
		c = -1,
		flag = 0,
		d = -1,
		possibleMoves= 0,
		Next = 0,
		i,j,count;
		
	//character to be checked
	char piece = (aTurn) ? 'A' : 'B';
	//check winner before each move
	if(findWinner(board,piece))
		*over = True;

	count = 0;
	//check if there is still a movable piece for player
	for(i = 0; i < R; i++)
		for(j = 0; j < C; j++){
			if(board -> board_squares[i][j] == piece)
				count += countMoves(board,i,j,piece);
		}
	
	//if no possible moves for player draw
	if(count == 0){
		*over = True;
		printf("\nIt is a draw");
	}

    /* Function Proper */
    //if no moves can be done ask for another piece
    while(!Next && !*over)
	{
		printf("\n---------------------");
		if(aTurn)
			printf("\n|   Alpha's turn    |");
    	else
    		printf("\n|   Beta's turn     |");
		PrintBoard(board);
		PrintPossiblePieces(board,piece);
		
	    //select piece to move
	    getMovablePiece(board,&a, &b,&flag,piece);
	    
	    //move piece and validate it
	    possibleMoves = PrintMoves(board,a,b,piece);
	    
	    flag = 0;
	    //select diagonal move
	    if(possibleMoves){
	    	getMove(board,a,b,&c,&d,&flag,piece);
	    	Next = 1;
	    	//check win every after each successful move
			if(findWinner(board,piece))
				*over = True;
		}
	}
}
#endif
