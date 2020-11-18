/*
TODO:
Randomize player and monster spawn location, at initialization
Output L if caught by goose or W if reached the win location, at game end
Move goose, in main game loop
Call other for-fun functions, in main game loop

*/

#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>

using namespace std;

#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

// set up the console, do not modify
Console out;

int main()
{
	/*
	Initialization...
	
	*/

	// set up the window, do not modify
    terminal_open();
  	terminal_set(SETUP_MESSAGE);

	// set the game map in a 320x180 window, for a 16x9 screen aspect ratio
    int map[NUM_BOARD_X][NUM_BOARD_Y];
    
    // initialize features in the game map
    map[0][1] = SHALL_NOT_PASS;
    map[0][0] = WINNER;

	// initialize the player and goose monster
	Actor player(PLAYER_CHAR, 10, 10);  // the player
	Actor monster(MONSTER_CHAR, 70, 20);  	// the monster
    Actor wall(WALL_CHAR, 0, 1);  	// wall
    Actor win(WIN_CHAR,0,0);


    // printing the game instructions
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");


	/*
	Main game loop...
	Will continuously take user input until the game finishes or is closed
	
	*/

	// initialize variable for keypresses, with TK_
	int keyEntered = TK_A;  
    
    // continuously taking inputs
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
        	&& !captured(player,monster)
			&& (map[player.get_x()][player.get_y()]!= WINNER))
	{
	    keyEntered = terminal_read();  // get player key press

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
    	    movePlayer(keyEntered,player, map);  // move the player

            // move goose
            
            // call other functions to do stuff?	    
        }
  	}


	/*
	Game end...
	
	*/

	// game naturally finished without closing the game window
    if (keyEntered != TK_CLOSE)
    {
        out.writeLine("Game has ended");
    
        // output L if caught by goose or W if reached the win location
	
        while (terminal_read() != TK_CLOSE);  // wait until window is closed
    }

    terminal_close();  // close game
}
