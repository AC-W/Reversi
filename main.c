#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void boardGeneration(char board[][26], int n);
bool legalMoveTest(char board[][26],int n, char colour,int row, int col);
bool legalMovesList(char board[][26],int n, char colour);
void replaceColours(char board[][26],int n, char colour,int row, int col);
void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
int makeMove(const char board[26][26], int n, char turn, int *row, int *col);
int gameConditionCheck(char board[][26], int n, char colour);
void copyBoard(char board[][26], char tempBoard [][26],int n);
int makeMove2(const char board[26][26], int n, char turn, int *row, int *col);
int moveValue(const char board[26][26],char tempBoard[][26],int n, char colour, int row, int col);
int moveCounter(char tempBoard[][26],int n, char colour);
int moveValue2(const char board[26][26],char tempBoard[][26],int n, char colour, int row, int col);
int getRand(int lowval,int highval);
void makeMoveRan(const char board[26][26], int n, char turn, int *row, int *col);
int takeScoreCounter(char board [][26],int n,char colour,int row, int col);
int takeScoreCounterDirection(char board [][26],int n,char colour,int row, int col,int deltaRow,int deltaCol);

void listMoves(char board[][26],int n, char colour);

int main(void){
int win = 0;
int draw = 0;
int lost = 0;
int n,rowNumber,colNumber,bestRowMove,bestColMove;
int *bestMoveRow = &bestRowMove;
int *bestMoveCol = &bestColMove;
char row,column,computerColor,scoreChecker;
char board[26][26];
char currentTurn = 'B';
char enemyTurn = 'W';
bool exit = false;
int end = 0;

printf("Enter the board dimension: ");
scanf("%d",&n);
boardGeneration(board,n);

printf("Computer plays (B/W) : ");
scanf(" %c",&computerColor);

exit = false;
boardGeneration(board,n); //Generate the board.
printBoard(board,n);

while ((legalMovesList(board,n,'B') || legalMovesList(board,n,'W')) && exit == false){
	if (currentTurn == 'B')
		enemyTurn = 'W';
	else
		enemyTurn = 'B';

	if (legalMovesList(board,n, currentTurn) && exit == false){
		if (computerColor == currentTurn){
			scoreChecker = makeMove(board,n,computerColor,bestMoveRow,bestMoveCol);
			if (legalMoveTest(board,n,computerColor,bestRowMove,bestColMove)){
				replaceColours(board,n,computerColor,bestRowMove,bestColMove); //if the move entered is vaild replaces all the apporiate colours.
				printf("Moved at %d %d\n",bestRowMove,bestColMove);
			}
			else {
				printf("Invalid move.\n");
				printf("%c player wins.\n",enemyTurn);
				exit = true;
			}
		}
		else {
			listMoves(board,n,currentTurn);
			printf("Make Your Move:");
			scanf(" %d %d",&bestRowMove,&bestColMove);
			if (legalMoveTest(board,n,currentTurn,bestRowMove,bestColMove)){
				replaceColours(board,n,currentTurn,bestRowMove,bestColMove); //if the move entered is vaild replaces all the apporiate colours.
			}
			else {
				printf("Invalid move.\n");
				printf("%c player wins.\n",enemyTurn);
				exit = true;
			}
		}
	}
	if (legalMovesList(board,n, enemyTurn) && exit == false){
		system("cls");
		printBoard(board,n);
		currentTurn = enemyTurn;
	}
}
int whiteScore = gameConditionCheck(board, n, 'W');
int blackScore = gameConditionCheck(board, n, 'B');
if (blackScore > whiteScore && exit == false){
	printf("B Player Wins");
}
else if (blackScore < whiteScore && exit == false){
	printf("W Player Wins");
}
else if (blackScore == whiteScore && exit == false){
	printf("Draw");
}
return 0;
}

int getRand(int lowval,int highval){
    return (rand()%(highval+1-lowval) + lowval);
}

