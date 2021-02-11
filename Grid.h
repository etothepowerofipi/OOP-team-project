#include <iostream>
#include <string>
#include <ctime>
#include "Hero.h"

class Marketplace{
    Inventory stock;
    Hero** heroes;
    int numofheroes;
public:
    Marketplace(Hero** ,int );

    void menu();
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
    int level() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool checkBlock(int,int);

    bool battle();
    void battleStats(Monster**,const int, const int) const;
    int battleMenu(const int) const;
};