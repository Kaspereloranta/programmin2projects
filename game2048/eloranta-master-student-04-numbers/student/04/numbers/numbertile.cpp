/*  Source file for NumberTile class.
 *
 * Also contains an operator for pair addition.
 *
 * Method implementations should be added to the same level as the existing
 * ones.
 * Program author
 * Name: Kasper Eloranta
 * E-Mail: kasper.eloranta@tuni.fi
 *
 * */
#include "numbertile.hh"
#include <iomanip>
#include <iostream>
using namespace std;

// The constructor method of the object.
NumberTile::NumberTile(int value,
                       int x, int y,
                       vector<vector<NumberTile> > *board )
    : value_(value),x_(x),y_(y), board_(*board){}


// Tells whether the certain tile is available or not and returns boolean
// about it.

// Students should not touch this method.
void NumberTile::print(int width)
{
    // std::setw() sets the width of next printable to given amount, usually
    // by adding spaces in front.
    cout << "|" << setw(width - 1) << value_;
}

// Returns value of the tile.
int NumberTile::value(){
    return value_;
}

// Clears the tile.
void NumberTile::clear(){
    value_ = 0;
}

// Doubles the value of the tile.
void NumberTile::double_value(){
    value_ = value_ * 2;
}

// Tells whether the certain tile is available or not,
// and returns boolean about it.
bool NumberTile::is_available(){

    if (value_ == 0) {
        return true;
    }
    else {
        return false;
    }
}

//Sets value given as a parameter to value of the tile, if it's empty.
bool NumberTile::setValue(int value){

    if(is_available()==true) {
         value_ = value;
         return true;
    }
    else {
        return false;
    }
}



