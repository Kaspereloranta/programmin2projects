/* Numbers ( or 2048, but that's an invalid name ) : Template code
 *
 * Desc:
 *  This program generates a game of 2048, a tile combining game
 * where the goal is to get from 2's to 2048. The board is SIZE x SIZE,
 * ( original was 4x4 ) and every round the player chooses a direction
 * to which the tiles should fall. If they collide with a wall or a different
 * value, they will move as close as they can get. If they collide with
 * a tile with same value, they will combine and double the value. The
 * tile will continue to move until a wall or other tile comes along, but a
 * single tile can only be combined once per "turn".
 *  Game will end when the goal value asked (orig 2048) is reached or new
 * tile can't be added to the board.
 *
 * Program author
 * Name: Kasper Eloranta
 * E-Mail: kasper.eloranta@tuni.fi 
 * */

#include "numbertile.hh"
#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <string>
using namespace std;

const int SIZE = 4;
const int NEW_VALUE = 2;
const int PRINT_WIDTH = 5;
const int DEFAULT_GOAL = 2048;

// Adds a single new value to board using rEng and distr for random positioning.
void newValue(vector<vector<NumberTile>> &board,
               default_random_engine &rEng,
               uniform_int_distribution<int> &distr){
    // Tries to assign NEW_VAl to randomly selected tile. Continues trying until
    // newVal() returns true.teemu.teekkari
    while(!board.at(distr(rEng)).at(distr(rEng)).setValue(NEW_VALUE));
}

// Initializes the board to size SIZE x SIZE and adds SIZE tiles with NEW_VALUE
// to it through new_value() func after initializing the random engine with
// a seed value.
void initBoard(vector<vector<NumberTile>> &board,
                default_random_engine &rEng,
                uniform_int_distribution<int> &distr){

    // Initialize the board with SIZE x SIZE empty numbertiles.
    for ( auto y = 0; y < SIZE; y++ ){
        board.push_back({});
        for ( auto x = 0; x < SIZE; x++ ){
            // If you don't want to use pairs, replace "std::make_pair(y, x)"
            // with "y, x".
            board.at(y).push_back(NumberTile(0, y, x, &board));
        }

    }

    // Ask user for the seed value and initialize rEng.
    cout << "Give a seed value or an empty line: ";
    string seed = "";
    getline(cin, seed);

    if(seed == "") {
        // If the user did not give a seed value, use computer time as the seed
        // value.
        rEng.seed(time(NULL));
    } else {
        // If the user gave a seed value, use it.
        rEng.seed(stoi(seed));
    }

    // Add some tiles to the board.
    for ( int i = 0 ; i < SIZE ; ++i ){
        newValue(board, rEng, distr);
    }
}

// Prints the board.
void print(vector<vector<NumberTile>> &board){   
    // The y isn't actually the y coordinate or some int, but an iterator that
    // is like a vector of NumberTiles.
    for ( auto y : board ){
        // Prints a row of dashes.
        cout << string(PRINT_WIDTH * SIZE + 1, '-') << endl;
        // And then print all cells in the desired width.
        for ( auto x : y ){
            x.print(PRINT_WIDTH);
        }
        // And a line after each row.
        cout << "|" << endl;
    }
    // Print a last row of dashes so that the board looks complete.
    cout << string(PRINT_WIDTH * SIZE + 1, '-') << endl;
}

// Moves the tiles to direction given as a parameter if possible.
// Bool-type parameter calculate is used depending on if we want to
// sum up possible adjacent tiles whose values are equal.
void move(string kirjain, vector<vector<NumberTile>> &board, bool calculate);

