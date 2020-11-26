/*
TODO:
Work through this skeleton

*/

/*
File for the Actor class

*/

#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS

#include <cmath>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

/*
    Modify this class to contain more characteristics of the "actor".  Add
    functions that will be useful for playing the game that are specific to
    the Actor.
    
    Feel free to add additional Classes to your program.
*/

/* 
    Going further:  Learn the other syntax for implementing a class that is
    more appropriate for working with multiple files, and improve the class code.
*/

class Actor {
private:
    int actorChar{};
    int location_x, location_y;
    int location_tile_x, location_tile_y;

public:
    Actor()
    {
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        location_tile_x = 0;
        location_tile_y = 0;
        put_actor();
    }

    Actor(char initPlayerChar, int x0, int y0, int tx0, int ty0)
    {
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        location_tile_x = tx0;
        location_tile_y = ty0;
        update_location(x0, y0);
    }

    int get_x() const
    {
        return location_x;
    }

    int get_y() const
    {
        return location_y;
    }

    string get_location_string() const
    {
        char buffer[80];
        //itoa(location_x,buffer,10);
        sprintf(buffer, "%d", location_x);
        string formatted_location = "(" + string(buffer) + ",";
        //itoa(location_y,buffer,10);
        sprintf(buffer, "%d", location_y);
        formatted_location += string(buffer) + ")";
        return formatted_location;
    }

    void change_char(char new_actor_char)
    {
        actorChar = min(int('~'), max(int(new_actor_char), int(' ')));
    }

    bool can_move(int delta_x, int delta_y) const
    {
        int new_x = location_x + delta_x;
        int new_y = location_y + delta_y;

        return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X
               && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
    }

    void update_location(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            terminal_clear_area(location_x, location_y, 1, 1);
            location_x += delta_x;
            location_y += delta_y;
            put_actor();
        }
        else if (actorChar == '@')
        {
            int new_x = location_x + delta_x;
            int new_y = location_y + delta_y;
            if (location_tile_x != 0 && new_x < MIN_BOARD_X)
            {
                location_x = MAX_BOARD_X;
                location_tile_x--;
                terminal_clear_area(MIN_BOARD_X, MIN_BOARD_Y, NUM_BOARD_X,
                                    NUM_BOARD_Y);
                put_actor();

            }
            else if (location_tile_x != TILES_X - 1 && new_x > MAX_BOARD_X)
            {
                location_x = MIN_BOARD_X;
                location_tile_x++;
                terminal_clear_area(MIN_BOARD_X, MIN_BOARD_Y, NUM_BOARD_X,
                                    NUM_BOARD_Y);
                put_actor();
            }
            if (location_tile_y != 0 && new_y < MIN_BOARD_Y)
            {
                location_y = MAX_BOARD_X;
                location_tile_y--;
                terminal_clear_area(MIN_BOARD_X, MIN_BOARD_Y, NUM_BOARD_X,
                                    NUM_BOARD_Y);
                put_actor();
            }
            else if (location_tile_y != TILES_Y - 1 && new_y > MAX_BOARD_Y)
            {
                location_y = MIN_BOARD_X;
                location_tile_y++;
                terminal_clear_area(MIN_BOARD_X, MIN_BOARD_Y, NUM_BOARD_X,
                                    NUM_BOARD_Y);
                put_actor();

            }
            cout << location_x << "," << location_y << "," << location_tile_x
                 << "," << location_tile_y
                 << endl;
        }

    }

    void put_actor() const
    {
        terminal_put(location_x, location_y, actorChar);
        terminal_refresh();
    }

};

#endif
