#ifndef FIELD_H
#define FIELD_H

class Field
{
private:
    int value;
    bool revealed;
    bool flagged;
    bool bombed;
public:
    Field ();
    bool setbomb();
    bool bomb();
    bool reveal();
    char state();
    void add_value();
    char state_lose();
    int getvalue();
    void change_status_of_flag();
    bool is_revealed();
    bool is_flagged();

};

#endif