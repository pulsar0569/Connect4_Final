#include "Connect4Game.hpp"
#include <cstdlib>
#include <fstream>

/* 
	TODO:
		- Make stronger cpu
*/

// Optional Helper Function
bool inBounds(int r, int c) {
	
    // Your solution here
    
    return false;
}

void initializeBoard(GameState& state) {	
    for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			state.board[i][j] = '.';
		}
	}

    state.currentPlayer = 'X';
}

bool isValidColumn(int col) {
	// If col is in range of [1, 7]
    if (col >= 1 && col <= 7) return true;

	return false;
}

int getLowestEmptyRow(const GameState& state, int col) {
    col--;
    for (int i = 5; i >= 0; i--) {
		if (state.board[i][col] == '.') {
			return i;
		}
	}
	return -1;
}

bool isValidMove(const GameState& state, int col) {
    if (getLowestEmptyRow(state, col) == -1 || !isValidColumn(col)) return false;
	return true;
}

bool dropPiece(GameState& state, int col) {
    if (isValidMove(state, col)) {
		// Get row index of available placement
		int row = getLowestEmptyRow(state, col);
		
		state.board[row][col-1] = state.currentPlayer;
		return true;

	} else return false;
}

void togglePlayer(GameState& state) {

    state.currentPlayer = state.currentPlayer == 'X' ? 'O' : 'X';
    
}

// Optional Helper Function
char lineWinner(const GameState& state, int r, int c, int dr, int dc) {
	
    char current = state.currentPlayer;
    char enemy = state.currentPlayer == 'X' ? 'O' : 'X';

    int currentCount = 0;
    int enemyCount = 0;

	// Check 4 in a row, starting at r, c, and check by step dr, dc
	for (int i = 0; i < 4; i++) {
        if (state.board[r][c] == current) {
            currentCount++; // Add count, 4 = win
        }
        else if (state.board[r][c] == enemy) {
            enemyCount++; // Add count, 4 = win
        } 
        
        r+=dr;
        c+=dc;
    }

    if (currentCount == 4) {
        return current;
    }
    if (enemyCount == 4) {
        return enemy;
    }
	
	return '\0';
}

char checkWinner(const GameState& state) {
	char winner;
	
	// Check horizontal winners
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
            winner = lineWinner(state, i, j, 0, 1); // Check horizontal winner

			if (winner == 'X' || winner == 'O') return winner;
		}
	}

	// Check vertical winners
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			winner = lineWinner(state, i, j, 1, 0); // Check vertical winner
			
			if (winner == 'X' || winner == 'O') return winner;
		}
	}

	// Check horizontal bottom left to top right
	for (int i = 5; i >= 3; i--) {
		for (int j = 0; j <= 3; j++) {
			winner = lineWinner(state, i, j, -1, 1);

			if (winner == 'X' || winner == 'O') return winner;
		}
	}

	// Check horizontal top left to bottom right
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			winner = lineWinner(state, i, j, 1, 1);

			if (winner == 'X' || winner == 'O') return winner;
		}
	}


	// No one won yet so return "no winner" char
	return '\0';
}

bool checkDraw(const GameState& state) {
	
	// Check if the top line has empty, if empty found, can still place
	for (int i = 0; i < 7; i++) {
		if (state.board[0][i] == '.') return false;
	}

	return true;
}

void printBoard(const GameState& state, std::ostream& out) {
	// Your solution here
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			out << state.board[i][j] << " ";
		}
		out << std::endl; // End with new line per row
	}
	for (int i = 1; i <= 7; i++) {
		out << i << " ";
	}
	out << std::endl;
}

bool saveBoardToFile(const GameState& state, const std::string& path) {
	std::ofstream FS(path);
	if (!FS.is_open()) {
		return false;
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			FS << state.board[i][j];
		}
	}

	FS << state.currentPlayer;
	FS.close();

	return true;
}

bool loadBoardFromFile(GameState& state, const std::string& path) {
	std::ifstream FS(path);

	if (!FS.is_open()) {
		return false;
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (FS.bad()) {
				FS.close();
				return false;
			}
			FS >> state.board[i][j];
		}
	}

	FS >> state.currentPlayer;
	FS.close();

	return true;
}
// Optional Helper Function
bool tryDropAs(GameState& temp, int col, char player) {
	
	// Your solution here

	return false;
}
// Brute forces every spot and returns num of col if win found, otherwise return -1
int checkImmediateWin(GameState temp) {
	// Used for reverting after placing piece down
	GameState original = temp;
	
	temp.currentPlayer = 'X';
	// Check with each player starting with self for immediate wins/losses
	for (int i = 0; i < 2; i++) {
		togglePlayer(temp);

		// Try each column for winner
		for (int i = 1; i < 8; i++) {
			// If successfully placed and immediate win/loss for any player
			
			dropPiece(temp, i);
			
			if (checkWinner(temp) != '\0') { 
				return i; // Returns position to place at
			}
			temp = original;
		}
	}
	// No immediate wins found
	return -1;
}

// Should return spots 1-7 inclusive
int chooseComputerMove(const GameState& state) {
	// Check for immediate wins/losses
	int winSpot = checkImmediateWin(state);
	if (winSpot != -1) return winSpot;

	// Make diagonals if can

	// Make columns if can

	// Capture center pieces at col 3 and 4
	for (int i = 3; i <= 4; i++) {
		if (getLowestEmptyRow(state, i) == 5) {
			return i;
		}
	}

	// Fallback random spot
	srand(time(0));
	int spot = (rand() % 7)+1;
	std::cout << "Placing at spot " << spot << std::endl;

	return spot;

	return -1;
}
