#include <stdio.h>
#include <stdlib.h>

/** NOTES & COMMENTS (Documentation)

- We felt that we did not need to explicitly apply all of the sets such as having S and Free as variables in the code.
  This is because when we figured out what kind of game the specs were describing, we knew what kind of operations and functions
  we would need to satisfy the GameOver function and other aspects of the game.
  
- For presentation, we declared all variables stated in the specs to display that we are aware of their meanings and know what they do.
  The functions we implemented are not explicitly identical to the specs but still serve and return the desired result of the specs as
  indicated in the specs instructions. Additional features outside of the spec requirements were added for better outputs and optimization.
 
- L = W - S indicates the winning condition of a tic-tac-toe game where a pattern of vertical, horizontal, or diagonal lines are made by a player.
  In the GameOver function, it says that for either Uno or Dos to win, they must be an element of L which basically means they need to create a winning
  condition. Since we figured that is what L means, we decided to implement GameOver to check for those winning conditions without the need for using
  set operations being W - S. It checks if a player has created a winning pattern and ends the game if ever. We have decided this because L and our function
  result in the same output which is acceptable according to the professor when one of our group mates consulted.

- Similar to GameOver function, we also implemented NextPlayerMove without explicitly following the specs instructions such as having only pos as a parameter.
  We decided this as in order to ensure proper data handling between player moves, we felt the need to add more parameters such as the Uno and Dos variables to
  properly track the tic-tac-toe game process. Since we figured out that NextPlayerMove determines the player moves and whether a space on the 3x3 board is taken
  or not. and if a winning condition consists of 3 markers, we were able to create a function that alternates player turns and validates taken spaces, 
  calling GameOver to check if L or a winning condition is met.
  
- We figured that the specs were indicating that the C program would resemble a game of tic-tac-toe because of these reasons:
	> P being a 3 x 3 board narrowed many options of the kind of game it could be
	> Seeing that Uno or Dos as possible winners of the game in GameOver hinted that it was only a 2-player game
	> W and its elements resembled all possible winning patterns of tic-tac-toe which were a horizontal line, vertical line, or diagonal lines
	> NextPlayerMoves functions looked like it was Uno and Dos taking positions on a board while taking turns  and the condition of Uno and Dos being below or equal 
	  to 3 checks to see if they have made a line consisting of 3 lines in a row    

**/

// struct to handle the coordinates on the board (x, y)
typedef struct {
	int x;
	int y;
} Position;

void DisplayBoard(int P[3][3]); // Function prototype to allow function to be called in NextPlayerMove

// Function to check if the game is over and determine the result
/* 
	GameOver This function basically finds the winner using L = W - S which are the results of finding the winning conditions 
	by searching for any horizontal, vertical, or diagonal line made by either Uno (player 1) or Dos (player 2) during their turns
	
	@param P - P is the 3 x 3 board of the game
	@param player - will return the winning player's int as 1 or 2 if a search of L is found which is the winning condition
	@param over - over is the parameter from NextPlayerMove that signals whether the game is over or not

*/
int GameOver(int P[3][3], int player, int over) {
	
	int i, j;
	
    // Check for win conditions
    for (i = 0; i < 3; ++i) {
        // Rows
        if (P[i][0] == player && P[i][1] == player && P[i][2] == player) // checks i 0, i 1, and i 2 which are possible rows
            return player;
        // Columns
        if (P[0][i] == player && P[1][i] == player && P[2][i] == player) // checks 0 i, 1 i, and 2 i which are possible columns
            return player;
    }
    
    // Diagonals
    if ((P[0][0] == player && P[1][1] == player && P[2][2] == player) ||
        (P[0][2] == player && P[1][1] == player && P[2][0] == player)) // 0 0, 1 1, 2 2 & 0 2, 1 1, and 2 0 are possible diagonals (left to right, vice-versa)
        return player;

    // Check for a draw
    int count = 0;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (P[i][j] != 0) count++; // checks if all of the board is occupied with no winning condition
        }
    }
    if (count == 9) return 3; // Draw
    
    return 0; // Game is not over
}

/* The function 'NextPlayerMove' is designed to track and update the moves of players in a two-player game.

	The game is represented by a 3x3 grid [P] where players, referred to as Uno and Dos, take turns making moves.
	The function checks for valid moves, updates the game state, and determines if there is a winner or if the game ends in a draw. 
	
	@param pos - represents the position where the current player wants to make a move.
	@param uno[] - an array representing the position where Uno (P1) has made moves.
	@param dos[] - an array representing the position where Dos (P2) has made moves.
	@param turn - a pointer to an integer indicating whose turn it is.
	@param over - a pointer to an integer whether the game is over (1) or not (0).
	@param P[3][3] - represents the 3x3 game board with player moves.
*/	
int NextPlayerMove(Position pos, Position Uno[], Position Dos[], int *turn, int *over, int P[3][3]) {
	
	int i;
	
    // Check if the selected position is already taken by Uno
    for (i = 0; i < 3; ++i) {
        if (Uno[i].x == pos.x && Uno[i].y == pos.y) {
            printf("\n\nPosition already taken by Uno! Try again.\n");
            return 0; // Position already taken by Uno
        }
    }

    // Check if the selected position is already taken by Dos
    for (i = 0; i < 3; ++i) {
        if (Dos[i].x == pos.x && Dos[i].y == pos.y) {
            printf("\n\nPosition already taken by Dos! Try again.\n");
            return 0; // Position already taken by Dos
        }
    }

    int player = (*turn == 1) ? 1 : 2; // player starts at 1, meaning player 1 or Uno goes first
    
    // Update the board representation with the player's move
    P[pos.x - 1][pos.y - 1] = player;

    // Update the corresponding player's position array
    if (player == 1) {
        Uno[*turn - 1] = pos; // Update Uno's position array
    } else {
        Dos[*turn - 1] = pos; // Update Dos's position array
    }

    *turn = (*turn == 1) ? 2 : 1; // Switches turn between Uno and Dos

    // Check game status
    int result = GameOver(P, player, *over); // Pass the board representation P
    
    
    if (result == player) { // if player value at the end of the game is 1, Uno wins
    	if(player == 1) {
    		DisplayBoard(P);
    		printf("\nUno wins!\n");
        	*over = 1; // Set game over
		}
		else if(player == 2) { // if player value at the end of the game is 2, Uno wins
			DisplayBoard(P);
			printf("\nDos wins!\n");
        	*over = 1; // Set game over
		}
        
        return player; // Player wins
    } else if (result == 3) { // if player value is 3, its a draw
    	DisplayBoard(P);
        printf("\nIt's a draw!\n");
        *over = 1; // Set game over
        return 3; // It's a draw
    }

    return 0; // No winner yet
}

