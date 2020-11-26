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
#include <vector>

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
vector<Actor>
wallSection(const int start[2], const int end[2], const int tile[2], map map);

// move player based on keypresses, could use look-up table or switches
bool movePlayer(int key, Actor & player, map map);

// event(s) for when the goose catches the player, can have a fight, HP bar, etc
bool captured(Actor const & player, Actor const & monster);

// for-fun and quality-of-life functions
void gooseApproaching(Actor &player, Actor &monster);

void renderEnv(const Actor &player, const vector<Actor> &walls, const Actor &win);

// void terminal_put(int x_location_on_board, int y_location_on_board,int CHAR);

#endif
