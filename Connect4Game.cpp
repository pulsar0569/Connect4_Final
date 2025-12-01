#include "Connect4Game.hpp"
#include <cstdlib>
#include <fstream>

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

    // Your solution here

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
    if (getLowestEmptyRow(state, col) == -1) return false;
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
	for (int i = 0; i < -1; i++) {
		for (int j = 0; j < -1; j++) {
			winner = lineWinner(state, i, j, -1, -1);

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

	/* Should look like this for an empty board:
	  
	   . . . . . . .
	   . . . . . . .
	   . . . . . . .
	   . . . . . . .
	   . . . . . . .
	   . . . . . . .
	   . . . . . . .
	   1 2 3 4 5 6 7
	

	   After some moves - ('X', 3), ('O', 4), ('X', 4):

	   . . . . . . .
	   . . . . . . .
	   . . . . . . .
	   . . . . . . .
	   . . . . . . .
	   . . . X . . .
	   . . X O . . .
	   1 2 3 4 5 6 7

	*/
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

bool tryDropAs(GameState& temp, int col, char player) {
	
	// Your solution here

	return false;
}

int chooseComputerMove(const GameState& state) {
	
	// Your solution here

	return -1;
}
