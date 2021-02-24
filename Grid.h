#include <iostream>
#include <string>
#include <ctime>
#include "Hero.h"

class Effects{
    private:
        std::vector <Monster*> monsters;
        std::vector <int> type;
        std::vector <int> amount;
        std::vector <int> rounds;

    public:
        Effects();
        ~Effects();

        void addEffect(Monster*, int*);
        void newRound();
};


class Marketplace{
private:
    Weapon** w;
    Armor** a;
    Spell** s;
    Potion** p;
    int noh;
    Inventory stock;
public:
    Marketplace(Hero** ,int);
    ~Marketplace();

    void menu(Hero** ,int );
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