#include <iostream>
#include <string>
#include <ctime>
#include "Monster.h"

class Marketplace{
    Inventory stock;
    Hero** heroes;
    int numofheroes;
public:
    Marketplace(Hero** );

    void menu();
    void buy();
    void sell();
};

class Grid{
    int maxi;
    int maxj;
    char tempchar;
    char map[20][20];
    int x; //x h grammh pou einai o xarakthras ston pinaka
    int y; //y h sthlh pou einai o xarakthras ston xarth
    int numofheroes;
    Hero** heroes;
    Marketplace* market;
public:
    Grid(Hero** ,int );
    
    bool menu();
    void print();
    void move();
    bool canPlace(int ,int );

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool checkBlock(int,int);

    bool battle();
};