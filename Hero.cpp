#include <iostream>
#include <string>
#include <ctime>
#include "Hero.h"
#include "Functions.h"
using namespace std;


//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

Level::Level(const int lvl= 1): realLevel(lvl), currentXp(0), levelUpXp(realLevel*100 + realLevel*(realLevel-1)) {}

Hero::Hero(const string s) : LivingBeing(s,1) {
    healthPower=100;
    MP=100;
    money=0;
    weapon.starterWeapon();
    armor.starterArmor();
}

Warrior::Warrior(const string s): Hero(s) 
{
    strength = 2;
    agility = 2;
    dexterity = 1;
}
Sorcerer::Sorcerer(const string s): Hero(s) 
{
    strength = 1;
    agility = 2;
    dexterity = 2;
}

Paladin::Paladin(const string s): Hero(s)
{
    strength = 2;
    agility = 1;
    dexterity = 2;
}

Inventory::Inventory() {} 
PlayerInventory::PlayerInventory(): Inventory() {}

//DESTRUCTORS
//DESTRUCTORS
//DESTRUCTORS

Hero::~Hero() {}
Inventory::~Inventory() {
    for(int i=0;i<spells.size();i++) delete spells[i];
}

PlayerInventory::~PlayerInventory() {}

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

int Level::getRL() const {return realLevel;}
int Level::getXP() const {return currentXp;}
int Level::getLvlUpXP() const {return levelUpXp;}

//HERO
//HERO
//HERO

void Hero::showStats(){
    cout << "Printing stats for " << getName() << "." << endl;
    cout << "Health points : " << healthPower << "/" << maxHP() << endl;
    cout << "Magical points : " << MP << "/" << maxMP() << endl;
    cout << "Level : " << level.getRL() << endl;
    cout << "Strength : " << strength << endl;
    cout << "Agility : " << agility << endl;
    cout << "Dexterity : " << dexterity << endl;
    cout << "Money : " << money << endl;
    cout << endl;
}

int Hero::maxHP() const{return 100+5*(level.getRL()-1);}
int Hero::maxMP() const{return 100+5*(level.getRL()-1);}

int Hero::attack(Monster* monster){
    int initialDamage = weapon.getDamage()+strength;
    if (monster->dodge() == false){
        monster->takeDamage(monster->defend(initialDamage));
    }
    return 42069;

}

void Hero::takeDamage(int damage){
    damage-=armor.getProtection();
    if(dodge()){cout << "Attack has been dodged!" << endl; return;}
    if(damage < 0) damage=0;
    healthPower-=damage;
    cout << name << " takes " << damage << " damage!" << endl;
}

bool Hero::dodge(){
    int temp = rand() % 100;
    return (temp <= agility );
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

    cout << "Here is the current inventory for " << getName() << endl;
    inventory.print(*this);

    char yes;
    int index;
    
    if (inventory.getWeaponsSize() > 0){
        cout << "Would you like to swap weapons? y/n" << endl;
        yes = inputAnswer();
        if (yes){
            cout << "Which weapon to equip? Input a number" << endl;
            index = inputNumber(inventory.getWeaponsSize());
            equip(inventory.equipWeapon(index,weapon));
        }
    }

    if (inventory.getArmorsSize() > 0){
        cout << "Would you like to swap armors? y/n" << endl;
        yes = inputAnswer();
        if (yes){
            cout << "Which armor to equip? Input a number" << endl;
            index = inputNumber(inventory.getArmorsSize());
            equip(inventory.equipArmor(index,armor));
        }
    }

    cout << "Current weapon is: " << endl;
    getWeapon().print();
    cout << "Current armor is: " << endl;
    getArmor().print();
}

int Inventory::getWeaponsSize() const{return weapons.size();}
int Inventory::getArmorsSize() const{return armors.size();}
int Inventory::getPotionsSize() const{return potions.size();}
int Inventory::getSpellsSize() const{return spells.size();}