void copyBoard(char board[][26], char tempBoard [][26],int n){
	int row,col;
	for (row = 0; row < n;  row++){
		for (col = 0; col < n;  col++){
			tempBoard [row][col] = board [row][col];
		}
	}
}


void makeMoveRan(const char board[26][26], int n, char turn, int *row, int *col){
	int currentRow = 0;
	int currentColumn  = 0;
	currentColumn = (getRand(0,n-1));
	currentRow = (getRand(0,n-1));
		do {
			currentColumn = (getRand(0,n-1));
			currentRow = (getRand(0,n-1));
		}
		while (!(legalMoveTest(board,n,turn,currentRow, currentColumn)));
	*row = currentRow;
	*col = currentColumn;
}

int makeMove(const char board[26][26], int n, char turn, int *row, int *col){
	int oldscore = -1000000000;
	int score = 0;
	int pause  = 0;
	char tempBoard [26][26];
	copyBoard(board,tempBoard,n);
	for (int currentRow = 0; currentRow < n; currentRow++){
		for (int currentCol = 0;currentCol < n;currentCol++){
			if (legalMoveTest(board,n,turn,currentRow, currentCol)){
				score = moveValue(board,tempBoard,n,turn,currentRow,currentCol);
				copyBoard(board,tempBoard,n);
				if (score >= oldscore){
					oldscore = score;
					*row = currentRow;
					*col = currentCol;
				} 
			}
		}
	}
	return score;
}

