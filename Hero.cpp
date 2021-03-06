#include <iostream>
#include <string>
#include <cstdlib>
#include "Hero.h"
#include "Functions.h"
using namespace std;


//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

Level::Level(): realLevel(1), currentXp(0) {}

Hero::Hero(const string s) : LivingBeing(s,1), level(Level()) {
    healthPower = maxHP();
    MP = maxMP();
    gold = 0;
    weapon = new Weapon();
    weapon->starterWeapon();
    inventory.addWeapon(*weapon);
    armor = new Armor();
    armor->starterArmor();
    inventory.addArmor(*armor);
}

Warrior::Warrior(const string s): Hero(s) {
    strength = 18;
    agility = 5;
    dexterity = 3;
}
Sorcerer::Sorcerer(const string s): Hero(s) {
    strength = 15;
    agility = 5;
    dexterity = 5;
}

Paladin::Paladin(const string s): Hero(s){
    strength = 18;
    agility = 2;
    dexterity = 5;
}

Inventory::Inventory() {} 
PlayerInventory::PlayerInventory():  maxCap(10) , Inventory() {}

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
    while(currentXp >= levelUpXp()){
        levelUp();
        levelUps++;
    }
    return levelUps;
}

void Level::levelUp(){
    currentXp -= levelUpXp();
    realLevel++;
}

int Level::levelUpXp() const{
    return realLevel*100 + realLevel*(realLevel-1);
}

int Level::getRL() const {return realLevel;}
int Level::getXP() const {return currentXp;}

void Level::print() const{
    cout << "Current level: " << realLevel << endl;
    cout << "Current experience " << currentXp << "/"  << levelUpXp() << endl;
}

//HERO
//HERO
//HERO

int Hero::maxHP() const{return 100+5*(level.getRL()-1);}
int Hero::maxMP() const{return 80+5*(level.getRL()-1);}


void Hero::showStats(){
    cout << "\nPrinting stats for " << name << "." << endl;
    cout << "Health points : " << healthPower << "/" << maxHP() << endl;
    cout << "Magical points : " << MP << "/" << maxMP() << endl;
    level.print();
    cout << "Strength : " << strength << endl;
    cout << "Agility : " << agility << endl;
    cout << "Dexterity : " << dexterity << endl;
    cout << "Gold : " << gold << '\n' << endl;
}

//BATTLE
void Hero::gainHP(){
    healthPower += 4*level.getRL();
    healthPower = min(healthPower,maxHP());
}

void Hero::gainMP(){
    MP += 3*level.getRL();
    MP = min(MP,maxMP());
}

void Hero::gainHP(const int potionEffect){
    const int initialHP = healthPower;
    healthPower += potionEffect;
    healthPower = min(healthPower,maxHP());
    const int difference = healthPower - initialHP;
    cout << name << " gained " << difference << " health!" << endl;
    if (healthPower == maxHP()){
        cout << name << "'s health has been fully restored!" << endl;
    }
}

void Hero::gainMP(const int potionEffect){
    const int initialMP = MP;
    MP += potionEffect;
    MP = min(MP,maxMP());
    const int difference = MP - initialMP;
    cout << name << " gained " << difference << " Magic Power!" << endl;
    if (MP == maxMP()){
        cout << name << "'s Magic Power has been fully restored!" << endl;
    }
}

int Hero::attack() {
    int damage = strength;
    if (weapon!=NULL)
        damage += weapon->getDamage();
    else
        damage++;
    return damage;
}

bool Hero::dodge(){
    int temp = rand()%100 + 1; // 1 <= temp <= 100
    return (temp <= agility);
}

bool Hero::defend(int damage){
    if(dodge()){
        cout << name << " dodges the attack!" << endl; 
        return 0;
    }
    if (armor!=NULL)
        damage -= armor->getProtection();
    return takeDamage(max(damage,0));
}

int Hero::castSpell(){
    if (inventory.getSpellsSize() > 0){
        cout << "Choose which spell to use" << endl;
        for (int i=0; i<inventory.getSpellsSize(); i++){
            cout << i+1 << '.';
            inventory.getSpell(i)->print();
        }
        int index = inputNumber(inventory.getSpellsSize()) -1;
        return index;
    }
    else
        cout << "This hero has no spells available" << endl;
    return -1;
}


