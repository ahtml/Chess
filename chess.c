#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct ChessPiece
{
	char pieceName;
	int movecount;
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

/**
Determine what colour the piece is
*/
int getColour(int asciiColour){
	// 1 --> White piece
	// 0 --> Black piece
	// determine colour using lower/upper case char of alpahbet
	if(asciiColour >= 97){
		printf("Piece is white\n");
		return 1;
	}
	else{
		printf("Piece is black\n");
		return 0;
	}
}

void possMovesPawn(int row,int column,int colour){
	/*
	TODO: 
	- Impliment En passant logic (https://en.wikipedia.org/wiki/En_passant)
	- Check for King in check scenario
	*/

	// If the pawn is black
	if(colour==0){
		// If the pawn is not in the last row
		if((row*8+column)<56){
			//If the spot one row in front is empty
			if(strcmp(&mainBoard[row+1][column].pieceName,"-") == 0){
				mainBoard[row][column].validPos[row+1][column] = true;
			}
			// If the pawn is not on the right edge
			if(column==7){
				if(getColour((int)&mainBoard[row+1][column+1].pieceName)!=colour){
					mainBoard[row][column].validPos[row+1][column+1] = true;
				}
			}
			// If the pawn is not on the left edge
			if(column==0){
				if(getColour(mainBoard[row+1][column-1].pieceName)!=colour){
					mainBoard[row][column].validPos[row+1][column-1] = true;
				}
			}
		}
		// If the piece hasn't moved yet and the spots for two rows in front are empty
		if((row*8+column)<16 && strcmp(&mainBoard[row+1][column].pieceName,"-") == 0 && strcmp(&mainBoard[row+2][column].pieceName,"-") == 0){
			mainBoard[row][column].validPos[row+2][column] = true;
		}
	}
	// If the pawn is white
	else{
		// If the pawn is not in the last row
		if((row*8+column)>7){
			//If the spot one row in front is empty
			if(strcmp(&mainBoard[row-1][column].pieceName,"-") == 0){
				mainBoard[row][column].validPos[row-1][column] = true;
			}
			// If the pawn is not on the right edge
			if(column==7){
				if(getColour((int)&mainBoard[row-1][column+1].pieceName)!=colour){
					mainBoard[row][column].validPos[row-1][column+1] = true;
				}
			}
			// If the pawn is not on the left edge
			if(column==0){
				if(getColour(mainBoard[row-1][column-1].pieceName)!=colour){
					mainBoard[row][column].validPos[row-1][column-1] = true;
				}
			}
		}
		// If the piece hasn't moved yet and the spots for two rows in front are empty
		if((row*8+column)>64 && strcmp(&mainBoard[row-1][column].pieceName,"-") == 0 && strcmp(&mainBoard[row-2][column].pieceName,"-") == 0){
			mainBoard[row][column].validPos[row-2][column] = true;
		}
	}
}

void possMovesCastle(int row,int column,int colour){
	/*
	TODO: 
	- Check for King in check scenario
	*/

	//Move forward
	for(int i = row+1;i<8;i++){
		//Can not jump over a piece
		if(strcmp(&mainBoard[i][column].pieceName,"-")!=0){
			//If the piece is the oppponents piece
			if(getColour((int)&mainBoard[i][column].pieceName)!=colour){
				mainBoard[row][column].validPos[i][column] = true;
			}
			break;
		}
		mainBoard[row][column].validPos[i][column] = true;
	}
	//Move backward
	for(int i = row-1;i>=0;i--){
		if(strcmp(&mainBoard[i][column].pieceName,"-")!=0){
			if(getColour((int)&mainBoard[i][column].pieceName)!=colour){
				mainBoard[row][column].validPos[i][column] = true;
			}
			break;
		}
		mainBoard[row][column].validPos[i][column] = true;
	}
	//Move to the right
	for(int i = column+1;i<8;i++){
		if(strcmp(&mainBoard[row][i].pieceName,"-")!=0){
			if(getColour((int)&mainBoard[row][i].pieceName)!=colour){
				mainBoard[row][column].validPos[row][i] = true;
			}
			break;
		}
		mainBoard[row][column].validPos[row][i] = true;
	}
	//Move to the left
	for(int i = column-1;i>=0;i--){
		if(strcmp(&mainBoard[row][i].pieceName,"-")!=0){
			if(getColour((int)&mainBoard[row][i].pieceName)!=colour){
				mainBoard[row][column].validPos[row][i] = true;
			}
			break;
		}
		mainBoard[row][column].validPos[row][i] = true;
	}
}

void possMovesKnight(int row, int column, int colour){
	/*
	TODO: 
	- Check for King in check scenario
	*/

	// Making an move by moving one to the right and two up
	if(row>=2 && column<=6){
		// Check if the spot is empty
		if(strcmp(&mainBoard[row-2][column+1].pieceName,"-")==0){
			mainBoard[row][column].validPos[row-2][column+1] = true;
		}
		// Check if the spot has the oponent's piece
		else if(getColour((int)&mainBoard[row-2][column+1])!=colour){
			mainBoard[row][column].validPos[row-2][column+1] = true;
		}
	}
	if(row>=1 && column<=5){
		if(strcmp(&mainBoard[row-1][column+2].pieceName,"-")==0){
			mainBoard[row][column].validPos[row-1][column+2] = true;
		}
		else if(getColour((int)&mainBoard[row-1][column+2])!=colour){
			mainBoard[row][column].validPos[row-1][column+2] = true;
		}
	}
	if(row<=6 && column<=5){
		if(strcmp(&mainBoard[row+1][column+2].pieceName,"-")==0){
			mainBoard[row][column].validPos[row+1][column+2] = true;
		}
		else if(getColour((int)&mainBoard[row+1][column+2])!=colour){
			mainBoard[row][column].validPos[row+1][column+2] = true;
		}
	}
	if(row<=5 && column<=6){
		if(strcmp(&mainBoard[row+2][column+1].pieceName,"-")==0){
			mainBoard[row][column].validPos[row+2][column+1] = true;
		}
		else if(getColour((int)&mainBoard[row+2][column+1])!=colour){
			mainBoard[row][column].validPos[row+2][column+1] = true;
		}
	}
	if(row<=5 && column>=1){
		if(strcmp(&mainBoard[row+2][column-1].pieceName,"-")==0){
			mainBoard[row][column].validPos[row+2][column-1] = true;
		}
		else if(getColour((int)&mainBoard[row+2][column-1])!=colour){
			mainBoard[row][column].validPos[row+2][column-1] = true;
		}
	}
	if(row<=6 && column>=2){
		if(strcmp(&mainBoard[row+1][column-2].pieceName,"-")==0){
			mainBoard[row][column].validPos[row+1][column-2] = true;
		}
		else if(getColour((int)&mainBoard[row+1][column-2])!=colour){
			mainBoard[row][column].validPos[row+1][column-2] = true;
		}
	}
	if(row>=1 && column>=2){
		if(strcmp(&mainBoard[row-1][column-2].pieceName,"-")==0){
			mainBoard[row][column].validPos[row-1][column-2] = true;
		}
		else if(getColour((int)&mainBoard[row-1][column-2])!=colour){
			mainBoard[row][column].validPos[row-1][column-2] = true;
		}
	}
	if(row>=2 && column>=1){
		if(strcmp(&mainBoard[row-2][column-1].pieceName,"-")==0){
			mainBoard[row][column].validPos[row-2][column-1] = true;
		}
		else if(getColour((int)&mainBoard[row-2][column-1])!=colour){
			mainBoard[row][column].validPos[row-2][column-1] = true;
		}
	}
}

void possMovesBishop(int row, int column, int colour){
	/*
	TODO: 
	- Check for King in check scenario
	*/

	// Move in the SE direction
	for(int i=row+1;i<8;i++){
		// Can not jump over piece
		if(strcmp(&mainBoard[i][column+i-row].pieceName,"-")!=0){
			//If the piece is the oppponents piece
			if(getColour((int)&mainBoard[i][column+i-row].pieceName)!=colour){
				mainBoard[row][column].validPos[i][column+i-row] = true;
			}
			break;
		}
		mainBoard[row][column].validPos[i][column+i-row] = true;
	}
	// Move in the NW direction
	for(int i = row-1;i>=0;i--){
		if(strcmp(&mainBoard[i][column+i-row].pieceName,"-")!=0){
			if(getColour((int)&mainBoard[i][column+i-row].pieceName)!=colour){
				mainBoard[row][column].validPos[i][column+i-row] = true;
			}
			break;
		}
		mainBoard[row][column].validPos[i][column+i-row] = true;
	}
	// Move in the SW direction
	for(int i = row+1;i<8;i++){
		if(strcmp(&mainBoard[i][column-i+row].pieceName,"-")!=0){
			if(getColour((int)&mainBoard[i][column-i+row].pieceName)!=colour){
				mainBoard[row][column].validPos[i][column-i+row] = true;
			}
			break;
		}
		mainBoard[row][column].validPos[i][column-i+row] = true;
	}
	// Move in the NE direction
	for(int i = row-1;i>=0;i--){
		if(strcmp(&mainBoard[i][column-i+row].pieceName,"-")!=0){
			if(getColour((int)&mainBoard[i][column-i+row].pieceName)!=colour){
				mainBoard[row][column].validPos[i][column-i+row] = true;
			}
			break;
		}
		mainBoard[row][column].validPos[i][column-i+row] = true;
	}
}

void possMovesQueen(int row, int column, int colour){
	/*
	TODO: 
	- Check for King in check scenario
	*/

	// The queen moves in a combination of the castle and the bishop
	possMovesCastle(row,column,colour);
	possMovesBishop(row,column,colour);
}

void possMovesKing(int row, int column, int colour){
	/*
	TODO:
	- Implement Castling
	- Check for King in check scenario
	*/

	// Not on the left side
	if(column!=0 && column!=7){
		if(strcmp(&mainBoard[row][column-1].pieceName,"-")==0 || getColour((int)&mainBoard[row][column-1])!=colour){
			mainBoard[row][column].validPos[row][column-1] = true;
		}
		if(strcmp(&mainBoard[row][column+1].pieceName,"-")==0 || getColour((int)&mainBoard[row][column+1])!=colour){
			mainBoard[row][column].validPos[row][column+1] = true;
		}
		if(row!=0){
			if(strcmp(&mainBoard[row-1][column-1].pieceName,"-")==0 || getColour((int)&mainBoard[row-1][column-1])!=colour){
				mainBoard[row][column].validPos[row-1][column-1] = true;
			}
			if(strcmp(&mainBoard[row-1][column].pieceName,"-")==0 || getColour((int)&mainBoard[row-1][column])!=colour){
				mainBoard[row][column].validPos[row-1][column] = true;
			}
			if(strcmp(&mainBoard[row-1][column+1].pieceName,"-")==0 || getColour((int)&mainBoard[row-1][column+1])!=colour){
				mainBoard[row][column].validPos[row-1][column+1] = true;
			}
		}
		if(row!=7){
			if(strcmp(&mainBoard[row+1][column-1].pieceName,"-")==0 || getColour((int)&mainBoard[row+1][column-1])!=colour){
				mainBoard[row][column].validPos[row+1][column-1] = true;
			}
			if(strcmp(&mainBoard[row+1][column].pieceName,"-")==0 || getColour((int)&mainBoard[row+1][column])!=colour){
				mainBoard[row][column].validPos[row+1][column] = true;
			}
			if(strcmp(&mainBoard[row+1][column+1].pieceName,"-")==0 || getColour((int)&mainBoard[row+1][column+1])!=colour){
				mainBoard[row][column].validPos[row+1][column+1] = true;
			}
		}
	}
	else if(column==0){
		if(strcmp(&mainBoard[row][column+1].pieceName,"-")==0 || getColour((int)&mainBoard[row][column+1])!=colour){
			mainBoard[row][column].validPos[row][column+1] = true;
		}
		if(row!=0){
			if(strcmp(&mainBoard[row-1][column].pieceName,"-")==0 || getColour((int)&mainBoard[row-1][column])!=colour){
				mainBoard[row][column].validPos[row-1][column] = true;
			}
			if(strcmp(&mainBoard[row-1][column+1].pieceName,"-")==0 || getColour((int)&mainBoard[row-1][column+1])!=colour){
				mainBoard[row][column].validPos[row-1][column+1] = true;
			}
		}
		if(row!=7){
			if(strcmp(&mainBoard[row+1][column].pieceName,"-")==0 || getColour((int)&mainBoard[row+1][column])!=colour){
				mainBoard[row][column].validPos[row+1][column] = true;
			}
			if(strcmp(&mainBoard[row+1][column+1].pieceName,"-")==0 || getColour((int)&mainBoard[row+1][column+1])!=colour){
				mainBoard[row][column].validPos[row+1][column+1] = true;
			}
		}
	}
	else{
		if(strcmp(&mainBoard[row][column-1].pieceName,"-")==0 || getColour((int)&mainBoard[row][column-1])!=colour){
			mainBoard[row][column].validPos[row][column-1] = true;
		}
		if(row!=0){
			if(strcmp(&mainBoard[row-1][column-1].pieceName,"-")==0 || getColour((int)&mainBoard[row-1][column-1])!=colour){
				mainBoard[row][column].validPos[row-1][column-1] = true;
			}
			if(strcmp(&mainBoard[row-1][column].pieceName,"-")==0 || getColour((int)&mainBoard[row-1][column])!=colour){
				mainBoard[row][column].validPos[row-1][column] = true;
			}
		}
		if(row!=7){
			if(strcmp(&mainBoard[row+1][column-1].pieceName,"-")==0 || getColour((int)&mainBoard[row+1][column-1])!=colour){
				mainBoard[row][column].validPos[row+1][column-1] = true;
			}
			if(strcmp(&mainBoard[row+1][column].pieceName,"-")==0 || getColour((int)&mainBoard[row+1][column])!=colour){
				mainBoard[row][column].validPos[row+1][column] = true;
			}
		}
	}

}

int possibleMoves(int row, int column){
	int colour = -1;
	int pos = 8*row + column;

	// If there is no piece in this square
	if(strcmp(&mainBoard[row][column].pieceName,"-")==0){
		printf("No piece found\n");
		return 0;
	}

	//Set the colour of the piece
	colour = getColour((int)&mainBoard[row][column].pieceName);
	
	//Identify and show possible moves respectively
	if(strcmp(&mainBoard[row][column].pieceName,"p") == 0 || strcmp(&mainBoard[row][column].pieceName,"P")==0){
		printf("Piece is a pawn.\n");
		possMovesPawn(row,column,colour);
	}
	else if(strcmp(&mainBoard[row][column].pieceName,"R") == 0 || strcmp(&mainBoard[row][column].pieceName,"r")==0){
		printf("Piece is a castle\n");
	}
	else if(strcmp(&mainBoard[row][column].pieceName,"N") == 0 || strcmp(&mainBoard[row][column].pieceName,"n")==0){
		printf("Piece is a knight\n");
	}
	else if(strcmp(&mainBoard[row][column].pieceName,"B") == 0 || strcmp(&mainBoard[row][column].pieceName,"b")==0){
		printf("Piece is a bishop\n");
	}
	else if(strcmp(&mainBoard[row][column].pieceName,"Q") == 0 || strcmp(&mainBoard[row][column].pieceName,"q")==0){
		printf("Piece is a queen\n");
	}
	else{
		printf("Piece is a king\n");
	}
	return 0;
}

void possibleMovesTests(){
	// For pawn
	possibleMoves(1,5);
	possibleMoves(6,4);
	possibleMoves(3,5);
}

int main(){
	
	initializeBoard();
	printBoard();
	possibleMovesTests();
	return 0;
}