int moveValue(const char board[26][26],char tempBoard[][26],int n, char colour, int row, int col){
	char enemeyColour = 'B';
	if (colour == 'B')
		enemeyColour = 'W';
	int score = 0;
	int tempRow = row;
	int tempCol = col;
	int deltaRow = 0;
	int deltaCol = 0;
	int currentRow,currentCol;
	replaceColours(tempBoard,n,colour,row,col);
	if ((row == 0 && col == 0)||(row == 0 && col == n-1)||(row == n-1 && col == n-1)||(row == n-1 && col == 0)){
		if (board[0][0] != colour && board[0][n-1] != colour && board[n-1][n-1] != colour && board[n-1][0] != colour){
			score = score + 10000;
		}
		else if (takeScoreCounter(tempBoard,n,colour,row,col) >= 6){
			score = score + 10000;
		}
	}
	else if ((row == 0 && col == 1)||(row == 1 && col == 0)||(row == 1 && col == 1) && (board[0][0] == 'U')){
		if (!(legalMoveTest(tempBoard,n,enemeyColour,0,0)||legalMoveTest(tempBoard,n,enemeyColour,0,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,0)))
			if (row == 0 && col == 1 && takeScoreCounterDirection(board,n,colour,row,col,0,1) >= 1)
				score = score + 1000;
			else if (gameConditionCheck(board,n,colour)+gameConditionCheck(board,n,enemeyColour) <= 52) 
				score = score - 1000;
		if (!(legalMoveTest(tempBoard,n,enemeyColour,0,0)||legalMoveTest(tempBoard,n,enemeyColour,0,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,0)))
			if (row == 1 && col == 0 && takeScoreCounterDirection(board,n,colour,row,col,-1,0) >= 1)
				score = score + 1000;
			else if (gameConditionCheck(board,n,colour)+gameConditionCheck(board,n,enemeyColour) <= 52)
				score = score - 1000;
		if (row == 1 && col == 1 && gameConditionCheck(board,n,colour)+gameConditionCheck(board,n,enemeyColour) <= 52)
			score = score - 1000;
	}
	else if ((row == 0 && col == n-2)||(row == 1 && col == n-1)||(row == 1 && col == n-2) && (board[0][n-1] == 'U')){
		if (!(legalMoveTest(tempBoard,n,enemeyColour,0,0)||legalMoveTest(tempBoard,n,enemeyColour,0,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,0)))
			if (row == 0 && col == n-2 && takeScoreCounterDirection(board,n,colour,row,col,0,-1) >= 1)
				score = score + 1000;
			else
				score = score - 1000;
		if (!(legalMoveTest(tempBoard,n,enemeyColour,0,0)||legalMoveTest(tempBoard,n,enemeyColour,0,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,0)))
			if (row == 1 && col == n-1 && takeScoreCounterDirection(board,n,colour,row,col,-1,0) >= 1)
				score = score + 1000;
			else
				score = score - 1000;
	}
		
	else if ((row == n-1 && col == 1)||(row == n-2 && col == 1)||(row == n-2 && col == 0) && (board[n-1][0] == 'U')){
		if (!(legalMoveTest(tempBoard,n,enemeyColour,0,0)||legalMoveTest(tempBoard,n,enemeyColour,0,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,0)))
			if (row == n-1 && col == 1 && takeScoreCounterDirection(board,n,colour,row,col,0,1) >= 1)
				score = score + 1000;
			else
				score = score - 1000;
		if (!(legalMoveTest(tempBoard,n,enemeyColour,0,0)||legalMoveTest(tempBoard,n,enemeyColour,0,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,0)))
			if (row == n-2 && col == 0 && takeScoreCounterDirection(board,n,colour,row,col,1,0) >= 1)
				score = score + 1000;
			else
				score = score - 1000;
	}
	
	else if ((row == n-1 && col == n-2)||(row == n-2 && col == n-1)||(row == n-2 && col == n-2) && (board[n-1][n-1] == 'U')){
		if (!(legalMoveTest(tempBoard,n,enemeyColour,0,0)||legalMoveTest(tempBoard,n,enemeyColour,0,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,0)))
			if (row == n-1 && col == n-2 && takeScoreCounterDirection(board,n,colour,row,col,0,-1) >= 1)
				score = score + 1000;
			else
				score = score - 1000;;
		if (!(legalMoveTest(tempBoard,n,enemeyColour,0,0)||legalMoveTest(tempBoard,n,enemeyColour,0,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,n-1)||legalMoveTest(tempBoard,n,enemeyColour,n-1,0)))
			if (row == n-2 && col == n-1 && takeScoreCounterDirection(board,n,colour,row,col,1,0) >= 1)
				score = score + 1000;
			else
				score = score - 1000;
	}
	
		score = score + 1*takeScoreCounter(board,n,colour,row,col);
		if (gameConditionCheck(board,n,colour)+gameConditionCheck(board,n,enemeyColour) >= 62)
			score = score + 100*takeScoreCounter(board,n,colour,row,col);

		for (currentRow = 0;currentRow < n;currentRow++){
			for(currentCol = 0;currentCol < n;currentCol++){
				if (legalMoveTest(tempBoard,n,enemeyColour,currentRow,currentCol)){
					if ((currentRow == 0 && currentCol == 0)||(currentRow == 0 && currentCol == n-1)||(currentRow == n-1 && currentCol == n-1)||(currentRow == n-1 && currentCol == 0))
						score = score - 10000;
					if ((currentRow == 0 && currentCol == 2)||(currentRow == n-3 && currentCol == 0)||(currentRow == 0 && currentCol == 2)||(currentRow == n-1 && currentCol == 2)||(currentRow == n-1 && currentCol == n-3)||(currentRow == n-3 && currentCol == n-1)||(currentRow == 0 && currentCol == n-3)|| (currentRow == 2 && currentCol == n-1))
						score = score - 20;
					score = score - 1*takeScoreCounter(tempBoard,n,enemeyColour,currentRow,currentCol);
					if (gameConditionCheck(tempBoard,n,colour)+gameConditionCheck(tempBoard,n,enemeyColour) >= 62)
						score = score - 10*takeScoreCounter(tempBoard,n,enemeyColour,currentRow,currentCol);
				}
			}
		}
score = score - 1.5*moveCounter(tempBoard,n,enemeyColour);
return score;
}

int moveCounter(char tempBoard[][26],int n, char colour){
	int row,col, moveCount = 0;
	for (row = 0;row < n;row++){
		for(col = 0;col < n;col++){
			if (legalMoveTest(tempBoard,n,colour,row,col))
				moveCount++;
		}
	}
	return moveCount;
}


