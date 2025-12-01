#include <fstream>
#include <iostream>

using namespace std;


struct GameState {
    char board[6][7];
    char currentPlayer; // 'X' or 'O'
};

void LoadStateEmpty(GameState& state) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            state.board[i][j] = '.';
        }
    }
    
    state.currentPlayer = 'X';
}

void LoadStateChar(GameState& state) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            state.board[i][j] = count + '0';
            count++;
        }
    }
    
    state.currentPlayer = 'X';
}

void LoadStateRand(GameState& state) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            state.board[i][j] = (i + j) % 2 == 0 ? 'X' : 'O';
        }
    }
    
    state.currentPlayer = 'O';
}

void PrintState(const GameState& state) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << state.board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Current Player: " << state.currentPlayer;
    
    cout << endl << endl;
}

void SaveState(const GameState& state, string location) {
    ofstream FS(location);
    if (!FS.is_open()) {
        cout << "Couldn't open save file at location: " << location << endl;
        return;
    }
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            FS << state.board[i][j];
        }
    }
    
    FS << state.currentPlayer;
    FS.close();
    
    cout << "GameState succesfully saved!" << endl;
    
}

void LoadState(GameState& state, string location) {
    ifstream FS(location);
    
    if (!FS.is_open()) {
        cout << "Couldn't open save file at location: " << location << endl;
        return;
    }
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            FS >> state.board[i][j];
        }
    }
    
    FS >> state.currentPlayer;
    FS.close();
    
    cout << "GameState successfully loaded!" << endl;
}

char lineWinner(const GameState& state, int r, int c, int dr, int dc) {
	
    char current = state.currentPlayer;
    char enemy = state.currentPlayer == 'X' ? 'O' : 'X';

    int currentCount = 0;
    int enemyCount = 0;

	for (int i = 0; i < 4; i++) {
        if (state.board[r][c] == current) {
            currentCount++;
        }
        else if (state.board[r][c] == enemy) {
            enemyCount++;
        }
        // Verbose what it's doing
        cout << "Checking r: " << r << ", c: " << c << " => " << state.board[r][c] << endl; 
        
        r+=dr;
        c+=dc;
    }

    if (currentCount == 4) {
        cout << "Returning current player won: " << current << "!!" << endl;
        return current;
    }
    if (enemyCount == 4) {
        cout << "Returning enemy player won: " << enemy << "!!" << endl;
        return enemy;
    }
	
	return '\0';
}


int main()
{
    GameState state;

    LoadStateChar(state);
    

    char winner;
    
   // Check horizontal winners
	// for (int i = 0; i < 6; i++) {
	// 	for (int j = 0; j < 4; j++) {
    //         winner = lineWinner(state, i, j, 0, 1); // Check horizontal winner
    //         cout << endl;
    //         if (winner == 'X' || winner == 'O') break;
	// 	}
    //     if (winner == 'X' || winner == 'O') break;
	// }

    // Check horizontal bottom left to top right
	// for (int i = 5; i >= 3; i--) {
	// 	for (int j = 0; j <= 3; j++) {
	// 		winner = lineWinner(state, i, j, -1, 1);
    //         cout << endl;

	// 		if (winner == 'X' || winner == 'O') break;
	// 	}
    //     if (winner == 'X' || winner == 'O') break;
	// }

    char setChar = 'O';

    state.board[2][2] = setChar;
    state.board[3][3] = setChar;
    state.board[4][4] = setChar;
    state.board[5][5] = setChar;

    PrintState(state);

    // Check horizontal top left to bottom right
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			winner = lineWinner(state, i, j, 1, 1);
            cout << endl;

			if (winner == 'X' || winner == 'O') break;
		}

        if (winner == 'X' || winner == 'O') break;
	}	

    cout << endl << endl << endl << "Winner is: " << winner << endl;

    /*

    // Diagonal check at 0, 0
    lineWinner(state, 0, 0, 1, 1);
    cout << endl << endl;

    // Horizontal check right at 0, 0
    lineWinner(state, 0, 0, 0, 1);
    cout << endl << endl;

    // Vertical check down at 0, 0
    lineWinner(state, 0, 0, 1, 0);
    cout << endl << endl;

    */
    
}