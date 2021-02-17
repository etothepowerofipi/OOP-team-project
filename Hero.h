#include <iostream>
#include <string>
#include <vector>
#include "Monster.h"

class Level
{
    private:
        int realLevel;
        int currentXp;
        int levelUpXp() const;

    public:
        Level();

        int addXp(int); //Pros8etei XP = <orisma> sto currentXP, kai epistrefei to posa level anebhke o hrwas.
        void levelUp();

        //accessors
        int getRL() const;
        int getXP() const;
        void print() const;
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

        void printWeapons();
        void printArmors();
        void printSpells();
        void printPotions();

        void addWeapon(Weapon);
        void addArmor(Armor);
        void addPotion(Potion);
        void addSpell(Spell*);

        void removeWeapon(int);
        void removeArmor(int);
        void removePotion(int);
        void removeSpell(int);

        Weapon getWeapon(int);
        Weapon* getPWeapon(int);
        Armor getArmor(int);
        Armor* getPArmor(int);
        Potion getPotion(int );
        Spell* getSpell(int );

        int getWeaponsSize() const;
        int getArmorsSize() const;
        int getPotionsSize() const;
        int getSpellsSize() const;
        int getSize() const;

        void print();
};

class PlayerInventory : public Inventory
{
    public:
        PlayerInventory();
        ~PlayerInventory();

        int Capacity(const int) const;
        bool isFull(const Hero&) const;
        void print(Hero&);
};

class Hero: public LivingBeing
{
    protected:
        int MP;
        int strength;
        int dexterity;
        int agility;
        int gold;
        Weapon* weapon;
        Armor* armor;
        Level level;
        PlayerInventory inventory;

        int maxHP() const;
        int maxMP() const;

        bool dodge();
        void faint();

    public:
        Hero(const std::string);
        ~Hero();

        //Battle
        void gainMP();
        void gainHP();
        void showStats();
        int attack();
        bool defend(int);
        int castSpell();
        int cast(Spell*);
        int usePotion();    
        void use(const Potion&);
        virtual void levelUp();
        void gainXP(const int);
        void gainGold(const int);
        
        //Marketplace
        bool buy(Weapon);
        bool buy(Armor);
        bool buy(Potion);
        bool buy(Spell*);
        void sell(std::string );
        void addGold(int);


        void checkInventory();
        void printInventory();
        void printWeapons();
        void printArmors();
        void printSpells();
        void printPotions();

        void removeWeapon(const int);
        void removeArmor(const int);
        void removeSpell(const int);
        void removePotion(const int);


        //accessors
        Weapon getWeapon() const;
        Weapon* getPWeapon();
        Armor getArmor() const;
        Armor* getPArmor();
        Level getLevel() const;
        PlayerInventory getInventory() const;
        int getAgility() const; 
        int getGold();
        virtual std::string type() const = 0;
        void print() const;
};

class Warrior: public Hero
{
    public: 
        Warrior(const std::string);
        void levelUp();
        std::string type() const;
};

class Sorcerer: public Hero
{
    public:
        Sorcerer(const std::string);
        void levelUp();
        std::string type() const;
};

class Paladin: public Hero
{
    public:
        Paladin(const std::string);
        void levelUp();
        std::string type() const;
};

int level(Hero** , const int );
void heroFainted(Hero**, int&, const int);