void boardGeneration(char board[][26], int n){ // This function generates a board for the game of reversi, vaild up to 26 by 26.
	int row,column;
	for (row = 0;row < n;row++){
		for (column = 0;column < n;column++){
			board[row][column] = 'U';
		}
	}
	//initize the pieces
	board [(n/2)-1][(n/2)-1] = 'B';
	board [(n/2)-1][(n/2)] = 'W';
	board [(n/2)][(n/2)-1] = 'W';
	board [(n/2)][(n/2)] = 'B';
}

bool legalMoveTest(char board[][26],int n, char colour,int row, int col){ //checks all the direction too determine if a move is legal.
	bool legal = false;
	int deltaRow,deltaCol;
	for(deltaRow = -1; deltaRow <= 1;deltaRow++){
		for(deltaCol = -1;deltaCol <= 1;deltaCol++){
			if (!(deltaCol == 0 && deltaRow == 0)){
				if (checkLegalInDirection(board,n,row,col,colour,deltaRow,deltaCol)) //if any of the 8 direction is legal then the move is legal.
					legal = true;
			}
		}
	}
	return legal;
}

void printBoard(char board[][26], int n) { //Prints the board with a,b,c ... indicating the rows and columns.
	int row,column;
	for (row = 0;row < n;row++){
		if (row == 0){ // prints the letters that indicate the columns.
			printf("  ");
			for (column = 0;column < n;column++){
				printf("  %d   ", column);
			}
		printf("\n");
		}
		printf("%d|", row); // prints the letters that indicate the rows.
		for (column = 0;column < n;column++){
			if (legalMoveTest(board,n,'W',row,column)){
				printf("  O  |");
			}
			else if(board[row][column] == 'U'){
				printf("     |");
			}
			else{
				printf("  %c  |",board[row][column]); //prints the board.
			}
		}
		printf("\n");
		for (column = 0;column < n-1;column++){
			printf("-------");
		}
		printf("\n");
	}
}

bool positionInBounds(int n, int row, int col) { //checks if the current position is on the board.
	if (row < n && col < n && row >= 0 && col >= 0)
		return true;
	else
		return false;  
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) { 
//The helper function that checks if the direction specify is vaild.
	int testCase=0;
	if (board[row][col] == 'U' && !(deltaRow == 0 && deltaCol== 0) && !(board[row+deltaRow][col+deltaCol] == colour)){//if the first colour it finds is the same, direction is invaild.
		//avoides checking deltaRow and deltaCol == 0 to avoid infinite loop.
		while (positionInBounds(n,row+deltaRow,col+deltaCol) && !(testCase == 1 || testCase == 2)){
			col = col + deltaCol;
			row = row + deltaRow;
			if  (board [row][col] == colour)
				testCase = 1; //finds the a different colour and set testCase = 1 so that the function start looking for the same colour.
			if (board [row][col] == 'U')
				testCase = 2; //if it finds a 'U' then sets testCase = 2 which exits the loop and indicate that direction is invaild.
			}
		}
	if (testCase == 1)
		return true;
	else
		return false;
}

bool legalMovesList(char board[][26],int n, char colour){ //uses the legalMoveTest function to list all the possible moves.
	bool legal = false;
	bool canMove = false;
	int row,col;
	for (row = 0;row < n;row++){
		for(col = 0;col < n;col++){
			if (legalMoveTest(board,n,colour,row,col))
				legal = true;
			if (legal){
				// if (colour == 'W'){
				// 	printf("W: %c%c\n",row+'a',col+'a');
				// }
				// else{
				// 	printf("B: %c%c\n",row+'a',col+'a');
				// }
			canMove = true;
			legal = false;
			}
		}
	}
	return canMove;
}

