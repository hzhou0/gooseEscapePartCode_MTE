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
#include <vector>
#include <chrono>

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


vector<Actor>
wallSection(const int start[2], const int end[2], const int tile[2], map map)
{
    int current[2] = {};
    current[0] = start[0];
    current[1] = start[1];
    vector<Actor> walls;
    while (!(current[0] == end[0] && current[1] == end[1]))
    {
        walls.emplace_back(SHALL_NOT_PASS, current[0], current[1], tile[0],
                           tile[1]);
        map[current[0]][current[1]][tile[0]][tile[1]] = SHALL_NOT_PASS;
        if (end[0] > current[0])
        {
            current[0]++;
        }
        else if (end[0] < current[0])
        {
            current[0]--;
        }
        if (end[1] > current[1])
        {
            current[1]++;
        }
        else if (end[1] < current[1])
        {
            current[1]--;
        }
    }
    return walls;
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


void renderEnv(const Actor &player, const vector<Actor> &walls, const Actor &win)
{
    for (auto &&wall:walls)
    {
        if (wall.get_tile_x() == player.get_tile_x() &&
            wall.get_tile_y() == player.get_tile_y())
        {
            wall.put_actor();
        }
        if (player.get_tile_x() == win.get_tile_x() &&
            player.get_tile_y() == win.get_tile_y())
        {
            win.put_actor();
        }
    }
}
// void terminal_put(int x_location_on_board, int y_location_on_board,int CHAR);