/* The function 'DisplayBoard' is responsible for displaying the current state of the 3x3 game board.
	It takes the 2D array 'P' as input, representing the state of the game where each cell can be empty (0),
	occupied by Player 1 (1), or occupied by Player 2 (2). The function creates a visual representation
	of the board using characters ('X', 'O', and empty space) and prints it to the console.
	
	@param P[3][3] - represents the 3x3 game board with player moves.
*/
void DisplayBoard(int P[3][3]) {
	
    char board[3][3]; // 3x3 board
    
    int i, j;

    // Fill the board based on the values in array P
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (P[i][j] == 0) {
                board[i][j] = ' ';
            } else if (P[i][j] == 1) {
                board[i][j] = 'X'; // Player 1 marker
            } else if (P[i][j] == 2) {
                board[i][j] = 'O'; // Player 2 marker
            }
        }
    }

    // Display the board
    printf("\n %c | %c | %c\n", board[0][0], board[0][1], board[0][2]); 
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

// MAIN
int main() {
		
	// Sets
    int A[] = {1, 2, 3}; // Set A containing positive integers less than 4
    
    // P is the result of A x A, resulting into a set of numbers that resemble a 3 x 3 board so A is no longer needed
    int P[3][3] = {0}; // Board representation initialized with zeros
    
    int B[2] = {1, 0}; // Boolean values for true and false
    
    int W[4][3][2] = { // W is the set of all winning conditions (vertical, horizontal, diagonal lines)
        {{1, 2}, {2, 2}, {3, 2}},
        {{2, 1}, {2, 2}, {2, 3}},
        {{1, 1}, {2, 2}, {3, 3}},
        {{1, 3}, {2, 2}, {3, 1}}
    };
    
    int S[9][2] = { // Set S representing the relation on A (similar to the 3x3 board)
        {1, 1}, {1, 2}, {1, 3},
        {2, 1}, {2, 2}, {2, 3},
        {3, 1}, {3, 2}, {3, 3}
    };

    // System Facts
    int turn = B[0]; // true
    int over = B[1]; // false

    // System Variables
    Position Free[3]; // Subset Free containing remaining positions for 3x3 board
    Position Uno[3] = { {-1, -1}, {-1, -1}, {-1, -1} }; // Initialize Uno positions
    Position Dos[3] = { {-1, -1}, {-1, -1}, {-1, -1} }; // Initialize Dos positions
    
    printf("\n-----------------\n");
    printf(" X TIC-TAC-TOE O\n");
    printf("-----------------\n");
    printf("\nWould you like to play?\n");
    printf("\n[Y]es || [N]o\n");
    
    char cYesOrNo;
	do {
        scanf(" %c", &cYesOrNo);  // user input for yes or no
    } while (cYesOrNo != 'Y' && cYesOrNo != 'y' && cYesOrNo != 'n' && cYesOrNo != 'N'); // validation for if user does not enter Y, y, N, or n


    if (cYesOrNo == 'Y' || cYesOrNo == 'y') {
    	int gameResult;
    	
    	printf("\nINSTRUCTIONS\n");
    	printf("\n1. Two players play, each taking turns placing markers on the board by typing two intgers resembling a coordinate on the board (ex. 1 1 for the first row & column).\n");
    	printf("\n2. The objective is to place markers on the board until one player creates a pattern:");
		printf("\n   A vertical, horizontal, or diagonal line anywhere on the board consisting of 3 pieces\n");	
		printf("\n3. If the board is filled with none of the winning lines is created by the same player, the game is a draw.\n");
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		
	    do {
	        DisplayBoard(P); // Display the board
	
	        int row, col; // represents coordinates on the board
	        
	        printf("\nEnter row and column 1-3 (ex. 1 1)\n");
	        printf("\nPlayer's choice (X = Uno, O = Dos): ");
	        scanf("%d %d", &row, &col); // users choice to place their markers via coordinates
	
	        // Validate the input range (1-3) for the row and column
	        if (row < 1 || row > 3 || col < 1 || col > 3) {
	            printf("\nInvalid input! Row and column must be between 1 and 3.\n");
	            continue; // Ask for input again
	        }
	
	        Position pos = {row, col}; // coordinates on board
	
	        // Make a move for the current player
	        gameResult = NextPlayerMove(pos, Uno, Dos, &turn, &over, P);
	
	        if (gameResult == 1 || gameResult == 2 || gameResult == 3) {
	            over = 1; // Set game over
	            break; // Exit the loop when the game ends
	        }
	
	    } while (over != 1); // loops while game is still ongoing	   	
	
	}
	else if(cYesOrNo == 'N' || cYesOrNo == 'n') { // if user says no, end program
		printf("\nGoodbye!");
		return 0;
	} 
	
	return 0;

}