void listMoves(char board[][26],int n, char colour){ //uses the legalMoveTest function to list all the possible moves.
	bool legal = false;
	int row,col;
	printf("Legal Moves: \n");
	for (row = 0;row < n;row++){
		for(col = 0;col < n;col++){
			if (legalMoveTest(board,n,colour,row,col))
				legal = true;
			if (legal){
				printf("(%d,%d)  ",row,col);
				legal = false;
			}
		}
	}
	printf("\n");
}

void replaceColours(char board[][26],int n, char colour,int row, int col){ //replaces the apporiate colour when a move is made.
	int tempRow = row;
	int tempCol = col;
	int deltaRow,deltaCol;
	for(deltaRow = -1; deltaRow <= 1;deltaRow++){
		for(deltaCol = -1;deltaCol <= 1;deltaCol++){
			if(checkLegalInDirection(board,n,row,col,colour,deltaRow,deltaCol)){ //check all eight direction, if that direction is vaild, it will start replacing the colours in that direction.
				while (!(board[tempRow+deltaRow][tempCol+deltaCol]==colour) && !(board[tempRow+deltaRow][tempCol+deltaCol]=='U') && positionInBounds(n,row,col)){ //replaces all the opposite colours with the colour placed until it reaches the same colour.
					if (colour == 'W')
						board[tempRow+deltaRow][tempCol+deltaCol] = 'W';
					else
						board[tempRow+deltaRow][tempCol+deltaCol] = 'B';
					tempRow=tempRow+deltaRow;
					tempCol=tempCol+deltaCol;
				}
			}
		tempRow = row;
		tempCol = col;
		}
	}
	board[row][col] = colour;
}

int gameConditionCheck(char board[][26], int n, char colour){
	int row;
	int col;
	int score = 0;
	for (row = 0; row < n ; row++){
		for (col = 0; col < n; col++){
			if (board[row][col] == colour)
				score ++;
		}
	}
	return score;
}

int takeScoreCounter(char board [][26],int n,char colour,int row, int col){
int deltaRow;
int deltaCol;
int score = 0;
int tempRow = row;
int tempCol = col;
	for(deltaRow = -1; deltaRow <= 1;deltaRow++){
		for(deltaCol = -1;deltaCol <= 1;deltaCol++){
			if (deltaCol != 0 || deltaRow !=0 ){
				if(checkLegalInDirection(board,n,row,col,colour,deltaRow,deltaCol)){ //check all eight direction, if that direction is vaild, it will start replacing the colours in that direction.
				while (!(board[tempRow+deltaRow][tempCol+deltaCol]==colour) && !(board[tempRow+deltaRow][tempCol+deltaCol]=='U')){ //replaces all the opposite colours with the colour placed until it reaches the same colour.
						score = score + 1;
					tempRow=tempRow+deltaRow;
					tempCol=tempCol+deltaCol;
				}
				tempRow = row;
				tempCol = col;
			}
			}
		}
	}
	return score;
}

int takeScoreCounterDirection(char board [][26],int n,char colour,int row, int col,int deltaRow,int deltaCol){
int score = 0;
int tempRow = row;
int tempCol = col;
	if (deltaCol != 0 || deltaRow !=0 ){
		if(checkLegalInDirection(board,n,row,col,colour,deltaRow,deltaCol)){ //check all eight direction, if that direction is vaild, it will start replacing the colours in that direction.
			while (!(board[tempRow+deltaRow][tempCol+deltaCol]==colour) && !(board[tempRow+deltaRow][tempCol+deltaCol]=='U')){ //replaces all the opposite colours with the colour placed until it reaches the same colour.
					score = score + 1;
				tempRow=tempRow+deltaRow;
				tempCol=tempCol+deltaCol;
			}
			tempRow = row;
			tempCol = col;
		}
		}
	return score;
}

