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
#include <array>
#include <chrono>
#include <vector>

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







array<int, 6> wallSection(const int start_x, const int start_y, const int end_x,
                          const int end_y, const int tile_x, const int tile_y,
                          map map,
                          bool render)
{
    int current_x, current_y;
    current_x = start_x;
    current_y = start_y;
    while (!(current_x ==
             end_x && current_y
                      == end_y))
    {
        map[current_x][current_y][tile_x][tile_y] =
                SHALL_NOT_PASS;
        if (render)
        {
            Actor wall(SHALL_NOT_PASS, current_x, current_y, tile_x, tile_y);
        }
        if (end_x > current_x)
        {
            current_x++;
        }
        else if (end_x < current_x)
        {
            current_x--;
        }
        if (end_y > current_y)
        {
            current_y++;
        }
        else if (end_y < current_y)
        {
            current_y--;
        }
    }
    array<int, 6> data = {start_x, start_y, end_x, end_y, tile_x, tile_y};
    return
            data;
}

// move player based on keypresses, could use look-up table or switches
bool movePlayer(int key, Actor &player, map map)
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

    if (map[player.get_x() + xMove][player.get_y() + yMove]
        [player.get_tile_x()][player.get_tile_y()] != SHALL_NOT_PASS)
    {
        //If the player crossed tiles
        if (player.update_location(xMove, yMove))
        {
            player.put_actor();
            return true;
        }
        player.put_actor();
    }
    return false;
}

// event(s) for when the goose catches the player, can have a fight, HP bar, etc
bool captured(Actor const &player, Actor const &monster)
{
    return (player.get_x() == monster.get_x()
            && player.get_y() == monster.get_y());
}


// for-fun and quality-of-life functions

void gooseApproaching(Actor &player, Actor &monster)
{
    static auto lastmove = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds =
            chrono::system_clock::now() - lastmove;
    if (elapsed_seconds.count() > GOOSE_MOVE_INTERVAL)
    {
        lastmove = chrono::system_clock::now();
        // Some computation here
        int yMove = 0, xMove = 0;
        if (player.get_tile_x() == monster.get_tile_x() &&
            player.get_tile_y() == monster.get_tile_y())
        {
            if (monster.get_x() > player.get_x())
            {
                xMove = -1;
            }
            else if (monster.get_x() < player.get_x())
            {
                xMove = 1;
            }
            if (monster.get_y() > player.get_y())
            {
                yMove = -1;
            }
            else if (monster.get_y() < player.get_y())
            {
                yMove = 1;
            }
            monster.update_location(xMove, yMove);
            monster.put_actor();
        }
        else
        {
            if (monster.get_tile_x() > player.get_tile_x())
            {
                xMove = -1;
            }
            else if (monster.get_tile_x() < player.get_tile_x())
            {
                xMove = 1;
            }
            if (monster.get_tile_y() > player.get_tile_y())
            {
                yMove = -1;
            }
            else if (monster.get_tile_y() < player.get_tile_y())
            {
                yMove = 1;
            }
            monster.update_location(xMove, yMove);
        }
    }
}


void
renderEnv(const Actor &player, const vector<array<int, 6>> &walls,
          const Actor &win, map map)
{
    for (auto &&wall:walls)
    {
        if (wall[4] == player.get_tile_x() &&
            wall[5] == player.get_tile_y())
        {
            wallSection(wall[0], wall[1], wall[2], wall[3], wall[4], wall[5],
                        map, true);
        }
        if (player.get_tile_x() == win.get_tile_x() &&
            player.get_tile_y() == win.get_tile_y())
        {
            win.put_actor();
        }
    }
}
// void terminal_put(int x_location_on_board, int y_location_on_board,int CHAR);