int* Hero::cast(const int index, Monster* monster)
{
    int* returnArray = new int[2];
    returnArray[0] = returnArray[1] = 0;
    if (inventory.getSpell(index)->getLevelReq() <= level.getRL())
    {
        if (inventory.getSpell(index)->getMP() <= MP){
            int damage = rand() % (inventory.getSpell(index)->getMax() - inventory.getSpell(index)->getMin());
            damage += inventory.getSpell(index)->getMin();
            damage += dexterity;
            MP -= inventory.getSpell(index)->getMP();
            cout << name << " casts " << inventory.getSpell(index)->getName() << "!" << endl;
            int result = monster->defend(damage);
            switch (result){
                case 1: //Monster died from the attack
                    returnArray[0] = 0; //Indicates monster did not take the spell normally
                    returnArray[1] = 1; //Indicates monster took damage
                    break;
                case 2: //Monster dodged the attack
                //this is here for clarity's sake
                    returnArray[0] = 0;
                    returnArray[1] = 0;
                    break;
                default:
                    returnArray[0] = inventory.getSpell(index)->type();
                    returnArray[1] = inventory.getSpell(index)->getReduction();
                    monster->takeSpell(inventory.getSpell(index));
            }
            return returnArray;
        }
        else{
            cout << "Hero's Magic Power is not enough to cast this spell." << endl;
            return returnArray;
        }
    }
    cout << "Hero's level is not high enough to cast this spell." << endl;
    return returnArray;
}

int Hero::usePotion(){
    if (getInventory().getPotionsSize() > 0){
        cout << "Choose which potion to use" << endl;
        printPotions();
        return inputNumber(getInventory().getPotionsSize()) - 1;
    }
    else
        cout << "This hero has no potions available" << endl;
    return -1;
}

void Hero::use(const int index){
    Potion p = inventory.getPotion(index);
    if (p.getMinLevel() <= level.getRL()){
        if (p.getUse() == "HP")
            gainHP(p.getEffectPoints());
        else if (p.getUse() == "MP")
            gainMP(p.getEffectPoints());
        else if (p.getUse() == "Strength") {
            strength += p.getEffectPoints();
            cout << name << "'s strength has been increased by " << p.getEffectPoints() << "!" << endl;
        }
        else if (p.getUse() == "Agility") {
            agility += p.getEffectPoints();
            cout << name << "'s agility has been increased by " << p.getEffectPoints() << "!" << endl;
        }
        else {
            dexterity += p.getEffectPoints();
            cout << name << "'s dexterity has been increased by " << p.getEffectPoints() << "!" << endl;
        }
        removePotion(index);
    }
    else
        cout << "Hero's level is not high enough to use this potion." << endl;
}

void Hero::faint(){
    cout << name << " has fainted and is out of the battle!" << endl;
    const int initialGold = gold;
    gold /=2;
    cout << name << " lost " << initialGold - gold << " gold!" << endl;
    healthPower = maxHP()/2;
    MP = maxMP()/2;
}

void Hero::gainXP(const int monsters){
    int expGained = 30*monsters*level.getRL();
    cout << name << " gained " << expGained << " experience!" << endl;
    const int levelUps = level.addXp(expGained);
    for (int i=0; i<levelUps; i++)
        levelUp();
    LivingBeing::level += levelUps;
}

void Hero::levelUp(){
    LivingBeing::level++;
    cout << name << " leveled up! Current level is: " << LivingBeing::level << endl;
    if(this->getLevel().getRL()%3 == 0) this->getPInventory()->increaseMaxCap(); //Au3hsh ari8mou item pou xwraei to inventory ka8e 3 level
    healthPower = maxHP();
    MP = maxMP();
}

void Hero::gainGold(const int monsters){
    int goldGained = 30*monsters*level.getRL();
    addGold(goldGained);
    cout << name << " gained " << goldGained << " gold! Current gold is : " << gold << endl;
}

void Hero::checkInventory(){
    cout << "\n\nHere is the current inventory for " << name << endl;
    inventory.print(*this);

    char yes;
    int index;

    if (inventory.getWeaponsSize() > 0){
        cout << "Would you like to swap weapons? y/n" << endl;
        yes = inputAnswer();
        if (yes){
            cout << "Which weapon to equip? Input a number" << endl;
            index = inputNumber(inventory.getWeaponsSize())-1;
            if( getLevel().getRL() < inventory.getWeapon(index).getMinLevel() ){
                cout << "Level requirement not met! Cannot equip weapon." << endl;
            }
            else{
                weapon=inventory.getPWeapon(index);
                cout << "Succesfuly equipped :" << endl; weapon->print();
            }
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
                if( getLevel().getRL() < inventory.getArmor(index).getMinLevel() ){
                    cout << "Level requirement not met! Cannot equip armor." << endl;
                }
                else{
                    armor=inventory.getPArmor(index);
                    cout << "Succesfuly equipped :" << endl; armor->print();
                }
            }
        }
    }
}


