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
#include <random>
#include <chrono>

using namespace std;

#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

Console out;  // set up the console, do not modify

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

    // initialize the player and goose monster
    Actor player(PLAYER_CHAR, 70, 10, TILES_X / 2, TILES_Y / 2);  // the player
    //generates walls on each tile
    vector<array<int, 6>> walls = genWall(map);
    //generate a random number of geese up to the cap on random tiles
    vector<Actor> monsters = genMonster(100);

    default_random_engine gen(
            chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> rand(0, 50);
    // Randomly places the win point on some tile
    Actor win(WINNER, MAX_BOARD_X / 2, MAX_BOARD_Y / 2,
              rand(gen)%TILES_X, rand(gen)%TILES_Y, false);
    map[win.get_x()][win.get_y()][win.get_tile_x()][win.get_tile_y()] = WINNER;

    // printing the game instructions
    out.writeLine("Escape the Goose! (They're everywhere) Player: " +
                  player.print_tile_string() + " Win: " +
                  win.print_tile_string());
    out.writeLine("Use the arrow keys to move.");
    out.writeLine("If the goose catches you, you get torn to shreds.");
    out.writeLine(
            "Mere walls cannot hope to stop geese. ");
    renderEnv(player, walls, win, map);


    /*
    Main game loop...
    Will continuously take user input until the game finishes or is closed
    */
    // initialize variable for registering keypresses, with TK_
    int keyEntered = TK_A;
    // continuously taking inputs
    while (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE
           && !captured(player, monsters)
           && (map[player.get_x()][player.get_y()][player.get_tile_x()][player.get_tile_y()] != WINNER))
    {
        //Move the geese toward the player
        gooseApproaching(player, monsters);
        if (terminal_has_input())//Make reading input non-blocking
        {
            keyEntered = terminal_read();  // get player key press
            if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
            {
                if (movePlayer(keyEntered, player, map))//if player moves to different tile
                {
                    renderEnv(player, walls, win, map);//renders the new tile
                    //update the tile location readout
                    out.writeLine(
                            "Escape the Goose! (They're everywhere) Player: " +
                            player.print_tile_string() + " Win: " +
                            win.print_tile_string());
                    out.writeLine("Use the arrow keys to move.");
                    out.writeLine("If the goose catches you, you get torn to shreds.");
                    out.writeLine(
                            "Mere walls cannot hope to stop geese. ");
                }
            }
        }
    }

    // game naturally finished without closing the game window
    if (keyEntered != TK_CLOSE && keyEntered != TK_ESCAPE)
    {
        out.writeLine("Game has ended.");

        if (!captured(player,
                      monsters))  // the player was not captured by goose
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



