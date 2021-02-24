#include <iostream>
#include <string>
#include <cstdlib>
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
    maxAttack = 8 + 5*level;
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
    defense = 5 + 2*level;
    dodgeChance = 10 + 3*level;
}



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

int Monster::defend(int damage){
    if(dodge()){
        cout << name << " dodges the attack!" << endl;
        return 2;
    }
    damage -= defense;
    return takeDamage(max(damage,0));
}

void Monster::takeSpell(const Spell* spell){
    int reduction = spell->getReduction();
    switch (spell->type()){
        case 1:
            minAttack -= reduction;
            minAttack = max(minAttack,0);
            maxAttack -= reduction;
            maxAttack = max(maxAttack,0);
            cout << name << "'s attack has been reduced by " << reduction << "!" << endl;
            break;
        case 2:
            defense -= reduction;
            defense = max(defense,0);
            cout << name << "'s defense has been reduced by " << reduction << "!" << endl;
            break;
        case 3:
            dodgeChance -= reduction;
            dodgeChance = max(dodgeChance,0);
            cout << name << "'s dodge rate has been reduced by " << reduction << "%!" << endl;         
    }
}

bool Monster::dodge(){
    int temp = rand()%100 + 1; // 1 <= temp <= 100
    return (temp <= dodgeChance);
}

void Monster::regainStats(const int type, const int amount){
    switch (type){
        case 1:
            minAttack += amount;
            maxAttack += amount;
            break;
        case 2:
            defense += amount;
            break;
        case 3:
            dodgeChance += amount;
    }
}

void Monster::faint(){
    cout << name << " has fainted! It's out of the battle!" << endl;
}

void Monster::print() const{
    cout << type() << "\tHP:" << healthPower << "\tName: " << name << endl;
}

int Monster::maxHP() const{
    return 50 + level*15;
}


//type

std::string Dragon::type() const{
    return "\tType: Dragon     ";
}

std::string Exosceleton::type() const{
    return "\tType: Exosceleton ";
}

std::string Spirit::type() const{
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
    cout << endl;
    return inputNumber(monsters)-1;
}