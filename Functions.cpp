#include <iostream>
#include "Functions.h"

using namespace std;

bool inputAnswer()
{
    char input;
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
    bool acceptable = input <= max;
    while (acceptable == false){
        cout << "Wrong input.Try again." << endl;
        cin >> input;
        acceptable = input <= max;
    }
    return input;
}