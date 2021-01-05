/* Class: Numbertile
 *
 * Acts as a single tile in the board.
 *
 * Students can modify both parts of the class and add their own variables
 * and methods. Implementations for the methods should be in the source file.
 *
 * Program author
 * Name: Kasper Eloranta
 * Student number: 274212
 * UserID: eloranta
 * E-Mail: kasper.eloranta@tuni.fi
 *
 * */
#ifndef NUMBERTILE_HH
#define NUMBERTILE_HH
#include <utility>
#include <vector>
using namespace std;

class NumberTile
{
public:

    // Public part contains variables and methods that can be used outside the
    // class itself.

    // Constructor that takes in a value, a location and the board the tile is on.
    NumberTile(int value, int x, int y,  vector<vector<NumberTile>> *board);

    // Prints the tile in the desired width.
    void print( int width );

    // Tells the value of the tile.
    int value();

    // Clears the tile.
    void clear();

    // Doubles the value of the tile.
    void double_value();

    // Tells whether the certain tile is empty or not and returns boolean
    // about it.
    bool is_available();

    // Tries to set a new value to the tile. Returns true if successful, false
    // if the tile already contains some value.
    bool setValue(int value);

private:
    // Private part contains variables and methods that shouldn't be usable
    // outside the class.

    // Value of the tile.
    int value_ = 0;
    int x_;
    int y_;
    vector<vector<NumberTile>> board_;


};

#endif // NUMBERTILE_HH