//MARKETPLACE
bool Hero::buy(Weapon w){
    if(inventory.isFull() == true){
        cout << name << "'s inventory is full! Cannot purchase another item." << endl; 
        return false;
    }
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
    if(inventory.isFull() == true){
        cout << name << "'s inventory is full! Cannot purchase another item." << endl; 
        return false;
    }
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
    if(inventory.isFull() == true){
        cout << name << "'s inventory is full! Cannot purchase another item." << endl; 
        return false;
    }
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
    if(inventory.isFull() == true){
        cout << name << "'s inventory is full! Cannot purchase another item." << endl; 
        return false;
    }
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

void Hero::addGold(int a){gold += a;}
void Hero::sell(string type){
    int inputI;
    if(type == "weapon"){
        cout << "Weapons on inventory of " << name << " are :" << endl;
        inventory.printWeapons();
        if(inventory.getWeaponsSize() != 0){
            cout << "Are you sure you want to sell a weapon? y/n" << endl;
            if(inputAnswer() == false) return;
            cout << "Input the number of the weapon you would like to sell." << endl;
            inputI=inputNumber(inventory.getWeaponsSize()) - 1;

            if(weapon->areTheSame(inventory.getWeapon(inputI)) ) weapon=weapon->noWeapon();
            addGold(inventory.getWeapon(inputI).getPrice()/2);
            inventory.removeWeapon(inputI);
            cout << "Current gold for " << name << " is :" << gold << endl;
        }
    }
    else if(type == "armor"){
        cout << "Armors on inventory of " << name << " are :" << endl;
        inventory.printArmors();
        if(inventory.getArmorsSize() != 0){
            cout << "Are you sure you want to sell an armor? y/n" << endl;
            if(inputAnswer() == false) return;
            cout << "Input the number of the armor you would like to sell." << endl;
            inputI=inputNumber(inventory.getArmorsSize()) - 1;

            if(armor->areTheSame(inventory.getArmor(inputI)) ) armor=armor->noArmor();
            addGold(inventory.getArmor(inputI).getPrice()/2);
            inventory.removeArmor(inputI);
            cout << "Current gold for " << name << " is :" << gold << endl;
        }
    }
    else if(type == "spell"){
        cout << "Spells on inventory of " << name << " are :" << endl;
        inventory.printSpells();
        if(inventory.getSpellsSize() != 0){
            cout << "Are you sure you want to sell a spell? y/n" << endl;
            if(inputAnswer() == false) return;
            cout << "Input the number of the spell you would like to sell." << endl;
            inputI=inputNumber(inventory.getSpellsSize()) - 1;
            addGold(inventory.getSpell(inputI)->getPrice()/2);
            inventory.removeSpell(inputI);
            cout << "Current gold for " << name << " is :" << gold << endl;
        }
    }
    else{
        cout << "Potions on inventory of " << name << " are :" << endl;
        inventory.printPotions();
        if(inventory.getPotionsSize() != 0){
            cout << "Are you sure you want to sell a potion? y/n" << endl;
            if(inputAnswer() == false) return;
            cout << "Input the number of the potion you would like to sell." << endl;
            inputI=inputNumber(inventory.getPotionsSize()) - 1;
            addGold(inventory.getPotion(inputI).getPrice()/2);
            inventory.removePotion(inputI);
            cout << "Current gold for " << name << " is :" << gold << endl;
        }
    }
}


//ACCESSORS
Weapon Hero::getWeapon() const {return *weapon;}
Weapon* Hero::getPWeapon(){return weapon;}
Armor Hero::getArmor() const {return *armor;}
Armor* Hero::getPArmor(){return armor;}
Level Hero::getLevel() const {return level;}
PlayerInventory Hero::getInventory() const {return inventory;}
PlayerInventory* Hero::getPInventory(){return &inventory;}
int Hero::getAgility() const {return agility;}
int Hero::getGold(){return gold;}

//PRINTERS
void Hero::print() const{
    cout << type() << "\tHP:" << healthPower << "\tMP:" << MP << "\tName: " << name << endl;
}
void Hero::printInventory(){ inventory.Inventory::print(); }
void Hero::printWeapons(){ inventory.printWeapons(); }
void Hero::printArmors(){ inventory.printArmors(); }
void Hero::printSpells(){ inventory.printSpells(); }
void Hero::printPotions(){ inventory.printPotions(); }


void Hero::removeSpell(const int index){
    inventory.removeSpell(index);
}

void Hero::removePotion(const int index){
    inventory.removePotion(index);
}



//SubClasses Hero

void Warrior::levelUp(){
    Hero::levelUp();
    strength += 8; //TOBECHANGED
    agility += 2;
    dexterity += 5;
}
string Warrior::type() const{
    return "\tType: Warrior    ";
}


void Sorcerer::levelUp(){
    Hero::levelUp();
    strength += 5; //TOBECHANGED
    agility += 2;
    dexterity += 8;
}
string Sorcerer::type() const{
    return "\tType: Sorcerer   ";
}

void Paladin::levelUp(){
    Hero::levelUp();
    strength += 8; //TOBECHANGED
    agility +=1;
    dexterity += 8;
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
            cout << (i+1) << "." << endl;
            weapons[i].print();
        }
    }
}

