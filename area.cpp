#include <iostream>
#include <cstdlib>
#include "field.h"
#include "area.h"
#include <vector>
#include <unistd.h>
#include <string>
#include <chrono>

using namespace std::chrono;

Area::Area(int x, int y, int bombs)
{
    x_axis = x;
    y_axis = y;
    spots = x*y;
    howmanybombs = bombs;
    gameend_lose = false;
    gameend_win = false;
}

void Area::initiate_game_area()
{
    game_area = new Field[spots];
    srand(time(NULL));
    rand();
    for(int i = 0 ; i < howmanybombs ; i++)
    {
        bool bombset;
        int random;
        do
        {
            random = rand() % spots;
            bombset = game_area[random].setbomb();
            //std::cout<<"Set bomb to spot number : "<<random<<" bombset = "<<bombset<<", state of field in that spot : "<<game_area[random].bomb()<<std::endl;
        } while (!bombset);
        // now code i don't really know how can i shorten it, sorry
        if(random % x_axis != 0 && random >= x_axis)
            game_area[random - 1 - x_axis].add_value();
        if(random >= y_axis)
            game_area[random - x_axis].add_value();
        if(random % x_axis != x_axis - 1 && random >= y_axis)
            game_area[random + 1 - x_axis].add_value();
        if(random % x_axis != 0)
            game_area[random -1].add_value();
        if(random % x_axis != x_axis - 1)
            game_area[random+1].add_value();
        if(random % x_axis != 0 && random < spots - x_axis)
            game_area[random -1 + x_axis].add_value();
        if(random < spots - x_axis)
            game_area[random + x_axis].add_value();
        if(random % x_axis != x_axis - 1 && random < spots - x_axis)
            game_area[random + 1 + x_axis].add_value();
        //printbombs();
        //std::cout<<std::endl<<"----------------------------"<<std::endl;
    }
    for(int i = 0 ; i < spots ; i++)
    {
        if(game_area[i].bomb())
            continue;
        else
            unrevealed_nonbombs.push_back(i);
    }
}
void Area::printbombs() // debug function
{
    int curspot = 0;
    std::cout<<"  |";
    for(int i = 0 ; i < x_axis ; i++)
        printf("%2d│",i+1);
    std::cout<<std::endl;
    for(int i = 0 ; i < y_axis ; i++)
    {
        std::cout<<"──┼";
        for(int j = 0 ; j < x_axis ; j++)
            std::cout<<"──┼";
        std::cout<<std::endl;
        printf("%2d│",i+1);
        for(int j = 0 ; j < x_axis ; j++)
        {
            printf("%2c│",game_area[curspot].state_lose());
            curspot++;
        }
        std::cout<<std::endl;
    }
}

void Area::display()
{
    char action;
    int x;
    int y;
    std::string xin;
    std::string yin;
    print_board();
    std::cout<<"What do you want to do ? "<<std::endl;
    std::cout<<"Input F if you want to put a flag or remove it"<<std::endl;
    std::cout<<"Input R if you want to reveal a field"<<std::endl;
    //std::cout<<unrevealed_nonbombs.size()<<" fields to win"<<std::endl; // Debugging cout, used for checking if game area works properly
    std::cin>>action;
    if(tolower(action) == 'f' || tolower(action) == 'r')
    {
        std::cout<<"Input row number"<<std::endl;
        std::cin>>xin;
        if(isnumber(xin))
            y = stoi(xin);
        else
            return;
        std::cout<<"Input column number"<<std::endl;
        std::cin>>yin;
        if(isnumber(yin))
            x = stoi(yin);
        else
            return;
        int place = x_axis*(y-1) + (x-1);
        if(place >= spots)
            return;
        if(tolower(action)=='r' && !game_area[place].is_flagged())
        {
            if(!game_area[place].is_revealed())
                uncover(game_area[place],place);
        }
        else if(tolower(action)=='f' && !game_area[place].is_revealed())
            game_area[place].change_status_of_flag();
        std::cout<<"Win check"<<std::endl;
        //sleep(2);
        gameend_win = no_more_fields();
    }
    else
        return;
}

