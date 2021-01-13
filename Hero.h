#include <iostream>
#include <string>
#include <vector>
#include "LivingBeing.h"

class Level
{
        int realLevel;
        int currentXp;
        int levelUpXp;

    public:
        Level(const int);

        void levelUp();

        int addXp(int); //Pros8etei XP = <orisma> sto currentXP, kai epistrefei to posa level anebhke o hrwas.
        int getRL();
        int getXP();
        int getLvlUpXP();
};

class Hero;
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
        std::vector <Spell*> spells;

    public:
        Inventory();
        ~Inventory();

        void addWeapon(Weapon);
        void addArmor(Armor);
        void addPotion(Potion);
        void addSpell(Spell*);

        Weapon equipWeapon(const int,const Weapon);
        Armor equipArmor(const int,const Armor);

        int getWeapons();
        int getArmors();
        int getPotions();
        int getSpells();
        bool isFull();
        void print(Hero&);
};

class Hero: public LivingBeing
{
    protected:
        int MP;
        int strength;
        int dexterity;
        int agility;
        int money;
        Weapon weapon;
        Armor armor;
        Level level;
        Inventory inventory;

    public:
        Hero(const std::string);
        ~Hero();

        int attack();
        void takeDamage(int);
        int use(Spell&);
        void use(Potion&);
        virtual void levelUp() = 0;
        void addXP(const int);
        void faint();

        void checkInventory();
        void buy(Weapon);
        void buy(Armor);
        void buy(Potion);
        void buy(Spell*);
        void addMoney(int a);

        void equip(const int);
        void equip(const Weapon&);
        void equip(const Armor&);

        Weapon getWeapon();
        Armor getArmor();
        Level getLevel();
        Inventory getInventory();
        int getAgility();    
};

class Warrior: public Hero
{
    public: 
        Warrior(const std::string);
        void levelUp();
};

class Sorcerer: public Hero
{
    public:
        Sorcerer(const std::string);
        void levelUp();
};

class Paladin: public Hero
{
    public:
        Paladin(const std::string);
        void levelUp();
};