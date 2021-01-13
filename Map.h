#include <iostream>
#include <string>
#include <ctime>
#include "Monster.h"

class Map{
    char grid[10][10];
    int x; //x h grammh pou einai o xarakthras ston pinaka
    int y; //y h sthlh pou einai o xarakthras ston xarth
public:
    Map();
    
    void print();
};