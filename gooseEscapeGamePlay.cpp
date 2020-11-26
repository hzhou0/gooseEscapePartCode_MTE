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
#include <random>

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







array<int, 6> wallSection(const int startX, const int startY, const int endX,
                          const int endY, const int tileX, const int tileY,
                          map map,
                          bool render)
{
    int current_x, current_y;
    current_x = startX;
    current_y = startY;
    //Generates walls from the start to the end
    while (!(current_x ==
             endX && current_y
                     == endY))
    {
        map[current_x][current_y][tileX][tileY] =
                SHALL_NOT_PASS;
        if (render)
        {
            //Actually prints the wall
            Actor wall(SHALL_NOT_PASS, current_x, current_y, tileX, tileY);
        }
        if (endX > current_x)
        {
            current_x++;
        }
        else if (endX < current_x)
        {
            current_x--;
        }
        if (endY > current_y)
        {
            current_y++;
        }
        else if (endY < current_y)
        {
            current_y--;
        }
    }
    //returns the vector of walls instead of the wall objects to optimize performance
    array<int, 6> data = {startX, startY, endX, endY, tileX, tileY};
    return data;
}

vector<array<int, 6>> genWall(map map)
{
    default_random_engine gen(
            chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> rand(0, 100);
    //Generates random amount of wallSections of each tile
    //Generate barrier walls for tiles at the outer limits
    vector<array<int, 6>> walls;
    for (int i = 0; i < TILES_X; i++)
    {
        for (int s = 0; s < TILES_Y; s++)
        {
            if (i == 0)
            {
                walls.emplace_back(wallSection(0,0,0,MAX_BOARD_Y,i,s,map,false));
            }
            else if (i == TILES_X-1)
            {
                walls.emplace_back(wallSection(MAX_BOARD_X,0,MAX_BOARD_X,MAX_BOARD_Y,i,s,map,false));
            }
            if (s == 0)
            {
                walls.emplace_back(wallSection(0,0,MAX_BOARD_X,0,i,s,map,false));
            }
            else if (s == TILES_Y-1)
            {
                walls.emplace_back(wallSection(0,MAX_BOARD_Y,MAX_BOARD_X,MAX_BOARD_Y,i,s,map,false));
            }
            else
            {
                int wallNum = rand(gen) % 3 + 1;
                for (int w = 0; w < (wallNum); w++)
                {
                    auto curWall = wallSection(rand(gen) % MAX_BOARD_X,
                                               rand(gen) % MAX_BOARD_Y,
                                               rand(gen) % MAX_BOARD_X,
                                               rand(gen) % MAX_BOARD_Y,
                                               i, s, map,
                                               false);
                    walls.emplace_back(curWall);
                }
            }
        }
    }
    return walls;
}

// move player based on keypresses, could use look-up table or switches
// return true if the player crosses over to a different tile
bool movePlayer(int key, Actor &player, map map)
{
    static auto lastmove = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds =
            chrono::system_clock::now() - lastmove;
    if (elapsed_seconds.count() > PLAYER_MOVE_INTERVAL)
    {
        lastmove = chrono::system_clock::now();
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
            if (player.update_location(xMove, yMove, player))
            {
                player.put_actor();
                return true;
            }
            player.put_actor();
        }
    }
    return false;
}

// event(s) for when the goose catches the player, can have a fight, HP bar, etc
// Check if the player and the geese is on the same tile and position
bool captured(Actor const &player, vector<Actor> const &monsters)
{
    for (auto const &monster: monsters)
    {
        if (player.get_x() == monster.get_x()
            && player.get_y() == monster.get_y() &&
            player.get_tile_x() == monster.get_tile_x() &&
            player.get_tile_y() == monster.get_tile_y())
        {
            return true;
        }
    }
    return false;
}


// for-fun and quality-of-life functions

void gooseApproaching(Actor &player, vector<Actor> &monsters)
{
    static auto lastmove = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds =
            chrono::system_clock::now() - lastmove;
    if (elapsed_seconds.count() > GOOSE_MOVE_INTERVAL)
    {
        lastmove = chrono::system_clock::now();
        for (Actor &monster: monsters)
        {
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
                monster.update_location(xMove, yMove, player);
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
                monster.update_location(xMove, yMove, player);
            }
        }
    }
}


void
renderEnv(const Actor &player, const vector<array<int, 6>> &walls,
          const Actor &win, map map)
{
    for (auto wall:walls)
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

vector<Actor> genMonster(int maxNum)
{
    vector<Actor> monsters;
    default_random_engine gen(
            chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> rand(0, 100);
    int monsterNum = rand(gen) % maxNum + 1;
    monsters.reserve(monsterNum);
    for (int i = 0; i < monsterNum; i++)
    {
        monsters.emplace_back(MONSTER_CHAR, rand(gen) % MAX_BOARD_X,
                              rand(gen) % MAX_BOARD_Y,
                              rand(gen) % TILES_X,
                              rand(gen) % TILES_Y, false);
    }
    return monsters;
}
// void terminal_put(int x_location_on_board, int y_location_on_board,int CHAR);
