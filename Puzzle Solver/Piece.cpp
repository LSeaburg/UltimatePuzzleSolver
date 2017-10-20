//
//  Piece.cpp
//  Puzzle Solver
//
//  Created by Logan Seaburg on 5/16/17.
//  Copyright © 2017 Logan Seaburg. All rights reserved.
//

#include <algorithm>
#include <math.h>
#include <iostream>
#include "Piece.h"
/*constructs a new Piece with 4 args, 1 per connection the piece has */
Piece::Piece() {
    con1 = 0;
    con2 = 0;
    con3 = 0;
    con4 = 0;
}

Piece::Piece(int Con1, int Con2, int Con3, int Con4) {
    con1 = Con1;
    con2 = Con2;
    con3 = Con3;
    con4 = Con4;
}

/*acts as if to rotate the piece 1 quarter turn clockwise */
void Piece::Rotate() {
    int temp = con1;
    con1 = con2;
    con2 = con3;
    con3 = con4;
    con4 = temp;
}

/*acts as if you're turning the piece upside down */
void Piece::Flip() {
    int temp = con2;
    con2 = con4;
    con4 = temp;
}

/*returns true if the piece has the connection that
 is passed as an argument */
bool Piece::Contains(int con) {
    if (con1 == con || con2 == con || con3 == con || con4 == con) {
        return true;
    }
    return false;
}

//operators that make set implementation possible
bool operator==(const Piece piece1, const Piece piece2) {
    if (piece1.con1 == piece2.con1 &&
        piece1.con2 == piece2.con2 &&
        piece1.con3 == piece2.con3 &&
        piece1.con4 == piece2.con4) {
        return true;
    }
    return false;
}
bool operator!=(const Piece piece1, const Piece piece2) {
    return !(piece1 == piece2);
}
bool operator>(const Piece piece1, const Piece piece2) {
    if (125 * piece1.con1 + 25 * piece1.con2 +  5 * piece1.con3 + piece1.con4 >
        125 * piece2.con1 + 25 * piece2.con2 +  5 * piece2.con3 + piece2.con4) {
        return true;
    }
    return false;
}
bool operator<(const Piece piece1, const Piece piece2) {
    if (piece1 == piece2) {
        return false;
    } else if (piece1 > piece2) {
        return false;
    }
    return true;
}
ostream& operator <<(ostream& out, const Piece& piece) {
    out << piece.con1 << " " << piece.con2 << " "
    << piece.con3 << " " << piece.con4 << "   ";
    return out;
}
