#include<stdio.h>
#include<conio.h>
#include<stdlib.h> // For rand and srand
#include <time.h> // to seed the random number generator

int hasWon = 0;

void combineTiles(char input,int board[4][4]);
// The combineTiles function merges equal adjacent tiles
// to form a tile with larger value

void pushTiles(char input,int board[4][4]);
// It pushes all the tiles in a direction

void addRandomTile(int board[4][4]);
// It adds a random tile {2,4} at a randomly chosen empty space

void redrawScreen(int board[4][4]);
// calls the system('cls') and prints the entire board

int checkGameEndCondition(int board[4][4]);
// Checks if the game has ended and whether the player has lost or won

int areBoardsEqual(int a[4][4],int b[4][4]);
// Checks equality of two 2D int arrays

int areTilesMovable(char direction,int board[4][4],int boardCopy[4][4]);
// Checks if tiles are movable in a direction

void resetCopy(int board[4][4],int boardCopy[4][4]);
// Reset board
int main()
{
	int board[4][4] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	int boardCopy[4][4] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	// Initialised board with zeros
	// This method is useful for debugging and play testing

	char input;
	addRandomTile(board);
	redrawScreen(board);
	while(checkGameEndCondition(board))
	{
		input=getch(); 
		// w for up, s for down
		// a for left, d for right
		
		if(input=='Q'||input=='q') // Press q to quit
			return 0;
		if(input!='w' && input!='s' && input!='a' && input!='d')
			continue;
		resetCopy(board,boardCopy);
		if(!areTilesMovable(input,board,boardCopy)){
			continue;			
		}
			
		pushTiles(input,board);
		combineTiles(input,board);
		pushTiles(input,board);
		// After combining tiles, some tiles become empty
		// To avoid that we just push all tiles in that 
		// direction again.
		
		addRandomTile(board);
		redrawScreen(board);
	}
	printf("Game over");
	getch();
	return 0;
}
void pushTiles(char input,int board[4][4])
{
	/*
	Say the user pressed the 'a' key, i.e. move all tiles to the left.
	Then we check from the left of the board if a tile has a non-zero value.
	If the tile is non-zero then we check if the tile left of it has zero value and then
	we check the tile 2 places left and 3 places left. Then we make the leftmost zero valued
	tile as our target tile and set the original position as zero.
	
	If the user pressed say the 'w' or 's' key we have to check in a column major format.
	The direction decides from which side we check for empty tiles.
	*/
	
    int i,j,magnitude;
    if(input == 'A' || input == 'a'){
        for(i = 0; i < 4; i++){
            for(j = 1; j < 4; j++){
                if(board[i][j] != 0){
                    magnitude = 0;
                    while(j-magnitude>0 && board[i][j-(magnitude+1)] == 0)
                        magnitude++;
                    if(magnitude != 0) {
                        board[i][j-magnitude] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
    if(input == 'D' || input == 'd'){
        for(i = 0; i < 4; i++){
            for(j = 2; j >= 0; j--){
                if(board[i][j] != 0){
                    magnitude = 0;
                    while(j-magnitude<3 && board[i][j-(magnitude-1)] == 0)
                        magnitude--;
                    if(magnitude != 0) {
                        board[i][j-magnitude] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
    if(input == 'W' || input == 'w'){
        for(j = 0; j < 4; j++){
            for(i = 1; i < 4; i++){
                if(board[i][j] != 0){
                    magnitude = 0;
                    while(i-magnitude>0 && board[i-(magnitude+1)][j] == 0)
                        magnitude++;
                    if(magnitude != 0) {
                        board[i-magnitude][j] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
    if(input == 'S' || input == 's'){
        for(j = 0; j < 4; j++){
            for(i = 2; i >= 0; i--){
                if(board[i][j] != 0){
                    magnitude = 0;
                    while(i-magnitude<3 && board[i-(magnitude-1)][j] == 0)
                        magnitude--;
                    if(magnitude != 0) {
                        board[i-magnitude][j] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}
void combineTiles(char input,int board[4][4])
{

	// Check if the adjacent tile in the given direction has
	// the same value. If yes then double the value and make the 
	// other tile zero
	
    int i,j;
	if(input == 'A' || input == 'a'){
        for(i = 0; i < 4; i++){
            for(j = 1; j < 4; j++){
                if(board[i][j] != 0){
                    if(board[i][j] == board[i][j-1]){
                            board[i][j-1]*=2;
                            board[i][j] = 0;
                    }
                }
            }
        }
    }

    if(input == 'D' || input == 'd'){
        for(i = 0; i < 4; i++){
            for(j = 2; j >= 0; j--){
                if(board[i][j] != 0){
                    if(board[i][j] == board[i][j+1]){
                            board[i][j+1]*=2;
                            board[i][j] = 0;
                    }
                }
            }
        }
    }
    if(input == 'W' || input == 'w'){
        for(j = 0; j < 4; j++){
            for(i = 1; i < 4; i++){
                if(board[i][j] != 0){
                    if(board[i-1][j] == board[i][j]){
                            board[i-1][j]*=2;
                            board[i][j] = 0;
                    }
                }
            }
        }
    }
    if(input == 'S' || input == 's'){
        for(j = 0; j < 4; j++){
            for(i = 2; i >= 0; i--){
                if(board[i][j] != 0){
                    if(board[i+1][j] == board[i][j]){
                            board[i+1][j]*=2;
                            board[i][j] = 0;
                    }
                }
            }
        }
    }
}
void addRandomTile(int board[4][4])
{
	int temp,i,j,value,iterations = 0,emptyTileExists = 0;
	time_t mytime;
	mytime = time(NULL);
	srand((int)mytime); // seeding the random number generator with system time
    for(i = 0; i < 4; i++){ // Check if an empty tile exists or not
            for(j = 0; i < 4; i++){
                    if(board[i][j] == 0){ emptyTileExists = 1; break;}
            }
    }
    if(!emptyTileExists) return;
	while(1)  
	{
		// Generate two random numbers and check if the coordinate has
		// a zero value. If yes put 2 or 4 otherwise roll again
	    iterations++;
        if(iterations>1000) break; 
		// Even when the board had one free space, it was able to 
		// populate that tile within much less than 200 iterations
		// 200 iterations has no visual impact (on my computer)
		i=rand()%4;
		j=rand()%4;
		if(board[i][j]==0)
		{
			value=rand()%2;
			if(value)
				board[i][j]=2;
			else board[i][j]=4;
			break;
		}
	}
}

int areBoardsEqual(int a[4][4],int b[4][4]){
	int i,j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(a[i][j] != b[i][j]) return 0;
		}
	}
	return 1;
}

void resetCopy(int board[4][4],int boardCopy[4][4]){

	// A helper function used for by value copy of two arrays

    int i,j;
    for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			boardCopy[i][j]=board[i][j];
		}
	}
}

int areTilesMovable(char direction,int board[4][4],int boardCopy[4][4]){
	pushTiles(direction,boardCopy);
	combineTiles(direction,boardCopy);
	pushTiles(direction,boardCopy);	
	if(!areBoardsEqual(board,boardCopy)) return 1;
	return 0;	
}

int checkGameEndCondition(int board[4][4])
{
	int i,j,boardCopy[4][4];
	int movesPossible = 0;
    resetCopy(board,boardCopy);

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(board[i][j] == 2048) // The game doesnt stop, the user can continue playing
				hasWon = 1;// A "You have won" message is displayed when the screen is redrawn
		}
	}
	
	/*
	The game ends (loose condition) when we cannot move or combine tiles in any direction.
	
	We are creating a copy of our board and finding the result of all four possible	
	user inputs. If the board before processing(push-combine-push) is same as the board 
	after processing then the move in that direction is not possible. If move in all directions
	is not possible then the game is over.
	*/

	movesPossible+=areTilesMovable('w',board,boardCopy); resetCopy(board,boardCopy);	
	movesPossible+=areTilesMovable('s',board,boardCopy); resetCopy(board,boardCopy);	
	movesPossible+=areTilesMovable('a',board,boardCopy); resetCopy(board,boardCopy);	
	movesPossible+=areTilesMovable('d',board,boardCopy); resetCopy(board,boardCopy);	

	return movesPossible;
}
void redrawScreen(int board[4][4])
{
	/*
	The latency we see during gameplay comes from the addRandomTile function and
	checkGameEndCondition and not this function. This function is significantly
	faster than all other major functions.
	
	combineTiles - 48 to 60 iterations
	pushTiles - 48 iterations
	addRandomTile - 200 iterations(worst case scenario)
	redrawScreen - 16 iterations
	checkGameEndCondition - 736 iterations
	areBoardsEqual - 16 iterations
	*/
	int i,j;
	system("cls"); 
	printf("\n");
	if(hasWon) printf("You have won but you can continue playing.\nPress q to quit.\n");
	// using the global hasWon flag, raised by the check game end condition
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
		    if(board[i][j]!=0)
                printf("%d\t",board[i][j]);
            else
                printf("_\t");
		}
		printf("\n");
	}
}
