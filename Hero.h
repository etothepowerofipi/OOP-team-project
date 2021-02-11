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
        Level(const int);

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
        int gold;
        Weapon weapon;
        Armor armor;
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
        void showStats();
        void attack(Monster*);
        bool defend(int);
        int castSpell();
        int cast(Spell*);
        int usePotion();    
        void use(const Potion&);
        virtual void levelUp() = 0;
        void gainXP(const int);
        void gainGold(const int);
        
        //Marketplace
        bool buy(Weapon);
        bool buy(Armor);
        bool buy(Potion);
        bool buy(Spell*);
        void addGold(int);


        void checkInventory();
        void equip(const int);
        void equip(const Weapon&);
        void equip(const Armor&);
        void removeSpell(const int);
        void removePotion(const int);


        //accessors
        Weapon getWeapon() const;
        Armor getArmor() const;
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
