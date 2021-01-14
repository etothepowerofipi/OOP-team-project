#include <iostream>
#include "Functions.h"

using namespace std;

bool inputAnswer()
{
    char input;
    cin >> input;
    bool acceptable = input == 'y' || input == 'Y' || input == 'n' || input == 'N';
    while (acceptable == false){
        cout << "Wrong input. Try again." << endl;
        cin >> input;
        acceptable = input == 'y' || input == 'Y' || input == 'n' || input == 'N';
    }

    return (input == 'y' || input == 'Y');   
}

int inputNumber(const int max)
{
    unsigned input;
    cin >> input;
    bool acceptable = input <= max;
    while (acceptable == false){
        cout << "Wrong input. Try again." << endl;
        cin >> input;
        acceptable = input <= max;
    }
    return input;
}


//INPUTMENU

bool left (char input) {return input == 'a' || input == 'A';}
bool right (char input) {return input == 'd' || input == 'D';}
bool up (char input) {return input == 'w' || input == 'W';}
bool down (char input) {return input == 's' || input == 'S';}
bool stop (char input) {return input == 'n' || input == 'N';}

int direction(char input)
{
    if (left(input) == true)
        return 1;
    else if (right(input) == true)
        return 2;
    else if (up(input) == true)
        return 3;
    else if (down(input) == true)
        return 4;
    else if (stop(input) == true)
        return 5;   
    return 0;
}

int inputMenu()
{
    char input;
    cin >> input;

    while (direction(input) == 0)
    {
        cout << "Wrong input. Try again." << endl;
        cin >> input;
    }
    return direction(input);
}

