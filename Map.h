#include <iostream>
#include <string>
#include <ctime>
#include "Monster.h"

class Map{
    int maxi;
    int maxj;
    char tempchar;
    char grid[20][20];
    int x; //x h grammh pou einai o xarakthras ston pinaka
    int y; //y h sthlh pou einai o xarakthras ston xarth
public:
    Map();
    
    void print();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};