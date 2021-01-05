#include <iostream>
#include <string>
#include <vector>
#include "Spells.h"
#include "Items.h"

class Level
{
        int realLevel;
        int currentXp;
        int levelUpXp;
    public:
        Level(const int);

        void levelUp();

        bool addXp(int);
        int getRL();
        int getXP();
        int getLvlUp();
};


class Inventory
{
    private:
        int maxcapacity;
        int curcapacity;
        int wcapacity;
        int acapacity;
        int pcapacity;
        int scapacity;
        std::vector <Weapon> weapons;
        std::vector <Armor> armors;
        std::vector <Potion> potions;
        std::vector <Spell> spells;

    public:
        Inventory();
        ~Inventory();

        bool isFull();
        void print(Hero&);

        Weapon equipWeapon(const int,const Weapon);
        Armor equipArmor(const int,const Armor);
};

class LivingBeing
{
    protected:
        std::string name;
        int healthPower;
        int level;
        int agility;

    public:
        LivingBeing(const std::string,const int);
        virtual ~LivingBeing();

        void takesDamage(const int);
        virtual void faint() = 0;

        string getName();
        int getHP();
        int getLevel();
        int getAgility();

        bool dodge();
};

class Hero: public LivingBeing
{
    protected:
        int MP;
        int strength;
        int dexterity;
        int money;
        Weapon weapon;
        Armor armor;
        Level level;
        Inventory inventory;
        
    public:
        Hero(const std::string);

        int attack();
        int use(Spell&);
        void use(Potion&);

        void checkInventory();

        void equip(const int);
        void equip(const Weapon&);
        void equip(const Armor&);

        Weapon getWeapon();
        Armor getArmor();
        Level getLevel();
        Inventory getInventory();

        
};




class Monster: public LivingBeing
{
    protected:
        int minAttack;
        int maxAttack;
        int defense;

    public:
        Monster(const std::string,const int);
        virtual ~Monster();

        int attack(); //Epistrefei tuxaio arithmo anamesa sto minAttack kai to maxAttack.
        int defend(const int); //Epistrefei to damage pou tha parei to teras meta th meiwsh tou incoming damage apo to defense.
};

class Dragon: public Monster
{
    public:
        Dragon(const std::string,const int);
        ~Dragon();
};

class Exosceleton: public Monster
{
    public:
        Exosceleton(std::string,const int);
        ~Exosceleton();
};

class Spirit: public Monster
{
    public:
        Spirit(const std::string,const int);
        ~Spirit();
};


