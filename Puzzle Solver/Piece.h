//
//  Piece.h
//  Puzzle Solver
//
//  Created by Logan Seaburg on 5/16/17.
//  Copyright © 2017 Logan Seaburg. All rights reserved.
//

#ifndef Piece_h
#define Piece_h

#include<set>
using namespace std;

/* Each peice is made up of 4 connection slots - 2 ins, and two outs.
 /  Out peices will be positive numbers while in peices will be negitive
 /  numbers.  In this way, a match is easy to check, for it will equal 0.
 /  The shape value pairs are as follows:
 /    Circle --------> 1
 /    Cross ---------> 2
 /    Outward Arrow -> 3
 /    Inward Arrow --> 4
 /      *Note that outward circles look like inward circles when negitive,
 /         and vice-versa
 */
struct Piece {
public:
    int con1;
    int con2;
    int con3;
    int con4;
    
    //functions
    Piece();
    Piece(int Con1, int Con2, int Con3, int Con4);
    void Rotate();
    void Flip();
    bool Contains(int con);
    friend bool operator==(Piece piece1, Piece piece2);
    friend bool operator!=(Piece piece1, Piece piece2);
    friend bool operator>(Piece piece1, Piece piece2);
    friend bool operator<(Piece piece1, Piece piece2);
    friend ostream& operator<<(ostream& out, Piece& piece);
};

#endif /* Piece_h */
