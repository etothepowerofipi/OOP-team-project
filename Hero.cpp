#include <iostream>
#include <string>
#include <ctime>
#include "Hero.h"
#include "Functions.h"
using namespace std;


//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

Level::Level(const int lvl= 1): realLevel(lvl), currentXp(0) {}

Hero::Hero(const string s) : LivingBeing(s,1) {
    healthPower=100;
    MP=100;
    gold=0;
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
    while(currentXp >= levelUpXp())
    {
        levelUp();
        levelUps++;
    }
    return levelUps;
}

void Level::levelUp()
{
    currentXp -= levelUpXp();
    realLevel++;
}

int Level::levelUpXp() const{
    return realLevel*100 + realLevel*(realLevel-1);
}

int Level::getRL() const {return realLevel;}
int Level::getXP() const {return currentXp;}

void Level::print() const{
    cout << "\tCurrent level: " << realLevel << endl;
    cout << "\tCurrent experience " << currentXp << "/"  << levelUpXp() << endl;
}

//HERO
//HERO
//HERO

int Hero::maxHP() const{return 100+5*(level.getRL()-1);}
int Hero::maxMP() const{return 100+5*(level.getRL()-1);}


void Hero::showStats(){
    cout << "Printing stats for " << getName() << "." << endl;
    cout << "Health points : " << healthPower << "/" << maxHP() << endl;
    cout << "Magical points : " << MP << "/" << maxMP() << endl;
    cout << "Level : " << level.getRL() << endl;
    cout << "Strength : " << strength << endl;
    cout << "Agility : " << agility << endl;
    cout << "Dexterity : " << dexterity << endl;
    cout << "Gold : " << gold << endl;
    cout << endl;
}

//BATTLE
void Hero::gainMP(){
    MP += 5*level.getRL();
    MP = min(MP,maxMP());
}

int Hero::attack(){
    return weapon.getDamage()+strength;
}

bool Hero::dodge(){
    int temp = rand() % 100;
    return (temp <= agility );
}

bool Hero::defend(int damage){
    if(dodge()){
        cout << name + " dodges the attack!" << endl; 
        return 0;
    }
    damage -= armor.getProtection();
    return takeDamage(max(damage,0));
}

void Hero::gainXP(const int monsters){
    int expGained = 10*monsters*level.getRL();
    cout << name + " gained " << expGained << " experience!" << endl;
    const int levelUps = level.addXp(expGained);
    for (int i=0; i<levelUps; i++)
        levelUp();;
}

void Hero::gainGold(const int monsters){
    int goldGained = 2*monsters*level.getRL();
    cout << name + " gained " << goldGained << " gold!" << endl;
    addGold(goldGained);
}

void Hero::checkInventory()
{
    cout << "Here is the current inventory for " + name << endl;
    inventory.print(*this);

    char yes;
    int index;
    
    if (inventory.getWeaponsSize() > 0){
        cout << "Would you like to swap weapons? y/n" << endl;
        yes = inputAnswer();
        if (yes){
            cout << "Which weapon to equip? Input a number" << endl;
            index = inputNumber(inventory.getWeaponsSize())-1;
            equip(inventory.equipWeapon(index,weapon));
        }
    }

    if (inventory.getArmorsSize() > 0){
        cout << "Would you like to swap armors? y/n" << endl;
        yes = inputAnswer();
        if (yes){
            cout << "Which armor to equip? Input a number" << endl;
            index = inputNumber(inventory.getArmorsSize())-1;
            equip(inventory.equipArmor(index,armor));
        }
    }

    cout << "Current weapon is: " << endl;
    getWeapon().print();
    cout << "Current armor is: " << endl;
    getArmor().print();
}

void Hero::printWeapons(){ inventory.printWeapons(); }
void Hero::printArmors(){ inventory.printArmors(); }
void Hero::printSpells(){ inventory.printSpells(); }
void Hero::printPotions(){ inventory.printPotions(); }