int moveValue2(const char board[26][26],char tempBoard[][26],int n, char colour, int row, int col){
	char enemeyColour = 'B';
	if (colour == 'B')
		enemeyColour = 'W';
	int score = 0;
	int tempRow = row;
	int tempCol = col;
	int deltaRow = 0;
	int deltaCol = 0;
	int currentRow,currentCol;
	for(deltaRow = -1; deltaRow <= 1;deltaRow++){
		for(deltaCol = -1;deltaCol <= 1;deltaCol++){
			if (deltaCol != 0 || deltaRow !=0 ){
				if(checkLegalInDirection(tempBoard,n,row,col,colour,deltaRow,deltaCol)){ //check all eight direction, if that direction is vaild, it will start replacing the colours in that direction.
				while (!(tempBoard[tempRow+deltaRow][tempCol+deltaCol]==colour) && !(tempBoard[tempRow+deltaRow][tempCol+deltaCol]=='U')){ //replaces all the opposite colours with the colour placed until it reaches the same colour.
						score = score + 1;
					tempRow=tempRow+deltaRow;
					tempCol=tempCol+deltaCol;
				}
				tempRow = row;
				tempCol = col;
			}
			}
		}
	}

	replaceColours(tempBoard,n,colour,row,col);
		for (currentRow = 0;currentRow < n;currentRow++){
			for(currentCol = 0;currentCol < n;currentCol++){
				if (legalMoveTest(tempBoard,n,enemeyColour,currentRow,currentCol)){
					if ((currentRow == 0 && currentCol == 0)||(currentRow == 0 && currentCol == n-1)||(currentRow == n-1 && currentCol == n-1)||(currentRow == n-1 && currentCol == 0))
						score = score - 1000;
					if (currentRow == 0 || currentCol == 0 || currentRow == n-1 || currentCol == n-1)
						score = score - 6;
					if ((currentRow == 0 && currentCol == 1)||(currentRow == 1 && currentCol == 0)||(currentRow == 1 && currentCol == 1))
						score = score + 6;
					if ((currentRow == 0 && currentCol == n-2)||(currentRow == 1 && currentCol == n-1)||(currentRow == 1 && currentCol == n-2) )
						score = score + 6;
					if ((currentRow == n-1 && currentCol == 1)||(currentRow == n-2 && currentCol == 1)||(currentRow == n-2 && currentCol == 0) )
						score = score + 6;
					if ((currentRow == n-1 && currentCol == n-2)||(currentRow == n-2 && currentCol == n-1)||(currentRow == n-2 && currentCol == n-2) )
						score = score + 6;
					tempRow = currentRow;
					tempCol = currentCol;
					for(deltaRow = -1; deltaRow <= 1;deltaRow++){
						for(deltaCol = -1;deltaCol <= 1;deltaCol++){
							if (deltaCol != 0 || deltaRow !=0 ){
								if(checkLegalInDirection(tempBoard,n,currentRow,currentCol,enemeyColour,deltaRow,deltaCol)){ //check all eight direction, if that direction is vaild, it will start replacing the colours in that direction.
								while (!(tempBoard[tempRow+deltaRow][tempCol+deltaCol]==enemeyColour) && !(tempBoard[tempRow+deltaRow][tempCol+deltaCol]=='U')){ //replaces all the opposite colours with the colour placed until it reaches the same colour.
									score = score - 1;
									tempRow=tempRow+deltaRow;
									tempCol=tempCol+deltaCol;
								}
							}
							tempRow = currentRow;
							tempCol = currentCol;
							}
						}
					}
				}
			}
		}
return score;
}

int makeMove2(const char board[26][26], int n, char turn, int *row, int *col){
	int oldscore = -100000000000;
	int score = 0;
	int pause  = 0;
	char tempBoard [26][26];
	copyBoard(board,tempBoard,n);
	for (int currentRow = 0; currentRow < n; currentRow++){
		for (int currentCol = 0;currentCol < n;currentCol++){
			if (legalMoveTest(board,n,turn,currentRow, currentCol)){
				score = moveValue2(board,tempBoard,n,turn,currentRow,currentCol);
				copyBoard(board,tempBoard,n);
				if (score >= oldscore){
					oldscore = score;
					*row = currentRow;
					*col = currentCol;
				} 
			}
		}
	}
	return score;
}