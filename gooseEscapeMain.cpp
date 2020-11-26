/*
TODO:
Randomize player and monster spawn location, at initialization
	Error check: while the spawns overlap, regenerate numbers
Move goose, in main game loop
Call other for-fun functions, in main game loop

*/

#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

Console out;  // set up the console, do not modify


void
renderEnv(const Actor &player, const vector<Actor> &walls, const Actor &win);

int main()
{
    /*
    Initialization...

    */

    // set up the window, do not modify
    terminal_open();
    terminal_set(SETUP_MESSAGE);

    // set the game map in a 320x180 window, for a 16x9 screen aspect ratio
    map map;

    // initialize features in the game map
    map[0][0][0][0] = WINNER;

    // initialize the player and goose monster
    Actor player(PLAYER_CHAR, 70, 10, 0, 0);  // the player
    Actor monster(MONSTER_CHAR, 70, 20, 0, 0);  // the monster
    int start[] = {30, 5};
    int end[] = {40, 20};
    int tile[] = {0, 0};

    vector<array<int,6>> walls;
    for (int i = 0; i < TILES_X; i++)
    {
        for (int s = 0; s < TILES_Y; s++)
        {
            auto curWall = wallSection(30+i,5+i,40+s,20+s,i,s,map, false);
            walls.emplace_back(curWall);
        }
    }
    Actor win(WINNER, 0, 0, 0, 0);

    // printing the game instructions
    out.writeLine("Escape the Goose! " + monster.get_location_string());
    out.writeLine("Use the arrow keys to move.");
    out.writeLine("If the goose catches you, you lose!");
    out.writeLine("Be careful! Sometimes the goose can jump through walls!");
    renderEnv(player, walls, win, map);


    /*
    Main game loop...
    Will continuously take user input until the game finishes or is closed
    */
    // initialize variable for registering keypresses, with TK_
    int keyEntered = TK_A;
    // continuously taking inputs
    while (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE
           && !captured(player, monster)
           && (map[player.get_x()][player.get_y()][0][0] != WINNER))
    {
        gooseApproaching(player, monster);
        if (terminal_has_input())
        {
            keyEntered = terminal_read();  // get player key press
            if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
            {
                if (movePlayer(keyEntered, player, map))
                {
                    renderEnv(player, walls, win, map);
                };  // move the player
                // move goose
                // call other functions to do stuff?
            }
        }
        // gooseApproaching(player,monster);
    }
    /*
    Game end...

    */

    // game naturally finished without closing the game window
    if (keyEntered != TK_CLOSE && keyEntered != TK_ESCAPE)
    {
        out.writeLine("Game has ended.");

        if (!captured(player, monster))  // the player was not captured by goose
        {
            out.writeLine("You escaped the goose and won!");
        }
        else
        {
            out.writeLine("The goose has caught you, you lost!");
        }

        // close window based on user input
        while (terminal_read() != TK_CLOSE && terminal_read() != TK_ESCAPE);
    }

    terminal_close();  // close game
}