// Sums up adjacent tiles depending on which direction player has moved
// the tiles before. The direction is given as a parameter way.
void sum(string way, vector<vector<NumberTile>> &board){

    int x=0;
    int y=0;

    if (way == "a"){
        while (y<4){
            x = 0;
            while(x<3) {
                if(board.at(y).at(x).value()==board.at(y).at(x+1).value()){
                    board.at(y).at(x+1).clear();
                    board.at(y).at(x).double_value();
                    ++x;
                }
                ++x;
            }
            ++y;
        }
    }
    if (way == "w"){
        while (x<4){
            y = 0;
            while(y<3) {
                if(board.at(y).at(x).value()==board.at(y+1).at(x).value()){
                    board.at(y+1).at(x).clear();
                    board.at(y).at(x).double_value();
                    ++y;
                }
                ++y;
            }
            ++x;
        }
    }
    if (way == "d"){
        while (y<4){
            x = 0;
            while(x<3) {
                if(board.at(y).at(x).value()==board.at(y).at(x+1).value()){
                    board.at(y).at(x).clear();
                    board.at(y).at(x+1).double_value();
                    ++x;
                }
                ++x;
            }
            ++y;
        }
    }
    if (way == "s"){
        while (x<4){
            y = 0;
            while(y<3) {
                if(board.at(y).at(x).value()==board.at(y+1).at(x).value()){
                    board.at(y).at(x).clear();
                    board.at(y+1).at(x).double_value();
                    ++y;
                }
                ++y;
            }
            ++x;
        }
    }
    bool calculate = false;
    move(way,board,calculate);
}

// Moves the tiles to direction given as a parameter if possible.
// Bool-type parameter calculate is used depending on if we want to
// sum up possible adjacent tiles whose values are equal.
void move(string way, vector<vector<NumberTile>> &board, bool calculate){

    int x = 0;  // Int-type variables x,y and i are used when we are
    int y = 0;  // going through tiles with while-structure
    int i = 0;  // to know which tiles are supposed to move and which aren't.
    int empty_tiles = 0;

    if (way == "a"){

        while(y<4){

            x = 0;

            while (x<4){

                empty_tiles = 0;

                if (board.at(y).at(x).is_available() == false){
                    i = 0;
                    while (i < x){
                        if (board.at(y).at(i).is_available()==true) {
                            ++empty_tiles;
                        }
                        else{
                            empty_tiles = 0;
                        }
                        ++i;
                    }
                    int arvo = board.at(y).at(x).value();
                    board.at(y).at(x).clear();
                    board.at(y).at(x-empty_tiles).setValue(arvo);
                }
                ++x;
            }
            ++y;
        }
     }

    if (way == "w"){

        while(x<4){

            y = 0;

            while (y<4){

                empty_tiles = 0;

                if (board.at(y).at(x).is_available() == false){
                    i = 0;
                    while (i < y){
                        if (board.at(i).at(x).is_available()==true) {
                            ++empty_tiles;
                        }
                        else{
                            empty_tiles = 0;
                        }
                        ++i;
                    }
                    int arvo = board.at(y).at(x).value();
                    board.at(y).at(x).clear();
                    board.at(y-empty_tiles).at(x).setValue(arvo);
                }
                ++y;
            }
            ++x;
         }
    }

    if (way == "s"){

        while(x < 4){

            y = 3;

            while (y>=0){
                empty_tiles = 0;
                if (board.at(y).at(x).is_available() == false){
                    i = 3;
                    while (i > y){
                        if (board.at(i).at(x).is_available()==true) {
                            ++empty_tiles;
                        }
                        else{
                            empty_tiles = 0;
                        }
                        --i;
                     }
                    int arvo = board.at(y).at(x).value();
                    board.at(y).at(x).clear();
                    board.at(y+empty_tiles).at(x).setValue(arvo);
                }
                --y;
            }
            ++x;
        }
    }
    if (way == "d"){

        while(y<4){

            x = 3;

            while (x>=0){
                empty_tiles = 0;
                if (board.at(y).at(x).is_available() == false){
                    i = 3;
                    while (i > x){
                        if (board.at(y).at(i).is_available()==true) {
                            ++empty_tiles;
                        }
                        else{
                            empty_tiles = 0;
                        }
                        --i;
                    }
                    int arvo = board.at(y).at(x).value();
                    board.at(y).at(x).clear();
                    board.at(y).at(x+empty_tiles).setValue(arvo);
                }
                --x;
            }
            ++y;
        }
    }
  if (calculate==true){
    sum(way, board);
  }
}

