#include "Items.h"
#include "Spells.h"
#include "Monster.h"



class Grid
{
    private:
        int rows;
        int columns;


    public:
        Grid(const int, const int);
};

class Cell
{
    private:

    public:
        Cell(const int avgPlayerLevel);
};

class Market: public Cell
{
    private:
        std::vector<Weapon> weapons;
        std::vector<Armor> armors;
        std::vector<Potion> potions;
        std::vector<Spell*> spells;

    public:
        Market(const int avgPlayerLevel);
};

class Common: public Cell
{
    private:
        std::vector<Monster*> monsters;

    public:
        Common(const int avgPlayerLevel);

};



