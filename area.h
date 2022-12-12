#ifndef AREA_H
#define AREA_H

#include <vector>
#include "field.h"
#include <string>

class Area
{
private:
    int x_axis;
    int y_axis;
    int spots; // how many spots in game area overall
    int howmanybombs;
    bool gameend_lose; // condition for losing the game
    bool gameend_win; // condition for winning the game
    Field *game_area;
    std::vector<int> bombspots;
    std::vector<int> unrevealed_nonbombs;
public:
    Area(int x, int y, int z);
    void initiate_game_area();
    void printbombs(); // debug function
    void display();
    void uncover(Field &x, int place);
    bool is_game_over();
    void gameend();
    bool no_more_fields();
    bool win();
    void print_board();
    bool isnumber(std::string input);
    void play();
};


#endif