void Area::uncover(Field &x, int place)
{
    if(x.reveal())
    {
        gameend_lose = true;
        return;
    }
    else
    {
        int pos = 0;
        for(int i : unrevealed_nonbombs)
        {
            if(place == i)
            {
                unrevealed_nonbombs.erase(unrevealed_nonbombs.begin() + pos);
                break;
            }
            pos++;
        }
    }
    if(x.getvalue() == 0)
    {
        if(place % x_axis != 0 && place >= x_axis)
        {
            //std::cout<<"Uncovering field number "<<place - 1 - x_axis<<std::endl;
            if(!game_area[place - 1 - x_axis].is_revealed())
                uncover(game_area[place - 1 - x_axis],place - 1 - x_axis);
        }
        if(place >= x_axis)
        {
            //std::cout<<"Uncovering field number "<<place - x_axis<<std::endl;
            if(!game_area[place - x_axis].is_revealed())
                uncover(game_area[place - x_axis],place-x_axis);
        }
        if(place % x_axis != x_axis - 1 && place >= x_axis)
        {
            //std::cout<<"Uncovering field number "<<place + 1 - x_axis<<std::endl;
            if(!game_area[place + 1 - x_axis].is_revealed())
                uncover(game_area[place + 1 - x_axis],place + 1 - x_axis);
        }
        if(place % x_axis != 0)
        {
            //std::cout<<"Uncovering field number "<<place - 1<<std::endl;
            if(!game_area[place - 1].is_revealed())
                uncover(game_area[place -1], place-1);
        }
        if(place % x_axis != x_axis - 1)
        {
            //std::cout<<"Uncovering field number "<<place + 1<<std::endl;
            if(!game_area[place + 1].is_revealed())
                uncover(game_area[place+1], place +1);
        }
        if(place % x_axis != 0 && place < spots - x_axis)
        {
            //std::cout<<"Uncovering field number "<<place - 1 + x_axis<<std::endl;
            if(!game_area[place - 1 + x_axis].is_revealed())
                uncover(game_area[place -1 + x_axis], place - 1 + x_axis);
        }
        if(place < spots - x_axis)
        {
            //std::cout<<"Uncovering field number "<<place + x_axis<<std::endl;
            if(!game_area[place + x_axis].is_revealed())
                uncover(game_area[place + x_axis] , place + x_axis);
        }
        if(place % x_axis != x_axis - 1 && place < spots - x_axis)
        {
            //std::cout<<"Uncovering field number "<<place + 1 + x_axis<<std::endl;
            if(!game_area[place + 1 + x_axis].is_revealed())
                uncover(game_area[place + 1 + x_axis] , place + 1+ x_axis);
        }
    }
}

bool Area::is_game_over()
{
    return gameend_lose;
}

void Area::gameend()
{
    printbombs();
    std::cout<<std::endl<<"You lose :("<<std::endl;

}

bool Area::no_more_fields()
{
    if(unrevealed_nonbombs.size()==0)
        return true;
    else
        return false;
}

bool Area::win()
{
    return gameend_win;
}

void Area::print_board()
{
    int curspot = 0;
    std::cout<<"  |";
    for(int i = 0 ; i < x_axis ; i++)
        printf("%2d│",i+1);
    std::cout<<std::endl;
    for(int i = 0 ; i < y_axis ; i++)
    {
        std::cout<<"──┼";
        for(int j = 0 ; j < x_axis ; j++)
            std::cout<<"──┼";
        std::cout<<std::endl;
        printf("%2d|",i+1);
        for(int j = 0 ; j < x_axis ; j++)
        {
            printf("%2c│",game_area[curspot].state());
            curspot++;
        }
        std::cout<<std::endl;
    }
    for(int i = 0 ; i <= x_axis ; i++)
        std::cout<<"──┼";
    std::cout<<std::endl;
}

bool Area::isnumber(std::string input)
{
    int len = input.length();
    for(int i = 0 ; i < len ; i++)
    {
        if(!isdigit(input[i]))
            return false;
    }
    return true;
}

void Area::play()
{
    auto start = high_resolution_clock::now();
    initiate_game_area();
    //x.printbombs();
    while(true)
    {
        system("clear");
        display();
        if(is_game_over())
        {
            system("clear");
            gameend();
            break;
        }
        if(win())
        {
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast <seconds>(stop - start);
            system("clear");
            print_board();
            std::cout<<std::endl<<"You win!"<<std::endl;
            std::cout<<"Final time is : "<<duration.count()<<" seconds"<<std::endl;
            break;
        }
    }
}