void Hero::addGold(int a){gold+=a;}
void Hero::sell(string type){
    int inputI;
    if(type == "weapon"){
        cout << "Weapons on inventory of " << getName() << " are :" << endl;
        inventory.printWeapons();
        if(inventory.getWeaponsSize() != 0){
            cout << "Input the number of the weapon you would like to sell." << endl;
            inputI=inputNumber(inventory.getWeaponsSize()) - 1;
            addGold(inventory.getWeapon(inputI).getPrice()/2);
            removeWeapon(inputI);
            cout << "New currency for " << getName() << " is :" << getGold() << endl;
        }
    }
    else if(type == "armor"){
        cout << "Armors on inventory of " << getName() << " are :" << endl;
        inventory.printArmors();
        if(inventory.getArmorsSize() != 0){
            cout << "Input the number of the armor you would like to sell." << endl;
            inputI=inputNumber(inventory.getArmorsSize()) - 1;
            addGold(inventory.getArmor(inputI).getPrice()/2);
            removeArmor(inputI);
            cout << "New currency for " << getName() << " is :" << getGold() << endl;
        }
    }
    else if(type == "spell"){
        cout << "Spells on inventory of " << getName() << " are :" << endl;
        inventory.printSpells();
        if(inventory.getSpellsSize() != 0){
            cout << "Input the number of the spell you would like to sell." << endl;
            inputI=inputNumber(inventory.getSpellsSize()) - 1;
            addGold(inventory.getSpell(inputI)->getPrice()/2);
            removeSpell(inputI);
            cout << "New currency for " << getName() << " is :" << getGold() << endl;
        }
    }
    else{
        cout << "Potions on inventory of " << getName() << " are :" << endl;
        inventory.printPotions();
        if(inventory.getPotionsSize() != 0){
            cout << "Input the number of the potion you would like to sell." << endl;
            inputI=inputNumber(inventory.getPotionsSize()) - 1;
            addGold(inventory.getPotion(inputI).getPrice()/2);
            removePotion(inputI);
            cout << "New currency for " << getName() << " is :" << getGold() << endl;
        }
    }
}
bool Hero::buy(Weapon w){
    if(gold >= w.getPrice()){
        gold-= w.getPrice();
        inventory.addWeapon(w);
        return true;
    }
    else{
        cout << "Not enough money!" << endl;
        return false;
    }
}