void Hero::addMoney(int a){money+=a;}
bool Hero::buy(Weapon w){
    if(money >= w.getPrice()){
        money-= w.getPrice();
        inventory.addWeapon(w);
        return true;
    }
    else{
        cout << "Too poor lmao!" << endl;
        return false;
    }
}
bool Hero::buy(Armor a){
    if(money >= a.getPrice()){
        money-= a.getPrice();
        inventory.addArmor(a);
        return true;
    }
    else{
        cout << "Too poor lmao!" << endl;
        return false;
    }
}
bool Hero::buy(Potion p){
    if(money >= p.getPrice()){
        money-= p.getPrice();
        inventory.addPotion(p);
        return true;
    }
    else{
        cout << "Too poor lmao!" << endl;
        return false;
    }
}
bool Hero::buy(Spell* s){
    if(money >= s->getPrice()){
        money-= s->getPrice();
        inventory.addSpell(s);
        return true;
    }
    else{
        cout << "Too poor lmao!" << endl;
        return false;
    }
}

void Hero::equip(const Weapon& w) {weapon = w;}
void Hero::equip(const Armor& a) {armor = a;}

Weapon Hero::getWeapon() const {return weapon;}
Armor Hero::getArmor() const {return armor;}
Level Hero::getLevel() const {return level;}
PlayerInventory Hero::getInventory() const {return inventory;}
int Hero::getAgility() const {return agility;}
int Hero::getMoney(){return money;}

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

void Hero::faint(){
    money /=2;
    cout << name + " has fainted and is out of the battle!" << endl;
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

Weapon Inventory::getWeapon(int i){
    return weapons[i];
}

Armor Inventory::getArmor(int i){
    return armors[i];
}

Potion Inventory::getPotion(int i){
    return potions[i];
}

Spell* Inventory::getSpell(int i){
    return spells[i];
}

int Inventory::getSize() const{
    return (weapons.size() + armors.size() + potions.size() + spells.size());
}


void Inventory::print() const
{
    if(weapons.size() == 0) cout << "No weapons currently on inventory!" << endl;
    else{
        cout << "Weapons:" << endl;
        for (int i=0; i<weapons.size(); i++){
            cout << (i+1) << ".";
            weapons[i].print();
        }
    }

    if(armors.size() == 0) cout << "No armors currently on inventory!" << endl;
    else{
        cout << "Armors:" << endl;
        for (int i=0; i<armors.size(); i++){
            cout << (i+1) << ".";
            armors[i].print();
        }
    }

    if(potions.size() == 0) cout << "No potions currently on inventory!" << endl;
    else{
        cout << "Potions:" << endl;
        for (int i=0; i<potions.size(); i++){
            cout << (i+1) << ".";            
            potions[i].print();
        }
    }

    if(spells.size() == 0) cout << "No spells currently on inventory!" << endl;
    else{
        cout << "Spells:" << endl;
        for (int i=0; i<spells.size(); i++){
            cout << (i+1) << ".";
            spells[i]->print();
        }
    }
}

void Inventory::removeWeapon(int i)
{
    weapons.erase(weapons.begin() + i);
}

void Inventory::removeArmor(int i)
{
    armors.erase(armors.begin() + i);
}

void Inventory::removePotion(int i)
{
    potions.erase(potions.begin() + i);
}

void Inventory::removeSpell(int i)
{
    spells.erase(spells.begin() + i);
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




//PLAYERINVENTORY
//PLAYERINVENTORY
//PLAYERINVENTORY

Weapon PlayerInventory::equipWeapon(const int index, Weapon currentWeapon)
{
    Weapon returnWeapon = weapons[index];
    weapons[index] = currentWeapon;
    return returnWeapon;
}

Armor PlayerInventory::equipArmor(const int index, Armor currentArmor)
{
    Armor returnArmor = armors[index];
    armors[index] = currentArmor;
    return returnArmor;
}


bool PlayerInventory::isFull(const Hero& h) const
{
    if(weapons.size() + armors.size() + potions.size() + spells.size() < Capacity(h.getLevel().getRL())) return false;
    return true;
}

int PlayerInventory::Capacity(const int level) const
{
    return (10 + level/3);
}

void PlayerInventory::print(const Hero& h) const
{
    cout << getSize() << '/' << Capacity(h.getLevel().getRL()) << " slots are in use." << endl;
    
    Inventory::print();

    cout << "Current equipment:" << endl;
    h.getWeapon().print();
    h.getArmor().print();
}

int level(Hero** heroes, const int numOfHeroes){
    int sum = 0;
    for (int i=0; i<numOfHeroes; i++)
        sum += heroes[i]->getLevel().getRL();
    int average = sum / numOfHeroes;
    return randomLevel(average);
}