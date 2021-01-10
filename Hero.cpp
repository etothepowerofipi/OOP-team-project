#include <iostream>
#include <string>
#include <ctime>
#include "Hero.h"
using namespace std;

//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

Level::Level(const int lvl= 1): realLevel(lvl), currentXp(0), levelUpXp(realLevel*100 + realLevel*(realLevel-1)) {}

Hero::Hero(const string s) : LivingBeing(s,1) {
    healthPower=100;
    MP=100;
    money=0;
    strength = 10;
    agility = 0.1;
    dexterity = 5;
    weapon.starterWeapon();
}

Warrior::Warrior(const string s): Hero(s) 
{
    strength *= 1.5;
    agility *= 1.5;
    dexterity *= 1;
}
Sorcerer::Sorcerer(const string s): Hero(s) 
{
    strength *= 1;
    agility *= 1.5;
    dexterity *= 1.5;
}

Paladin::Paladin(const string s): Hero(s)
{
    strength *= 1.5;
    agility *= 1;
    dexterity *= 1.5;
}

Inventory::Inventory(): curcapacity(0),maxcapacity(100) {} //TOBECHANGED

//DESTRUCTORS
//DESTRUCTORS
//DESTRUCTORS

Hero::~Hero() {}
Inventory::~Inventory() {
    for(int i=0;i<scapacity;i++) delete spells[i];
}

//LEVEL
//LEVEL
//LEVEL
int Level::addXp(int xptoadd)
{
    int levelUps = 0;
    currentXp+=xptoadd;
    while(currentXp >= levelUpXp)
    {
        levelUp();
        levelUps++;
    }
    return levelUps;
}

void Level::levelUp()
{
    realLevel++;
    currentXp -= levelUpXp;
    levelUpXp = realLevel*100 + realLevel*(realLevel-1);
}

int Level::getRL() {return realLevel;}
int Level::getXP() {return currentXp;}
int Level::getLvlUpXP() {return levelUpXp;}

//HERO
//HERO
//HERO
int Hero::attack(){return (weapon.getDamage()+strength);}
void Hero::takeDamage(int damage){
    damage-=armor.getProtection();
    if(dodge(agility)){cout << "Attack has been dodged!" << endl; return;}
    if(damage < 0) damage=0;
    healthPower-=damage;
    cout << name << " takes " << damage << " damage!" << endl;
}

void Hero::faint(){
    cout << name << " has fainted!" << endl;
    healthPower/=2;
}

void Hero::addXP(const int xpToAdd) 
{
    const int levelUps = level.addXp(xpToAdd);
    for (int i=0; i<levelUps; i++)
        levelUp();
}

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
    cin >> answer;
    if (answer == 'y' || answer == 'Y')
    {
        cout << "Which armor to equip? Input a number" << endl;
        int answer;
        equip(inventory.equipArmor(answer,armor));
    }
}

void Hero::addMoney(int a){money+=a;}
void Hero::buy(Weapon w){
    cout << "Would you like to buy this weapon? y/n" << endl; w.print();
    char a;
    cin >> a;
    if(a == 'y'){
        if(money >= w.getPrice()){
            money-=w.getPrice();
            inventory.addWeapon(w);
        }
        else cout << "Too poor lmao!" << endl;
    }
}
void Hero::buy(Armor a){
    cout << "Would you like to buy this armor? y/n" << endl; a.print();
    char an;
    cin >> an;
    if(an == 'y'){
        if(money >= a.getPrice()){
            money-=a.getPrice();
            inventory.addArmor(a);
        }
        else cout << "Too poor lmao!" << endl;
    }
}
void Hero::buy(Potion p){
    cout << "Would you like to buy this potion? y/n" << endl; p.print();
    char a;
    cin >> a;
    if(a == 'y'){
        if(money >= p.getPrice()){
            money-=p.getPrice();
            inventory.addPotion(p);
        }
        else cout << "Too poor lmao!" << endl;
    }
}
void Hero::buy(Spell* s){
    cout << "Would you like to buy this spell? y/n" << endl; s->print();
    char a;
    cin >> a;
    if(a == 'y'){
        if(money >= s->getPrice()){
            money-=s->getPrice();
            inventory.addSpell(s);
        }
        else cout << "Too poor lmao!" << endl;
    }
}

void Hero::equip(const Weapon& w){weapon = w;}
void Hero::equip(const Armor& a){armor = a;}

Weapon Hero::getWeapon(){return weapon;}
Armor Hero::getArmor(){return armor;}
Level Hero::getLevel(){return level;}
Inventory Hero::getInventory(){return inventory;}
int Hero::getAgility(){return agility;}

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

//SubClasses Hero

void Warrior::levelUp()
{
    LivingBeing::level++;
    healthPower += 50;
    MP =+ 50;

    strength += 10* 1.5; //TOBECHANGED
    agility += 0.05* 1.5;
    dexterity += 5;
}

void Sorcerer::levelUp()
{
    LivingBeing::level++;
    healthPower += 50;
    MP =+ 50;

    strength += 10; //TOBECHANGED
    agility += 0.05* 1.5;
    dexterity += 5* 1.5;
}

void Paladin::levelUp()
{
    LivingBeing::level++; // = level.reallevel
    healthPower += 50;
    MP =+ 50;

    strength += 10* 1.5; //TOBECHANGED
    agility += 0.05;
    dexterity += 5* 1.5;
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
    for (int i=0; i<weapons.size(); i++){
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
        spells[i]->print();
    }
}

void Inventory::addWeapon(Weapon w)
{
    weapons.push_back(w);
}

void Inventory::addArmor(Armor a)
{
    armors.push_back(a);
}

void Inventory::addPotion(Potion p)
{
    potions.push_back(p);
}

void Inventory::addSpell(Spell* s)
{
    spells.push_back(s);
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