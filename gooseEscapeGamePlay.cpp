/*
TODO:
Work through this skeleton
Create random num generator function

*/

/*
File of constants and prototype functions for the game...
Prototype functions are in the corresponding *.hpp file

*/

#include <iostream>
#include <cmath>

using namespace std;

#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;

/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/


// print the game board function

// randomly generate integers to place the player, goose, and other features
int random_nums(int lower_limit, int upper_limit)
{
//	srand((int) time(0));  // time is undeclared?
	int a_random = (rand() % lower_limit) + upper_limit;

	return a_random;  // int randomly generated between lower and upper limits
}

// move player based on keypresses, could use look-up table or switches
void movePlayer(int key, Actor &player, int map[NUM_BOARD_X][NUM_BOARD_Y])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;

    if (player.can_move(xMove, yMove) &&
		map[player.get_x() + xMove][player.get_y() + yMove] != SHALL_NOT_PASS)
	{
		player.update_location(xMove, yMove);
	}
}

// event(s) for when the goose catches the player, can have a fight, HP bar, etc
bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x()
            && player.get_y() == monster.get_y());
}

// for-fun and quality-of-life functions

// void terminal_put(int x_location_on_board, int y_location_on_board,int CHAR);
