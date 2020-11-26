/*
TODO:
Work through this skeleton

*/

/*
File of constants and function prototypes for the game...
Fleshed-out functions are in the corresponding *.cpp file

*/

#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY

#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include <array>

/*
Constants for game features, can use enum in place of integers
    
*/
// different types of spaces in the game map
const int EMPTY = 0;  // empty space
const int SHALL_NOT_PASS = int('o');  // impassable barrier for player character
const int WINNER = int('%');  // win condition to move toward


// player and the goose monster
const int PLAYER_CHAR = int('@');  // player character controlled by user
const int MONSTER_CHAR = int('G');  // goose to avoid

//goose move interval
const double GOOSE_MOVE_INTERVAL=0.5;
/*
Function prototypes...

*/

// print the game board function protype

//generates and returns a section of wall
array<int, 6> wallSection( int start_x,  int start_y,  int end_x,
                           int end_y,  int tile_x,  int tile_y,
                           map map, bool render);

// move player based on keypresses, could use look-up table or switches
bool movePlayer(int key, Actor & player, map map);

// event(s) for when the goose catches the player, can have a fight, HP bar, etc
bool captured(Actor const & player, Actor const & monster);

// for-fun and quality-of-life functions
void gooseApproaching(Actor &player, Actor &monster);

void
renderEnv(const Actor &player, const vector<array<int,6>> &walls, const Actor &win, map map);

// void terminal_put(int x_location_on_board, int y_location_on_board,int CHAR);

#endif
