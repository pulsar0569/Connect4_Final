#include <iostream>
#include <sstream>
#include "Connect4Game.hpp"

int main() {
    // Set up initial board state for new game
	GameState state;
	initializeBoard(state);

    const int GAMEMODE_PVP = 1; // Player versus Player mode
    const int GAMEMODE_PVC = 2; // Player versus Computer mode

	const std::string savePath = "game.save";

	std::cout << "Select mode: 1) Player vs Player  2) Player vs Computer" << '\n';
	std::cout << "Enter 1 or 2: ";
	std::string modeInput;
	int mode = GAMEMODE_PVP;
	if (std::getline(std::cin, modeInput)) {
		std::istringstream miss(modeInput);
		int m;
		if (miss >> m) {
			if (m == GAMEMODE_PVP || m == GAMEMODE_PVC) {
                mode = m;
            }
		}
	}

	std::cout << "Select start: 1) New Game 2) Load Game" << std::endl;
	std::cout << "Enter 1 or 2: ";

	if (std::getline(std::cin, modeInput)) {
		std::istringstream stream(modeInput);
		int n;
		if (stream >> n) {
			if (n == 2) {
				loadBoardFromFile(state, savePath);
			}
		}
	}

    // Continue until player wins or board is full
	while (true) {
		printBoard(state, std::cout);
		int col = -1;
		if (mode == GAMEMODE_PVC && state.currentPlayer == 'O') {
			col = chooseComputerMove(state);
			if (col == -1) {
				std::cout << "No moves available.\n";
				break;
			}
			std::cout << "Computer chooses column " << col << "\n";
		} else {
			std::cout << "Player " << state.currentPlayer << ", enter column (1-7) or Q to quit: ";
			std::string input;

			if (!std::getline(std::cin, input)) { break; }
			if (input.size() > 0 && (input[0] == 'q' || input[0] == 'Q')) {
				std::cout << "Goodbye!\n";
				break;
			}
			std::istringstream iss(input);
			if (!(iss >> col)) {
				std::cout << "Invalid input. Please enter a number from 1 to 7.\n";
				continue;
			}
			if (!isValidMove(state, col)) {
				std::cout << "Invalid move. Column must be 1-7 and not full.\n";
				continue;
			}

			saveBoardToFile(state, savePath);
		}

        // Drop piece and check game state
		dropPiece(state, col);
		char w = checkWinner(state);
		if (w == 'X' || w == 'O') {
			printBoard(state, std::cout);
			std::cout << "Player " << w << " wins!\n";
			break;
		}
		if (checkDraw(state)) {
			printBoard(state, std::cout);
			std::cout << "Draw!\n";
			break;
		}
		togglePlayer(state);
	}
	
	return 0;
}