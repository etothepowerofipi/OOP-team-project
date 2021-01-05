#include <iostream>
#include <string>
#include <ctime>
#include "LivingBeing.h"

using namespace std;


//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS


Level::Level(const int lvl= 1): realLevel(lvl), currentXp(0), levelUpXp(realLevel*100 + realLevel*(realLevel-1)) {}

LivingBeing::LivingBeing(const string s, const int lvl=1): name(s), level(lvl) {}

Monster::Monster(const string s, const int lvl=1): LivingBeing(s,lvl), healthPower(50+lvl*15)  {}

Dragon::Dragon(const string n,int lvl) : minAttack(5+6*lvl) , maxAttack(10+6*lvl) , defense(10+4*lvl) , agility(10+2*lvl) , Monster(n,lvl) {}
Exosceleton::Exosceleton(const string n,int lvl) : minAttack(3+3*lvl) , maxAttack(3+3*lvl) , defense(20+5*lvl) , agility(10+2*lvl) , Monster(n,lvl) {}
Spirit::Spirit(const string n,int lvl) : minAttack(3+3*lvl) , maxAttack(3+3*lvl) , defense(10+4*lvl) , agility(20+3*lvl) , Monster(n,lvl) {}

Hero::Hero(const string s): level(1) , name(s) , healthPower(100) , MP(100) , money(0) , LivingBeing(s) {}

Inventory::Inventory(): curcapacity(0),maxcapacity(100) {} //TOBECHANGED



//DESTRUCTORS
//DESTRUCTORS
//DESTRUCTORS
LivingBeing::~LivingBeing() {}

Hero::~Hero() {}

Monster::~Monster() {}

Dragon::~Dragon() {}

Exosceleton::~Exosceleton() {}

Spirit::~Spirit() {}

Inventory::~Inventory() {}





//LEVEL
//LEVEL
//LEVEL
bool Level::addXp(int xptoadd)
{
    currentXp+=xptoadd;
    if(currentXp >= levelUpXp){
        realLevel++;
        currentXp -= levelUpXp;
        return true;
    }
    return false;
}

int Level::getRL() {return realLevel;}
int Level::getXP() {return currentXp;}
int Level::getLvlUp() {return levelUpXp;}







//LivingBeing
//LivingBeing
//LivingBeing

string LivingBeing::getName(){return name;}
int LivingBeing::getHP(){return healthPower;}
int LivingBeing::getLevel(){return level;}
int LivingBeing::getAgility(){return agility;}




bool LivingBeing::dodge()
{
    const int chance = agility * 100;
    int temp = rand()%100;
    if (temp>=chance)
        return false;
    return true;
}


//HERO

void Hero::checkInventory()
{
    inventory.print(*this);
    cout << "Would you like to swap weapons? y/n" << endl;
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y')
    {
        cout << "Which weapon to equip? Input a number" << endl;
        int answer;
        equip(inventory.equipWeapon(answer,weapon));
    }
    cout << "Would you like to swap armors? y/n" << endl;
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y')
    {
        cout << "Which armor to equip? Input a number" << endl;
        int answer;
        equip(inventory.equipArmor(answer,armor));
    }
}

void Hero::equip(const Weapon& w){weapon = w;}
void Hero::equip(const Armor& a){armor = a;}

Weapon Hero::getWeapon(){return weapon;}
Armor Hero::getArmor(){return armor;}
Level Hero::getLevel(){return level;}
Inventory Hero::getInventory(){return inventory;}

// int Hero::use(Spell& s)
// {
//     if (s.getLevelReq() <= level.getRL())
//     {
//         int damage = rand() % 

//         return damage;
//     }
//     cout << "Hero's level is not high enough to use this spell." << endl;
//     return 0;
// }

void Hero::use(Potion& p)
{
    if (p.getMinLevel() <= level.getRL())
    {
        if (p.getUse() == "HP")
        {
            healthPower += p.getEffectPoints(); //TOBECHANGED
        }
        else if (p.getUse() == "MP")
        {
            MP += p.getEffectPoints();
        }
        else if (p.getUse() == "Strength")
        {
            strength += p.getEffectPoints();
        }
        else if (p.getUse() == "Agility")
        {
            agility += p.getEffectPoints();
        }
        else //p.getUse() == "Dexterity"
        {
            dexterity += p.getEffectPoints();
        }
    }
    else
        cout << "Hero's level is not high enough to use this potion." << endl;
}






//MONSTER
//MONSTER
//MONSTER
int Monster::attack()
{
    int temp = maxAttack - minAttack;
    temp = rand() % (temp+1);
    temp += minAttack;
    return temp;
}

int Monster::defend(const int attack)
{
    int damage = attack - defense;
    if (damage < 0)
        return 0;
    return damage;    
}



//INVENTORY

bool Inventory::isFull()
{
    if(wcapacity+acapacity+pcapacity+scapacity < maxcapacity) 
        return false;
    return true;
}

void Inventory::print(Hero& h)
{
    int equipmentCounter = 0;
    cout << "Here is the current equipment for " + h.getName() << endl;
    cout << curcapacity << '/' << maxcapacity << " slots are in use." << endl;
    cout << "Weapons:" << endl;
    for (int i=0; i<wcapacity; i++){
        cout << ++equipmentCounter << ". ";
        weapons[i].print();
    }
    cout << "Current weapon is: " << endl;
    h.getWeapon().print();
  

    equipmentCounter = 0;
    cout << "Armors:" << endl;
    for (int i=0; i<acapacity; i++){
        cout << ++equipmentCounter << ". ";
        armors[i].print();
    }
    cout << "Current armor is: " << endl;
    h.getArmor().print();
  

    equipmentCounter = 0;
    cout << "Potions:" << endl;
    for (int i=0; i<pcapacity; i++){
        cout << ++equipmentCounter << ". ";
        potions[i].print();
    }

    equipmentCounter = 0;
    cout << "Spells:" << endl;
    for (int i=0; i<scapacity; i++){
        cout << ++equipmentCounter << ". ";
        spells[i].print();
    }
}

Weapon Inventory::equipWeapon(const int index, Weapon currentWeapon)
{
    Weapon returnWeapon = weapons[index];
    weapons[index] = currentWeapon;
    return returnWeapon;
}

Armor Inventory::equipArmor(const int index, Armor currentArmor)
{
    Armor returnArmor = armors[index];
    armors[index] = currentArmor;
    return returnArmor;
}

