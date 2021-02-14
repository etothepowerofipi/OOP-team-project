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
    healthPower=maxHP();
    MP=maxMP();
    gold=0;
    weapon=new Weapon();
    weapon->starterWeapon();
    inventory.addWeapon(*weapon);
    armor=new Armor();
    armor->starterArmor();
    inventory.addArmor(*armor);
}

Warrior::Warrior(const string s): Hero(s) 
{
    strength = 5;
    agility = 2;
    dexterity = 1;
}
Sorcerer::Sorcerer(const string s): Hero(s) 
{
    strength = 3;
    agility = 2;
    dexterity = 2;
}

Paladin::Paladin(const string s): Hero(s)
{
    strength = 5;
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
int Level::addXp(int xpToAdd)
{
    int levelUps = 0;
    currentXp += xpToAdd;
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
int Hero::maxMP() const{return 80+5*(level.getRL()-1);}


void Hero::showStats(){
    cout << "\n\nPrinting stats for " << getName() << "." << endl;
    cout << "Health points : " << healthPower << "/" << maxHP() << endl;
    cout << "Magical points : " << MP << "/" << maxMP() << endl;
    level.print();
    cout << "Strength : " << strength << endl;
    cout << "Agility : " << agility << endl;
    cout << "Dexterity : " << dexterity << endl;
    cout << "Gold : " << gold << '\n' << endl;
}

//BATTLE
void Hero::gainMP(){
    MP += 5*level.getRL();
    MP = min(MP,maxMP());
}

int Hero::attack(){
    return weapon->getDamage()+strength;
}

bool Hero::dodge(){
    int temp = rand()%100 + 1; // 1 <= temp <= 100
    return (temp <= agility );
}

bool Hero::defend(int damage){
    if(dodge()){
        cout << name + " dodges the attack!" << endl; 
        return 0;
    }
    damage -= armor->getProtection();
    return takeDamage(max(damage,0));
}

void Hero::gainXP(const int monsters){
    int expGained = 10*monsters*level.getRL();
    cout << name + " gained " << expGained << " experience!" << endl;
    const int levelUps = level.addXp(expGained);
    for (int i=0; i<levelUps; i++)
        levelUp();
}

void Hero::gainGold(const int monsters){
    int goldGained = 2*monsters*level.getRL();
    addGold(goldGained);
    cout << name + " gained " << goldGained << " gold! Current gold is : " << gold << endl;
}

void Hero::checkInventory(){
    cout << "\n\nHere is the current inventory for " + name << endl;
    inventory.print(*this);

    char yes;
    int index;

    if (inventory.getWeaponsSize() > 0){
        cout << "Would you like to swap weapons? y/n" << endl;
        yes = inputAnswer();
        if (yes){
            cout << "Which weapon to equip? Input a number" << endl;
            index = inputNumber(inventory.getWeaponsSize())-1;
            weapon=inventory.getPWeapon(index);
        }
    }
    if(weapon->getTwoHanded() == true) armor=NULL;
    else{
        if (inventory.getArmorsSize() > 0){
            cout << "Would you like to swap armors? y/n" << endl;
            yes = inputAnswer();
            if (yes){
                cout << "Which armor to equip? Input a number" << endl;
                index = inputNumber(inventory.getArmorsSize())-1;
                armor=inventory.getPArmor(index);
            }
        }
    }
}

void Hero::printInventory(){ inventory.Inventory::print(); }
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
            cout << "Are you sure you want to sell a weapon?" << endl;
            if(inputAnswer() == false) return;
            cout << "Input the number of the weapon you would like to sell." << endl;
            inputI=inputNumber(inventory.getWeaponsSize()) - 1;
            if(weapon == inventory.getPWeapon(inputI)) weapon=NULL;
            addGold(inventory.getWeapon(inputI).getPrice()/2);
            inventory.removeWeapon(inputI);
            cout << "New currency for " << getName() << " is :" << getGold() << endl;
        }
    }
    else if(type == "armor"){
        cout << "Armors on inventory of " << getName() << " are :" << endl;
        inventory.printArmors();
        if(inventory.getArmorsSize() != 0){
            cout << "Are you sure you want to sell an armor?" << endl;
            if(inputAnswer() == false) return;
            cout << "Input the number of the armor you would like to sell." << endl;
            inputI=inputNumber(inventory.getArmorsSize()) - 1;
            if(armor == inventory.getPArmor(inputI)) armor=NULL;
            addGold(inventory.getArmor(inputI).getPrice()/2);
            inventory.removeArmor(inputI);
            cout << "New currency for " << getName() << " is :" << getGold() << endl;
        }
    }
    else if(type == "spell"){
        cout << "Spells on inventory of " << getName() << " are :" << endl;
        inventory.printSpells();
        if(inventory.getSpellsSize() != 0){
            cout << "Are you sure you want to sell a spell?" << endl;
            if(inputAnswer() == false) return;
            cout << "Input the number of the spell you would like to sell." << endl;
            inputI=inputNumber(inventory.getSpellsSize()) - 1;
            addGold(inventory.getSpell(inputI)->getPrice()/2);
            inventory.removeSpell(inputI);
            cout << "New currency for " << getName() << " is :" << getGold() << endl;
        }
    }
    else{
        cout << "Potions on inventory of " << getName() << " are :" << endl;
        inventory.printPotions();
        if(inventory.getPotionsSize() != 0){
            cout << "Are you sure you want to sell a potion?" << endl;
            if(inputAnswer() == false) return;
            cout << "Input the number of the potion you would like to sell." << endl;
            inputI=inputNumber(inventory.getPotionsSize()) - 1;
            addGold(inventory.getPotion(inputI).getPrice()/2);
            inventory.removePotion(inputI);
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

Weapon Hero::getWeapon() const {return *weapon;}
Weapon* Hero::getPWeapon(){return weapon;}
Armor Hero::getArmor() const {return *armor;}
Armor* Hero::getPArmor(){return armor;}
Level Hero::getLevel() const {return level;}
PlayerInventory Hero::getInventory() const {return inventory;}
int Hero::getAgility() const {return agility;}
int Hero::getGold(){return gold;}

void Hero::print() const{
    cout << type() + "\tHP:" << healthPower << "\tMP:" << MP << "\tName: " + name << endl;
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
        if (p.getUse() == "HP"){
            healthPower += p.getEffectPoints();
            cout << getName() << " used a potion of HP to restore " << p.getEffectPoints() << " health!" << endl;
        }
        else if (p.getUse() == "MP"){
            MP += p.getEffectPoints();
            cout << getName() << " used a potion of MP to restore " << p.getEffectPoints() << " magical power!" << endl;
        }
        else if (p.getUse() == "Strength"){
            strength += p.getEffectPoints();
            cout << getName() << " used a potion of strength to boost their strength by " << p.getEffectPoints() << " points!" << endl;
        }
        else if (p.getUse() == "Agility"){
            agility += p.getEffectPoints();
            cout << getName() << " used a potion of agility to boost their agility by " << p.getEffectPoints() << " points!" << endl;
        }
        else{
            dexterity += p.getEffectPoints();
            cout << getName() << " used a potion of dexterity to boost their dexterity by " << p.getEffectPoints() << " points!" << endl;
        }
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
    return "\tType: Warrior    ";
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
    return "\tType: Sorcerer   ";
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
    return "\tType: Paladin    ";
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
Weapon* Inventory::getPWeapon(int i){return &weapons[i];}
Armor Inventory::getArmor(int i){return armors[i];}
Armor* Inventory::getPArmor(int i){return &armors[i];}
Potion Inventory::getPotion(int i){return potions[i];}
Spell* Inventory::getSpell(int i){return spells[i];}

void Inventory::print()
{
    cout << "Weapons:" << endl;
    printWeapons();

    cout << "\nArmors:" << endl;
    printArmors();

    cout << "\nSpells:" << endl;
    printSpells();

    cout << "\nPotions:" << endl;
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

bool PlayerInventory::isFull(const Hero& h) const{
    if(weapons.size() + armors.size() + potions.size() + spells.size() < Capacity(h.getLevel().getRL())) return false;
    return true;
}

int PlayerInventory::Capacity(const int level) const{
    return (10 + level/3);
}

void PlayerInventory::print(Hero& h){
    cout << getSize() << '/' << Capacity(h.getLevel().getRL()) << " slots are in use." << endl;
    
    Inventory::print();

    if(h.getPWeapon() == NULL) cout << "No weapon currently equiped" << endl;
    else{
        cout << "\nCurrent weapon is :" << endl;
        h.getWeapon().print();
    }
    if(h.getPArmor() == NULL) cout << "No armor currently equiped" << endl;
    else{
        if(h.getWeapon().getTwoHanded() == false){
                cout << "\nCurrent armor is :" << endl; 
                h.getArmor().print();
        }
    }
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