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
        int getRL() const;
        int getXP() const;
        int getLvlUpXP() const;
};

class Hero;
class Inventory
{
    protected:
        std::vector <Weapon> weapons;
        std::vector <Armor> armors;
        std::vector <Potion> potions;
        std::vector <Spell*> spells;

    public:
        Inventory();
        virtual ~Inventory();

        void addWeapon(Weapon);
        void addArmor(Armor);
        void addPotion(Potion);
        void addSpell(Spell*);

        void removeWeapon(int);
        void removeArmor(int);
        void removePotion(int);
        void removeSpell(int);

        Weapon getWeapon(int );
        Armor getArmor(int );
        Potion getPotion(int );
        Spell* getSpell(int );

        int getWeaponsSize() const;
        int getArmorsSize() const;
        int getPotionsSize() const;
        int getSpellsSize() const;
        int getSize() const;

        void print() const;
};

class PlayerInventory : public Inventory
{
    public:
        PlayerInventory();
        ~PlayerInventory();

        Weapon equipWeapon(const int,Weapon);
        Armor equipArmor(const int,Armor);

        int Capacity(const int) const;
        bool isFull(const Hero&) const;
        void print(const Hero&) const;
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
        PlayerInventory inventory;

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
        void showStats();
        int maxHP();
        int maxMP();

        void checkInventory();
        bool buy(Weapon);
        bool buy(Armor);
        bool buy(Potion);
        bool buy(Spell*);
        void addMoney(int);

        void equip(const int);
        void equip(const Weapon&);
        void equip(const Armor&);

        Weapon getWeapon() const;
        Armor getArmor() const;
        Level getLevel() const;
        PlayerInventory getInventory() const;
        int getAgility() const; 
        int getMoney();
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