#include <iostream>
#include "field.h"

Field::Field()
{
    value = 0;
    bombed = false;
    revealed = false;
    flagged = false;
}
bool Field::setbomb()
{
    if(bombed)
        return false;
    bombed = 1;
    return true;
}
bool Field::bomb()
{
    return bombed;
}
bool Field::reveal()
{
    revealed = true;    
    return bombed;
}
char Field::state()
{
    if(revealed&&bombed)
        return '*';
    else if(flagged)
        return 'F';
    else if(revealed)
        return value+48;
    else
        return '.';
}
void Field::add_value()
{
    value++;
}
char Field::state_lose()
{
    if(bombed)
        return '*';
    else if(flagged && !bombed)
        return 'X';
    else if(flagged)
        return 'F';
    else if(revealed)
        return value+48;
    else
        return '.';
}
int Field::getvalue()
{
    return value;
}
void Field::change_status_of_flag()
{
    if(flagged)
        flagged = false;
    else
        flagged = true;
}

bool Field::is_revealed()
{
    return revealed;
}

bool Field::is_flagged()
{
    return flagged;
}