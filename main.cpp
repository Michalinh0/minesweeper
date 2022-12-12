#include <iostream>
#include "area.h"
#include "field.h"
#include <unistd.h>

using namespace std;

int main()
{
    string input;
    int level;
    while(true)
    {
        system("clear");
        cout<<"Welcome to Minesweeper! ver 1.0"<<endl;
        cout<<"Choose your difficulty : "<<endl;
        cout<<"1. Easy ( 9 x 9 board , 10 bombs )"<<endl;
        cout<<"2. Intermediate ( 16 x 16 board , 40 bombs )"<<endl;
        cout<<"3. Expert ( 30 x 16 board , 99 bombs )"<<endl;
        cin>>input;
        if(input.length()==1 && (input[0]=='1' || input[0]=='2' || input[0]=='3'))
        {
            level = stoi(input);
            break;
        }
    }
    if(level == 1)
    {
        Area game(9,9,5);
        game.play();
    }
    else if(level == 2)
    {
        Area game(16,16,40);
        game.play();
    }
    else if(level == 3)
    {
        Area game(30,16,99);
        game.play();
    }
    return 0;
}


// Beginner : (9,9,10)
// Intermediate : (16,16,40)
// Expert : (30,16,99)

// box coding characters on wikipedia