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

//goose move/time
const double GOOSE_MOVE_INTERVAL=0.7;
//player move/time
//Stops button spamming
const double PLAYER_MOVE_INTERVAL=0.1;


//generates and returns a section of wall
array<int, 6> wallSection(int startX, int startY, int endX,
                          int endY, int tileX, int tileY,
                          map map, bool render=false);
//generates a random amount of wall in each tile and returns them
vector<array<int, 6>> genWall(map map);

vector<Actor> genMonster(int);
// move player based on keypresses, could use look-up table or switches
bool movePlayer(int key, Actor & player, map map);

// event(s) for when the goose catches the player, can have a fight, HP bar, etc
bool captured(Actor const &player, vector<Actor> const &monsters);

//Moves all geese towards the player's tile and location
void gooseApproaching(Actor &player, vector<Actor> &monsters);

//Render walls and win tile when the player moves into a new tile
void
renderEnv(const Actor &player, const vector<array<int,6>> &walls, const Actor &win, map map);

#endif