void Inventory::printArmors(){
    if(armors.size() == 0) cout << "No armors currently on inventory!" << endl;
    else{
        for (int i=0; i<armors.size(); i++){
            cout << (i+1) << "." << endl;
            armors[i].print();
        }
    }
}

void Inventory::printSpells(){
    if(spells.size() == 0) cout << "No spells currently on inventory!" << endl;
    else{
        for (int i=0; i<spells.size(); i++){
            cout << (i+1) << "." << endl;
            spells[i]->print();
        }
    }
}

void Inventory::printPotions(){
    if(potions.size() == 0) cout << "No potions currently on inventory!" << endl;
    else{
        for (int i=0; i<potions.size(); i++){
            cout << (i+1) << "." << endl;            
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
    vector<Weapon> temp;
    for(int j=0;j<weapons.size();j++){
        if(j != i) temp.push_back(weapons[j]);
    }
    weapons.clear();
    weapons = temp;
}

void Inventory::removeArmor(int i){
    vector<Armor> temp;
    for(int j=0;j<armors.size();j++){
        if(j != i) temp.push_back(armors[j]);
    }
    armors.clear();
    armors = temp;
}

void Inventory::removeSpell(int i){
    vector<Spell*> temp;
    for(int j=0;j<spells.size();j++){
        if(j != i) temp.push_back(spells[j]);
    }
    spells.clear();
    spells = temp;
}

void Inventory::removePotion(int i){
    vector<Potion> temp;
    for(int j=0;j<potions.size();j++){
        if(j != i) temp.push_back(potions[j]);
    }
    potions.clear();
    potions = temp;
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

void PlayerInventory::increaseMaxCap(){maxCap++;}

bool PlayerInventory::isFull(){
    if(weapons.size() + armors.size() + potions.size() + spells.size() < maxCap) return false;
    return true;
}

int PlayerInventory::Capacity(){
    return maxCap;
}

void PlayerInventory::print(Hero& h){
    cout << getSize() << '/' << Capacity() << " slots are in use." << endl;
    
    Inventory::print();

    if(h.getPWeapon() == NULL) cout << "No weapon currently equipped" << endl;
    else{
        if(h.getPWeapon()->getName() == "No weapon") cout << "No weapon currently equipped" << endl;
        else{
            cout << "\nCurrent weapon is :" << endl;
            h.getWeapon().print();
        }
    }
    if(h.getPArmor() == NULL) cout << "No armor currently equipped" << endl;
    else{
        if(h.getPArmor()->getName() == "No armor") cout << "No armor currently equipped" << endl;
        else{
            if(h.getPWeapon() != NULL){
                if(h.getWeapon().getTwoHanded() == false){
                        cout << "\nCurrent armor is :" << endl; 
                        h.getArmor().print();
                }
            }
            else{
                cout << "\nCurrent armor is :" << endl; 
                h.getArmor().print();
            }
        }
    }
    cout << endl;
}
const Spell* PlayerInventory::getSpell(int i) const{return spells[i];}


//OTHER
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