#ifndef TYPES
#define TYPES

/* Constants */
//Number of Rows
#define R 7
//Number of Columns
#define C 5

//diagonal move coordinates
#define alphaMoves (int[3][2]) {{-1,-1},{-1,0},{-1,1}}
#define betaMoves (int[3][2]) {{1,-1},{1,0},{1,1}}

/* New Data Types */
//Boolean Data Type
enum boolean{True = 1, False = 0};
typedef enum boolean bool;

//Board Data Data Type
typedef struct boardData
{
    //All squares
    char board_squares[R][C];
    //default squares of alpha
    int alpha_squares[5][2];
    //default squares of beta
    int beta_squares[5][2];
    //number of pieces left in the game
    int beta;
    int alpha;
    
} boardData;
#endif
