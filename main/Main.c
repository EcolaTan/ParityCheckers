#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"Functions.h"

int main()
{
    /* System Variables */
    //Board Variable
    boardData board;  
    //Is Alpha's Turn?
    bool aTurn = True;
    //Is Over?
    bool over = False;
    /* Initializations */
    generateGame(&board);
	while(!over){
		NextPlayerMove(&board,aTurn,&over);
		aTurn = !aTurn;
	}
}
