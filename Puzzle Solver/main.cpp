//
//  main.cpp
//  Puzzle Solver
//
//  Created by Logan Seaburg on 5/16/17.
//  Copyright © 2017 Logan Seaburg. All rights reserved.
//
//  Finds all 229,205 solutions of The Ultimate Puzzle.
//

#include <iomanip>
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include "Piece.h"
using namespace std;

const int boardSize = 4;
const bool flippable = false;
const Piece keyPiece = Piece(1, 4, -1, -3); // Must be set to a piece value to avoid reflections & rotations

void InitialPieces(set<Piece>& AllPieces);
void Output(Piece board[boardSize][boardSize]);
set<Piece> Arrangements(Piece original);
void SolvePuzzle(Piece Board[boardSize][boardSize], set<Piece>& PiecesRemaining);

int solutions = 0;
unsigned long long fails = 0;

int main() {
    set<Piece> PiecesRemaining;
    InitialPieces(PiecesRemaining);
    Piece Board[boardSize][boardSize];
    SolvePuzzle(Board, PiecesRemaining);
    return 0;
}

void InitialPieces(set<Piece>& AllPieces) {
    // Pieces to The Ultimate Puzzle, shiny side up
    AllPieces.emplace(Piece(1, 4, -1, -3));
    AllPieces.emplace(Piece(1, 4, -4, -2));
    AllPieces.emplace(Piece(2, 1, -1, -2));
    AllPieces.emplace(Piece(2, 1, -4, -4));
    AllPieces.emplace(Piece(2, 1, -3, -2));
    AllPieces.emplace(Piece(2, 3, -1, -3));
    AllPieces.emplace(Piece(2, 3, -2, -1));
    AllPieces.emplace(Piece(2, 2, -2, -4));
    AllPieces.emplace(Piece(2, 3, -3, -4));
    AllPieces.emplace(Piece(3, 1, -4, -3));
    AllPieces.emplace(Piece(3, 3, -2, -1));
    AllPieces.emplace(Piece(3, 3, -4, -1));
    AllPieces.emplace(Piece(3, 4, -4, -2));
    AllPieces.emplace(Piece(4, 2, -2, -1));
    AllPieces.emplace(Piece(4, 2, -2, -4));
    AllPieces.emplace(Piece(4, 4, -2, -3));
    
    //also can look to Scrambling Squares for good piece options
}

//Displays a text version of a solved board when it is finally found.
void Output(Piece Board[boardSize][boardSize]) {
    solutions++;
    if (solutions % 1000 == 0)
        cout << solutions << endl;
    cout << solutions << '.' << endl;
    for (int r = 0; r < boardSize; r++) {
        for (int c = 0; c < boardSize; c++) { //top row
            cout << "  ";
            if (Board[r][c].con1 > 0) {
                cout << " ";
            }
            cout << Board[r][c].con1  << "    ";
        }
        cout << endl;
        for (int c = 0; c < boardSize; c++) { //middle row
            if (Board[r][c].con4 > 0) {
                cout << " ";
            }
            cout << Board[r][c].con4 << "  ";
            if (Board[r][c].con2 > 0) {
                cout << " ";
            }
            cout << Board[r][c].con2 << "  ";
        }
        cout << endl;
        for (int c = 0; c < boardSize; c++) { //bottom row
            cout << "  ";
            if (Board[r][c].con3 > 0) {
                cout << " ";
            }
            cout << Board[r][c].con3 << "    ";
        }
        cout << endl << endl;//one line to seperate rows
    }
    cout << endl << endl;
}

/* Returns a set of all 8 posible ways that a single piece can
 /  be placed in the puzzle - the 4 quarter-turns on each side.
 */
set<Piece> Arrangements(Piece original) {
    set<Piece> arrangements;
    arrangements.emplace(original);
    if (original == keyPiece) { //by keeping one piece constant we avoid reflections and rotations
        return arrangements;
    }
    for (int i = 0; i < 3; i++) {
        original.Rotate();
        arrangements.emplace(original);
    }
    if (flippable) {
        original.Flip();
        arrangements.emplace(original);
        for (int i = 0; i < 3; i++) {
            original.Rotate();
            arrangements.emplace(original);
        }
    }
    return arrangements;
}

//A recursive function that will return all possible combinations.
void SolvePuzzle(Piece Board[boardSize][boardSize], set<Piece>& PiecesRemaining) {
    if (PiecesRemaining.size() == 0) { //if the program found a solution
        Output(Board);
    }
    int placed = boardSize * boardSize - PiecesRemaining.size();
    int row = (placed / boardSize);
    int col = (placed % boardSize);
    for (Piece curr : PiecesRemaining) {
        if ((row == 0 || curr.Contains(-Board[row - 1][col].con3)) && //if the piece can be placed here
            (col == 0 || curr.Contains(-Board[row][col - 1].con2))) {
            for (Piece arrangement : Arrangements(curr)) {
                if ((row == 0 || arrangement.con1 + Board[row - 1][col].con3 == 0) && //if the piece can be placed here
                    (col == 0 || arrangement.con4 + Board[row][col - 1].con2 == 0)) {
                    set<Piece> tempPiecesRemaining = PiecesRemaining;
                    Board[row][col] = arrangement;
                    tempPiecesRemaining.erase(curr); // pieces are never truly erased from PiecesRemaining, they're just not passed to the next layer
                    SolvePuzzle(Board, tempPiecesRemaining);
                    Board[row][col] = Piece();
                }
            }
        }
    }
    fails++;
}