bool Hero::buy(Armor a){
    if(gold >= a.getPrice()){
        gold-= a.getPrice();
        inventory.addArmor(a);
        return true;
    }
    else{
        cout << "Not enough money!" << endl;
        return false;
    }
}
bool Hero::buy(Potion p){
    if(gold >= p.getPrice()){
        gold-= p.getPrice();
        inventory.addPotion(p);
        return true;
    }
    else{
        cout << "Not enough money!" << endl;
        return false;
    }
}
bool Hero::buy(Spell* s){
    if(gold >= s->getPrice()){
        gold-= s->getPrice();
        inventory.addSpell(s);
        return true;
    }
    else{
        cout << "Not enough money!" << endl;
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
int Hero::getGold(){return gold;}

void Hero::print() const{
    cout << type();
    LivingBeing::print();
}


int Hero::castSpell(){
    if (getInventory().getSpellsSize() > 0){
        cout << "Choose which spell to use" << endl;
        for (int i=0; i<getInventory().getSpellsSize(); i++)
            getInventory().getSpell(i)->print();
        return inputNumber(getInventory().getSpellsSize()) - 1;
    }
    else
        cout << "This hero has no spells available" << endl;
    return -1;
}

int Hero::cast(Spell* s)
{
    if (s->getLevelReq() <= level.getRL())
    {
        int damage = rand() % (s->getMax() - s->getMin());
        damage += s->getMin();
        return damage;
    }
    cout << "Hero's level is not high enough to use this spell." << endl;
    return 0;
}

int Hero::usePotion(){
    if (getInventory().getPotionsSize() > 0){
        cout << "Choose which potion to use" << endl;
        for (int i=0; i<getInventory().getPotionsSize(); i++)
            getInventory().getPotion(i).print();
        return inputNumber(getInventory().getPotionsSize()) - 1;
    }
    else
        cout << "This hero has no potions available" << endl;
    return -1;
}


void Hero::use(const Potion& p){
    if (p.getMinLevel() <= level.getRL()){
        if (p.getUse() == "HP") healthPower += p.getEffectPoints(); //TOBECHANGED
        
        else if (p.getUse() == "MP") MP += p.getEffectPoints();
        
        else if (p.getUse() == "Strength") strength += p.getEffectPoints();
        
        else if (p.getUse() == "Agility") agility += p.getEffectPoints();
        
        else dexterity += p.getEffectPoints();
    }
    else
        cout << "Hero's level is not high enough to use this potion." << endl;
}

void Hero::removeSpell(const int index){
    inventory.removeSpell(index);
}

void Hero::removePotion(const int index){
    inventory.removePotion(index);
}

void Hero::faint(){
    cout << name + " has fainted and is out of the battle!" << endl;
    const int initialGold = gold;
    gold /=2;
    cout << name + " lost " << initialGold - gold << " gold!" << endl;
    healthPower = maxHP()/2;
    MP = maxMP()/2;
}

//SubClasses Hero

void Warrior::levelUp()
{
    LivingBeing::level++;
    level.levelUp();
    healthPower += 50;
    MP =+ 50;

    strength += 10* 1.5; //TOBECHANGED
    agility += 0.05* 1.5;
    dexterity += 5;
}
string Warrior::type() const{
    return "\tType: Warrior";
}


void Sorcerer::levelUp()
{
    LivingBeing::level++;
    level.levelUp();
    healthPower += 50;
    MP =+ 50;

    strength += 10; //TOBECHANGED
    agility += 0.05* 1.5;
    dexterity += 5* 1.5;
}
string Sorcerer::type() const{
    return "\tType: Sorcerer";
}

void Paladin::levelUp()
{
    LivingBeing::level++; // = level.reallevel
    level.levelUp();
    healthPower += 50;
    MP =+ 50;

    strength += 10* 1.5; //TOBECHANGED
    agility += 0.05;
    dexterity += 5* 1.5;
}
string Paladin::type() const{
    return "\tType: Paladin";
}

//INVENTORY
int Inventory::getWeaponsSize() const{return weapons.size();}
int Inventory::getArmorsSize() const{return armors.size();}
int Inventory::getPotionsSize() const{return potions.size();}
int Inventory::getSpellsSize() const{return spells.size();}
int Inventory::getSize() const{return (weapons.size() + armors.size() + potions.size() + spells.size());}

void Inventory::printWeapons() {
    if(weapons.size() == 0) cout << "No weapons currently on inventory!" << endl;
    else{
        for (int i=0; i<weapons.size(); i++){
            cout << (i+1) << ".";
            weapons[i].print();
        }
    }
}

void Inventory::printArmors(){
    if(armors.size() == 0) cout << "No armors currently on inventory!" << endl;
    else{
        for (int i=0; i<armors.size(); i++){
            cout << (i+1) << ".";
            armors[i].print();
        }
    }
}

void Inventory::printSpells(){
    if(spells.size() == 0) cout << "No spells currently on inventory!" << endl;
    else{
        for (int i=0; i<spells.size(); i++){
            cout << (i+1) << ".";
            spells[i]->print();
        }
    }
}

void Inventory::printPotions(){
    if(potions.size() == 0) cout << "No potions currently on inventory!" << endl;
    else{
        for (int i=0; i<potions.size(); i++){
            cout << (i+1) << ".";            
            potions[i].print();
        }
    }
}

Weapon Inventory::getWeapon(int i){return weapons[i];}
Armor Inventory::getArmor(int i){return armors[i];}
Potion Inventory::getPotion(int i){return potions[i];}
Spell* Inventory::getSpell(int i){return spells[i];}

void Inventory::print()
{
    cout << "Weapons:" << endl;
    printWeapons();

    cout << "Armors:" << endl;
    printArmors();

    cout << "Spells:" << endl;
    printSpells();

    cout << "Potions:" << endl;
    printPotions();
}

void Inventory::removeWeapon(int i){
    weapons.erase(weapons.begin() + i);
}

void Inventory::removeArmor(int i){
    armors.erase(armors.begin() + i);
}

void Inventory::removePotion(int i){
    potions.erase(potions.begin() + i);
}

void Inventory::removeSpell(int i){
    spells.erase(spells.begin() + i);
}

void Inventory::addWeapon(Weapon w){
    weapons.push_back(w);
}

void Inventory::addArmor(Armor a){
    armors.push_back(a);
}

void Inventory::addPotion(Potion p){
    potions.push_back(p);
}

void Inventory::addSpell(Spell* s){
    spells.push_back(s);
}




//PLAYERINVENTORY
//PLAYERINVENTORY
//PLAYERINVENTORY

Weapon PlayerInventory::equipWeapon(const int index, Weapon currentWeapon){
    Weapon returnWeapon = weapons[index];
    weapons[index] = currentWeapon;
    return returnWeapon;
}

Armor PlayerInventory::equipArmor(const int index, Armor currentArmor){
    Armor returnArmor = armors[index];
    armors[index] = currentArmor;
    return returnArmor;
}


bool PlayerInventory::isFull(const Hero& h) const{
    if(weapons.size() + armors.size() + potions.size() + spells.size() < Capacity(h.getLevel().getRL())) return false;
    return true;
}

int PlayerInventory::Capacity(const int level) const{
    return (10 + level/3);
}

void PlayerInventory::print(const Hero& h){
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

void heroFainted(Hero** heroArray, int& size, const int index){
    Hero* hero = heroArray[index];
    heroArray[index] = heroArray[size-1];
    heroArray[--size] = hero;
}