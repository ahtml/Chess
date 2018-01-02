#include <stdio.h>
#include <stdbool.h>

struct ChessPiece
{
	char pieceName;
	/*
	R: Castle (5 points)
	N: Knight (3 points)
	B: Bishop (3 points)
	P: Pawn (1 point)
	Q: Queen (9 points)
	-: No piece
	*/
	bool validPos[8][8]; // Where the piece can move
};

struct ChessPiece mainBoard [8][8];

// Function to initialize all the pieces
void initializeBoard(){
	// Pieces for black side
	mainBoard[0][0].pieceName = 'R';
	mainBoard[0][1].pieceName = 'N';
	mainBoard[0][2].pieceName = 'B';
	mainBoard[0][3].pieceName = 'Q';
	mainBoard[0][4].pieceName = 'K';
	mainBoard[0][5].pieceName = 'B';
	mainBoard[0][6].pieceName = 'N';
	mainBoard[0][7].pieceName = 'R';
	// Setting up pawns for black side
	for(int i = 0; i<8;i++){
		mainBoard[1][i].pieceName = 'P';
	}
	// Setting up initial blank pieces
	for(int i = 2; i<6;i++){
		for(int j=0;j<8;j++){
			mainBoard[i][j].pieceName = '-';
		}
	}
	// Pieces for white side
	for(int i = 0; i<8;i++){
		mainBoard[6][i].pieceName = 'p';
	}
	mainBoard[7][0].pieceName = 'r';
	mainBoard[7][1].pieceName = 'n';
	mainBoard[7][2].pieceName = 'b';
	mainBoard[7][3].pieceName = 'q';
	mainBoard[7][4].pieceName = 'k';
	mainBoard[7][5].pieceName = 'b';
	mainBoard[7][6].pieceName = 'n';
	mainBoard[7][7].pieceName = 'r';
}

// Printing the board
void printBoard(){
	printf(" |");
	for(int i=1;i<8;i++){
		printf("%d ",i);
	}
	printf("8|\n");
	for(int i = 0;i<8;i++){
		printf("%c|",65+i);
		for(int j = 0;j<7;j++){
			printf("%c ",mainBoard[i][j].pieceName);
		}
		printf("%c|%c\n",mainBoard[i][7].pieceName,65+i);
	}
	printf(" |");
	for(int i=1;i<8;i++){
		printf("%d ",i);
	}
	printf("8|\n");
}

int main(){
	
	initializeBoard();
	printBoard();
	return 0;
}