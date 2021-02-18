#include <iostream>
#include <string>
#include <ctime>
#include "Monster.h"
using namespace std;


//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

Monster::Monster(const string s, const int lvl=1):  LivingBeing(s,lvl) {
    healthPower = maxHP();
}

Dragon::Dragon(const string n,int lvl) :  Monster(n,lvl) {
    minAttack = 5 + 3*level;
    maxAttack = 10 + 4*level;
    defense = 5 + 2*level;
    dodgeChance = 5 + 2*level;
}
Exosceleton::Exosceleton(const string n,int lvl) : Monster(n,lvl) {
    minAttack = 4 + 3*level;
    maxAttack = 5 + 4*level;
    defense = 6 + 3*level;
    dodgeChance = 5 + 2*level;
}
Spirit::Spirit(const string n,int lvl) : Monster(n,lvl) {
    minAttack = 4 + 3*level;
    maxAttack = 5 + 4*level;
    defense = 10 + 4*level;
    dodgeChance = 10 + 3*level;
}

//DESTRUCTORS
//DESTRUCTORS
//DESTRUCTORS

Monster::~Monster() {}

Dragon::~Dragon() {}

Exosceleton::~Exosceleton() {}

Spirit::~Spirit() {}

//MONSTER
//MONSTER
//MONSTER
void Monster::gainHP(){
    healthPower += 4*level;
    healthPower = min(healthPower,maxHP());
}

int Monster::attack(){
    int damage = rand() % (maxAttack - minAttack);
    damage += minAttack;
    return damage;
}

bool Monster::defend(int damage){
    if(dodge()){
        cout << getName() + " dodges the attack!" << endl;
        return 0;
    }
    damage -= defense;
    return takeDamage(max(damage,0));
}

void Monster::takeSpell(Spell* spell){
    if (spell->type() == "Ice"){
        minAttack -= spell->getReduction();
        maxAttack -= spell->getReduction();
        cout << name << "'s attack has been reduced by " << spell->getReduction() << "!" << endl;
    }
    else if (spell->type() == "Fire"){
        defense -= spell->getReduction();
        cout << name << "'s defense has been reduced by " << spell->getReduction() << "!" << endl;
    }
    else{
        dodgeChance -= spell->getReduction();
        cout << name << "'s dodge rate has been reduced by " << spell->getReduction() << "!" << endl;
    }
}

bool Monster::dodge(){
    int temp = rand()%100 + 1; // 1 <= temp <= 100
    return (temp <= dodgeChance);
}

void Monster::regainStats(const string type, const int amount){
    if (type == "Ice"){
        minAttack += amount;
        maxAttack += amount;
    }
    else if(type == "Fire"){
        defense += amount;
    }
    else{
        dodgeChance += amount;
    }
}

void Monster::faint(){
    cout << getName() + " has fainted! It's out of the battle!" << endl;
}

void Monster::print() const{
    cout << type() + "\tHP:" << healthPower << "\tName: " + name << endl;
}

int Monster::maxHP() const{
    return 50 + level*15;
}


//type

string Dragon::type() const{
    return "\tType: Dragon     ";
}

string Exosceleton::type() const{
    return "\tType: Exosceleton";
}

string Spirit::type() const{
    return "\tType: Spirit     ";
}


Monster* monsterGenerator(const int heroAverage){
    int type = rand() % 3;
    Monster* monster;
    switch (type){
        case 0:
            monster = new Dragon(genName("monster"),randomLevel(heroAverage));
            break;
        case 1:
            monster = new Exosceleton(genName("monster"),randomLevel(heroAverage));
            break;
        case 2:
            monster = new Spirit(genName("monster"),randomLevel(heroAverage));
            break;
    }
    return monster;
}

void removeMonster(Monster** monsterArray, int& size, const int index){
    Monster* monster = monsterArray[index];
    monsterArray[index] = monsterArray[size-1];
    monsterArray[--size] = monster;
}

int chooseMonster(Monster** monsterArray, const int monsters){
    cout << "Which monster would you like to attack?" << endl;
    for (int i=0; i<monsters; i++){
        cout << (i+1) << ". ";
        monsterArray[i]->print();
    }
    return inputNumber(monsters)-1;
}