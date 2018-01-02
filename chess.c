#include <stdio.h>
char mainBoard [8][8];

// Function to initialize all the pieces
void initializeBoard(){
	// Pieces for black side
	mainBoard[0][0] = 'R';
	mainBoard[0][1] = 'N';
	mainBoard[0][2] = 'B';
	mainBoard[0][3] = 'Q';
	mainBoard[0][4] = 'K';
	mainBoard[0][5] = 'B';
	mainBoard[0][6] = 'N';
	mainBoard[0][7] = 'R';
	// Setting up pawns for black side
	for(int i = 0; i<8;i++){
		mainBoard[1][i] = 'P';
	}
	// Setting up initial blank pieces
	for(int i = 2; i<6;i++){
		for(int j=0;j<8;j++){
			mainBoard[i][j] = '-';
		}
	}
	// Pieces for white side
	for(int i = 0; i<8;i++){
		mainBoard[6][i] = 'p';
	}
	mainBoard[7][0] = 'r';
	mainBoard[7][1] = 'n';
	mainBoard[7][2] = 'b';
	mainBoard[7][3] = 'q';
	mainBoard[7][4] = 'k';
	mainBoard[7][5] = 'b';
	mainBoard[7][6] = 'n';
	mainBoard[7][7] = 'r';
}

// Printing the board
void printBoard(){
	for(int i = 0;i<8;i++){
		for(int j = 0;j<8;j++){
			printf("%c ",mainBoard[i][j]);
		}
		printf("\n");
	}
}

int main(){
	
	initializeBoard();
	printBoard();
	return 0;
}