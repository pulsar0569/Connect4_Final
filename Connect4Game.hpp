#pragma once

#include <iostream>
#include <fstream>
#include <string>

/**
 * \file connect4.h
 * \brief This file contains the type definitions 
 * and function prototypes used in the Connect 4 Project.
 */

/**
 * \brief Represents the entire game state for Connect 4.
 *
 * The board has 6 rows and 7 columns. Empty cells contain '.' (dot).
 * The current player is either 'X' or 'O'.
 */
struct GameState {
    char board[6][7];
    char currentPlayer; // 'X' or 'O'
};

/**
 * \brief Check whether a board coordinate is within bounds.
 *
 * Bounds are rows 0..5 and columns 0..6 (0-based indices for internal logic).
 * \param r 0-based row index
 * \param c 0-based column index
 * \return true if (r,c) is inside the 6x7 board; false otherwise
 */
bool inBounds(int r, int c);

/**
 * \brief Fill the board with '.' and set currentPlayer to 'X'.
 * \param state game state to initialize (output)
 */
void initializeBoard(GameState& state);

/**
 * \brief Check if a 1-based column index is within 1..7.
 * \param col 1-based column index
 * \return true if col is in [1,7], false otherwise
 */
bool isValidColumn(int col);

/**
 * \brief Get the lowest empty row index in a given column.
 * \param state game state (input)
 * \param col 1-based column index
 * \return 0-based row index, or -1 if the column is full or invalid
 */
int getLowestEmptyRow(const GameState& state, int col);

/**
 * \brief Determine whether a move can be played in the given column.
 * \param state game state (input)
 * \param col 1-based column index
 * \return true if the move is within bounds and the column is not full
 */
bool isValidMove(const GameState& state, int col);

/**
 * \brief Drop the current player's piece into the given column.
 * \param state game state (modified)
 * \param col 1-based column index
 * \return true if the piece was placed, false if the move was invalid
 */
bool dropPiece(GameState& state, int col);

/**
 * \brief Toggle currentPlayer between 'X' and 'O'.
 * \param state game state (modified)
 */
void togglePlayer(GameState& state);

/**
 * \brief Check if either player has four in a row.
 * \param state game state (input)
 * \return 'X' if X has won, 'O' if O has won, or '\0' if no winner
 */
char checkWinner(const GameState& state);

/**
 * \brief Check whether the game is a draw.
 *
 * A draw occurs when there is no winner and no valid moves remain.
 * \param state game state (input)
 * \return true if the board is full and there is no winner
 */
bool checkDraw(const GameState& state);

/**
 * \brief Print the board to the provided output stream.
 * \param state game state (input)
 * \param out destination output stream
 */
void printBoard(const GameState& state, std::ostream& out);

/**
 * \brief Save the board and current player to a text file.
 *
 * The format is 6 lines of 7 characters (board rows), followed by one line with the current player.
 * \param state game state (input)
 * \param path filesystem path to write
 * \return true on success, false on failure
 */
bool saveBoardToFile(const GameState& state, const std::string& path);

/**
 * \brief Load the board and current player from a text file.
 * \param state game state (output)
 * \param path filesystem path to read
 * \return true on success, false on malformed file or I/O error
 */
bool loadBoardFromFile(GameState& state, const std::string& path);

// Computer move chooser for PvC mode. Returns a column 1..7, or -1 if no move.
/**
 * \brief Choose a computer move for the current player using a simple heuristic.
 *
 * Heuristic: play a winning move if available; otherwise block opponent's immediate win;
 * otherwise choose the first available column from left to right.
 * \param state game state (input)
 * \return selected 1-based column, or -1 if no moves are available
 */
int chooseComputerMove(const GameState& state);

/**
 * \brief Attempt to drop a piece for a specified player without changing turn.
 *
 * This helper simulates a drop into a 1-based column for the given player
 * by placing the piece at the current lowest empty row in that column.
 * It temporarily sets and restores `currentPlayer` but does not toggle turns.
 * \param state game state to modify (in-place simulation)
 * \param col 1-based column index (1..7)
 * \param player the piece to place ('X' or 'O')
 * \return true if a piece was placed; false if the column is invalid or full
 */
bool tryDropAs(GameState& state, int col, char player);

/**
 * \brief Check for a 4-in-a-row starting at a cell and advancing by a delta.
 *
 * If the starting cell is not empty and the next three cells along the
 * (dr, dc) direction match it, returns that player's symbol. Otherwise '\\0'.
 * Uses 0-based indices and expects callers to ensure the 4-length segment is
 * within bounds.
 * \param state game state (input)
 * \param r starting row (0-based)
 * \param c starting column (0-based)
 * \param dr row delta per step (-1, 0, or 1)
 * \param dc column delta per step (-1, 0, or 1)
 * \return 'X', 'O', or '\\0' if not a winning segment
 */
char lineWinner(const GameState& state, int r, int c, int dr, int dc);