bool has_game_ended(vector<vector<NumberTile>> &board, int goal_value);

// Function command asks player direction where the tiles are wanted to be moved.
// If player gives command q the function will shut the program down. If player
// gives some other command than direction commands {w,a,s,d], the program will
// print an error notice.

bool command(vector<vector<NumberTile>> &board,default_random_engine &rEng,
             uniform_int_distribution<int> &distr,int goal_value){

    bool calculate = true;
    string input;
    cout << "Dir> ";
    cin >> input;

    if (input == "q"){
        return false;
    }
    else if (input!="w" and input!="a" and input!="s" and input!="d") {
        cout << "Error: unknown command." << endl;
    }
    else  {

        move(input,board,calculate);
        if (has_game_ended(board,goal_value)==true){
            print(board);
            cout << "You reached the goal value of "
                 << goal_value << "!" << endl;
            return false;
        }
        else{
            newValue(board,rEng,distr);
        }
    }
    return true;
}
// Function has_game_ended checks if the player has won or lost game. Player wins
// if one of the tiles contains the goal value which is 2048 as a default if player
// didn't change it at the beginning of program. Player loses if all of the tiles
// include a number and there are not a single tile which is next to tile including same
// value.

bool has_game_ended(vector<vector<NumberTile>> &board, int goal_value){

    int x = 0;
    int y = 0;
    int reserved_tiles = 0;

    while(y<4){

        x = 0;

        while(x<4){

            if(board.at(y).at(x).value()==goal_value){

                return true;
            }
            if(board.at(y).at(x).is_available()==false) {

                if(x>0 and x<3 and y>0 and y<3){

                    if(board.at(y).at(x).value() == board.at(y).at(x+1).value()
                     or board.at(y).at(x).value() == board.at(y).at(x-1).value()
                     or board.at(y).at(x).value() == board.at(y+1).at(x).value()
                     or board.at(y).at(x).value() == board.at(y-1).at(x).value()){
                     --reserved_tiles;
                    }
                }

                else if(x == 0){

                    if(board.at(y).at(x).value() == board.at(y).at(x+1).value()){
                        --reserved_tiles;
                    }
                }

                else if(y == 0){

                    if(board.at(y).at(x).value()==board.at(y+1).at(x).value()){
                        --reserved_tiles;
                    }
                }

                else if(x==3){

                    if(board.at(y).at(x).value()==board.at(y).at(x-1).value()){
                        --reserved_tiles;
                    }
                }

                else if(y==3){

                    if(board.at(y).at(x).value()==board.at(y-1).at(x).value()){
                        --reserved_tiles;
                    }
                }

                else{
                    ++reserved_tiles;
                }
            }
            ++x;
       }
        ++y;
    }
    if (reserved_tiles == 16){

        cout <<"Can't add new tile, you lost!" << endl;
        return true;
    }

    return false;
}

// Ask user if goal value needs to be changed and
// returns it.
int define_goal_value(){

    string value = "";
    int goal_value = 0;

    cout << "Give a goal value or an empty line: ";
    getline(cin,value);

    if (value !=""){
        goal_value = stoi(value);
    }
    else{
        goal_value = DEFAULT_GOAL;
    }
    return goal_value;
}

// The main function of the program.
int main()
{
    // Declare the board and randomengine.
    vector<vector<NumberTile>> board;
    default_random_engine randomEng;
    // And initialize the disrt to give numbers from the correct
    uniform_int_distribution<int> distr(0, SIZE - 1);
    initBoard(board, randomEng, distr);   

    int goal_value = define_goal_value();
    print(board);

    while(command(board,randomEng,distr, goal_value) == true){
        print(board);          
    }
}

